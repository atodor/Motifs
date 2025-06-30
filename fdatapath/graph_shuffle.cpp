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
  vector<pair<int, int> > edges;
  map<int, set<int> > neighbors;
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
      neighbors[p1].insert(p2);
      neighbors[p2].insert(p1);
    }
  intStream.close();

  srand(time(NULL));
  for (int i = 0; i < graph.size(); i++)
    if (rand() % 100 < graph[i].second * 100)
      edges.push_back(graph[i].first);
  
  long long int n_replacements = 1000 * edges.size() * log2(edges.size());
  long long int k = 0;
  for (; k < n_replacements; k++)
    {
      int edge1 = rand() % edges.size();
      int edge2 = rand() % edges.size();
      // switch edges
      if (edges[edge1].first != edges[edge2].first && edges[edge1].first != edges[edge2].second && 
	  edges[edge1].second != edges[edge2].first && edges[edge1].second != edges[edge2].second && // the two edges are not coincident on a node
	  !neighbors[edges[edge1].first].count(edges[edge2].second) &&
	  !neighbors[edges[edge1].second].count(edges[edge2].first) && 
	  !neighbors[edges[edge2].first].count(edges[edge1].second) &&
	  !neighbors[edges[edge2].second].count(edges[edge1].first)) ////the two new edges that will be added don't already exist
	  //accept(nu1, nv1, nu2, nv2)) // checks if this switch leads towards desired type of graph
	{
	  k++;
	  neighbors[edges[edge1].first].erase(edges[edge1].second);
	  neighbors[edges[edge1].first].insert(edges[edge2].second);
	  neighbors[edges[edge2].first].erase(edges[edge2].second);
	  neighbors[edges[edge2].first].insert(edges[edge1].second);
	  neighbors[edges[edge1].second].erase(edges[edge1].first);
	  neighbors[edges[edge1].second].insert(edges[edge2].first);
	  neighbors[edges[edge2].second].erase(edges[edge2].first);
	  neighbors[edges[edge2].second].insert(edges[edge1].first);
	  int tmp = edges[edge1].second;
	  edges[edge1].second = edges[edge2].second;
	  edges[edge2].second = tmp;
	  int s1 = neighbors[edges[edge1].first].size();
	  int s2 = neighbors[edges[edge2].first].size();
	  if (s1 != neighbors[edges[edge1].first].size() || s2 != neighbors[edges[edge2].first].size())
	    {
	      cout << "error" << endl;
	      exit(0);
	    }
	}
    }	      
    for (int i = 0; i < edges.size(); i++)
      cout << i << "\t" << edges[i].first << "\t" << edges[i].second << "\t" << 1 << endl; 
}
