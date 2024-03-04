//
// Created by ritag on 05/05/2023.
//

#ifndef DA_PROJ2_GRAPH_H
#define DA_PROJ2_GRAPH_H


#include "VertexEdge.h"
#include <map>

class Graph {
public:
    Graph();
    void restoreGraph(Graph a);
    Vertex *findVertex(const int id) const;
    bool addVertex(int id,std::string longitutde, std::string latitude);
    bool addVertex(int id);
    bool addEdge(const int orig, const int dest, double dist);
    std::map<int, Vertex *> getVertexSet() const;
    bool removeVertex(const int id);
protected:
    std::map<int, Vertex *> vertexSet;// vertex set
};


#endif //DA_PROJ2_GRAPH_H
