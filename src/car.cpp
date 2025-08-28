#include "car.h"
#include <cmath>
#include <algorithm>

Car::Car(float start_x, float start_y, float width, float height) {
    shape.setSize({width, height});
    shape.setOrigin(width / 2.f, height / 2.f);
    shape.setPosition(start_x, start_y);
    shape.setFillColor(sf::Color::Yellow);
}

void Car::accelerate(float amount) {
  accel_input += amount;
  if (accel_input > MAX_ACCEL)
    accel_input = MAX_ACCEL;
  if (accel_input < -MAX_ACCEL)
    accel_input = -MAX_ACCEL;
}

void Car::turn(float amount) {
  steer_angle += amount;
  steer_angle = std::clamp(steer_angle, -MAX_STEER, MAX_STEER);
}

void Car::stop() {
  accel_input = 0.f;
  velocity *= DAMPING;
  if (std::abs(velocity) < 0.1f)
    velocity = 0.f;
}

void Car::update(float dt, const sf::RenderWindow& window) {
  velocity += accel_input * dt;
  velocity = std::clamp(velocity, MIN_VELO, MAX_VELO);

  if (accel_input == 0.f) {
    stop();
  }

  direction_angle += (steer_angle - direction_angle) * dt * STEER_INERTIA;

  sf::Vector2f offset(std::cos(direction_angle) * velocity * dt,
                      std::sin(direction_angle) * velocity * dt);

  shape.move(offset);

  shape.setRotation(direction_angle * 180.f / 3.14159265f);
}

void Car::pick_up(Passenger* p) {
  if (passenger != nullptr) delete passenger;
  passenger = p;
}

void Car::drop_off() {
  passenger = nullptr;
}

void Car::draw(sf::RenderWindow& window) {
  window.draw(shape);
}

float Car::get_velocity() const { return velocity; }
float Car::get_accel_input() const { return accel_input; }
float Car::get_steer_angle() const { return steer_angle; }

Car::~Car() {
  if (passenger != nullptr) {
    delete passenger;
    passenger = nullptr;
  }
}
