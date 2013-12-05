#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "route.h"

/*Route::Route()
{
}

enum _type { TK, TS, TSD, TC, BU, V, B, R, N, KL, SURF };
*/
Route::Route(std::string n, std::string t, Point* s, Point* a): name(n), starting(s), arrival(a), type(t){
    if (type == "V")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(5.0/100.0);
    if (type == "B")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(4.0/100.0);
    if (type == "R")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(3.0/100.0);
    if (type == "N")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(2.0/100.0);
    if (type == "KL")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(1.0/100.0)*(10.0/60.0);
    if (type == "SURF")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(10.0/100.0);
    if (type == "TPH")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(2.0/100.0)+4.0;
    if (type == "TC")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(3.0/100.0)+2.0;
    if (type == "TSD")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(3.0/100.0)+1.0;
    if (type == "TS")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(4.0/100.0)+1.0;
    if (type == "TK")
        value = abs((s->get_Altitude()-a->get_Altitude()))*(4.0/100.0)+1.0;
    if (type == "BUS")
    {
        //arc2000 -> arc1600
        if (s->getNom() == "arc2000" && a->getNom()=="arc1600")
            value=40;
        //arc1600 -> arc2000
        if (s->getNom() == "arc1600" && a->getNom()=="arc2000")
            value=40;
        //arc1600 -> arc1800
        if (s->getNom() == "arc1600" && a->getNom() == "arc1800")
            value=30;
        //arc1800 -> arc1600
        if (s->getNom() == "arc1800" && a->getNom() == "arc1600")
            value=30;
    }
}

std::string Route::getType() { return type; }
std::string Route::getName() { return name; }
Point* Route::getStarting() { return starting; }
Point* Route::getArrival() { return arrival; }
float Route::getValue() { return value; }
void Route::toCout()
{
    std::cout << "Route [" + getName() << "] (" << getType() << ") {" << getStarting()->getNom() << "," << getArrival()->getNom() << "} - " << getValue() << "min \n";
}
