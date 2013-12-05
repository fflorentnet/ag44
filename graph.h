#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <string>
#include <point.h>
#include <stack>
#include <queue>
#include <set>
#include "route.h"
class Graph
{
private:
    std::set<Point*> dfsPoint;
    std::queue<Route*> dfsRoute;

    std::map<int, Point*> listPoint;
    std::map<std::pair<Point*,Point*> , Route*> listRoute;

    std::map<std::pair<Point*,Point*>, Point*> next;
    std::map<std::pair<Point*,Point*>, float> dist;

    bool comparaisonRoute(std::string typeCherche, std::string typeDonne);

public:
    std::stack<Route*> pileRoute;
    Graph();
    void addPoint(int num, std::string name, Point *p);
    void addRoute(Route* r);
    Point* getPoint(int num);
    Point* getPoint(std::string n);
    Route* getRoute(Point* p1, Point* p2);
    std::stack<Route*> Dijkstra(Point* source, Point* dest);
    void FWarshall();
    std::string getPath(Point* i, Point* j);
    bool verifierMarquage(std::map<Point*, bool> marquage);

    void DFS(Point* s, std::string typeRoute, bool test);
    void subDFS(Point* s, std::string typeRoute, bool test);
    ~Graph();

    void getPoints();
    void getRoutes();
};

#endif // GRAPH_H
