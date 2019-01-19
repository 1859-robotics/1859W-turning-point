#ifndef AUTON_DEF_HPP
#define AUTON_DEF_HPP

//TODO: make some kinda script to generate this

// tile names
#define AUTON_NAME_RED_A "RED A"
#define AUTON_NAME_RED_B "RED B"
#define AUTON_NAME_BLUE_A "BLUE A"
#define AUTON_NAME_BLUE_B "BLUE B"

#define TILE_BLUE_A 1
#define TILE_BLUE_B 2
#define TILE_RED_A 3
#define TILE_RED_B 4

// auton names
#define BLUE_NEAR_1   "alliance post & cap"
#define BLUE_NEAR_2   "alliance post"
#define BLUE_FAR_1    "center post & park"
#define BLUE_FAR_2    "center post & cap"

#define RED_NEAR_1   "alliance post & cap"
#define RED_NEAR_2   "alliance post"
#define RED_FAR_1    "center post & park"
#define RED_FAR_2    "center post & cap"

// auton lists
#define AUTON_OPTIONS_RED_A "none" "\n" \
                            RED_NEAR_1 "\n" \
                            RED_NEAR_2

#define AUTON_OPTIONS_RED_B "none" "\n" \
                            RED_FAR_1 "\n" \
                            RED_FAR_2

#define AUTON_OPTIONS_BLUE_A "none" "\n" \
                             BLUE_NEAR_1 "\n" \
                             BLUE_NEAR_2
                             
#define AUTON_OPTIONS_BLUE_B "none" "\n" \
                             BLUE_FAR_1 "\n" \
                             BLUE_FAR_2

#endif
