#ifndef BIKE_H
#define BIKE_H

#include <string>
#include <iostream>
using namespace std;

class Bike {
private:
    int bikeId;
    string model;
    string status;      // Available, Rented, Broken, Maintenance
    int stationId;
    string lastMaintenance;

public:
    Bike() : bikeId(0), model("Unknown"), status("Available"), stationId(-1), lastMaintenance("N/A") {}

    Bike(int id, string modelName, string bikeStatus, int stId, string maintenance)
        : bikeId(id), model(modelName), status(bikeStatus), stationId(stId), lastMaintenance(maintenance) {}

    int getBikeId() const { return bikeId; }
    string getModel() const { return model; }
    string getStatus() const { return status; }
    int getStationId() const { return stationId; }
    string getLastMaintenance() const { return lastMaintenance; }

    void setStatus(const string& newStatus) { status = newStatus; }
    void setStationId(int newStationId) { stationId = newStationId; }
    void setLastMaintenance(const string& date) { lastMaintenance = date; }

    void display() const {
        cout << "Bike ID: " << bikeId
             << " | Model: " << model
             << " | Status: " << status
             << " | Station: " << stationId
             << " | Last Maintenance: " << lastMaintenance << endl;
    }
};

#endif
