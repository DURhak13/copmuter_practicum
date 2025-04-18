#include "player.h"
#include "types.h"
#include <iostream>
#include "enemy.h"

void Player::move(Map& map, char direction) {
    int dx = 0, dy = 0;
    int prevX, prevY;
    if (direction == 'w') dy = -1;
    else if (direction == 's') dy = 1;
    else if (direction == 'a') dx = -1;
    else if (direction == 'd') dx = 1;

    if (map[y + dy][x + dx] != WALL) {  // Проверяем, не уперлись ли в стену
        prevX = x;
        prevY = y;
        x += dx;
        y += dy;
    }
}

void Player::attacking(std::vector<Enemy*>& enemies, Map& level) {
    char dir;
    std::cout << "Choose direction (WASD): ";
    std::cin >> dir;

    int dx = 0, dy = 0;
    if (dir == 'w') dy = -1;
    else if (dir == 's') dy = 1;
    else if (dir == 'a') dx = -1;
    else if (dir == 'd') dx = 1;
    else return;

    if (name == "WARRIOR") {
        for (auto* enemy : enemies) {
            if (enemy->occupiesPosition(x + dx, y + dy)) {
                std::cout << "You hit the " << enemy->name << "!\n";
                enemy->health -= 20;
                if (enemy->name!= "Ogre") {
                    enemy->x += dx; // отталкивание
                    enemy->y +=dy;
                }

            }
        }
    } else if (name == "ARCHER") {
        for (int i = 1; i < 10; ++i) {
            int tx = x + dx * i;
            int ty = y + dy * i;
            if (level[ty][tx] == WALL) break;

            for (auto* enemy : enemies) {
                if (enemy->occupiesPosition(tx, ty)) {
                    std::cout << "Arrow hits " << enemy->name << "!\n";
                    enemy->health -= 15;
                    return;
                }
            }
        }
    } else if (name == "MAGE") {
        int range;
        std::cout << "Fireball range (1-5): ";
        std::cin >> range;

        int cx = x + dx * range;
        int cy = y + dy * range;

        std::cout << "Fireball explodes!\n";
        for (auto* enemy : enemies) {
            if (std::abs(enemy->x - cx) <= 1 && std::abs(enemy->y - cy) <= 1) {
                enemy->health -= 25;
                std::cout << enemy->name << " is hit by the fireball!\n";
            }
        }
    }
}

std::string getClassName(PlayerClass cls) {
    switch (cls) {
        case WARRIOR: return "Warrior";
        case ARCHER: return "Archer";
        case MAGE: return "Mage";
        default: return "Unknown";
    }
}

PlayerClass chooseClass() {
    int choice;
    std::cout << "Choose your class:\n";
    std::cout << "1. Warrior (High HP, High ATK, 3 MOV)\n";
    std::cout << "2. Archer  (Medium HP, Medium ATK, 2 MOV)\n";
    std::cout << "3. Mage    (Low HP, High ATK, 1 MOV)\n";
    std::cout << "Enter number: ";
    std::cin >> choice;

    switch (choice) {
        case 1: return WARRIOR;
        case 2: return ARCHER;
        case 3: return MAGE;
        default:
            std::cout << "Invalid choice. Defaulting to Warrior.\n";
            return WARRIOR;
    }



}
