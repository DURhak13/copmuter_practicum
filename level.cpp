
#include "level.h"
#include <random>
#include <ctime>
#include <iostream>


Map generateLevel() {
    Map map(HEIGHT, std::vector<char>(WIDTH, WALL));

    // Пол
    for (int y = 1; y < HEIGHT - 1; ++y) {
        for (int x = 1; x < WIDTH - 1; ++x) {
            map[y][x] = FLOOR;
        }
    }

    // Ямы и мосты
    int pitCount = randInt(5, 10);
    int bridgeCount = randInt(10, 20);
    for (int i = 0; i < pitCount; ++i) {
        int x = randInt(2, WIDTH - 2);
        int y = randInt(2, HEIGHT - 2);
        if (map[y][x] == PIT) {pitCount++;}
        map[y][x] = PIT;
    }
    for (int i = 0; i < bridgeCount; ++i) {
        int x = randInt(2, WIDTH - 2);
        int y = randInt(2, HEIGHT - 2);
        if (map[y][x] == BRIDGE) {bridgeCount++;}
        map[y][x] = BRIDGE;
    }

    // Лестница
    while (true) {
        int x = randInt(2, WIDTH - 2);
        int y = randInt(2, HEIGHT - 2);
        if (map[y][x] == FLOOR) {
            map[y][x] = LADDER;
            break;
        }
    }

    // Внутренние стены
    for (int i = 0; i < 10; ++i) {
        int x = randInt(2, WIDTH - 3);
        int y = randInt(2, HEIGHT - 3);
        if (map[y][x] == FLOOR) {
            map[y][x] = WALL;
        }
    }

    return map;
}

std::vector<Enemy*> generateEnemies(Map& level) {
    std::vector<Enemy*> enemies;

    int dogCount = rand() % 3 + 1; // Генерация 1-3 собак
    for (int i = 0; i < dogCount; i++) {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        if (level[y][x] == FLOOR) {
            enemies.push_back(new Dog(x, y));
        }
    }
    int ogrCount = 1 ;// Генерация 1 огра
    for (int i = 0; i < ogrCount; i++) {
        int x = rand() % (WIDTH - 2) ;
        int y = rand() % (HEIGHT - 2) ;
        if (level[y][x] == FLOOR) {
            enemies.push_back(new Ogre(x, y));
            level[y][x] = 'O';
            level[y][x + 1] = 'O';
            level[y + 1][x] = 'O';
            level[y + 1][x + 1] = 'O';
        }
    }
    int bowCount = 1 ;// Генерация 1-2 скелетонов
    for (int i = 0; i < bowCount; i++) {
        int x = rand() % (WIDTH - 2) + 1;
        int y = rand() % (HEIGHT - 2) + 1;
        if (level[y][x] == FLOOR) {
            enemies.push_back(new SkeletonArcher(x, y));
        }
    }

    return enemies;
}

void printMap(const Map& map, const Player& player, const std::vector<Enemy*>& enemies) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {

            if (x == player.x && y == player.y) {
                std::cout << PLAYER;  // Символ игрока
            }

            else {
                bool printed = false;
                for (const auto& enemy : enemies) {
                    if (enemy->x == x && enemy->y == y) {
                        std::cout << enemy->getSymbol();
                        printed = true;
                        break;
                    }
                }
                if (!printed) {
                    std::cout << map[y][x];
                }
            }
        }
        std::cout << std::endl;
    }
}
