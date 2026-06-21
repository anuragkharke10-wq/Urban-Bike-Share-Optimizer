#ifndef REBALANCING_OPTIMIZER_H
#define REBALANCING_OPTIMIZER_H

#include "Station.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

struct SurplusStation {
    int stationId;
    int surplus;

    bool operator<(const SurplusStation& other) const {
        return surplus < other.surplus;
    }
};

struct DeficitStation {
    int stationId;
    int deficit;

    bool operator<(const DeficitStation& other) const {
        return deficit < other.deficit;
    }
};

class RebalancingOptimizer {
public:
    static void showStationsByEmptyCapacity(const unordered_map<int, Station>& stations) {
        if (stations.empty()) {
            cout << "No stations available.\n";
            return;
        }

        priority_queue<pair<int, int>> pq; // empty spots, station ID
        for (const auto& pair : stations) {
            pq.push({pair.second.getEmptySpots(), pair.first});
        }

        cout << "\n--- Stations Ranked by Empty Spots ---\n";
        while (!pq.empty()) {
            int emptySpots = pq.top().first;
            int stationId = pq.top().second;
            pq.pop();
            cout << "Station " << stationId << " | Empty Spots: " << emptySpots << endl;
        }
    }

    static void optimizeRebalancing(unordered_map<int, Station>& stations, int truckCapacity) {
        if (stations.empty()) {
            cout << "No stations available for rebalancing.\n";
            return;
        }

        priority_queue<SurplusStation> surplusPQ;
        priority_queue<DeficitStation> deficitPQ;

        // Target = half full station. Above target gives bikes, below target receives bikes.
        for (const auto& pair : stations) {
            const Station& st = pair.second;
            int target = st.getCapacity() / 2;
            int diff = st.getCurrentBikes() - target;

            if (diff > 0) surplusPQ.push({st.getStationId(), diff});
            else if (diff < 0) deficitPQ.push({st.getStationId(), -diff});
        }

        if (surplusPQ.empty() || deficitPQ.empty()) {
            cout << "Stations are already balanced or insufficient surplus/deficit data.\n";
            return;
        }

        cout << "\n--- Rebalancing Plan Using Greedy + Priority Queue ---\n";
        int remainingTruckCapacity = truckCapacity;

        while (!surplusPQ.empty() && !deficitPQ.empty() && remainingTruckCapacity > 0) {
            SurplusStation surplus = surplusPQ.top();
            DeficitStation deficit = deficitPQ.top();
            surplusPQ.pop();
            deficitPQ.pop();

            int moveCount = min({surplus.surplus, deficit.deficit, remainingTruckCapacity});
            stations[surplus.stationId].setCurrentBikes(stations[surplus.stationId].getCurrentBikes() - moveCount);
            stations[deficit.stationId].setCurrentBikes(stations[deficit.stationId].getCurrentBikes() + moveCount);

            remainingTruckCapacity -= moveCount;

            cout << "Move " << moveCount << " bikes from Station " << surplus.stationId
                 << " to Station " << deficit.stationId << endl;

            surplus.surplus -= moveCount;
            deficit.deficit -= moveCount;

            if (surplus.surplus > 0) surplusPQ.push(surplus);
            if (deficit.deficit > 0) deficitPQ.push(deficit);
        }

        cout << "Truck remaining capacity: " << remainingTruckCapacity << endl;
    }
};

#endif
