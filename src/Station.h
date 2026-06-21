#ifndef STATION_H
#define STATION_H

#include <string>
#include <iostream>
using namespace std;

class Station {
private:
    int stationId;
    string name;
    int capacity;
    int currentBikes;

public:
    Station() : stationId(0), name("Unknown"), capacity(0), currentBikes(0) {}

    Station(int id, string stationName, int cap, int bikes)
        : stationId(id), name(stationName), capacity(cap), currentBikes(bikes) {}

    int getStationId() const { return stationId; }
    string getName() const { return name; }
    int getCapacity() const { return capacity; }
    int getCurrentBikes() const { return currentBikes; }
    int getEmptySpots() const { return capacity - currentBikes; }

    void addBike() {
        if (currentBikes < capacity) currentBikes++;
    }

    void removeBike() {
        if (currentBikes > 0) currentBikes--;
    }

    void setCurrentBikes(int bikes) {
        if (bikes < 0) bikes = 0;
        if (bikes > capacity) bikes = capacity;
        currentBikes = bikes;
    }

    void display() const {
        cout << "Station ID: " << stationId
             << " | Name: " << name
             << " | Capacity: " << capacity
             << " | Bikes: " << currentBikes
             << " | Empty Spots: " << getEmptySpots() << endl;
    }
};

#endif
