#include"responses.h"

BusesForStopResponse::BusesForStopResponse(string s1) {s = s1;};
StopsForBusResponse::StopsForBusResponse(string s1) {s = s1;};
AllBusesResponse::AllBusesResponse(string s1) {s = s1;};
ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  os << r.s;
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  os << r.s;
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  os << r.s;
  return os;
}
