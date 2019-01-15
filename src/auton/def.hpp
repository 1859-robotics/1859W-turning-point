#ifndef AUTON_DEF_HPP
#define AUTON_DEF_HPP

//TODO: make some kinda script to generate this

// tile names
#define AUTON_NAME_RED_A "RED A"
#define AUTON_NAME_RED_B "RED B"
#define AUTON_NAME_BLUE_A "BLUE A"
#define AUTON_NAME_BLUE_B "BLUE B"

#define TILE_RED_A 3
#define TILE_RED_B 4
#define TILE_BLUE_A 1
#define TILE_BLUE_B 2

// auton names
#define BLUE_NEAR_1  "alliance post\n"
#define BLUE_FAR_1 "center post\n"

#define RED_NEAR_1  "alliance post\n"
#define RED_FAR_1  "center post\n"

// auton lists
#define AUTON_OPTIONS_RED_A RED_NEAR_1 \
                            "none"
#define AUTON_OPTIONS_RED_B RED_FAR_1 \
                            "none"
#define AUTON_OPTIONS_BLUE_A BLUE_NEAR_1 \
                             "none"
#define AUTON_OPTIONS_BLUE_B BLUE_FAR_1 \
                             "none"

#endif
