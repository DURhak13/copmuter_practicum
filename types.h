#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <cstdlib>
#include <ctime>

// Карта
using Map = std::vector<std::vector<char>>;

// Символы на карте
const char WALL    = '#';
const char FLOOR   = '.';
const char PIT     = '~';
const char BRIDGE  = 'X';
const char LADDER  = 'L';
const char PLAYER  = '@';

// Генератор случайных чисел
inline int randInt(int min, int max) {
    srand(time(0));
    return rand() % (max - min + 1) + min;
}

#endif // TYPES_H
