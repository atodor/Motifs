#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      cout << "Usage: " << argv[0] << " " << "network_file" << endl;
      return 0;
    }                

  ifstream intStream(argv[1]);
  char line[500];
  vector< pair <pair<int, int>, double > >graph;
  vector<pair<int, int> > edges, newEdges;
  set<int> nodes;
  while (intStream.good())
    {
      intStream.getline(line,500);
      if (strlen(line) <= 0)
	continue;
      string sp1, sp2, sp;
      double p;
      int p1, p2;
      istringstream strStream(line);
      getline(strStream, sp1, '\t');
      getline(strStream, sp2, '\t');
      getline(strStream, sp, '\t');
      istringstream nrStream1(sp1);
      istringstream nrStream2(sp2);
      istringstream nrStream3(sp);
      nrStream1 >> p1;
      nrStream2 >> p2;
      nrStream3 >> p;
      pair<int, int> endpoints = pair<int, int>(p1, p2);
      pair< pair<int, int>, double> edge = pair< pair<int, int>, double>(endpoints, p);
      graph.push_back(edge);
      nodes.insert(p1);
      nodes.insert(p2);
    }
  intStream.close();

  srand(time(NULL));
  for (int i = 0; i < graph.size(); i++)
    if (rand() % 100 < graph[i].second * 100)
      edges.push_back(graph[i].first);

  int n = nodes.size();
  double R = (double)edges.size() / (double)n * (double)(n - 1);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i != j)
	{
	  double p = (double)rand() / (double)RAND_MAX;
	  if (p < R)
	  newEdges.push_back(pair<int,int>(i, j));
	}

  int nn = newEdges.size();
  for (int i = 0; i < nn; i++)
    cout << newEdges[i].first << "\t" << newEdges[i].second << "\t" << 1 << endl; 
}
