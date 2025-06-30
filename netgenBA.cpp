#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <set>

#define N 300
#define M 5
#define P 0.5
#define E 2

using namespace std;

int main(int argc, char *argv[])
{

  for (int m = 0; m < M; m++)
    {
      set<pair<int,int> > edges;
      double x = (double)rand() / (double)RAND_MAX;
      map<int,int> incoming, outgoing, incoming_c, outgoing_c;

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


      cout << 2 << "\t" << edges.size() << endl;
      int i = 2;
      int n = 50;
      while (n <= N)
	{
	  while (i < n)
	    {
	      incoming.insert(pair<int, int>(i, 0));
	      outgoing.insert(pair<int, int>(i, 0));
	      int c_in = 0, c_out = 0;
	      for (map<int, int>:: iterator mIt = incoming.begin(); mIt != incoming.end(); mIt++)
		c_in += mIt->second;
	      for (map<int, int>:: iterator mIt = outgoing.begin(); mIt != outgoing.end(); mIt++)
		c_out += mIt->second;
	      incoming_c.insert(pair<int, int>(i, c_in));
	      outgoing_c.insert(pair<int, int>(i, c_out));
	      int oldin[E] = {0}, j[E];
	      for (int k = 0; k < E; k++)
		{
		  int new_edge = 0;
		  while (!new_edge)
		    {
		      x = (double)rand() / (double)RAND_MAX;
		      int xx = rand() % 2*i;
		      if (x < P)
			{
			  int l;
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
			  for (l = 0; l < i; l++)
			    if(outgoing_c[l] >= xx)
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
	      //cout << edges.size() << endl;
	      int totalin = 0;
	      for (int k = 0; k < E; k++)
		totalin += oldin[k];
	      for (int k = 0; k < E; k++)
		{
		  incoming[j[k]] += oldin[k];
		  outgoing[j[k]] += 1 - oldin[k];
		  for (int l = j[k]; l <= i ; l++)
		    {
		      incoming_c[l] += oldin[k];
		      outgoing_c[l] += 1 - oldin[k];
		    }

		  //incoming_c[j[k]] += oldin[k];
		  //outgoing_c[j[k]] += 1 - oldin[k];
		}
	      incoming[i] += E - totalin;
	      outgoing[i] += totalin;
	      incoming_c[i] += E - totalin;
	      outgoing_c[i] += totalin;
	      i++;
	      cout << i << "\t" << edges.size() << endl;
	    }
	  stringstream of;
	  of << "../Data/Synth/BA" << m << "_" << n << ".txt";
	  ofstream os;
	  os.open(of.str().c_str());
	  for (set<pair<int,int> >::iterator sIt = edges.begin(); sIt != edges.end(); sIt++)
	    os << sIt->first << "\t" << sIt->second << endl;
	  os.close();
	  cout << edges.size() << endl;
	  n += 50;
	}
    }
}
