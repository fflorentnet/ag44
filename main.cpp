#include <iostream>
#include <time.h>
#include "parser.h"
using namespace std;

int main()
{
    Graph* g;
    Parser p("dataski.txt");
    g = p.getGraph();

    g->FWarshall();
    do
    {
        std::cout << "Entrez deux points:" << endl;
        std::string point1 = "";
        std::cout << "Premier point: \t";
        std::cin >> point1;
        std::string point2 = "";
        std::cout << "Second point: \t";
        std::cin >> point2;

        Point* src = g->getPoint(point1);
        Point* dst = g->getPoint(point2);
        std::cout << "Source:" << point1 << endl;
        std::cout << "Destination:" << point2 << endl;

    if (src != NULL && dst != NULL)
    {


        std::cout << src->getNom() << g->getPath(src,dst) << dst->getNom() << endl;
        std::stack<Route*> fw = g->pileRoute;
        std::cout << "Floyd-Warshall:" << endl;
        float total=0;
        while (!fw.empty())
        {
            Route* temp = fw.top();
            temp->toCout();
            total+=temp->getValue();
            fw.pop();
        }
        std::cout << "Temps total: " << total << "min" << endl;
        do
        {
            g->pileRoute.pop();
        }while(!g->pileRoute.empty());

        std::cout << endl << "Dijkstra:" << endl;
        std::stack<Route*> dij = g->Dijkstra(src,dst);
        total=0;
        while (!dij.empty())
        {
            Route* temp = dij.top();
            temp->toCout();
            total+=temp->getValue();
            dij.pop();
        }
        std::cout << "Temps total: " << total << "min" << endl;
    }
    }while(true);
    return 0;
}

