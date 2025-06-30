#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <cstdlib>
//#include "../../ProbGraphs/Code/Probgraphs/Graph.h"

using namespace std;

void readGraph(char* fileName, vector<pair<int, int> > &edges, vector<double> &probabilities)
{
  map <string, int> ids;
  //set <string, int> ids_map;
  //cout << "Usage: " << argv[0] << " path organism1 organism2" << endl;

  //	Graph g("", "all");
  //	g.read("./", 100.0);

	//  Graph g=Graph();
	//g.read();
	ifstream listFile(fileName);
	if(listFile.fail())
		cout << "File read error: " << fileName << endl;
	char line[500];
	int i=0;
	while (listFile.good())
	{
		listFile.getline(line,500);
		if (strlen(line) <= 0)
			continue;
       		string v1, v2, prob;
		int id1,id2;
		double p;
		istringstream strStream(line);
		getline(strStream, v1, '\t');
		//istringstream nStream1(v1);
		//nStream1 >> id1;
		if (!ids.count(v1))
		  {
		    ids[v1] = i;
		    i++;
		  }
		getline(strStream, v2, '\t');
		//istringstream nStream2(v2);
		//nStream2 >> id2;
		if (!ids.count(v2))
		  {
		    ids[v2] = i;
		    i++;
		  }
		getline(strStream, prob, '\t');
		istringstream nStream3(prob);
		nStream3 >> p;
		edges.push_back(pair<int,int>(ids[v1],ids[v2]));
		probabilities.push_back(p);
	}
	listFile.close();
}


int main(int argc, char *argv[])
{
  if(argc<2)
  {
    cout << "Usage: " << argv[0] << " file" << endl;
	return 0;
  }
  vector <pair<int,int> > edges;
  vector <double> probabilities;
  readGraph(argv[1], edges, probabilities);

  for (int i = 0; i < edges.size(); i++)
    {
      cout << i + 1 << "\t" << edges[i].first << "\t" << edges[i].second << "\t" << probabilities[i] << endl;
    }
  return 0;
}
