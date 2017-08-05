#ifndef __STEPPER_H
#define __STEPPER_H

#include "sys.h"
#include "timer.h"

#define SPEED_LEVEL_0 0
#define SPEED_LEVEL_1 1
#define SPEED_LEVEL_2 2
#define SPEED_LEVEL_3 3
#define SPEED_LEVEL_4 4
#define SPEED_LEVEL_5 5
#define SPEED_LEVEL_6 6
#define SPEED_LEVEL_7 7
#define SPEED_LEVEL_8 8
#define SPEED_LEVEL_9 9
#define SPEED_LEVEL_10 10
#define STEPPER_SPEED_LOW 0
#define STEPPER_SPEED_HIGH 1

#define STEPPER_CLOCKWISE 0
#define STEPPER_ANTI_CLOCKWISE 1

extern u8 stepper_speed;
extern u8 stepper_speed;
extern u32 stepper_steps;

void stepper_speed_set_h(u8 speed, u8 mode);
void stepper_direction_set(u8 direction);
void stepper_steps_set(u32 steps);

#endif
