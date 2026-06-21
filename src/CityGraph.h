#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>
using namespace std;

struct Edge {
    int to;
    int time;
    int safetyPenalty;
};

class CityGraph {
private:
    unordered_map<int, vector<Edge>> adj;

public:
    void addBikeLane(int from, int to, int time, int safetyPenalty) {
        adj[from].push_back({to, time, safetyPenalty});
        adj[to].push_back({from, time, safetyPenalty});
        cout << "Bike lane added between station " << from << " and " << to << ".\n";
    }

    void findSafestFastestPath(int source, int destination) const {
        if (adj.find(source) == adj.end() || adj.find(destination) == adj.end()) {
            cout << "Source or destination station is not present in city graph.\n";
            return;
        }

        unordered_map<int, int> distance;
        unordered_map<int, int> parent;

        for (const auto& pair : adj) {
            distance[pair.first] = numeric_limits<int>::max();
            parent[pair.first] = -1;
        }

        // Weight = time + safety penalty. Lower penalty means safer route.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (currentDistance > distance[node]) continue;

            auto it = adj.find(node);
            if (it == adj.end()) continue;

            for (const Edge& edge : it->second) {
                int weight = edge.time + edge.safetyPenalty;
                if (distance[node] + weight < distance[edge.to]) {
                    distance[edge.to] = distance[node] + weight;
                    parent[edge.to] = node;
                    pq.push({distance[edge.to], edge.to});
                }
            }
        }

        if (distance[destination] == numeric_limits<int>::max()) {
            cout << "No route found.\n";
            return;
        }

        vector<int> path;
        int current = destination;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        reverse(path.begin(), path.end());

        cout << "Safest/Fastest Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << " | Total Cost: " << distance[destination] << endl;
    }

    void displayGraph() const {
        if (adj.empty()) {
            cout << "City graph is empty.\n";
            return;
        }
        cout << "\n--- City Bike Lane Graph ---\n";
        for (const auto& pair : adj) {
            cout << "Station " << pair.first << " connects to: ";
            for (const Edge& edge : pair.second) {
                cout << "(" << edge.to << ", time=" << edge.time
                     << ", safetyPenalty=" << edge.safetyPenalty << ") ";
            }
            cout << endl;
        }
    }
};

#endif
