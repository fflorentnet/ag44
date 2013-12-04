#include "point.h"
#include <limits>
#include <iostream>
#include <stdlib.h>
/*Point::Point()
{
}
*/

std::string Point::getNom() { return nom; }
int Point::get_Altitude() { return altitude; }

void Point::addVoisin(Point* p, float value)
{
    voisins[p]=value;
}
float Point::getValue(Point* p)
{
    float temp = std::numeric_limits<float>::infinity();
    if (voisins[p])
        temp = voisins[p];
    if (nom == p->getNom())
        temp = 0;
    return temp;
}
