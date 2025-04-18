
#include "enemy.h"
#include <iostream>

void Dog::takeTurn(Player& player, Map& level) {
    int dx = 0, dy = 0;
    // Проверка на яму
    if (level[y][x] == PIT) {
        std::cout << name << " упала!\n";
        health = 0;  // Враг умирает
        return;
    }

    if (x < player.x) dx = 1;
    else if (x > player.x) dx = -1;
    if (y < player.y) dy = 1;
    else if (y > player.y) dy = -1;

    if (x + dx >= 0 && x + dx < level[0].size() && y + dy >= 0 && y + dy < level.size()) {
        if (level[y + dy][x + dx] != PIT && level[y + dy][x + dx] != WALL && (x + dx != player.x || y + dy != player.y)) {
            x += dx;
            y += dy;
        }
    }

    if ((abs(player.x - x) == 1 && player.y == y) || (abs(player.y - y) == 1 && player.x == x)) {
        std::cout << name << " кусает тебя\n";
        player.health -= attack;
    }
}

void Ogre::takeTurn(Player& player, Map& level) {

    level[player.prevY][player.prevX] = PIT;  // Создаем яму на месте, где был игрок в прошлом ходу
    std::cout << "Огр сделал яму!\n";
}

void SkeletonArcher::takeTurn(Player& player, Map& level) {
    // Проверка на яму
    if (level[y][x] == PIT) {
        std::cout << name << " упал в яму!\n";
        health = 0;  // Враг умирает
        return;
    }

    if (y == player.y) {
        int step = (player.x > x) ? 1 : -1;
        bool clear = true;
        for (int i = x + step; i != player.x; i += step) {
            if (level[y][i] == WALL) {
                clear = false;
                break;
            }
        }
        if (clear) {
            std::cout << "Скелет попал в тебя!\n";
            player.health -= attack;
            return;
        }
    }

    else if (x == player.x) {
        int step = (player.y > y) ? 1 : -1;
        bool clear = true;
        for (int i = y + step; i != player.y; i += step) {
            if (level[i][x] == WALL) {
                clear = false;
                break;
            }
        }
        if (clear) {
            std::cout << "Скелет попал в тебя!\n";
            player.health -= attack;
            return;
        }
    }

    // Если не может стрелять — двигается к игроку
    if (x != player.x) {
        int dx = (player.x > x) ? 1 : -1;
        if (level[y][x + dx] != PIT && level[y][x + dx] != WALL) x += dx;
    } else if (y != player.y) {
        int dy = (player.y > y) ? 1 : -1;
        if (level[y + dy][x] != PIT && level[y + dy][x] != WALL ) y += dy;
    }
}
