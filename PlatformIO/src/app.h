#ifndef APP_H
#define APP_H

#include <stdint.h>

typedef enum MotorDirection
{
    MOTOR_DIRECTION_OFF,
    MOTOR_DIRECTION_CLOCKWISE,
    MOTOR_DIRECTION_COUNTER_CLOCKWISE
} MotorDirection;

int32_t app_Init();
void app_Loop(float dt);
void app_DeInit();

void SetMotorDirection(MotorDirection direction);

#endif // APP_H