#include "Inputs.h"

int32_t Input_GetKey(Inputs *inputs, InputKey key)
{
    for (int i = 0; i < inputs->pressed_length; i++)
        if (inputs->pressed[i] == key)
            return i;
    return -1;
}

bool Input_IsPressed(Inputs *inputs, InputKey key)
{
   return Input_GetKey(inputs, key) != -1;
}

void Input_SetKey(Inputs *inputs, InputKey key)
{
    if (!Input_IsPressed(inputs, key))
        inputs->pressed[inputs->pressed_length++] = key;
}

void Input_ClearKeys(Inputs *inputs)
{
    inputs->pressed_length = 0;
}

void Input_RemoveKey(Inputs *inputs, InputKey key)
{
    int32_t key_index = Input_GetKey(inputs, key);
    if (key_index != -1)
    {
        InputKey prev_keys[INPUT_KEYS_COUNT];
        uint32_t prev_keys_length = inputs->pressed_length;
        memcpy(prev_keys, inputs->pressed, sizeof(inputs->pressed));
        Input_ClearKeys(inputs);

        for (int i = 0; i < prev_keys_length; i++)
            if (i != key_index)
                Input_SetKey(inputs, prev_keys[i]);
    }
}
