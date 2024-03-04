//
// Created by Lara Bastos on 24/05/2023.
//

#include <limits>
#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <set>
#include "ManageNetwork.h"


void ManageNetwork::tspBacktrack(Graph& graph, std::vector<int>& path,  double currentCost, double& minCost, int currentVertex, std::vector<std::pair<std::vector<int>,double>>& paths) {

    //check if all cities where visited already
    if (path.size() == graph.getVertexSet().size()) {
        double finalCost;
        for (auto adj : graph.findVertex(currentVertex)->getAdj()){
            if (adj->getDest()->getId()==0){
             finalCost = currentCost + adj->getDist();
                if (finalCost < minCost) {
                    minCost = finalCost;
                }

                paths.push_back(make_pair(path,finalCost));
            }
        }


        return;
    }

    for (auto edge : graph.findVertex(currentVertex)->getAdj()) {
        int nextVertex = edge->getDest()->getId();

        if (!edge->getDest()->isVisited()) {
            double edgeWeight = edge->getDist();
            double newCost = currentCost + edgeWeight;

            if (newCost < minCost) {

                    path.push_back(nextVertex);
                    edge->getDest()->setVisited(true);

                    tspBacktrack(graph, path, newCost, minCost, nextVertex,paths);

                    path.pop_back();
                    edge->getDest()->setVisited(false);

            }
        }
    }
}


std::vector<std::pair<std::vector<int>,double>> ManageNetwork::backtrackboundingTSP() {
    Graph graph=ReadFiles::graph;
    std::vector<int> path;
    for (auto vertexPair:graph.getVertexSet()){
        vertexPair.second->setVisited(false);
    }
    double currentCost = 0.0;
    double minCost = std::numeric_limits<double>::max();

    path.push_back(0); // Starting from node with id=0
    graph.findVertex(0)->setVisited(true);


    std::vector<std::pair<std::vector<int>,double>> paths;
    std::vector<std::pair<std::vector<int>,double>> mincostpaths;


    tspBacktrack(graph, path, currentCost, minCost, 0, paths);
    std::sort(paths.begin(),paths.end(),cmp);


   double min = paths.at(0).second;

    for (auto path:paths){
        if (path.second==min){
            mincostpaths.push_back(path);
        }
        else {
            break;
        }
    }

    return mincostpaths;

}


bool ManageNetwork::cmp(std::pair<std::vector<int>,double> v1, std::pair<std::vector<int>,double> v2){

    return v1.second<v2.second;
}

std::pair<std::vector<int>,double> ManageNetwork::preOrderMST() {
    std::vector<int> preorder;
    double cost=0;
    int lastid;
    std::stack<Vertex*> stack;
    stack.push(ReadFiles::graph.findVertex(0));
    Graph debug = ReadFiles::graph;
    bool child;
    while (!stack.empty()) {
        Vertex* current = stack.top();
        stack.pop();
        preorder.push_back(current->getId());
        lastid=current->getId();
        child=true;
        for (auto vertexPair : ReadFiles::graph.getVertexSet() ) {
            if (vertexPair.second->getId()!=0 && vertexPair.second->getId()!=lastid){
                if (vertexPair.second->getPath()->getOrig()->getId()==current->getId()){
                    cost+=getDist(vertexPair.second->getId(),current->getId());
                    stack.push(vertexPair.second);
                    child=false;
                }
            }
        }
        if (child && !stack.empty())  cost+=getDist(current->getId(),stack.top()->getId());;
    }

    preorder.push_back(0);
    for (auto vertexPair : ReadFiles::graph.getVertexSet()){
        if (vertexPair.second->getId()==lastid){
            cost+=getDist(0,vertexPair.second->getId() );

        }
    }

    return std::make_pair(preorder,cost);
}

std::pair<std::vector<int>,double> ManageNetwork::TSPHeuristicAproximation() {

    Prim();
    std::pair<std::vector<int>,double> path = preOrderMST();


    return path;
}

std::set<Edge *> ManageNetwork::Prim() {
    if (ReadFiles::graph.getVertexSet().empty()) {
        return {};
    }
    std::set<Edge*> mst;
    for(auto vertex : ReadFiles::graph.getVertexSet()) {
        vertex.second->setDist(std::numeric_limits<double>::max());
        vertex.second->setPath(nullptr);
        vertex.second->setVisited(false);
    }
    Graph a=ReadFiles::graph;
    // start with an arbitrary vertex
    Vertex* root = ReadFiles::graph.getVertexSet().begin()->second;
    root->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(root);
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getDist() < oldDist) {
                    w->setDist(e->getDist());
                    w->setPath(e);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
        if (v->getPath() != nullptr){
            mst.insert(v->getPath());
            v->getPath()->getDest()->incrementmstdegree();
            v->getPath()->getOrig()->incrementmstdegree();
        }


    }

    return mst;
}


double ManageNetwork::getDist(int a,int b){
    for (auto edge:ReadFiles::graph.findVertex(a)->getAdj()){
        if (edge->getDest()->getId()==b) return edge->getDist();
    }

    return haversineDistance(ReadFiles::graph.findVertex(a)->getLat(),ReadFiles::graph.findVertex(a)->getLon(),ReadFiles::graph.findVertex(b)->getLat(),ReadFiles::graph.findVertex(b)->getLon());

}

constexpr double kEarthRadiusKm = 6371.0;

double ManageNetwork::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double ManageNetwork::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = degreesToRadians(lat2 - lat1);
    double dLon = degreesToRadians(lon2 - lon1);

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(degreesToRadians(lat1)) * std::cos(degreesToRadians(lat2)) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return kEarthRadiusKm * c;
}

std::set<Edge*> ManageNetwork::minimumWeightPerfectMatching(const std::vector<Vertex*>& vertices) {
    std::set<Edge*> matching;
    std::vector<bool> matched(vertices.size(), false);

    /*for (Vertex* vertex : vertices){
        for (auto a:vertex->getAdj()){
            if (std::find(vertices.begin(),vertices.end(), a->getDest())==vertices.end()){
                bool isinvert=false;
                while (!isinvert){

                }
            }
        }
    }*/

    for (Vertex* vertex : vertices) {
        if (!matched[vertex->getId()]) {
            double minDist = std::numeric_limits<double>::max();
            Edge* minEdge = nullptr;

            for (Edge* edge : vertex->getAdj()) {
                Vertex* dest = edge->getDest();
                if (!matched[dest->getId()] && edge->getDist() < minDist && std::find(vertices.begin(),vertices.end(),edge->getDest())!=vertices.end()) {
                    minDist = edge->getDist();
                    minEdge = edge;
                }
            }

            if (minEdge != nullptr) {
                matched[vertex->getId()] = true;
                matched[minEdge->getDest()->getId()] = true;
                matching.insert(minEdge);
            }
        }
    }

    return matching;
}


// Construct the approximate TSP tour using the Christofides algorithm
std::vector<Vertex*> ManageNetwork::christofidesAlgorithm() {
    Graph graph=ReadFiles::graph;
    std::map<int,Vertex*> vertexSet = ReadFiles::graph.getVertexSet();

    // Step 1: Compute the minimum spanning tree
    std::set<Edge*> mst = Prim();
    // Step 2: Find vertices with odd degrees in the MST
    std::vector<Vertex*> oddVertices;

    for (Edge* edge : mst) {
        if (edge->getDest()->getmstdegree()%2==1 && (std::find(oddVertices.begin(),oddVertices.end(),edge->getDest())==oddVertices.end())){
            oddVertices.push_back(edge->getDest());
        }
        if ((edge->getOrig()->getmstdegree()%2==1) && (std::find(oddVertices.begin(),oddVertices.end(),edge->getOrig())==oddVertices.end())){
            oddVertices.push_back(edge->getOrig());
        }
    }

    //nenhum é impar

    // Step 3: Find a minimum weight perfect matching on the odd degree vertices
    std::set<Edge*> matching = minimumWeightPerfectMatching(oddVertices);

    // Combine the edges from the MST and the matching to form a multigraph
    std::set<Edge*> multigraph;
    for (auto edge:mst){
        if (multigraph.find(edge)==multigraph.end()){
            multigraph.insert(edge);
            multigraph.insert(edge->getDest()->addEdge(edge->getOrig(),edge->getDist()));
        }
    }
    bool reverse=false;
    for (auto edge:matching){
        if (multigraph.find(edge)==multigraph.end()){
            multigraph.insert(edge);
            multigraph.insert(edge->getDest()->addEdge(edge->getOrig(),edge->getDist()));
        }
    }
    //multigraph.insert(matching.begin(), matching.end());

    // Step 4: Find an Eulerian circuit in the multigraph
    std::vector<Vertex*> circuit;
    Vertex* start = vertexSet[0];


    //erro:
    while (!multigraph.empty()) {
        Vertex* current = start;
        Vertex* next = nullptr;

        do {
            circuit.push_back(current);
            Edge* edge = nullptr;

            for (Edge* e : current->getAdj()) {
                if (multigraph.find(e) != multigraph.end()) {
                    edge = e;
                    break;
                }
            }

            if (edge != nullptr) {
                for (auto edge2: edge->getDest()->getAdj()){
                    if (edge2->getDest()==edge->getOrig()){
                        multigraph.erase(edge2);
                    }
                }
                next = edge->getDest();
                multigraph.erase(edge);
            } else {
                next = nullptr;
            }

            current = next;
        } while (next != start && current!= nullptr );
    }

    // Step 5: Remove repeated vertices from the circuit to obtain the final TSP tour
    std::vector<Vertex*> tspTour;
    std::set<Vertex*> visited;

    for (Vertex* vertex : circuit) {
        if (visited.find(vertex) == visited.end()) {
            tspTour.push_back(vertex);
            visited.insert(vertex);
        }
    }

    return tspTour;
}
