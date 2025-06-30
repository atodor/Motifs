#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <time.h>

using namespace std;

void readFile(char* fileName, vector<string> &e1, vector<string> &e2)
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
      string p1, p2;
      istringstream strStream(line);
      getline(strStream, p1, '\t');
      getline(strStream, p2, '\t');
      e1.push_back(p1);
      e2.push_back(p2);
    }
  listFile.close();
}

int main(int argc, char *argv[])
{
  if(argc < 2)
  {
    cout << "Usage: " << argv[0] << " network" << endl;
	return 0;
  }
  vector<string> e1, e2;
  readFile(argv[1], e1, e2);
  int n = e1.size();
  double c= 300000000000 / (n * n) ;
  srand(time(NULL));
  int r, rr;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i != j)
      {
	r = rand();
	rr = r%1000000000;
	if (rr < c)
	  cout << e1[i] << "\t" << e2[j] << endl;
      }
  //cout << RAND_MAX << endl;
}
