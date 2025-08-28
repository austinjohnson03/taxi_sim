#include "passenger.h"
#include <utility>

Passenger::Passenger(std::string name) {
  if (name.empty()) {
    this->name = "Unknown";
  } else {
    this->name = std::move(name);
  }
}

