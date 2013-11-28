#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <string>
#include <point.h>
#include <stack>
#include "route.h"
class Graph
{
private:
    std::map<int, Point*> listPoint;
    std::map<std::pair<Point*,Point*> , Route*> listRoute;

    std::map<std::pair<Point*,Point*>, Point*> next;
    std::map<std::pair<Point*,Point*>, float> dist;

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
    ~Graph();
};

#endif // GRAPH_H
