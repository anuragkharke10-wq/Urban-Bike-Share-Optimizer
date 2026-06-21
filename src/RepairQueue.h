#ifndef REPAIR_QUEUE_H
#define REPAIR_QUEUE_H

#include <queue>
#include <iostream>
using namespace std;

class RepairQueue {
private:
    queue<int> repairLine;

public:
    void reportBrokenBike(int bikeId) {
        repairLine.push(bikeId);
        cout << "Bike " << bikeId << " added to repair line.\n";
    }

    int repairNextBike() {
        if (repairLine.empty()) {
            cout << "No bikes waiting for repair.\n";
            return -1;
        }
        int bikeId = repairLine.front();
        repairLine.pop();
        cout << "Bike " << bikeId << " repaired first as per FIFO order.\n";
        return bikeId;
    }

    void displayRepairLine() const {
        if (repairLine.empty()) {
            cout << "Repair line is empty.\n";
            return;
        }
        queue<int> temp = repairLine;
        cout << "\n--- Repair Line FIFO Order ---\n";
        while (!temp.empty()) {
            cout << "Bike ID: " << temp.front() << endl;
            temp.pop();
        }
    }
};

#endif
