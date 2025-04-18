#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <cstdlib>
#include "player.h"
#include "enemy.h"
#include "types.h"

const int WIDTH = 30;
const int HEIGHT = 15;

Map generateLevel();


void printMap(const Map& map, const Player& player, const std::vector<Enemy*>& enemies);
std::vector<Enemy*> generateEnemies(Map& level);
#endif // LEVEL_H
