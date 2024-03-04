//
// Created by ritag on 05/05/2023.
//

#include <string>
#include "Graph.h"
#include <map>

#include "ReadFiles.h"


Graph::Graph() {
    vertexSet={};
}
/*void Graph::restoreGraph(Graph a){
    vertexSet={};
    for (auto a:a.vertexSet){
        std::string id=a->getId();
        addVertex(id);
    }
    for (auto a:a.vertexSet){
        std::string id=a->getId();
        auto vertex= findVertex(id);
        for (auto adj:a->getAdj()){
            std::string id2=adj->getDest()->getId();
            int w=adj->getCapacity();
            std::string service=adj->getService();
            vertex->addEdge(findVertex(id2),w,service);
        }
    }
}*/

std::map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Vertex* Graph::findVertex(const int id) const {
    auto it = vertexSet.find(id);
    if (it != vertexSet.end())
        return it->second;
    return nullptr;
}


bool Graph::addVertex(int id, std::string lon, std::string lat) {
    vertexSet[id] = new Vertex(id, lon, lat);
    return true;
}

bool Graph::addVertex(int id) {
    vertexSet[id] = new Vertex(id);
    return true;
}


bool Graph::addEdge(const int source, const int dest, double dist) {
    auto v1 = vertexSet[source];
    auto v2 = vertexSet[dest];
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, dist);
    return true;
}

bool Graph::removeVertex(const int id) {
    auto it = vertexSet.find(id);
    if (it == vertexSet.end()) {
        return false;
    }
    Vertex* v = it->second;
    for (auto e : v->getAdj()) {
        v->removeEdge(e->getDest()->getId());
    }
    for (auto u : v->getIncoming()) {
        u->getOrig()->removeEdge(v->getId());
    }
    delete v;
    vertexSet.erase(it);
    return true;
}