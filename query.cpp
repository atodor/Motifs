#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <sqlite3.h>
#include "queries.h"
#include "timer.h"

using namespace std;

int main(int argc, char *argv[])
{
  if(argc<3)
  {
    cout << "Usage: " << argv[0] << " table query" << endl;
	return 0;
  }

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

  char *zErrMsg = 0;
  Timer timer;
  rc = sqlite3_exec(db, stat, NULL, 0, &zErrMsg);
  double t = timer.GetTime();
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }

  sqlite3_close(db);
  cout << t << endl;
  return 0;
}
