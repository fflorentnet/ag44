#ifndef PARSER_H
#define PARSER_H
#include<string>
#include <iostream>
#include "graph.h"
class Parser
{
private:
    Graph* g;
    std::string split(std::string chaine, char joker, int p);
public:
    Parser(std::string fileName);
    Graph* getGraph();
};

#endif // PARSER_H
