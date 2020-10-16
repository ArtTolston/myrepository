#pragma once
#include<string>
#include<iostream>
using namespace std;

struct BusesForStopResponse {
    BusesForStopResponse(string s1);
    string s;
};


struct StopsForBusResponse {
  StopsForBusResponse(string s1);
  string s;
};


struct AllBusesResponse {
  AllBusesResponse(string s1);
  string s;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);
