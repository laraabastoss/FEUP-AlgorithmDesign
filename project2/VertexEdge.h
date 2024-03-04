//
// Created by ritag on 05/05/2023.
//

#ifndef DA_PROJ2_VERTEXEDGE_H
#define DA_PROJ2_VERTEXEDGE_H

#include <string>
#include <vector>
#include "MutablePriorityQueue.h"

class Edge;


class Vertex {
public:
    Vertex(int id, std::string lon, std::string lat);
    Vertex(int id);
    bool operator<(Vertex & vertex) const;
    int getId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    std::vector<Edge *> getIncoming() const;
    double getDist() const;
    Edge *getPath() const;
    double getLat() const;
    double getLon() const;
    void setVisited(bool visited);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(int destID);
    void setDist(double dist);
    void setPath(Edge *path);
    void incrementmstdegree();
    int getmstdegree();
    friend class MutablePriorityQueue<Vertex>;

protected:
    int id;
    int mstdegree = 0;
    double lon;
    double lat;
    std::vector<Edge *> adj;
    bool visited = false;
    std::vector<Edge *> incoming;
    double dist = 0;
    Edge *path = nullptr;
    int queueIndex = 0;
};

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double dist);
    Vertex * getDest() const;
    Vertex * getOrig() const;
    double getDist() const;
protected:
    Vertex * dest;
    Vertex *orig;
    double dist;
};


#endif //DA_PROJ2_VERTEXEDGE_H
