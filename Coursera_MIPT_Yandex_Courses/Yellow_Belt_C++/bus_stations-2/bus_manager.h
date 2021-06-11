#pragma once
#include"responses.h"
#include<map>
#include<vector>
#include<string>
using namespace std;
using Table_of_buses = map<string, vector<string>>;

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops);

    BusesForStopResponse GetBusesForStop(const string& stop) const;

    StopsForBusResponse GetStopsForBus(const string& bus) const;

    AllBusesResponse GetAllBuses() const;

      private:
  Table_of_buses stops_for_buses, buses_for_stops;
};
