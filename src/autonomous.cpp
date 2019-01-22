#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"

void runAuton() {
  if(hc::pentane::selectedTile == -1) {
  std::cout << "did not run auton" << std::endl;
    if(SKILLS_MODE) {
      #include "./auton/skills-0.auton"

      return;
    }
    return;
  }

  if(hc::pentane::selectedTile == TILE_RED_A) {
    std::cout << "runing on tile: " << TILE_RED_A << std::endl;
    if(hc::pentane::selectedAuton == RED_NEAR_1) {
      #include "./auton/red-near-1.auton"
    } else if(hc::pentane::selectedAuton == RED_NEAR_2) {
      #include "./auton/red-near-0.auton"
    }
  } else if(hc::pentane::selectedTile == TILE_RED_B) {
    std::cout << "runing on tile: " << TILE_RED_B << std::endl;
    if(hc::pentane::selectedAuton == RED_FAR_1) {
      #include "./auton/red-far-1.auton"
    } else if(hc::pentane::selectedAuton == RED_FAR_2) {
      #include "./auton/red-far-0.auton"
    }
  } else if(hc::pentane::selectedTile == TILE_BLUE_B) {
    std::cout << "runing on tile: " << TILE_BLUE_B << std::endl;
    std::cout << "hc::pentane::selectedAuton: " << hc::pentane::selectedAuton << std::endl;
    std::cout << "BLUE_FAR_1: " << BLUE_FAR_1 << std::endl;
    std::cout << "BLUE_FAR_2: " << BLUE_FAR_2 << std::endl;
    if(hc::pentane::selectedAuton == BLUE_FAR_1) {
      #include "./auton/blue-far-1.auton"
    } else if(hc::pentane::selectedAuton == BLUE_FAR_2) {
      #include "./auton/blue-far-0.auton"
    }
  } else if(hc::pentane::selectedTile == TILE_BLUE_A) {
    std::cout << "runing on tile: " << TILE_BLUE_A << std::endl;
    std::cout << "hc::pentane::selectedAuton: " << hc::pentane::selectedAuton << std::endl;
    std::cout << "BLUE_NEAR_1: " << BLUE_NEAR_1 << std::endl;
    std::cout << "BLUE_NEAR_2: " << BLUE_NEAR_2 << std::endl;
    if(hc::pentane::selectedAuton == BLUE_NEAR_1) {
      #include "./auton/blue-near-1.auton"
    } else if(hc::pentane::selectedAuton == BLUE_NEAR_2) {
      #include "./auton/blue-near-0.auton"
    }
  }
}

void autonomous() {
  robot.reset();
  pros::Task track(hc::benzene::track, &posTracker);

  posTracker.setPos({ 0, 0 }, 0);

  robot.moveToSimple({ 10, 10 });

  pros::delay(10000);

  robot.moveToSimple({ 10, 10 });

  // runAuton();
  track.remove();
}
