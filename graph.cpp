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
void Graph::addPoint(int num, std::string name, Point *p)
{
    listPoint[num]=p;
    std::cout << "Point " << num << " ajouté [" << p->getNom() <<"] (" << p->get_Altitude() << "m)" <<endl;
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


    std::map<std::pair<Point*, Point*>, float>::const_iterator itDist;

    Point* i;
    Point* j;
    Point* k;

    for(itTemp = listPoint.begin(); itTemp != listPoint.end(); itTemp++)
    {
        i = (*itTemp).second;
        for(itTempp = listPoint.begin(); itTempp != listPoint.end(); itTempp++)
        {
            j = (*itTempp).second;
            dist[std::make_pair(i,j)] = i->getValue(j);
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
