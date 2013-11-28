#ifndef ROUTE_H
#define ROUTE_H
#include <string>
#include "point.h"
class Route
{
private:
    std::string type;
    std::string name;
    Point* starting;
    Point* arrival;
    float value=0;
public:
    Route(std::string n, std::string t, Point* s, Point* a);
    ~Route();
    std::string getType();
    std::string getName();
    Point* getStarting();
    Point* getArrival();
    void toCout();
    float getValue();
};

#endif // ROUTE_H
