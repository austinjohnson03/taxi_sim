#pragma once
#include <string>

class Passenger {
  public:
    Passenger(std::string name);

    std::string get_name() const { return name; }
    unsigned int get_time_idling() const { return time_idling; }
    unsigned int get_time_in_transit() const { return time_in_transit; }
    void increment_time_idle() { time_idling++; }
    void reset_time_idle() { time_idling = 0; }
    void reset_time_in_transit() { time_in_transit = 0; }
    void increment_time_in_transit() { time_in_transit++; }

  private:
    std::string name;
    unsigned int time_idling = 0;
    unsigned int time_in_transit = 0;
};
