#include "main.h"
#include "app.hpp"
#include "robot-config.hpp"

void runAuton() {
  if(SKILLS_MODE) {
    #include "./auton/skills.auton"

    return;
  }

  if(hc::pentane::selectedAuton == "" || hc::pentane::selectedAuton == "none") {
    std::cout << "did not run auton" << std::endl;
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
    }
  } else if(hc::pentane::selectedTile == TILE_BLUE_A) {
    std::cout << "runing on tile: " << TILE_BLUE_A << std::endl;
    if(hc::pentane::selectedAuton == BLUE_NEAR_1) {
      #include "./auton/blue-near-1.auton"
    }
  } else if(hc::pentane::selectedTile == TILE_BLUE_B) {
    std::cout << "runing on tile: " << TILE_BLUE_B << std::endl;
    if(hc::pentane::selectedAuton == BLUE_FAR_1) {
      #include "./auton/blue-far-1.auton"
    }
  }
}

void autonomous() {
  robot.reset();
      pros::Task track(hc::benzene::track, &posTracker);

  runAuton();
  track.remove();
}
