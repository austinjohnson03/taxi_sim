#pragma once

#include <SFML/Graphics.hpp>
#include "passenger.h"

class Car {
  public:
    Car(float start_x, float start_y, float width = 60.f, float height = 30.f);
    ~Car();

    void update(float dt, const sf::RenderWindow& window);

    void accelerate(float amount);
    void turn(float amount);
    void stop();

    void pick_up(Passenger* p);
    void drop_off();


    float get_velocity() const;
    float get_accel_input() const;
    float get_steer_angle() const;

    void draw(sf::RenderWindow& window);

  private:
    sf::RectangleShape shape;
    Passenger* passenger = nullptr;

    float velocity = 0.f;
    float steer_angle = 0.f;
    float direction_angle = 0.f;
    float steer_timer = 2.f;

    const float MAX_STEER = 0.9f;  // ~34 degrees in radians
    const float MIN_VELO = -100.f;
    const float MAX_VELO = 200.f;
    const float MAX_ACCEL = 100.f;
    const float DAMPING = 0.95f;
    const float STEER_INERTIA = 5.f;
    const float STEER_INTERVAL = 0.3f;

    float accel_input = 0.f;
};
