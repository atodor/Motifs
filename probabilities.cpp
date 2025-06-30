#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#define N_NETWORKS 40

using namespace std;

void readGraph(char* dirName, double probabilities[][N_NETWORKS], vector<pair<string, string> > &edges, vector<string> &networks)
{
  DIR *dir;
  struct dirent *ent;
  dir = opendir(dirName);
  if (dir != NULL)
    {
      ent = readdir(dir);
      //int k = 0;
      while (ent != NULL)
	{
	  char fileName[1000];
	  sprintf(fileName,"%s%s",dirName,ent->d_name);
	  networks.push_back(ent->d_name);
	  //cout << ent->d_name << "\t" << ent->d_type << endl;
	  ifstream listFile(fileName);
	  if(listFile.fail())
	    cout << "File read error: " << fileName << endl;
	  char line[500];
	  //int i=0;
	  while (listFile.good())
	    {
	      listFile.getline(line,500);
	      if (strlen(line) <= 0)
		continue;
	      string p1, p2, prob;
	      int id1,id2;
	      double p;
	      istringstream strStream(line);
	      getline(strStream, p1, '\t');
	      getline(strStream, p2, '\t');
	      getline(strStream, prob, '\t');
	      istringstream nStream3(prob);
	      nStream3 >> p;
	      pair<string,string> edge = pair<string,string>(p1,p2);
	      bool found = false;
	      int pos;
	      for (int i = 0; i < edges.size(); i++)
		if (edge == edges[i])
		  {
		    found = true;
		    pos = i;
		    break;
		  }
	      if (! found)
		{
		  edges.push_back(edge);
		  probabilities[edges.size() - 1][networks.size() - 1] = p;
		}
	      else
		probabilities[pos][networks.size() - 1] = p;
	    }
	  listFile.close();
	  ent = readdir(dir);
	}
    } 
}

int main(int argc, char *argv[])
{
  if(argc<2)
  {
    cout << "Usage: " << argv[0] << " dir" << endl;
	return 0;
  }

  double probabilities[1000000][N_NETWORKS];
  vector<pair<string, string> > edges;
  vector<string> networks;

  readGraph(argv[1], probabilities, edges, networks);
  
  for (int i = 0; i < edges.size(); i++)
    {
      for (int j = 0; j < networks.size(); j++)
	if (networks[j] != "." && networks[j] != ".." && networks[j] != "bak")
	  cout << probabilities[i][j] << "\t";
      cout << endl;
    }
  
  /*
  for (int j = 0; j < networks.size(); j++)
    {
      cout << j << "\t" << networks[j] << endl;
    }
  */
  return 0;
}
