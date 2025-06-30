#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <math.h>

#define N_SAMPLES 60

using namespace std;

void read_expr(char * fname, map<string, vector <double> > &expr)
{
  ifstream intStream(fname);
  if(intStream.fail())
    {
      cout << "File read error: " << fname << endl;
      return;
    }
  char line[50000];
  set<pair<string,string> > graph;
  set<string> proteins;
  while (intStream.good())
    {
      intStream.getline(line,50000);
      //cout << line << endl;
      if (strlen(line) <= 0 || line[0]=='#')
	continue;
      string probe, s_expr;
      istringstream strStream(line);
      getline(strStream, probe, '\t');
      expr[probe] = vector<double>(N_SAMPLES);
      //cout << probe << "\t"; 
      for (int i = 0; i < N_SAMPLES; i++)
	{
	  getline(strStream, s_expr, '\t');
	  istringstream nStream(s_expr);
	  nStream >> expr[probe][i];
	  //cout << expr[probe][i] << endl;
	  }
    }
  intStream.close();
}

void read_probes(char * fname, map<string, set<string> > &probes)
{
  ifstream mFile(fname);
  if(mFile.fail())
    {
      cout << "File read error: " << fname << endl;
      return;
    }
  char line[500];
  while (mFile.good())
    {
      mFile.getline(line,50000);
      if (strlen(line) <= 0 || line[0]=='#')
	continue;
      //cout << line << endl;
      string head, tail;
      istringstream strStream(line);
      getline(strStream, head, '\t');
      head=string("\"")+head+string("\"");
      //cout << head << endl;
      //if (!m.count(head))
      //m.insert(pair<string, set<string> >(head,set<string>()));
      do
	{
	  getline(strStream,tail,' ');
	  if (tail!="///" && tail!="" && tail!=" " && tail!="\t")
	    probes[tail].insert(head);
	}
      while (!strStream.eof());
    }
  mFile.close();
}

int main(int argc, char *argv[])
{
  if (argc < 3)
    {
      cout << "Usage: " << argv[0] << " " << "expr_file probe_file" << endl;
      return 0;
    }                

  map<string, vector<double> > expr;
  map<string, vector<double> > gene_expr;
  map<string, double> mean, std;

  map<string, set<string> > probes;
  read_expr(argv[1], expr);
  read_probes(argv[2], probes);

  /*
  for (map<string, set<string> >::iterator mIt = probes.begin(); mIt != probes.end(); mIt++)
    {
      cout << mIt->first << "\t";
      for (set<string>::iterator sIt = mIt->second.begin(); sIt != mIt->second.end(); sIt++)
	cout << *sIt << "\t";
      cout << endl;
      //return 0;
    }
	 
	 
       for (map<string, vector<double> >::iterator mIt = expr.begin(); mIt != expr.end(); mIt++)
    {
      cout << mIt->first << "\t";
      for(int i = 0; i < N_SAMPLES; i++)
	cout << mIt->second[i] << "\t";
      cout << endl;
    }
       cout << expr.size() << endl;
  */
  
  //rearrange by gene name and take maximum of gene expression in probes
  for (map<string, set<string> >::iterator mIt = probes.begin(); mIt != probes.end(); mIt++)
    {
      //cout << mIt->first << endl;
      //cout << expr[*mIt->second.begin()] << endl;
      double max[N_SAMPLES];
      for(int i = 0; i < N_SAMPLES; i++)
	{
	  //cout << expr[*(mIt->second.begin())][i] << endl;
	  max[i] = expr[*(mIt->second.begin())][i];
	}
      //for(int i = 0; i < N_SAMPLES; i++)
      //cout << max[i] << "\t";
      //cout << endl;
      for (set<string>::iterator sIt = mIt->second.begin(); sIt != mIt->second.end(); sIt++)
	{
	  //cout << *sIt << endl;
	 for(int i = 0; i < N_SAMPLES; i++)
	   if(expr[*sIt][i] > max[i])
	     max[i] = expr[*sIt][i];
	}
      gene_expr[mIt->first] = vector<double>(N_SAMPLES);
      for(int i = 0; i < N_SAMPLES; i++)
	gene_expr[mIt->first][i] = max[i];
      //cout << gene_expr[mIt->first][0]<< endl;
    }

	 // compute mean
  for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
    {
      mean[mIt->first] = 0.0;
      for(int i = 0; i < N_SAMPLES; i++)
	mean[mIt->first] += mIt->second[i];
      mean[mIt->first] /= (double)N_SAMPLES;
    }

	 // compute standard deviation
  for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
    {
      std[mIt->first] = 0.0;
      for(int i = 0; i < N_SAMPLES; i++)
	std[mIt->first] += pow(mIt->second[i] - mean[mIt->first], 2);
      std[mIt->first] = pow(std[mIt->first], 0.5);
    }

	 //normalize
  for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
      for(int i = 0; i < N_SAMPLES; i++)
	mIt->second[i] = (mIt->second[i] - mean[mIt->first]) / std[mIt->first];

       //print
  /*
       for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
    {
      cout << mIt->first << "\t";
      for(int i = 0; i < N_SAMPLES; i++)
	cout << mIt->second[i] << "\t";
      cout << endl;
  */

  stringstream of;
  of << "../Data/GSE19804/genes.txt";
  ofstream os;
  os.open(of.str().c_str());
  
  int k = 0;
  for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
    {
      os << mIt->first << "\t" << ++k << endl;
    }
  os.close();

  for(int i = 0; i < N_SAMPLES; i++)
    {
      for (map<string, vector<double> >::iterator mIt = gene_expr.begin(); mIt != gene_expr.end(); mIt++)
      cout << mIt->second[i] << "\t";
      cout << endl;
    }
  }
