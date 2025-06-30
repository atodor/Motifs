#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>

using namespace std;

void readFile(char* fileName, set<string> &proteins)
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
		proteins.insert(p1);
		proteins.insert(p2);
		//cout << p1 << endl;
	}
	listFile.close();
}

int main(int argc, char *argv[])
{
  if(argc<2)
  {
    cout << "Usage: " << argv[0] << " network" << endl;
	return 0;
  }
  set <string> proteins;
  readFile(argv[1], proteins);
  cout << proteins.size() << endl;
  return 0;
}
