
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cctype>
#include "level.h"
#include "player.h"
#include "enemy.h"
#include "types.h"

int main() {
    // Выбор класса только один раз
    PlayerClass chosenClass = chooseClass();
    Player player(0, 0);
    player.setClass(chosenClass);
    int sogr = 0;
    int sbow = 0;
    int sdog = 0;
    int lvl = -1;
    while (true) {
        lvl++;
        Map level = generateLevel();

        int startX, startY;
        while (true) {
            startX = randInt(1, WIDTH - 2);
            startY = randInt(1, HEIGHT - 2);
            if (level[startY][startX] == FLOOR) break;
        }

        player.x = startX;
        player.y = startY;
        std::vector<Enemy*> enemies = generateEnemies(level);
        bool alive = true;
        int tic = 0;
        printMap(level, player, enemies);
        char tile = FLOOR;
        while (alive && tile != LADDER) {

            tic++;

            // Вывод состояния игрока и легенды
            std::cout << "\nClass: " << getClassName(player.cls);
            std::cout << " | HP: " << player.health;
            std::cout << " | ATK: " << player.attack;
            std::cout << " | MOV: " << player.moves << "\n";

            std::cout << "Legend: @=Игрок  #=Стена  .=Пол  ~=Яма  X=Хрупкий мост  L=Лестница A=Лучник D=Собака O=Огр\n";


            std::cout << "Move (WASD), Q to quit: ";

            char input;
            std::cin >> input;
            input = tolower(input);

            if (input == 'q') return 0;

            int dx = 0, dy = 0; bool atk= false;
            if (input == 'w') dy = -1;
            else if (input == 's') dy = 1;
            else if (input == 'a') dx = -1;
            else if (input == 'd') dx = 1;
            else if (input == 'f') {
                atk= true;
            }
            player.prevX = player.x;
            player.prevY = player.y;
            int newX = player.x + dx;
            int newY = player.y + dy;
            char tile = level[newY][newX];

            system("clear");
            if (atk) {
                player.attacking(enemies, level);
            }
            for (auto it = enemies.begin(); it != enemies.end();) {
                if ((*it)->health <= 0) {
                    if ((*it)->name == "Ogre") {
                        level[(*it)->y][(*it)->x] = '.';
                        level[(*it)->y][(*it)->x + 1] = '.';
                        level[(*it)->y + 1][(*it)->x] = '.';
                        level[(*it)->y + 1][(*it)->x + 1] = '.';
                    }
                    sogr++;
                    sbow++;
                    sdog++;
                    delete *it;  // Удаляем  врага
                    it = enemies.erase(it);

                } else {
                    ++it;
                }
            }
            // Ход врагов
            if (tic >= player.moves) {
                tic = 0 ;
                for (auto& enemy : enemies) {
                    enemy->takeTurn(player, level);
                }
            }
            if (tile != WALL) {
                player.x = newX;
                player.y = newY;



            printMap(level, player, enemies);




                if (tile == PIT) {
                    std::cout << "You fell into a pit!\n";
                    alive = false;
                }
                else if (tile == BRIDGE) {
                    level[newY][newX] = PIT;
                    std::cout << "The bridge collapsed behind you!\n";
                }
                else if (tile == LADDER) {
                    std::cout << "You descend to the next level...\n\n";
                    break;
                }
            }
            if (player.health <= 0) {
                alive = false;
                std::cout << "Game Over!\n";
            }

        }

        if (!alive) {
            std::cout << "Game Over!\n" << "Убито Огров " << sogr << " Скелетов " << sbow <<" Собак" << sdog <<"\n" ;
            std::cout << "Пройдено этажей " << lvl  <<"\n" ;
            break;
        }
    }

    return 0;
}
