#ifndef CHARGE_LOG_H
#define CHARGE_LOG_H

#include <stack>
#include <string>
#include <iostream>
using namespace std;

struct ChargeTransaction {
    int transactionId;
    int userId;
    int bikeId;
    double amount;
    string reason;
};

class ChargeLog {
private:
    stack<ChargeTransaction> chargeStack;
    int nextTransactionId = 1;

public:
    int recordCharge(int userId, int bikeId, double amount, const string& reason) {
        ChargeTransaction txn = {nextTransactionId++, userId, bikeId, amount, reason};
        chargeStack.push(txn);
        cout << "Charge recorded. Transaction ID: " << txn.transactionId << endl;
        return txn.transactionId;
    }

    void rollbackLastCharge() {
        if (chargeStack.empty()) {
            cout << "No charge available to rollback.\n";
            return;
        }
        ChargeTransaction txn = chargeStack.top();
        chargeStack.pop();
        cout << "Rolled back Transaction ID: " << txn.transactionId
             << " | User: " << txn.userId
             << " | Bike: " << txn.bikeId
             << " | Amount: Rs. " << txn.amount << endl;
    }

    void displayCharges() const {
        if (chargeStack.empty()) {
            cout << "No charge logs.\n";
            return;
        }

        stack<ChargeTransaction> temp = chargeStack;
        cout << "\n--- Charge Log Latest First ---\n";
        while (!temp.empty()) {
            ChargeTransaction txn = temp.top();
            temp.pop();
            cout << "Txn ID: " << txn.transactionId
                 << " | User: " << txn.userId
                 << " | Bike: " << txn.bikeId
                 << " | Amount: Rs. " << txn.amount
                 << " | Reason: " << txn.reason << endl;
        }
    }
};

#endif
