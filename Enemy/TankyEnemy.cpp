#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "TankyEnemy.hpp"

TankyEnemy::TankyEnemy(int x, int y)
    : Enemy("play/enemy-4.png", x, y, 30, 20, 1000, 50) {
}

