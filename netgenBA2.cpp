#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <set>
#include <time.h>

#define N 300
#define M 10
#define P 0.5
#define K 150

using namespace std;

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
      set<pair<int,int> > edges;
      double x = (double)rand() / (double)RAND_MAX;
      map<int,int> incoming, outgoing, incoming_c, outgoing_c;
      
      incoming.insert(pair<int, int>(0, 0));
      incoming.insert(pair<int, int>(1, 0));
      incoming.insert(pair<int, int>(2, 0));
      outgoing.insert(pair<int, int>(0, 0));
      outgoing.insert(pair<int, int>(1, 0));
      outgoing.insert(pair<int, int>(2, 0));
      incoming_c.insert(pair<int, int>(0, 0));
      incoming_c.insert(pair<int, int>(1, 0));
      incoming_c.insert(pair<int, int>(2, 0));
      outgoing_c.insert(pair<int, int>(0, 0));
      outgoing_c.insert(pair<int, int>(1, 0));
      outgoing_c.insert(pair<int, int>(1, 0));

	  edges.insert(pair<int,int>(0, 1));
	  edges.insert(pair<int,int>(0, 2));
	  edges.insert(pair<int,int>(1, 2));

	  //0
	  outgoing[0]+=2;
	  outgoing_c[0]+=2;
	  //1
	  incoming[1]++;
	  incoming_c[1]=incoming_c[0]+1;
	  outgoing[1]++;
	  outgoing_c[1]=outgoing_c[0]+1;
	  //2

	  incoming[2] += 2;
	  incoming_c[2] = incoming_c[1] + 2;
	  outgoing_c[2] = outgoing_c[1];
      

      /*
      incoming.insert(pair<int, int>(0, 0));
      incoming.insert(pair<int, int>(1, 0));
      outgoing.insert(pair<int, int>(0, 0));
      outgoing.insert(pair<int, int>(1, 0));
      incoming_c.insert(pair<int, int>(0, 0));
      incoming_c.insert(pair<int, int>(1, 0));
      outgoing_c.insert(pair<int, int>(0, 0));
      outgoing_c.insert(pair<int, int>(1, 0));
      if (x < P)
	{
	  edges.insert(pair<int,int>(0, 1));
	  incoming[1]++;
	  incoming_c[1]++;
	  outgoing[0]++;
	  outgoing_c[0]++;
	}
      else
	{
	  edges.insert(pair<int,int>(1, 0));
	  incoming[0]++;
	  outgoing[1]++;
	  incoming_c[0]++;
	  outgoing_c[1]++;
	}
      */

	  cout << 2 << "\t" << edges.size() << endl;
      int i = 3;
      int n = 150;
      while (n <= N)
	{
	  while (i < n)
	    {
	      cout << i<< endl;
	      incoming.insert(pair<int, int>(i, 0));
	      outgoing.insert(pair<int, int>(i, 0));
	      int c_in = 0, c_out = 0;
	      for (map<int, int>:: iterator mIt = incoming.begin(); mIt != incoming.end(); mIt++)
		c_in += mIt->second;
	      for (map<int, int>:: iterator mIt = outgoing.begin(); mIt != outgoing.end(); mIt++)
		c_out += mIt->second;
	      incoming_c.insert(pair<int, int>(i, c_in));
	      outgoing_c.insert(pair<int, int>(i, c_out));
	      int type[E], j[E];

	      /*for (int k = 0; k < E; k++)
		{
		  oldin[k] = 0;
		  }*/
	      for (int k = 0; k < E; k++)
		{
		  int new_edge = 0;
		  while (!new_edge)
		    {
		      x = (double)rand() / (double)RAND_MAX;
		      int xx = rand() % (outgoing_c[i-1] + 1);
		      //cout << outgoing_c[i-1] << " "<< xx << endl;
		      if (x < P)
			{
			  int l;
			  type[k] = 0; //0 - into the new node
			  for (l = 0; l < i; l++)
			    if(outgoing_c[l] >= xx)
			      break;
			  j[k] = l;
			  pair<int,int> e_p = pair<int,int>(j[k], i);
			  if (!edges.count(e_p))	
			    {
			      new_edge = 1;
			      edges.insert(e_p);
			    }
			  //oldin[k]
			  //incoming[i]++;
			  //outgoing[j]++;
			}
		      else
			{
			  int l;
			  type[k] = 1; //1 - out from the new node
			  for (l = 0; l < i; l++)
			    if(incoming_c[l] >= xx)
			      break;
			  j[k] = l;
			  pair<int,int> e_p = pair<int,int>(i, j[k]);
			  if (!edges.count(e_p))	
			    {
			      new_edge = 1;
			      edges.insert(e_p);
			    }
			}
		    }
		}
	      //int totalin = 0;
	      //for (int k = 0; k < E; k++)
	      //totalin += oldin[k];
	      for (int k = 0; k < E; k++)
		{
		  incoming[j[k]] += type[k];
		  outgoing[j[k]] += 1 - type[k];
		  for (int l = j[k]; l <= i ; l++)
		    {
		      incoming_c[l] += type[k];
		      outgoing_c[l] += 1 - type[k];
		    }

		  //incoming_c[j[k]] += oldin[k];
		  //outgoing_c[j[k]] += 1 - oldin[k];
		}

	      for (int k = 0; k < E; k++)
		{
		  incoming[i] += 1 - type[k];
		  outgoing[i] += type[k];
		  incoming_c[i] += 1 - type[k];
		  outgoing_c[i] += type[k];
		}
	      /*
	      incoming[i] += E - totalin;
	      outgoing[i] += totalin;
	      incoming_c[i] += E - totalin;
	      outgoing_c[i] += totalin;
	      */

	      i++;
	      //cout << i << "\t" << edges.size() << endl;
	    }
	  stringstream of;
	  of << "../Data/Synth/BA" << m << "_" << E << "_" << n << ".txt";
	  ofstream os;
	  os.open(of.str().c_str());
	  for (set<pair<int,int> >::iterator sIt = edges.begin(); sIt != edges.end(); sIt++)
	    os << sIt->first << "\t" << sIt->second << "\t" << 0.7 << endl;
	  os.close();
	  cout << edges.size() << endl;
	  n += K;
	}
    }
}
