
#pragma once
#include <string>
#include "types.h"

class Enemy;

enum PlayerClass { WARRIOR, ARCHER, MAGE };

struct Player {
    std::string name;
    int x, y, prevX = x, prevY = y;
    int health;
    int attack;
    int moves;
    PlayerClass cls;
    void move(Map& map, char direction);
    void attacking(std::vector<Enemy*>& enemies, Map& level);

    Player(int startX, int startY) : x(startX), y(startY) {}

    void setClass(PlayerClass c) {
        cls = c;
        switch (c) {
            case WARRIOR:
                name = "WARRIOR";
                health = 100;
                attack = 15;
                moves = 3;
                break;
            case ARCHER:
                name =  "ARCHER";
                health = 70;
                attack = 10;
                moves = 2;
                break;
            case MAGE:
                name = "MAGE";
                health = 50;
                attack = 20;
                moves = 1;
                break;
        }
    }
};

std::string getClassName(PlayerClass cls);
PlayerClass chooseClass();

