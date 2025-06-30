#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <sqlite3.h>
#include "queries.h"
#include "timer.h"
#include <time.h>

#define F 10.0

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
  if(argc<4)
  {
    cout << "Usage: " << argv[0] << " table query sampling" << endl;
	return 0;
  }

  Timer timer;

  sqlite3 *db;
  char stat[10000];  
 int rc;
  rc = sqlite3_open("../graph5.db", &db);
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
  int sampling = atoi(argv[3]);
  //cout << "first" << endl;
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
    case 15:
      sprintf(stat, Q15, argv[1], argv[1], argv[1]);
      break;
    case 16:
      sprintf(stat, Q16, argv[1], argv[1], argv[1]);
      break;
    case 17:
      sprintf(stat, Q17, argv[1], argv[1], argv[1]);
      break;
    case 18:
      sprintf(stat, Q18, argv[1], argv[1], argv[1]);
      break;
    case 19:
      sprintf(stat, Q19, argv[1], argv[1], argv[1]);
      break;
    case 20:
      sprintf(stat, Q20, argv[1], argv[1], argv[1]);
      break;
    case 21:
      sprintf(stat, Q21, argv[1], argv[1], argv[1]);
      break;
    default: q = 1;
    }

  //int sl = strlen(stat);
  //strcpy(stat + sl - 1," limit 10;");
  struct params par;
  rc = sqlite3_exec(db, stat, callback_motifs, &par, &zErrMsg);
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }
  //cout << "second" << endl;

  sqlite3_close(db);

  cout << par.motifs.size() << "\t";  

  if (sampling == 2)
    {
      cout << timer.GetTime() << "\t";
      return 0;
    }

  double mean = 0.0;
  for(int i = 0; i < par.motifs.size(); i++)
    {
      double prod = 1.0;
      for(int j = 0; j < par.motifs[i].size(); j++)
	prod *= probs[par.motifs[i][j]];
      mean += prod;
    }

  cout << mean << "\t";
  
  if (sampling == 3)
    {
      cout << "0\t" << timer.GetTime() << "\t";
      return 0;
    }

  double var = 0.0;
  int n_samples;
  int selected_samples[par.motifs.size()];
  //cout << "~" << sampling << "~" << endl;
  // cout << par.motifs[i].size() << endl;
  if (sampling)
    {
      n_samples = 0;
      srand(time(NULL));
      for (int i = 0; i < par.motifs.size(); i++)
	{
	  double r = (double)rand() / (double)RAND_MAX;
	  //cout << r << endl;
	  if (r < (par.motifs.size() < 1000000 ? 1.0 / F : 1.0 / F / 1000.0))
	    {
	      selected_samples[n_samples] = i;
	      n_samples++;
	    }
	}
    }
  else
    {
      n_samples = par.motifs.size();
      for (int i = 0; i < n_samples; i++)
	selected_samples[i] = i;
    }

  double correction = 0.0;
  for (int i = 0; i < n_samples; i++)
    {
      double prod = 1.0;
      for (int j = 0; j < par.motifs[selected_samples[i]].size(); j++)
	{
	  prod *= probs[par.motifs[selected_samples[i]][j]];
	  //cout << par.motifs[selected_samples[i]][j] << endl;
	  //cout << prod << endl;
	}
      correction += prod * (1.0 - prod);
      double sum = 0.0;
      for (int j = 0; j < n_samples; j++)
	{
	  double prod1 = 1.0;
	  double prod2 = 1.0;
	  set<int>edges_diff, edges_inters;
	  split(par.motifs[selected_samples[j]], par.motifs[selected_samples[i]], edges_diff, edges_inters);
	  //cout << edges_diff.size() << "\t" << edges_inters.size() << endl;
	  for (set<int>::iterator sIt1 = edges_diff.begin(); sIt1 != edges_diff.end(); sIt1++)
	    prod1 *= probs[*sIt1];
	  for (set<int>::iterator sIt2 = edges_inters.begin(); sIt2 != edges_inters.end(); sIt2++)
	    prod2 *= probs[*sIt2];
	  sum += prod1 * (1.0 - prod2);
	  //cout << edges_diff.size() << "\t" << edges_inters.size() << "\t" << prod1 << "\t" << prod2 << "\t" << prod1 * (1.0 - prod2) << "\t" <<sum << endl;
	}
      //cout << prod << sum << endl;
      var += prod * sum;
    }
  var = F * F * var + (F - 1.0) * correction;
  cout << var << "\t";
  
  double t = timer.GetTime();

  cout << t << "\t";

  return 0;
 }
