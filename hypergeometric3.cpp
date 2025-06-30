#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
#include <algorithm>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 3)
    {
      cout << "Usage: " << argv[0] << " " << "network_file pairs_file" << endl;
      return 0;
    }                

  ifstream intStream(argv[1]);
  char line[500];
  set<pair<string,string> > graph;
  set<string> proteins;
  while (intStream.good())
    {
      intStream.getline(line,500);
      if (strlen(line) <= 0)
	continue;
      string p1, p2;
      istringstream strStream(line);
      getline(strStream, p1, '\t');
      getline(strStream, p2, '\t');
      proteins.insert(p1);
      proteins.insert(p2);
      graph.insert(pair<string,string>(p1,p2));
      //cout << p1<<":"<<p2 << endl;
    }
  intStream.close();

  ifstream intStream2(argv[2]);
  while (intStream2.good())
    {
      intStream2.getline(line,500);
      if (strlen(line) <= 0)
	continue;
      string p1, p2;
      istringstream strStream(line);
      getline(strStream, p1, '\t');
      getline(strStream, p2, '\t');

      set<string> neighbors1, neighbors2;
      for (set<pair<string,string> >::iterator sIt2 = graph.begin(); sIt2 != graph.end(); sIt2++)
	{
	  if (sIt2->first == p1)
	    neighbors1.insert(sIt2->second);
	  if (sIt2->second == p1)
	    neighbors1.insert(sIt2->first);
	  if (sIt2->first == p2)
	    neighbors2.insert(sIt2->second);
	  if (sIt2->second == p2)
	    neighbors2.insert(sIt2->first);
	}
      
      int n1 = neighbors1.size(), n2 = neighbors2.size(), inters = 0;
      for (set<string>::iterator sIt1 = neighbors1.begin(); sIt1 != neighbors1.end(); sIt1++)
	if (neighbors2.count(*sIt1))
	  inters++;
      //cout << n1 << "\t" << n2 << "\t" << inters << "\t" << proteins.size() << endl;
      //double hg =  gsl_cdf_hypergeometric_Q (inters - 1 , n1, proteins.size() - n1, n2);
      double hg =  0;

      for (int i = inters; i <= (n1<n2?n1:n2); i++)
	{
	  double res = gsl_ran_hypergeometric_pdf (i , n1, proteins.size() - n1, n2);
	  //cout << i << "\t" << res << endl;
	  hg += res;
	}
      //cout << "~" << hg << endl;
      double lhg = -log(hg);
      if (1-hg < 1e-10)
	lhg = 0.0;
      //cout << p1 << "\t" << p2 << "\t" << n1 << "\t" << n2 << "\t" << inters << "\t" << proteins.size() << "\t" << hg << "\t" << lhg << endl;
      cout << p1 << "\t" << p2 << "\t" << lhg << endl;
    }
  intStream2.close();
  cout << proteins.size() << endl;

  return 0;
}

