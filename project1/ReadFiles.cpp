//
// Created by ritag on 05/05/2023.
//



#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "ReadFiles.h"
#include "VertexEdge.h"


/*Real Life Graphs*/


Graph ReadFiles::graph;
Graph ReadFiles::subgraph1;
Graph ReadFiles::subgraph2;

double strtod(std::basic_string<char, std::char_traits<char>, std::allocator<char>> basicString);

int ReadFiles::readNodesRealWorldGraphs(int fileName) {
    std::string directory = "../Project2Data/Real-World-Graphs/";
    if (fileName==1){
        directory = "../Project2Data/Real-World-Graphs/graph1/nodes.csv";
    }
    else if (fileName==2) {
        directory = "../Project2Data/Real-World-Graphs/graph2/nodes.csv";;
    }
    else if (fileName==3) {
        directory = "../Project2Data/Real-World-Graphs/graph3/nodes.csv";;
    }

    std::ifstream file(directory);
    if (file.fail()) {
        return 1;
    }
    std::string line;
    std::getline(file, line); // skip first line
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> parameters;
        while (std::getline(iss, word, ',')) {
            parameters.push_back(word);
        }

        graph.addVertex(stoi(parameters[0]), parameters[1],parameters[2]);

        parameters.clear();
    }
    file.close();
    Graph a=graph;
    return 0;
}

int ReadFiles::readEdgesRealWorldGraphs(int fileName) {
    std::string directory = "../Project2Data/Real-World-Graphs/";
    if (fileName==1){
        directory = "../Project2Data/Real-World-Graphs/graph1/edges.csv";
    }
    else if (fileName==2) {
        directory = "../Project2Data/Real-World-Graphs/graph2/edges.csv";;
    }
    else if (fileName==3) {
        directory = "../Project2Data/Real-World-Graphs/graph3/edges.csv";;
    }


    std::ifstream file(directory);
    if (file.fail()) {
        return 1;
    }
    std::string line;
    std::getline(file, line); // skip first line

    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> parameters;
        while (std::getline(iss, word, ',')) {
            parameters.push_back(word);
        }
        graph.addEdge(stoi(parameters[0]),stoi(parameters[1]), stod(parameters[2]));
    }

    file.close();
    Graph a=graph;
    return 0;
}

int ReadFiles::readToyGraphs(int fileName)  {
    std::string directory = "../Project2Data/Toy-Graphs/";
    if (fileName==1){
        directory = "../Project2Data/Toy-Graphs/tourism.csv";
    }
    else if (fileName==2) {
        directory = "../Project2Data/Toy-Graphs/stadiums.csv";;
    }
    else if (fileName==3) {
        directory = "../Project2Data/Toy-Graphs/shipping.csv";;
    }

    std::ifstream file(directory);
    if (file.fail()) {
        return 1;
    }
    std::string line;
    std::getline(file, line); // skip first line
    while(std::getline(file, line)){
        std::istringstream iss(line);
        std::string word;
        std::vector<std::string> parameters;
        while (std::getline(iss, word, ',')) {
            parameters.push_back(word);
        }
        if (!graph.findVertex(stoi(parameters[0]))) {
            graph.addVertex(stoi(parameters[0]));
        }
        if (!graph.findVertex(stoi(parameters[1]))){
            graph.addVertex(stoi(parameters[1]));
        }
        graph.addEdge(stoi(parameters[0]),stoi(parameters[1]), stod(parameters[2]));
        graph.addEdge(stoi(parameters[1]),stoi(parameters[0]), stod(parameters[2]));
        parameters.clear();
    };
    file.close();
    return 0;
}



