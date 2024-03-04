//
// Created by Lara Bastos on 24/05/2023.
//

#ifndef DA_PROJ2_MANAGENETWORK_H
#define DA_PROJ2_MANAGENETWORK_H
#include "ReadFiles.h"
#include "MutablePriorityQueue.h"
#include <stack>
#include "set"
#include <cmath>


class ManageNetwork {
public:

    static std::vector<std::pair<std::vector<int>,double>> backtrackboundingTSP();
    static void tspBacktrack(Graph& graph, std::vector<int>& path,  double currentCost, double& minCost, int currentVertex, std::vector<std::pair<std::vector<int>,double>>& paths);
    static bool cmp(std::pair<std::vector<int>,double> v1, std::pair<std::vector<int>,double> v2);
    static std::pair<std::vector<int>,double> preOrderMST();
    static std::pair<std::vector<int>,double> TSPHeuristicAproximation();
    static std::set<Edge*> Prim();
    static double getDist(int a,int b);
    static double haversineDistance(double lat1, double lon1, double lat2, double lon2);
    static double degreesToRadians(double degrees);
    static std::set<Edge*> minimumWeightPerfectMatching(const std::vector<Vertex*>& vertices);
    static std::vector<Vertex*> christofidesAlgorithm();

};


#endif //DA_PROJ2_MANAGENETWORK_H
