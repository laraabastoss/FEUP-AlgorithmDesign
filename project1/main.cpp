//
// Created by ritag on 05/05/2023.
//

#include <iostream>
#include "ReadFiles.h"
#include "ManageNetwork.h"

using namespace std;
int main(){

    //ReadFiles::readNodesRealWorldGraphs(3);
    ReadFiles::readToyGraphs(2);
    //Graph g=ReadFiles::graph;
    std::vector<Vertex*> a= ManageNetwork::christofidesAlgorithm();
    std::cout<<a.size();

    //std::vector<std::pair<std::vector<int>,double>> a = ManageNetwork::backtrackboundingTSP(g);
    //std::pair<std::vector<int>,double> tspPath = ManageNetwork::TSPHeuristicAproximation();
    int total_edges = 0;
    /*for (const auto& vertexPair : g.getVertexSet()) {
        int nodeId = vertexPair.first;
        Vertex* vertex = vertexPair.second;
        total_edges+=vertex->getAdj().size();
    }*/
    cout << "nº edges" << total_edges << endl;
    /*ReadFiles::readToyGraphs(2);
    //ReadFiles::readEdgesRealWorldGraphs(1);
    Graph& g=ReadFiles::graph;
    std::cout<<g.getVertexSet().size();
    std::vector<Vertex*> a= ManageNetwork::christofidesAlgorithm();
    for(auto v:a){
        cout<<v->getId();
    }*/
   /*std::vector<std::pair<std::vector<int>,double>> a = ManageNetwork::backtrackboundingTSP(g);
    std::pair<std::vector<int>,double> tspPath = ManageNetwork::TSPHeuristicAproximation();*/

    return 0;
};