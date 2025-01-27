#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define INPUT_KEYS_COUNT 4

typedef enum InputKey {
    INPUT_LEFT, INPUT_RIGHT, INPUT_UP, INPUT_DOWN
} InputKey;

typedef struct Inputs
{
    InputKey pressed[INPUT_KEYS_COUNT];
    uint32_t pressed_length;
} Inputs;

int32_t Input_GetKey(Inputs *inputs, InputKey key);
bool Input_IsPressed(Inputs *inputs, InputKey key);
void Input_SetKey(Inputs *inputs, InputKey key);
void Input_ClearKeys(Inputs *inputs);
void Input_RemoveKey(Inputs *inputs, InputKey key);

#endif // __INPUTS_H__