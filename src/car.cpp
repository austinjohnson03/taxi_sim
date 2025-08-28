#include "car.h"
#include <cmath>
#include <algorithm>

Car::Car(float start_x, float start_y, float width, float height) {
    shape.setSize({width, height});
    shape.setOrigin(width / 2.f, height / 2.f);
    shape.setPosition(start_x, start_y);
    shape.setFillColor(sf::Color::Red);
  }

void Car::accelerate(float a) {
  accel_input = std::clamp(a , -MAX_ACCEL, MAX_ACCEL);
}

void Car::steer(float angle) {
  steer_angle = std::clamp(angle, -MAX_STEER, MAX_STEER);
}

void Car::update(float dt, const sf::RenderWindow& window) {
  sf::Vector2f pos = shape.getPosition();
  float winW = window.getSize().x;
  float winH = window.getSize().y;

  float margin = 100.f;
  bool near_left = pos.x < margin;
  bool near_right = pos.x > winW - margin;
  bool near_top = pos.y < margin;
  bool near_bottom = pos.y > winH - margin;

  bool near_edge = near_left || near_right || near_top || near_bottom;
  
  if (!near_edge) {
    steer_timer -= dt;
    if (steer_timer <= 0.f) {
      int r = std::rand() % 3;
      if (r == 0) {
        steer_angle = -0.3f;
      } else if (r == 1) {
        steer_angle = 0.3f;
      } else {
        steer_angle = 0.f;
      }

      steer_timer = STEER_INTERVAL;
    }
  } else {
    steer_timer = STEER_INTERVAL; // reset steer timer while near edge
                                  //
    accel_input = -MAX_ACCEL / -2.f;
    
    sf::Vector2f center(winW / 2.f, winH / 2.f);
    sf::Vector2f to_center = center - pos;
    float target_angle = std::atan2(to_center.y, to_center.x);

    float angle_diff = target_angle - direction_angle;
    steer_angle = std::clamp(angle_diff, -MAX_STEER, MAX_STEER);
  }

  velocity += accel_input * dt;
  velocity = std::clamp(velocity, MIN_VELO, MAX_VELO);

  if (accel_input == 0.f) {
    velocity *= DAMPING;
    if (std::abs(velocity) < 0.1f)
      velocity = 0.f;
  }

  direction_angle += (steer_angle - direction_angle) * dt * STEER_INERTIA;
  sf::Vector2f offset(std::cos(direction_angle) * velocity * dt, 
                      std::sin(direction_angle) * velocity * dt);
  shape.move(offset);

  shape.setRotation(direction_angle * 180.f / 3.14159265f);

  sf::Vector2f size = shape.getSize();
  float halfW = size.x / 2.f;
  float halfH = size.y / 2.f;    

  sf::Vector2f newPos = shape.getPosition();
  if (newPos.x - halfW < 0.f) newPos.x = halfW;
  if (newPos.x + halfW > winW) newPos.x = winW - halfW;
  if (newPos.y - halfH < 0.f) newPos.y = halfH;
  if (newPos.y + halfH > winH) newPos.y = winH - halfH;

  shape.setPosition(newPos);
}

void Car::draw(sf::RenderWindow& window) {
  window.draw(shape);
}

float Car::get_velocity() const { return velocity; }
float Car::get_accel_input() const { return accel_input; }
float Car::get_steer_angle() const { return steer_angle; }
