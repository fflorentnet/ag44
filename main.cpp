#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "parser.h"
using namespace std;

void fwarshall(Graph* g)
{
    std::cout << "Entrez deux points:" << endl;
    std::string point1 = "villaroger";
    std::cout << "Premier point: \t";
    std::cin >> point1;
    std::string point2 = "33";
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
    }
    if (src == NULL)
    {
        std::cout << "Le point " << point1 << " n'existe pas." << endl;
    }
    if (dst == NULL)
    {
        std::cout << "Le point " << point2 << " n'existe pas." << endl;
    }
}
void dijkstra(Graph* g)
{
    int total;
    std::cout << "Entrez deux points:" << endl;
    std::string point1 = "villaroger";
    std::cout << "Premier point: \t";
    std::cin >> point1;
    std::string point2 = "33";
    std::cout << "Second point: \t";
    std::cin >> point2;

    Point* src = g->getPoint(point1);
    Point* dst = g->getPoint(point2);
    std::cout << "Source:" << point1 << endl;
    std::cout << "Destination:" << point2 << endl;

    if (src != NULL && dst != NULL)
    {
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
    if (src == NULL)
    {
        std::cout << "Le point " << point1 << " n'existe pas." << endl;
    }
    if (dst == NULL)
    {
        std::cout << "Le point " << point2 << " n'existe pas." << endl;
    }

}
void dfs(Graph* g)
{
    g->getPoints();
    std::cout << "Entrez le sommet de départ et le type de route:" << endl;
    std::string point1 = "villaroger";
    std::cout << "Depart: \t";
    std::cin >> point1;
    std::string type = "33";
    std::cout << "Type de route: \t";
    std::cin >> type;
    std::cout << "Quel type de comparaison voulez-vous utiliser ?" <<endl;
    std::cout << "1. typeCherche == typeRoute ?" << endl;
    std::cout << "2. typeCherche >= typeRoute ? (N > R > B > V)" << endl;
    std::string test = "1";
    std::cin >> test;
    bool testDFS = true;
    if (atoi(test.c_str()) == 1)
        testDFS = false;
    else
        testDFS = true;
    Point* src = g->getPoint(point1);
    std::cout << "Source:" << point1 << endl;
    std::cout << "Type:" << type << endl;

    if (src != NULL && type != "")
    {
        g->DFS(src,type, testDFS);
    }
    if (src == NULL)
    {
        std::cout << "Le point " << point1 << " n'existe pas." << endl;
    }
}

void menu(Graph* g)
{
    bool b=true;
    std::string menu = "";
    do
    {
        std::cout << endl << endl << endl;
        std::cout << "Menu" << endl << "-------" << endl;
        std::cout << "1 - Afficher les routes" << endl;
        std::cout << "2 - Afficher les noeuds" << endl;
        std::cout << "3 - Floyd-Warshal [deux noeuds]" << endl;
        std::cout << "4 - Dijkstra [deux noeuds]" << endl;
        std::cout << "5 - Noeuds accessibles à partir d'un noeud source et un type de piste"<< endl;
        std::cout << "6 - Charger un autre graphe" << endl;
        std::cout << "7 - Quitter le programme" << endl;
        std::cin >> menu;

        std::cout << endl << endl << endl;
        switch(atoi(menu.c_str()))
        {
        case 1: std::cout <<"Affichage des routes" << endl << "-------" << endl; g->getRoutes();  break;
        case 2: std::cout <<"Affichage des points" << endl << "-------" <<endl; g->getPoints(); break;
        case 3: fwarshall(g); break;
        case 4: dijkstra(g); break;
        case 5: dfs(g); break;
        case 6: delete g; b=false; break;
        case 7: delete g;
            exit(EXIT_SUCCESS); break;
        default: break;
        }
    }while(b);
}

int main()
{
    do
    {
        std::string filename = "dataski.txt";
        Graph* g;
        std::cout << "Entrez un nom de fichier [dataski.txt] :" << endl;
        std::cin >> filename;
        Parser p(filename);
        g = p.getGraph();
        g->FWarshall();
        menu(g);
    }while(true);
    return 0;
}

