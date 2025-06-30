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


bool uniprot2name2(string gene, set <string> &sname)
{
  xmlDocPtr doc;
  xmlNodePtr cur, parent;
  xmlChar *type, *org;
  string xmlFileName = string("/home/atodor/w/probgraphs/data/Uniprot/XML/") + gene + ".xml";
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

	  while(cur)
	    {
	      while (cur && (xmlStrcmp(cur->name, (const xmlChar *)"name"))) cur=cur->next;
	      type=xmlGetProp(cur, (const xmlChar*)"type");
	      while( xmlStrcmp(type, (const xmlChar *)"primary") && cur)
		{
		  cur=cur->next;
		  type=xmlGetProp(cur, (const xmlChar*)"type");
		}
	      if (cur && (strlen((char*)cur->xmlChildrenNode->content) > 1))
		{
		  sname.insert(string((char*)cur->xmlChildrenNode->content));
		  //cur = cur->next;
		  //found = true;
		  cout << "~" << (char*)(cur->xmlChildrenNode->content) << "~" <<endl;
		}
	    }
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



bool uniprot2name(string gene, set <string> &sname)
{
  xmlDocPtr doc;
  xmlNodePtr cur, parent;
  xmlChar *type, *org;
  char name[1000];
  char strorg[1000];
  string xmlFileName = string("/home/atodor/w/probgraphs/data/Uniprot/XML/") + gene + ".xml";
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
	  if (!found)
	    found = find(cur, sname, "primary");
	  cur = parent->xmlChildrenNode;
	  if (!found)
	    found = find(cur, sname, "ordered locus");
	  cur = parent->xmlChildrenNode;
	  if (!found)
	    found = find(cur, sname, "ORF");
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
		getline(strStream, p1, ' ');
		getline(strStream, p2, ' ');
		proteins.insert(p1);
		proteins.insert(p2);
		//cout << p1 << endl;
	}
	listFile.close();
}


void parse(string s, set<string>& list)
{
  string pp1;
  istringstream p1Stream(s);
  do		
    {
      getline(p1Stream, pp1, '|');
      list.insert(pp1);
    }
  while (!p1Stream.eof());
}

void readMap(char* fname, map<string,set<string> > &m)
{
  ifstream mFile(fname);
  if(mFile.fail())
    {
      cout << "File read error: " << fname << endl;
      return;
    }
  char line[50000];
  while (mFile.good())
    {
      mFile.getline(line,50000);
      if (strlen(line) <= 0)
	continue;
      //cout << line << endl;
      string head, tail;
      istringstream strStream(line);
      getline(strStream, head, '\t');
      //cout << head << endl;
      if (!m.count(head))
	m.insert(pair<string, set<string> >(head,set<string>()));
      do
	{
	  getline(strStream,tail,'\t');
	  if (tail.size() > 0)
	    m[head].insert(tail);
	}
      while (!strStream.eof());
    }
  mFile.close();
}

/*
  void readMap(char* fname, map<string,set<string> > &m)
{
  ifstream mFile(fname);
  if(mFile.fail())
    {
      cout << "File read error: " << fname << endl;
      return;
    }
  char line[50000];
  while (mFile.good())
    {
      mFile.getline(line,50000);
      if (strlen(line) <= 0)
	continue;
      string head, tail;
      istringstream strStream(line);
      getline(strStream, head, '\t');
      if (!m.count(head))
	m.insert(pair<string, set<string> >(head,set<string>()));
      do
	{
	  getline(strStream,tail,'\t');
	  if (tail.size() > 0)
	    m[head].insert(tail);
	}
      while (!strStream.eof());
    }
  mFile.close();
}
*/

int main(int argc, char *argv[])
{
  if(argc<6)
  {
    cout << "Usage: " << argv[0] << " network kegg2uniprot term termfile termmapping" << endl;
	return 0;
  }
  set <string> proteins;
  map <string, set <string> > kegg2uniprot;
  map <string, set <string> > terms;
  map <string, set <string> > mappedterms;
  readFile(argv[1], proteins);
  readMap(argv[2], kegg2uniprot);
  readMap(argv[4], terms);
  readMap(argv[5], mappedterms);
  int count = 0;
  for (set<string>::iterator sIt = proteins.begin(); sIt != proteins.end(); sIt++)
    {
      bool has_term = false;
      set<string> proteins1; 
      parse(*sIt, proteins1); 
      for (set<string>::iterator sIt1 = proteins1.begin(); sIt1 != proteins1.end(); sIt1++)
	{
	  //cout << *sIt1 << endl;
	for (set<string>::iterator sIt2 = kegg2uniprot[*sIt1].begin(); sIt2 != kegg2uniprot[*sIt1].end(); sIt2++)
	  {
	    set<string> names;
	    bool file = uniprot2name(*sIt2, names);
	    if (file)
	      {
		//cout << *sIt2 << ": "<< names.size() << endl;
		for (set<string>::iterator sIt3 = names.begin(); sIt3 != names.end(); sIt3++)
		  {
		    //cout << *sIt3 << "\t" << terms[*sIt3].size() << "\t" << terms[*sIt3].count(argv[3]) << endl;
		  if (terms[*sIt3].count(argv[3]))
		    has_term = true;

		  //for (set<string>::iterator sIt4 = terms[*sIt3].begin(); sIt4 != terms[*sIt3].end(); sIt4++)
		  //cout << *sIt4 << "\t";
		  }
		//cout << endl;
	      }
	    //cout << endl;
	    //else
	    //out << *sIt2 << endl;
	  }
	}
      if (has_term)
	count++;
      //cout << endl;
    }
  
  cout << proteins.size() << "\t" << count << endl;
  return 0;
}
