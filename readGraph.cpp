#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <sqlite3.h>
#include "queries.h"
#include "/home/atodor/svn/P-Andrei/ProbGraphs/Code/ProbGraphs/RandomGraph.h"
#include "timer.h"

#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc<2)
  {
    cout << "Usage: " << argv[0] << " organism" << endl;
	return 0;
  }
  string GRAPH_DIR="/home/atodor/svn/P-Andrei/PowerLawAnalysis/Data/MINT/Nets/";
  vector<string>ids;
  RandomGraph g(argv[1], "all");
  g.read(string(GRAPH_DIR), 100.0);
  map<pair<int, int>,double> edges= g.getEdges();
  for (map<pair<int, int>,double>::iterator mIt = edges.begin(); mIt!=edges.end(); mIt++)
    if (mIt->first.first < mIt->first.second)
      cout << mIt->first.first << "\t" << mIt->first.second << "\t" << mIt->second<< endl; 
  //cout << g.nodeCount() << "\t" << g.edgeCount() << endl;
}
