#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"

void runAuton() {
  if(w::auton_selector::selectedTile == TILE_RED_A) {
    if(w::auton_selector::selectedAuton == RED_NEAR_1) {
      #include "./auton/red-near-1.auton"
    } else if(w::auton_selector::selectedAuton == RED_NEAR_2) {
      #include "./auton/red-near-0.auton"
    } else if(w::auton_selector::selectedAuton == RED_NEAR_3) {
      #include "./auton/red-near-2.auton"
    }
  } else if(w::auton_selector::selectedTile == TILE_RED_B) {
    if(w::auton_selector::selectedAuton == RED_FAR_1) {
      #include "./auton/red-far-0.auton"
    }
  } else if(w::auton_selector::selectedTile == TILE_BLUE_B) {
    if(w::auton_selector::selectedAuton == BLUE_FAR_1) {
      #include "./auton/blue-far-0.auton"
    }
  } else if(w::auton_selector::selectedTile == TILE_BLUE_A) {
    if(w::auton_selector::selectedAuton == BLUE_NEAR_1) {
      #include "./auton/blue-near-1.auton"
    } else if(w::auton_selector::selectedAuton == BLUE_NEAR_2) {
      #include "./auton/blue-near-0.auton"
    } else if(w::auton_selector::selectedAuton == BLUE_NEAR_3) {
      #include "./auton/blue-near-2.auton"
    }
  }
}

void autonomous() {
  robot.reset();
  pros::Task track(w::odom::track, &posTracker);

  #include "./auton/test.auton"

  std::cout << "end" << std::endl;

  while(true) { pros::delay(20); }
}
