#ifndef PLIB_DATA_STRUCT_H
#define PLIB_DATA_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file plib_data_struct.h
 * @brief Définitions types de données et fonctions de manipulation
 * @author Ramiro Najera
 * @version 1.0.2
 * @date 2025-04-23
 */

#include <stdint.h>

/** @brief Macro pour calculer taille de tableau */
#define SIZE_ARRAY(arr) (sizeof(arr) / sizeof((arr)[0]))
/** @brief Taille d'un char */
#define SIZE_CHAR       1
/** @brief Taille d'un int */
#define SIZE_INT        2
/** @brief Taille d'un long */
#define SIZE_LONG       4
/** @brief Taille d'un float */
#define SIZE_FLOAT      4

/** @brief Combine 2 bytes */
#define CONCAT(byte1, byte0) (((uint16_t)(byte1) << 8) + (byte0))
/** @brief Retourne le MSB d'un int */
#define GET_HIGH_BYTE(intValue) ((uint8_t)((intValue >> 8)))
/** @brief Retourne le LSB d'un int */
#define GET_LOW_BYTE(intValue) ((uint8_t)((intValue) & 0xFF))
/** @brief Met bit à 1 d'un flag */
#define SET_FLAG_BIT(flag, bit) ((flag) |= (1U << (bit)))
/** @brief Met bit à 0 d'un flag */
#define CLEAR_FLAG_BIT(flag, bit)  ((flag) &= ~(1U << (bit)))
/** @brief Retourne la valeur d'un bit d'un flag */
#define GET_FLAG_BIT(flag, bit)   ((flag >> (bit)) & 1U)

/** @brief Union pour manipuler des données entre float et chaine de char */
union FloatUsCharUnion
{
    /** @brief Valeur float */
    float floatValue;
    /** @brief Chaîne de char */
    uint8_t usChar[4];
};

/** @brief Union pour manipuler des données entre int et chaine de char */
union IntUsCharUnion
{
    /** @brief Valeur uint16_t */
    uint16_t usIntValue;
    /** @brief Valeur int */
    int16_t IntValue;
    /** @brief Chaîne de char */
    uint8_t usChar[2];
};

/** @brief Union pour manipuler des données entre long et chaine de char */
union LongUsCharUnion
{
    /** @brief Valeur uint32_t */
    uint32_t usLongValue;
    /** @brief Valeur long */
    long longValue;
    /** @brief Valeur float */
    float floatValue;
    /** @brief Chaine de char */
    uint8_t usChar[4];
    /** @brief Chaine de int */
    uint16_t usInt[2];
};

/** @brief Union pour manipuler des données entre char et uint8_t */
union CharUsCharUnion
{
    /** @brief Valeur uint8_t */
    uint8_t usCharValue;
    /** @brief Valeur char */
    int8_t charValue;
};

/** @brief Strcture pour manipuler des chaînes de bytes (bytearray) */
struct Bytearray
{
    uint8_t array[64];
    uint8_t len;
};

/**
 * @brief Calcule un CRC 8 bits
 * @param buffer Tableau de données
 * @param size Taille du tableau
 * @return uint8_t CRC
 */
uint8_t Utils_Calculate_CRC8_Raw(uint8_t* buffer, uint8_t size);

/**
 * @brief Vérifie si un numéro est dans une plage de données
 * @param value Valeur d'entrée
 * @param setpoint Valeur de consigne
 * @param tolerance Tolérance
 * @return uint8_t 1 si dans le plage, sinon 0
 */
uint8_t Utils_Check_In_Range(uint16_t value, uint16_t setpoint, uint16_t tolerance);

/**
 * @brief Rajoute un byte à la fin de la chaîne de bytes
 * @param s Structure de chaîne de bytes
 * @param b Byte à rajouter
 */
void Bytearray_Add_Byte(struct Bytearray *s, uint8_t b);

/**
 * @brief Décale tous les byte de la chaîne de bytes
 * @param s Structure de chaîne de bytes
 * @param n Nombre de positions à décaler dans la chaîne de bytes
 */
void Bytearray_Shift_Left(struct Bytearray *s, uint8_t n);

/**
 * @brief Efface tous les bytes de la chaîne de bytes
 * @param s Structure de chaîne de bytes
 */
void Bytearray_Clear(struct Bytearray *s);

#ifdef __cplusplus
}
#endif

#endif  // PLIB_DATA_STRUCT_H