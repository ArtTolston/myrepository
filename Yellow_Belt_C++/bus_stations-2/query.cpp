#include"query.h"

istream& operator >> (istream& is, Query& q) {
  q.stops.clear();
  string str;
  is >> str;
    if(str == "NEW_BUS"){
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stops_count = 0;
        is >> stops_count;
        string stop;
        for(int i = 0; i < stops_count; i++) {
            is >> stop;
            q.stops.push_back(stop);
        }
    }
    else if(str == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if(str == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if("ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
  return is;
}
