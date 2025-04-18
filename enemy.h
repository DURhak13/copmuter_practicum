#pragma once
#include "player.h"
#include <vector>
#include <string>
#include "types.h"

using Map = std::vector<std::vector<char>>; //


struct Enemy {
    int x, y;
    int health;
    int attack;
    std::string name;

    virtual void takeTurn(Player& player, Map& level) = 0;
    virtual char getSymbol() const = 0;
    virtual bool occupiesPosition(int px, int py) const {
        return (x == px && y == py);
    }
};

struct Dog : public Enemy {
    Dog(int startX, int startY) {
        x = startX;
        y = startY;
        health = 30;
        attack = 5;
        name = "Dog";
    }
    void takeTurn(Player& player, Map& level) override;
    char getSymbol() const override { return 'D'; }

};

struct Ogre : public Enemy {
    int width = 2;
    int height = 2;

    Ogre(int startX, int startY) {
        x = startX;
        y = startY;
        health = 100;
        attack = 20;
        name = "Ogre";
    }

    void takeTurn(Player& player, Map& level) override;
    char getSymbol() const override { return 'O'; }
    bool occupiesPosition(int px, int py) const override {
        return (px >= x && px <= x + 1) && (py >= y && py <= y + 1);
    }
};


struct SkeletonArcher : public Enemy {
    SkeletonArcher(int startX, int startY) {
        x = startX;
        y = startY;
        health = 20;
        attack = 10;
        name = "SkeletonArcher";
    }
    void takeTurn(Player& player, Map& level) override;
    char getSymbol() const override { return 'A'; }
};


