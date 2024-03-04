//
// Created by ritag on 05/05/2023.
//

#include "VertexEdge.h"

Vertex::Vertex(int id, std::string lon, std::string lat){
    this->id=id;
    this->lat=stod(lat);
    this->lon=stod(lon);
}

Vertex::Vertex(int id){
    this->id=id;
}

Edge * Vertex::addEdge(Vertex *d, double dist) {
    auto newEdge = new Edge(this, d, dist);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

double Vertex::getLat() const{
    return this->lat;
}

double Vertex::getLon() const{
    return this->lon;
}

bool Vertex::isVisited() const {
    return this->visited;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}


void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

void Vertex::incrementmstdegree(){
    this->mstdegree=mstdegree+1;
}

int Vertex::getmstdegree(){
    return mstdegree;
}




/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double dist): orig(orig), dest(dest), dist(dist) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

double Edge::getDist() const {
    return this->dist;
}



