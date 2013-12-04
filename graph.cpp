#include "graph.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits>
#include <sstream>
using namespace std;
Graph::Graph()
{
}
Graph::~Graph()
{
    dist.clear();
    listPoint.clear();
    listRoute.clear();
    next.clear();
}

void Graph::addPoint(int num, std::string name, Point *p)
{
    listPoint[num]=p;
    std::cout << "Point " << num << " ajouté [" << p->getNom() <<"] (" << p->get_Altitude() << "m)" <<endl;
}
void Graph::getRoutes()
{
    Route* p;
    std::map<std::pair<Point*, Point*>, Route*>::const_iterator it;
    for (it = listRoute.begin(); it != listRoute.end(); it++)
    {

        p = (*it).second;
        if (p != NULL)
            p->toCout();
    }
}
void Graph::getPoints()
{
    Point* p;
    int num;
    std::map<int, Point*>::const_iterator it;
    for (it = listPoint.begin(); it != listPoint.end(); it++)
    {
        p = (*it).second;
        num = (*it).first;
        std::cout << "Point " << (num) << " [" << p->getNom() <<"] (" << p->get_Altitude() << "m)" <<endl;
    }
}

void Graph::addRoute(Route* r)
{
    listRoute[std::make_pair(r->getStarting(),r->getArrival())]=r;
    r->toCout();
}

Point* Graph::getPoint(int num)
{
    return listPoint[num];
}
Point* Graph::getPoint(std::string n)
{
    Point* tempit = NULL;
    Point* temp = NULL;
    std::map<int, Point*>::const_iterator it;
    for (it = listPoint.begin(); it != listPoint.end(); it++)
    {
        tempit = (*it).second;
        if (tempit->getNom() == n)
        {
            temp = tempit;
            break;
        }
    }
    return temp;
}
void Graph::FWarshall()
{
    std::map<int, Point*>::const_iterator itTemp;
    std::map<int, Point*>::const_iterator itTempp;
    std::map<int, Point*>::const_iterator itTp;

    Point* i;
    Point* j;
    Point* k;

    Route* r;
    float rTemp=0;
    for(itTemp = listPoint.begin(); itTemp != listPoint.end(); itTemp++)
    {
        i = (*itTemp).second;
        for(itTempp = listPoint.begin(); itTempp != listPoint.end(); itTempp++)
        {
            j = (*itTempp).second;
            r = listRoute[std::make_pair(i,j)];
            if (!r)
            {
                rTemp = std::numeric_limits<float>::infinity();
               listRoute.erase(std::make_pair(i,j));
            }
            else
                rTemp = r->getValue();

            dist[std::make_pair(i,j)] = rTemp;
            next[std::make_pair(i,j)] = NULL;
        }
    }
    //k
    for(itTemp = listPoint.begin(); itTemp != listPoint.end(); itTemp++)
    {
        k = (*itTemp).second;
        /*i*/ for(itTempp = listPoint.begin(); itTempp != listPoint.end(); itTempp++)
        {
            i = (*itTempp).second;
            /*j*/ for(itTp = listPoint.begin(); itTp != listPoint.end(); itTp++)
            {
                j = (*itTp).second;

                if (dist[std::make_pair(i,k)]+dist[std::make_pair(k,j)] < dist[std::make_pair(i,j)])
                {
                    dist[std::make_pair(i,j)] = dist[std::make_pair(i,k)] + dist[std::make_pair(k,j)];
                    next[std::make_pair(i,j)] = k;
                }
            }
        }
    }
}
std::string Graph::getPath(Point* i, Point* j)
{
    float distij = dist[std::make_pair(i,j)];
    if (distij == std::numeric_limits<float>::max())
    {
        return "No path - " + '\n';
    }
    else
    {
        if (i == j)
        {
            return "";
        }
        else
        {
            Point* intermediaire = next[std::make_pair(i,j)];
            if (!intermediaire)
            {
                std::stringstream ss;
                ss << distij;
                pileRoute.push(getRoute(i,j));
                return " --(" + ss.str() + ")---> "; //i->getNom() + " -> " + j->getNom();
            }
            else
            {
                std::string result = getPath(i,intermediaire) + intermediaire->getNom() + getPath(intermediaire,j);
                return result;
            }
        }
    }
}

std::stack<Route*> Graph::Dijkstra(Point *source, Point *dest)
{
    int infini = 10000;
    std::map<Point*, bool> marquage;
    std::map<Point*, float> label;
    std::map<int, Point*>::const_iterator it;
    std::map<std::pair<Point*, Point*>, Route*>::const_iterator itr;
    std::map<Point*, Point*> chemin;

    for (it=listPoint.begin();it != listPoint.end();it++)
    {
        marquage[(*it).second] = false;
        label[(*it).second] = infini;
    }
    label[source]=0;
    do
    {
        Point* marque;
        int min = infini;
        for (it=listPoint.begin();it != listPoint.end();it++)
        {
            Point* temp = (*it).second;
            if (!marquage[temp])
            {
                if (min > label[temp])
                {
                    min = label[temp];
                    marque=temp;
                }
            }
        }

        marquage[marque]=true;
        for (itr=listRoute.begin();itr != listRoute.end();itr++)
        {
            Route* rTemp = (*itr).second;
            if (rTemp != 0)
            {
                if (rTemp->getStarting() == marque)
                {

                    Point* voisin = rTemp->getArrival();
                    float valeurRoute = rTemp->getValue();
                    if (valeurRoute != 0)
                    {
                        if (label[voisin]>label[marque]+valeurRoute)
                        {
                            label[voisin]=std::min(label[voisin],label[marque]+valeurRoute);
                            chemin[voisin] = marque;
                        }
                    }
                }
            }
        }

    }while(!verifierMarquage(marquage));
    std::stack<Route*> cheminSort;
    Point* sortie = dest;
    Route* tempRoute;
    do
    {
        tempRoute=getRoute(chemin[sortie],sortie);
        cheminSort.push(tempRoute);
        sortie = chemin[sortie];
    }while(sortie!=source);

    return cheminSort;
}
Route* Graph::getRoute(Point* p1, Point* p2)
{
    Route* temp = listRoute[std::make_pair(p1,p2)];
    return temp;

}
void Graph::DFS(Point* s, std::string typeRoute)
{
    Route* r;
    bool b=false;
    std::set<Route*>::const_iterator it;
    std::cout << "Lancement DFS:" <<endl;
    dfsRoute.clear();
    dfsPoint.clear();
    subDFS(s, typeRoute);
    for (it = dfsRoute.begin(); it != dfsRoute.end(); it++)
    {
        r = *it;
        r->toCout();
        b = true;
    }
    if (!b)
        std::cout << "Il n'y a pas de point accessible avec le type " << typeRoute << " à partir de " << s->getNom() <<endl;
    std::cout << endl;
}

void Graph::subDFS(Point* s, std::string typeRoute)
{
    std::map<std::pair<Point*, Point*>, Route*>::const_iterator it;
    std::pair<Point*, Point*> pairPoints;
    Point* voisin;
    Route* route;
    dfsPoint.insert(s);
    std::string type = "";
    for (it = listRoute.begin(); it != listRoute.end();it++)
    {
        pairPoints = (*it).first;
        route = (*it).second;
        if (pairPoints.first == s && route != NULL)
        {
            voisin = pairPoints.second;
            type = route->getType();
            if (!dfsPoint.count(voisin) && comparaisonRoute(typeRoute,route->getType())) // le tas ne possède pas déjà le voisin
            {
                dfsRoute.insert(route);
                subDFS(voisin, typeRoute);
            }
        }
    }
}
bool Graph::comparaisonRoute(std::string typeCherche, std::string typeDonne)
{
    bool b = false;
    if (typeCherche == typeDonne)
        b =  true;
    else
    {
        if (typeCherche != "B" && typeCherche != "V" && typeCherche != "R" && typeCherche != "N")
        {
            b =  false;
        }
        else
        {
            if (typeCherche == "V")
                b =  false;
            else if (typeCherche == "B" && typeDonne != "V")
                b =  false;
            else if (typeCherche == "R" && (typeDonne != "B" && typeCherche != "V"))
                     b =  false;
            else if ((typeCherche == "N" && (typeDonne != "R" & typeDonne != "B" && typeCherche != "V")))
                b =  false;
            else
                b =  true;
        }
    }
    return b;

}

bool Graph::verifierMarquage(std::map<Point*, bool> marquage)
{
    bool b = true;
    std::map<Point*, bool>::const_iterator it;
    for (it=marquage.begin();it != marquage.end();it++)
    {
        if (!(*it).second)
        {
            b = false;
            break;
        }
    }
    return b;
}
