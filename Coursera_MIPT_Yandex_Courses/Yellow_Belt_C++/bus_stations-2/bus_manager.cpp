#include "bus_manager.h"
#include "responses.h"
  void BusManager::AddBus(const string& bus, const vector<string>& stops) {
        for(const auto& i: stops) {
            BusManager::stops_for_buses[bus].push_back(i);
            BusManager::buses_for_stops[i].push_back(bus);
        }
  }

  BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
        if(BusManager::buses_for_stops.count(stop) == 0) {
            return BusesForStopResponse("No stop");
        } else {
            string s;
            for(const auto& i: BusManager::buses_for_stops.at(stop)) {
                s += i + " ";
            }
            s += "\n";
            return BusesForStopResponse(s);
        }
  }

  StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
      if (BusManager::stops_for_buses.count(bus) == 0) {
        return StopsForBusResponse("No bus");
      } else {
        string s;
        for (const string& stop : BusManager::stops_for_buses.at(bus)) {
           s += "Stop " + stop + ": ";
          if (BusManager::buses_for_stops.at(stop).size() == 1) {
            s += "no interchange\n";
          } else {
            for (const string& other_bus : BusManager::buses_for_stops.at(stop)) {
              if (bus != other_bus) {
                s += other_bus + " ";
              }
            }
            s += "\n";
          }
        }
        return StopsForBusResponse(s);
      }
  }

  AllBusesResponse BusManager::GetAllBuses() const {
      if (BusManager::stops_for_buses.empty()) {
        return AllBusesResponse("No buses");
      } else {
        string s;
        for (const auto& bus_item : BusManager::stops_for_buses) {
          s += "Bus " + bus_item.first + ": ";
          for (const string& stop : bus_item.second) {
            s += stop + " ";
          }
          s += "\n";
        }
        return AllBusesResponse(s);
      }
  }

//  tuple<Table_of_buses, Table_of_buses> For_Unit_Tests(void) {
//    return make_tuple(stops_for_buses, buses_for_stops);

