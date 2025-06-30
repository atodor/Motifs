#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sqlite3.h>

using namespace std;

void readGraph(char* fileName, vector<pair<int, int> > &edges, vector<double> &probabilities)
{
	ifstream listFile(fileName);
	if(listFile.fail())
		cout << "File read error: " << fileName << endl;
	char line[500];
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
		istringstream nStream1(v1);
		nStream1 >> id1;
		getline(strStream, v2, '\t');
		istringstream nStream2(v2);
		nStream2 >> id2;
		getline(strStream, prob, '\t');
		istringstream nStream3(prob);
		nStream3 >> p;
		edges.push_back(pair<int,int>(id1,id2));
		probabilities.push_back(p);
	}
	listFile.close();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++)
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  printf("\n");
  return 0;
}

void insrt(sqlite3 *db, char * table, int id, int v1, int v2, double p)
{
  char *zErrMsg = 0;
  char stat[1000];
  sprintf(stat, "insert into %s values (%d, %d, %d, %f);", table, id, v1, v2, p);
  int rc = sqlite3_exec(db, stat, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }
}

int main(int argc, char *argv[])
{
  if(argc<4)
  {
    cout << "Usage: " << argv[0] << " file table dir" << endl;
	return 0;
  }
  vector <pair<int,int> > edges;
  vector <double> probabilities;
  readGraph(argv[1], edges, probabilities);

  sqlite3 *db;
  char stat[1000]; 
  int rc;
  rc = sqlite3_open("graph5.db", &db);
  if( rc )
    {
      cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
      sqlite3_close(db);
      return(1);
    }

  char *zErrMsg = 0;
  sprintf(stat, "create table %s (id N, v1 N, v2 N, p N(10,9));", argv[2]);
  rc = sqlite3_exec(db, stat, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK )
    {
      cerr << "SQL error: " << zErrMsg << endl;
      cout << stat << endl;
      sqlite3_free(zErrMsg);
    }
  
  for (int i = 0;i < edges.size(); i++)
    {
      insrt(db,argv[2],i,edges[i].first,edges[i].second,probabilities[i]);
      int directed = atoi(argv[3]);
      if(!directed)
	{
	  insrt(db,argv[2],i,edges[i].second,edges[i].first,probabilities[i]);
	}
    }
  sqlite3_close(db);
  return 0;
}
