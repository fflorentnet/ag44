#ifndef POINT_H
#define POINT_H
#include <string>
#include <map>
class Point
{
private:
    std::string nom;
    int altitude;
    std::map<Point*, float> voisins;
public:
    Point(std::string n, int alt): nom(n), altitude(alt){};
    std::string getNom();
    int get_Altitude();
    void addVoisin(Point* p, float value);
    float getValue(Point* p);

};

#endif // POINT_H
