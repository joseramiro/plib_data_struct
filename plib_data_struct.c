/**
 * @file plib_data_struct.c
 * @brief Définitions types de données et fonctions de manipulation
 * @author Ramiro Najera
 * @version 1.0.2
 * @date 2025-04-23
 */

#include "plib_data_struct.h"
#include <string.h>

unsigned char Utils_Calculate_CRC8_Raw(unsigned char* buffer, unsigned char size)
{
    unsigned char crc = 0xff;
    unsigned char i, j;
    for (i = 0; i < size; i++)
    {
        crc ^= buffer[i];
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (unsigned char)((crc << 1) ^ 0x32);
            else
                crc <<= 1;
        }
    }
    return crc;
}

unsigned char Utils_Check_In_Range(unsigned int value, unsigned int setpoint, unsigned int tolerance)
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

void Bytearray_Add_Byte(struct Bytearray *s, unsigned char b)
{
    if(s->len < sizeof(s->array))
        s->array[s->len++] = b;
}

void Bytearray_Shift_Left(struct Bytearray *s, unsigned char n)
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
    unsigned char newLen = s->len - n;

    for (unsigned char i = 0; i < newLen; i++)
        s->array[i] = s->array[i + n];

    // fill with zero the rest
    for (unsigned char i = newLen; i < s->len; i++)
        s->array[i] = 0;

    s->len = newLen;
}

void Bytearray_Clear(struct Bytearray *s)
{
    memset(s->array, 0, sizeof(s->array));
    s->len = 0;
}