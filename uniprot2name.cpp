#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstring>
#include <cstdlib>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

using namespace std;

bool find(xmlNodePtr cur, set<string> &name, char * t)
{
  bool found = false;
  xmlChar * type;
  while(cur)
    {
      while (cur && (xmlStrcmp(cur->name, (const xmlChar *)"name"))) cur=cur->next;
      type=xmlGetProp(cur, (const xmlChar*)"type");
      while( xmlStrcmp(type, (const xmlChar *)t) && cur)
	{
	  cur=cur->next;
	  type=xmlGetProp(cur, (const xmlChar*)"type");
	}
      if (cur && (strlen((char*)cur->xmlChildrenNode->content) > 1))
	{
	  name.insert(string((char*)cur->xmlChildrenNode->content));
	  //cout << "~" << (char*)(cur->xmlChildrenNode->content) << "~" <<endl;
	  cur = cur->next;
	  found = true;
	}
    }
  return found;
}

bool uniprot2name(string dir, string gene, set <string> &sname)
{
  xmlDocPtr doc;
  xmlNodePtr cur, parent;
  xmlChar *type, *org;
  char name[1000];
  char strorg[1000];
  string xmlFileName = dir + gene + ".xml";
  doc = xmlParseFile(xmlFileName.c_str());
  if (doc == NULL )
    {
      //     fprintf(stderr,"Error!. Document is not parsed successfully. %s\n", gene.c_str());
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return false;
    }
  
  cur = xmlDocGetRootElement(doc);
  if (cur == NULL)
    {
      //fprintf(stderr,"Document is Empty\n");
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return false;
    }
  name[0] = 0;
  strorg[0] = 0;
  cur = cur->xmlChildrenNode;
  cur = cur->next;
  if ((!xmlStrcmp(cur->name, (const xmlChar *)"entry")))
    {
      cur = cur->xmlChildrenNode;
      while (cur && xmlStrcmp(cur->name, (const xmlChar *)"gene"))
	{
	  cur = cur->next;
	}
      if(cur)
	{
	  parent = cur;
	  cur = cur->xmlChildrenNode;
	  bool found=false;
	  //if (!found)
	    found = find(cur, sname, "primary");
	    /*
	  cur = parent->xmlChildrenNode;
	  //if (!found)
	    found = find(cur, sname, "synonym");
	  cur = parent->xmlChildrenNode;
	  //if (!found)
	    found = find(cur, sname, "ORF");
	    */
	}
      else
	{
	  //fprintf(stderr,"Error!. Gene name missing: %s. \n", gene.c_str());
	  xmlFreeDoc(doc);
	  xmlCleanupParser();
	  return true;
	}
    }  
	xmlFreeDoc(doc);
	xmlCleanupParser();
	return true;
}

void readFile(char* fileName, set<pair<string,string> > &interactions)
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
		interactions.insert(pair<string,string>(p1, p2));
	}
	listFile.close();
}

int main(int argc, char *argv[])
{
  if(argc<3)
  {
    cout << "Usage: " << argv[0] << " mips_network XML_dir" << endl;
	return 0;
  }
  set <pair<string, string> > interactions;
  readFile(argv[1], interactions);
  for (set<pair<string, string> >::iterator sIt = interactions.begin(); sIt != interactions.end(); sIt++)
    {
      set<string> names1, names2;
      uniprot2name(string(argv[2]), sIt->first, names1);
      uniprot2name(string(argv[2]), sIt->second, names2);
      /*
      cout << sIt->first << "\t";
      for (set<string >::iterator sIt1 = names1.begin(); sIt1 != names1.end(); sIt1++)
	cout << *sIt1 << "\t";
      cout << endl;
      cout << sIt->second << "\t";
      for (set<string >::iterator sIt2 = names2.begin(); sIt2 != names2.end(); sIt2++)
	cout << *sIt2 << "\t";
      cout << endl;
      */
      for (set<string >::iterator sIt1 = names1.begin(); sIt1 != names1.end(); sIt1++)
	for (set<string >::iterator sIt2 = names2.begin(); sIt2 != names2.end(); sIt2++)
	  cout << *sIt1 << "\t" << *sIt2 << endl;
    }
  return 0;
}
