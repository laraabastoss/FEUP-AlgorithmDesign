//
// Created by ritag on 05/05/2023.
//

#ifndef DA_PROJ2_READFILES_H
#define DA_PROJ2_READFILES_H


#include "Graph.h"

class ReadFiles {
public:
    static int readNodesRealWorldGraphs(int fileName);
    static int readEdgesRealWorldGraphs(int fileName);
    static int readToyGraphs(int fileName);

    static std::vector<Graph> realWorldGraphs;
    static std::vector<Graph> ToyGraphs;
    static Graph graph;
    static Graph subgraph1;
    static Graph subgraph2;
    friend class ManageNetwork;
    friend class Graph;

};


#endif //DA_PROJ2_READFILES_H
