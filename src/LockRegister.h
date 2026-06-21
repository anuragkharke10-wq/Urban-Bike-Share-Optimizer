#ifndef LOCK_REGISTER_H
#define LOCK_REGISTER_H

#include <map>
#include <string>
#include <iostream>
using namespace std;

struct LockInfo {
    int lockId;
    int bikeId;
    int stationId;
    string status;
};

class LockRegister {
private:
    map<int, LockInfo> locks; // balanced BST, sorted by lock ID

public:
    void registerLock(int lockId, int bikeId, int stationId, const string& status) {
        locks[lockId] = {lockId, bikeId, stationId, status};
        cout << "Lock registered successfully.\n";
    }

    bool searchLock(int lockId) const {
        auto it = locks.find(lockId);
        if (it == locks.end()) {
            cout << "Lock not found.\n";
            return false;
        }
        const LockInfo& lock = it->second;
        cout << "Lock ID: " << lock.lockId
             << " | Bike ID: " << lock.bikeId
             << " | Station ID: " << lock.stationId
             << " | Status: " << lock.status << endl;
        return true;
    }

    void displayAllLocks() const {
        if (locks.empty()) {
            cout << "No locks registered.\n";
            return;
        }
        cout << "\n--- Lock Register Sorted by Lock ID ---\n";
        for (const auto& pair : locks) {
            const LockInfo& lock = pair.second;
            cout << "Lock ID: " << lock.lockId
                 << " | Bike ID: " << lock.bikeId
                 << " | Station ID: " << lock.stationId
                 << " | Status: " << lock.status << endl;
        }
    }
};

#endif
