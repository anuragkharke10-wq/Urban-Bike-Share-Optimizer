#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

#include "Bike.h"
#include "Station.h"
#include "LockRegister.h"
#include "ChargeLog.h"
#include "RepairQueue.h"
#include "CityGraph.h"
#include "RebalancingOptimizer.h"

using namespace std;

class BikeShareSystem {
private:
    unordered_map<int, Bike> bikes;       // Bike finder: O(1) average lookup
    unordered_map<int, Station> stations; // Station storage
    LockRegister lockRegister;            // map/BST sorted lock records
    ChargeLog chargeLog;                  // stack rollback
    RepairQueue repairQueue;              // queue FIFO repair
    CityGraph cityGraph;                  // graph + Dijkstra pathfinding

public:
    void loadSampleData() {
        stations[101] = Station(101, "Central Park Dock", 20, 18);
        stations[102] = Station(102, "Metro Station Dock", 25, 6);
        stations[103] = Station(103, "University Dock", 15, 13);
        stations[104] = Station(104, "Mall Dock", 30, 8);

        bikes[1] = Bike(1, "Yulu Miracle", "Available", 101, "2026-01-12");
        bikes[2] = Bike(2, "Yulu DeX", "Available", 101, "2026-01-20");
        bikes[3] = Bike(3, "Citi Bike Classic", "Broken", 103, "2025-12-30");
        bikes[4] = Bike(4, "PedalCity Swift", "Available", 104, "2026-02-10");

        lockRegister.registerLock(5001, 1, 101, "Active");
        lockRegister.registerLock(5002, 2, 101, "Active");
        lockRegister.registerLock(5003, 3, 103, "Faulty");
        lockRegister.registerLock(5004, 4, 104, "Active");

        cityGraph.addBikeLane(101, 102, 10, 2);
        cityGraph.addBikeLane(102, 103, 12, 1);
        cityGraph.addBikeLane(101, 103, 30, 5);
        cityGraph.addBikeLane(103, 104, 8, 2);
        cityGraph.addBikeLane(102, 104, 20, 4);

        cout << "Sample data loaded successfully.\n";
    }

    void addBike() {
        int id, stationId;
        string model, status, maintenance;

        cout << "Enter Bike ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (bikes.find(id) != bikes.end()) {
            cout << "Bike ID already exists.\n";
            return;
        }

        cout << "Enter Model Name: ";
        getline(cin, model);
        cout << "Enter Status (Available/Rented/Broken/Maintenance): ";
        getline(cin, status);
        cout << "Enter Station ID: ";
        cin >> stationId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Last Maintenance Date: ";
        getline(cin, maintenance);

        bikes[id] = Bike(id, model, status, stationId, maintenance);
        if (stations.find(stationId) != stations.end()) {
            stations[stationId].addBike();
        }
        cout << "Bike added successfully.\n";
    }

    void addStation() {
        int id, capacity, currentBikes;
        string name;

        cout << "Enter Station ID: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (stations.find(id) != stations.end()) {
            cout << "Station ID already exists.\n";
            return;
        }

        cout << "Enter Station Name: ";
        getline(cin, name);
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Current Bikes: ";
        cin >> currentBikes;

        stations[id] = Station(id, name, capacity, currentBikes);
        cout << "Station added successfully.\n";
    }

    void registerLock() {
        int lockId, bikeId, stationId;
        string status;
        cout << "Enter Lock ID: ";
        cin >> lockId;
        cout << "Enter Bike ID: ";
        cin >> bikeId;
        cout << "Enter Station ID: ";
        cin >> stationId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Lock Status: ";
        getline(cin, status);
        lockRegister.registerLock(lockId, bikeId, stationId, status);
    }

    void searchLock() const {
        int lockId;
        cout << "Enter Lock ID to search: ";
        cin >> lockId;
        lockRegister.searchLock(lockId);
    }

    void rentBike() {
        int userId, bikeId;
        double amount;
        cout << "Enter User ID: ";
        cin >> userId;
        cout << "Enter Bike ID: ";
        cin >> bikeId;
        cout << "Enter Charge Amount: ";
        cin >> amount;

        auto it = bikes.find(bikeId);
        if (it == bikes.end()) {
            cout << "Bike not found.\n";
            return;
        }
        if (it->second.getStatus() != "Available") {
            cout << "Bike is not available. Current status: " << it->second.getStatus() << endl;
            return;
        }

        int stationId = it->second.getStationId();
        bikes[bikeId].setStatus("Rented");
        if (stations.find(stationId) != stations.end()) {
            stations[stationId].removeBike();
        }
        chargeLog.recordCharge(userId, bikeId, amount, "Bike rental charge");
        cout << "Bike rented successfully.\n";
    }

    void rollbackLastCharge() {
        chargeLog.rollbackLastCharge();
    }

    void reportBrokenBike() {
        int bikeId;
        cout << "Enter Broken Bike ID: ";
        cin >> bikeId;
        if (bikes.find(bikeId) == bikes.end()) {
            cout << "Bike not found.\n";
            return;
        }
        bikes[bikeId].setStatus("Broken");
        repairQueue.reportBrokenBike(bikeId);
    }

    void repairNextBike() {
        int bikeId = repairQueue.repairNextBike();
        if (bikeId != -1 && bikes.find(bikeId) != bikes.end()) {
            bikes[bikeId].setStatus("Available");
            bikes[bikeId].setLastMaintenance("Today");
        }
    }

    void findBikeById() const {
        int bikeId;
        cout << "Enter Bike ID: ";
        cin >> bikeId;
        auto it = bikes.find(bikeId);
        if (it == bikes.end()) {
            cout << "Bike not found.\n";
            return;
        }
        it->second.display();
    }

    void showStationsByEmptyCapacity() const {
        RebalancingOptimizer::showStationsByEmptyCapacity(stations);
    }

    void addBikeLane() {
        int from, to, time, safetyPenalty;
        cout << "Enter From Station ID: ";
        cin >> from;
        cout << "Enter To Station ID: ";
        cin >> to;
        cout << "Enter Time in Minutes: ";
        cin >> time;
        cout << "Enter Safety Penalty (lower = safer): ";
        cin >> safetyPenalty;
        cityGraph.addBikeLane(from, to, time, safetyPenalty);
    }

    void findRoute() const {
        int source, destination;
        cout << "Enter Source Station ID: ";
        cin >> source;
        cout << "Enter Destination Station ID: ";
        cin >> destination;
        cityGraph.findSafestFastestPath(source, destination);
    }

    void runRebalancing() {
        int truckCapacity;
        cout << "Enter Truck Capacity: ";
        cin >> truckCapacity;
        RebalancingOptimizer::optimizeRebalancing(stations, truckCapacity);
    }

    void displayAllData() const {
        cout << "\n========== ALL BIKES ==========" << endl;
        if (bikes.empty()) cout << "No bikes available.\n";
        for (const auto& pair : bikes) pair.second.display();

        cout << "\n========== ALL STATIONS ==========" << endl;
        if (stations.empty()) cout << "No stations available.\n";
        for (const auto& pair : stations) pair.second.display();

        lockRegister.displayAllLocks();
        chargeLog.displayCharges();
        repairQueue.displayRepairLine();
        cityGraph.displayGraph();
    }
};

void printMenu() {
    cout << "\n================ PedalCity Bike-Share Optimizer ================\n";
    cout << "1. Load Sample Data\n";
    cout << "2. Add Bike\n";
    cout << "3. Add Station\n";
    cout << "4. Register Lock\n";
    cout << "5. Search Lock by ID\n";
    cout << "6. Rent Bike\n";
    cout << "7. Rollback Last Charge\n";
    cout << "8. Report Broken Bike\n";
    cout << "9. Repair Next Bike\n";
    cout << "10. Find Bike by ID\n";
    cout << "11. Show Stations by Empty Capacity\n";
    cout << "12. Add Bike Lane\n";
    cout << "13. Find Safest/Fastest Route\n";
    cout << "14. Run Rebalancing Optimizer\n";
    cout << "15. Display All Data\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

int main() {
    BikeShareSystem system;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: system.loadSampleData(); break;
            case 2: system.addBike(); break;
            case 3: system.addStation(); break;
            case 4: system.registerLock(); break;
            case 5: system.searchLock(); break;
            case 6: system.rentBike(); break;
            case 7: system.rollbackLastCharge(); break;
            case 8: system.reportBrokenBike(); break;
            case 9: system.repairNextBike(); break;
            case 10: system.findBikeById(); break;
            case 11: system.showStationsByEmptyCapacity(); break;
            case 12: system.addBikeLane(); break;
            case 13: system.findRoute(); break;
            case 14: system.runRebalancing(); break;
            case 15: system.displayAllData(); break;
            case 0: cout << "Exiting PedalCity system.\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
