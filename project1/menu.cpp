//
// Created by ritag on 29/05/2023.
//

#include <iostream>
#include <string>
#include "menu.h"
#include "ManageNetwork.h"
#include "ReadFiles.h"

using namespace std;

void menu::start() {
    vector<pair<bool,int>> allowed_algorithms={{false,0},{false,0},{false,0}}; //backtracking, triangular, christofides
    cout<<"Traveling Salesman Problem"<<"\n"<<
          "Which graph do you want to read?"<<"\n"<<
          "1. Real - World - Graphs"<<"\n"<<
          "2. Toy - Graphs"<<"\n"<<
          "3.Fully - Conected - Graphs"<<"\n";

    string graph_group;
    cout<<"Option:";
    int option;
    getline(cin,graph_group);
    bool getinput = true;
    while (getinput) {
        getinput = false;
        try {
            option = stoi(graph_group);
        }
        catch (exception &err) {
            cout << "Invalid Input! It must be a number!";
            getline(cin, graph_group);
            getinput = true;
        }
    }
    string graph;
    int graph_option;
    bool getgraph = true;
    switch (option) {
        case 1:
            cout<<"Choose the graph"<<"\n"<<"1. Graph 1"<<"\n"<<"2. Graph 2"<<"\n"<<"3. Graph 3";
            cout<<"Option:";
            getline(cin,graph);
            while (getgraph) {
                getgraph= false;
                try {
                    graph_option = stoi(graph);
                }
                catch (exception &err) {
                    cout << "Invalid Input! It must be a number!";
                    getline(cin, graph);
                    getgraph = true;
                }
            }
            ReadFiles::readNodesRealWorldGraphs(graph_option);
            ReadFiles::readEdgesRealWorldGraphs(graph_option);
            allowed_algorithms={{false,0},{true,0},{true,0}};
            cout <<"Data read succeessfully"<<"\n";
            TSP(allowed_algorithms);
            break;
        case 2:
            cout<<"Choose the graph"<<"\n"<<"1. Tourism"<<"\n"<<"2. Stadium"<<"\n"<<"3. Shipping";
            cout<<"Option:";
            getline(cin,graph);
            while (getgraph) {
                getgraph = false;
                try {
                    graph_option = stoi(graph);
                }
                catch (exception &err) {
                    cout << "Invalid Input! It must be a number!";
                    getline(cin, graph);
                    getgraph = true;
                }
            }
            ReadFiles::readToyGraphs(graph_option);
            if(graph_option==3) allowed_algorithms={{true,0},{true,0},{false,0}};
            else allowed_algorithms={{true,0},{true,0},{true,0}};
            cout <<"Data read succeessfully"<<"\n";
            TSP(allowed_algorithms);
            break;
        /*Case 3 Fully-Connected"*/
    }

}

void menu::TSP(vector<pair<bool,int>>allowed_algorithms){
    cout<<"Which algorithm do you want to use?"<<"\n";
    int indice=1;
    if(allowed_algorithms[0].first==true) {
        cout<<to_string(indice)<<". Backtraking and bounding"<<"\n";
        indice++;
    }
    if(allowed_algorithms[1].first==true) {
        cout<<to_string(indice)<<". Triangular approximation"<<"\n";
        indice++;
    }
    if(allowed_algorithms[2].first==true) {
        cout<<to_string(indice)<<". Heuristic - Christofides n"<<"\n";
    }
    string algorithm;
    cout<<"Option:";
    int algorithm_option;
    getline(cin,algorithm);
    bool getinput = true;
    while (getinput) {
        getinput = false;
        try {
            algorithm_option = stoi(algorithm);
        }
        catch (exception &err) {
            cout << "Invalid Input!";
            getline(cin, algorithm);
            getinput = true;
        }
        if(algorithm_option<1 || algorithm_option>3){
            cout << "Invalid Input!";
            getinput=true;
        }
    }
    for( int i=0;i<=2;i++){
        if(allowed_algorithms[i].first==algorithm_option){
            if(i==0){
                ManageNetwork::backtrackboundingTSP();
                allowed_algorithms[0].first=false;
            }
            else if(i==1){
                ManageNetwork::TSPHeuristicAproximation();
                allowed_algorithms[1].first=false;
            }
            else if(i==2){
                ManageNetwork::christofidesAlgorithm();
                allowed_algorithms[2].first=false;
            }

        }
    }
    bool repeat=true;
    while(repeat) {
        cout << "Want to compare the result with result of another algorithm? (Y/N)";
        string answer;
        getline(cin, answer);
        if (answer == "Y") {
            cout << "Which algorithm do you want to compare to?";
            int indice = 1;
            if (allowed_algorithms[0].first == true) {
                cout << to_string(indice) << ". Backtraking and bounding" << "\n";
                indice++;
            }
            if (allowed_algorithms[1].first == true) {
                cout << to_string(indice) << ". Triangular approximation" << "\n";
                indice++;
            }
            if (allowed_algorithms[2].first == true) {
                cout << to_string(indice) << ". Heuristic - Christofides n" << "\n";
                indice++;
            }

            string algorithm;
            cout << "Option:";
            int algorithm_option;
            getline(cin, algorithm);
            bool getinput = true;
            while (getinput) {
                getinput = false;
                try {
                    algorithm_option = stoi(algorithm);
                }
                catch (exception &err) {
                    cout << "Invalid Input!";
                    getline(cin, algorithm);
                    getinput = true;
                }
                if (algorithm_option < 1 || algorithm_option > 3) {
                    cout << "Invalid Input!";
                    getinput = true;
                }
            }
            for (int i = 0; i <= 2; i++) {
                if (allowed_algorithms[i].first == algorithm_option) {
                    if (i == 0) {
                        ManageNetwork::backtrackboundingTSP();
                        allowed_algorithms[0].first = false;
                    } else if (i == 1) {
                        ManageNetwork::TSPHeuristicAproximation();
                        allowed_algorithms[1].first = false;
                    } else if (i == 2) {
                        ManageNetwork::christofidesAlgorithm();
                        allowed_algorithms[2].first = false;
                    }

                }
            }
            repeat=false;

        } else if (answer == "N") {
            bool cycle=true;
            while (cycle) {
                cout << "Do you want to read another file? (Y/N)";
                string a;
                getline(cin, a);
                if (a == "Y") {
                    cycle=false;
                    menu::start();
                }
                else if (a == "N") {
                    cycle=false;
                }
                else {
                    cout << "Invalid Input!";
                }
            }
            repeat=false;
        } else {
            cout << "Invalid input" << "\n";

        }
    }
}