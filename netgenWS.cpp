#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
//#include <set>
#include <time.h>

//#define N 300
#define M 10
#define P 0.1
#define STEP 150
#define START 150
#define END 300
#define VMX 10001

using namespace std;

void removeEdge(vector<int> adj[], int i, int v)
{
    int pos = -1;
    for (int j=0; j<adj[i].size(); j++)
    {
        if (adj[i][j] == v)
        {
            pos = j; break;
        }
    }
    if (pos < 0)    printf("Something is wrong in removeEdge.\n");
    for (int j=pos; j<adj[i].size() - 1; j++)
    {
        adj[i][j] = adj[i][j + 1];
    }
    adj[i].pop_back();
}

bool isInWS(vector<int> adj[], int i, int u)
{
    if (i == u) return true;
    for (int j=0; j<adj[i].size(); j++)
    {
        if (adj[i][j] == u) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{

  if (argc < 2)
    {
      cout << "Usage: " << argv[0] << " degree" << endl;
      return 0;
    }                

  srand(time(NULL));

  int E;
  istringstream numberStream1(argv[1]);
  numberStream1 >> E;
  for (int m = 0; m < M; m++)
    {
      for (int n = START; n <= END; n += STEP)
	{
	  //set<pair<int,int> > edges;
	  vector<int> adj[VMX];
	  for (int i = 0; i < n; i++)
	    {
	      for (int j = 1; j <= E; j++)
		{
		  int u = (i + j) % n;
		  adj[i].push_back(u);
		  adj[u].push_back(i);
		  //edgeCounter ++;
		}
	    }
	  for (int i = 0; i < n; i++)
	    {
	      for (int j = 0; j < adj[i].size(); j++)
		{
		  int v = adj[i][j];
		  if (v > i)
		    {
		      int u = rand() % n;
		      if (!isInWS(adj, i, u))
			{
			  // replace with probability p
			  if ((rand() / (double)RAND_MAX) < P)
			    {
			      removeEdge(adj, i, v);
			      removeEdge(adj, v, i);
			      
			      adj[i].push_back(u);
			      adj[u].push_back(i);
			    }
			}
		    }
		}
	    }
	  
	  stringstream of;
	  of << "../Data/Synth/WS" << m << "_" << E << "_" << n << ".txt";
	  ofstream os;
	  os.open(of.str().c_str());
	  for(int i = 0; i < n; i++)
	    for(int j = 0; j < adj[i].size(); j++)
	      if (i < adj[i][j])
		os << i << "\t" << adj[i][j] << "\t" << "0.7" << endl;
	  os.close();
	}
    }
}
