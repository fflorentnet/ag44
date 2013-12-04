#include "parser.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "route.h"
using namespace std;
std::string Parser::split(std::string chaine, char joker, int p)
{
    int nbChar = chaine.length();
    int jokCpt = 1;
    std::string temp = "";
    for (int i = 0 ; i < nbChar; i++)
    {
        //std::cout << "joker:"<<(int)joker<<endl;
        if (chaine[i] == joker)
        {
            jokCpt++;
            //std::cout << "test" <<endl;
        }
        else
        {
            if (jokCpt == p)
            {
                temp = temp + chaine[i];
            }
        }
    }

    return temp;
}

Parser::Parser(std::string fileName)
{
    g = new Graph();
    string temp;
    ifstream graph;
    int cpt=0;
    int nombreNoeud=0;
    int nombreEdge=0;
    bool noeudParsed=false;
    bool edgeParsed=false;
    string name;
    string alt;
    string number;
    string start;
    string end;
    string type;
    Point* p;
    Route* r;
    try {
    graph.open(fileName.c_str());
    while(getline(graph,temp)){
        if(cpt==0 &&!noeudParsed)
        {
            nombreNoeud=atoi(temp.c_str());
            noeudParsed = true;
        }
        if (cpt == nombreNoeud+1 && noeudParsed)
        {
            nombreEdge=atoi(temp.c_str());
            edgeParsed=true;
            noeudParsed=false;
            cpt = 0;
        }
        if (cpt != 0 && noeudParsed && !edgeParsed)
        {

            //    std::cout << "<Point number>" << split(temp, '\t', 1) << '\t' << "<Place name>" << split(temp, '\t', 2) << '\t' << "<altitude>" << split(temp,'\t',3)  << endl;
            number=split(temp,'\t',1);
            name=split(temp,'\t',2);
            alt=split(temp,'\t',3);
            p = new Point(name, atoi(alt.c_str()));
            g->addPoint(atoi(number.c_str()), name, p);
        }

        if (cpt != 0 && !noeudParsed && edgeParsed)
        {
            //std::cout << "<Route number>" << split(temp, '\t', 1) << '\t' << "<Route name>" << split(temp, '\t', 2) << '\t' << "<type>" << split(temp,'\t',3) << '\t' << "<Startpoint>" << split(temp,'\t',4) << '\t' << "<Endpoint>" << split(temp,'\t',5)  << endl;
            number=split(temp,'\t',1);
            name=split(temp,'\t',2);
            type=split(temp,'\t',3);
            start=split(temp,'\t',4);
            end=split(temp,'\t',5);

            r = new Route(name, type, g->getPoint(atoi(start.c_str())), g->getPoint(atoi(end.c_str())));
            //g->getPoint(atoi(start.c_str()))->addVoisin(g->getPoint(atoi(end.c_str())), r->getValue());
            g->addRoute(r);
        }

        cpt++;
    }
      graph.close();

    }
    catch(std::ifstream::failure e)
    {
        std::cout << "I can't open the file "+fileName+"\n";
    }
}
Graph* Parser::getGraph() { return g; }
