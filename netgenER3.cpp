#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>

//#define N 100
#define START 150
#define END 300
#define STEP 150
#define R 2.0

#define M 10
//#define P (125.0 / 9900.0)

using namespace std;

int main(int argc, char *argv[])
{
  srand(time(NULL));
  for (int m = 0; m < M; m++)
    {
      //int i = 0;

      int n = START;
      while (n <= END)
	{
	  vector<pair<int,int> > edges;
	  //double dn = (double)n;
	  //double P = dn * 1.25 / (dn * (dn - 1.0));
	  for (int i = 0; i < n; i++)
	    for (int j = 0; j < n; j++)
	      if (i != j)
		{
		  //double x = (double)rand() / (double)RAND_MAX;
		  //if (x < P)
		      edges.push_back(pair<int,int>(i, j));
		}
	  int nn = R * n;
	  cout << n << "\t"<< nn << endl;
	  int NN = edges.size();
	  for (int i = 0; i < nn; i++)
	    {
	      int j = rand() % (NN - i) + i;
	      pair<int,int> tmp = edges[i];
	      edges[i] = edges[j];
	      edges[j] = tmp;
	    }
	  stringstream of;
	  of << "../Data/Synth/ER" << m << "_" << (int)R << "_"<< n <<".txt";
	  ofstream os;
	  os.open(of.str().c_str());
	  for (int i = 0; i < nn; i++)
	    os << edges[i].first << "\t" << edges[i].second << "\t" << 0.7 << endl;
	  os.close();
	  n += STEP;
	}
    }
}
