#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <map>
#include <set>
#include <sqlite3.h>
#include "queries.h"
#include "timer.h"
#include <time.h>

#define F 10;

using namespace std;

struct params
{
  vector<vector<int> > motifs;
  map<int,set<int> >h;
};

static int callback_db(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  map <int, double> *probs = (map <int, double> *)NotUsed;
  (*probs)[atoi(argv[0])] = atof(argv[1]);
  return 0;
}

static int callback_motifs(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  struct params * par = (struct params *)NotUsed;
  vector<int> tmp;
  for (i = 0; i < argc; i++)
    tmp.push_back(atoi(argv[i]));
  par->motifs.push_back(tmp);
  for (i = 0; i < argc; i++)
    par->h[tmp[i]].insert(par->motifs.size()-1);
  return 0;
}
  
  void split(vector<int> motif1, vector<int> motif2, set<int> &diff, set<int> &inters)
    {
      for (int i = 0; i < motif1.size(); i++)
	{
	  int found = 0;
	  for (int j = 0; j < motif2.size(); j++)
	    if (motif2[j] == motif1[i])
	      {
		found = 1;
		break;
	      }
	  if (found)
	    inters.insert(motif1[i]);
	  else diff.insert(motif1[i]);
	}
    }

  set<int> m_union(vector<int> edges, map<int,set<int> >h)
    {
      set <int> res;
      for (int i = 0; i < edges.size(); i++)
	{
	  //cout << edges[i] << ":";
	for (set<int>::iterator sIt = h[edges[i]].begin(); sIt != h[edges[i]].end(); sIt++)
	  {
	    res.insert(*sIt);
	    //cout << *sIt << "\t";
	  }
	}
      //cout << endl;
      return res;
    }

int main(int argc, char *argv[])
{
  if(argc<3)
  {
    cout << "Usage: " << argv[0] << " table query" << endl;
	return 0;
  }

  Timer timer;

  sqlite3 *db;
  char stat[1000]; 
  int rc;
  rc = sqlite3_open("graph4.db", &db);
  if( rc )
    {
      cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      return(1);
    }

  map<int, double > probs;

  char *zErrMsg = 0;
  sprintf(stat, "select id, p from %s;", argv[1]);
  rc = sqlite3_exec(db, stat, callback_db, &probs, &zErrMsg);
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }
  
  int q = atoi(argv[2]);
  switch(q)
    {
    case 1:
      sprintf(stat, Q1, argv[1]);
      break;
    case 2:
      sprintf(stat, Q2, argv[1], argv[1]);
      break;
    case 3:
      sprintf(stat, Q3, argv[1], argv[1], argv[1]);
      break;
    case 4:
      sprintf(stat, Q4, argv[1]);
      break;
    case 5:
      sprintf(stat, Q5, argv[1], argv[1]);
      break;
    case 6:
      sprintf(stat, Q6, argv[1], argv[1]);
      break;
    case 7:
      sprintf(stat, Q7, argv[1], argv[1]);
      break;
    case 8:
      sprintf(stat, Q8, argv[1], argv[1], argv[1]);
      break;
    case 9:
      sprintf(stat, Q9, argv[1], argv[1], argv[1]);
      break;
    case 10:
      sprintf(stat, Q10, argv[1], argv[1], argv[1]);
      break;
    case 11:
      sprintf(stat, Q11, argv[1], argv[1], argv[1], argv[1]);
      break;
    case 12:
      sprintf(stat, Q12, argv[1], argv[1], argv[1]);
      break;
    case 13:
      sprintf(stat, Q13, argv[1], argv[1], argv[1]);
      break;
    case 14:
      sprintf(stat, Q14, argv[1], argv[1], argv[1], argv[1]);
      break;
    default: q=1;
    }

  struct params par;
  rc = sqlite3_exec(db, stat, callback_motifs, &par, &zErrMsg);
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }

  sqlite3_close(db);

  cout << par.motifs.size() << "\t";  

  double mean = 0.0;
  for(int i = 0; i < par.motifs.size(); i++)
    {
      double prod = 1.0;
      for(int j = 0; j < par.motifs[i].size(); j++)
	prod *= probs[par.motifs[i][j]];
      mean += prod;
    }

  cout << mean << "\t";
  
  double var = 0.0;
  int n_samples = par.motifs.size();
  if (sampling)
    n_samples /= 10;
  else
    n_samples = 0;
  int selected_samples[par.motifs.size()];
  if (sampling)
    {
      srand(time(NULL));
      for (int i = 0; i < n_samples; i++)
	if (rand()%100 < F)
	  {
	    selected_samples[n_samples] = i;
	    n_samples++;
	  }
    }
  else
    for (int i = 0; i < n_samples; i++)
      selected_samples[i] = i;
  for (int i = 0; i < n_samples; i++)
    {
      double prod = 1.0;
      for (int j = 0; j < par.motifs[i].size(); j++)
	prod *= probs[par.motifs[i][j]];
      double sum = 0.0;
      //cout << i << "/" << par.motifs.size() << endl;
      set<int> share = m_union(par.motifs[i], par.h);
      for (set<int>::iterator sIt = share.begin(); sIt != share.end(); sIt++)
	{
	  double prod1 = 1.0;
	  double prod2 = 1.0;
	  set<int>edges_diff, edges_inters;
	  split(par.motifs[*sIt], par.motifs[i], edges_diff, edges_inters);
	  for (set<int>::iterator sIt1 = edges_diff.begin(); sIt1 != edges_diff.end(); sIt1++)
	    prod1 *= probs[*sIt1];
	  for (set<int>::iterator sIt2 = edges_inters.begin(); sIt2 != edges_inters.end(); sIt2++)
	    prod2 *= probs[*sIt2];
	  sum += prod1 * (1.0 - prod2);
	}
      var += prod * sum;
    }
  
  /*
  for (int i = 0; i < par.motifs.size(); i++)
    {
      double prod = 1.0;
      for (int j = 0; j < par.motifs[i].size(); j++)
	prod *= probs[par.motifs[i][j]];
      double sum = 0.0;
      cout << i << "/" << par.motifs.size() << endl;
	for (int j = 0; j < par.motifs.size(); j++)
	{
	  double prod1 = 1.0;
	  double prod2 = 1.0;
	  set<int>edges_diff, edges_inters;
	  split(par.motifs[j], par.motifs[i], edges_diff, edges_inters);
	  for (set<int>::iterator sIt1 = edges_diff.begin(); sIt1 != edges_diff.end(); sIt1++)
	    prod1 *= probs[*sIt1];
	  for (set<int>::iterator sIt2 = edges_inters.begin(); sIt2 != edges_inters.end(); sIt2++)
	    prod2 *= probs[*sIt2];
	  sum += prod1 * (1.0 - prod2);
	}
      var += prod * sum;
    }
  */


  cout << var << "\t";
  
  double t = timer.GetTime();

  cout << t << endl;

  return 0;
 }
