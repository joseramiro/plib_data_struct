/**
 * @file plib_data_struct.c
 * @brief Définitions types de données et fonctions de manipulation
 * @author Ramiro Najera
 * @version 1.0.2
 * @date 2025-04-23
 */

#include "plib_data_struct.h"
#include <string.h>

uint8_t Utils_Calculate_CRC8_Raw(uint8_t* buffer, uint8_t size)
{
    uint8_t crc = 0xff;
    
    for (uint8_t i = 0; i < size; i++)
    {
        crc ^= buffer[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (uint8_t)((crc << 1) ^ 0x32);
            else
                crc <<= 1;
        }
    }
    return crc;
}

uint8_t Utils_Check_In_Range(uint16_t value, uint16_t setpoint, uint16_t tolerance)
{
    // Calculate thresholds and set 0 if minimum negative
    float setpointF = setpoint;
    float maxThreshold = (setpointF + tolerance);
    float minThreshold = (setpointF - tolerance);
    if(minThreshold < 0)
        minThreshold = 0;
    // Value is already in range: Nothing to be done
    if(value >= minThreshold && value <= maxThreshold)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Bytearray_Add_Byte(struct Bytearray *s, uint8_t b)
{
    if(s->len < sizeof(s->array))
        s->array[s->len++] = b;
}

void Bytearray_Shift_Left(struct Bytearray *s, uint8_t n)
{
    // do nothing if array is empty or not shift
    if (n == 0 || s->len == 0)
        return;

    // clear if overflow
    if (n >= s->len)
    {
        Bytearray_Clear(s);
        return;
    }

    // move shift data
    uint8_t newLen = s->len - n;

    for (uint8_t i = 0; i < newLen; i++)
        s->array[i] = s->array[i + n];

    // fill with zero the rest
    for (uint8_t i = newLen; i < s->len; i++)
        s->array[i] = 0;

    s->len = newLen;
}

void Bytearray_Clear(struct Bytearray *s)
{
    memset(s->array, 0, sizeof(s->array));
    s->len = 0;
}