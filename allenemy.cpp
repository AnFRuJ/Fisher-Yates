#include"allenemy.h"

AllEnemy::AllEnemy() {
    modles_n = 2;
    elit_n = 2;
    boss_n = 2;    //种类，血量，攻击， 护盾, 最大护盾, 回盾
    molds.push_back({0,   0,    0,    0,    0,       0});
    molds.push_back({1,   20,   5,    5,    5,       5});
    molds.push_back({2,   50,   5,    0,    0,       5});

    elit.push_back({0,    0,    0,    0,    0,       0});
    elit.push_back({1,    80,   10,   10,   10,      10});
    elit.push_back({2,    20,   10,   40,   40,      15});

    boss.push_back({0,    0,    0,    0,    0,       0});
    boss.push_back({1,    300,  20,   0,    0,       15});
    boss.push_back({2,    180,  15,   20,   20,      20});
}

std::array<int, 6> AllEnemy::CopyEnemy(int i) {
    return molds[i];
}

std::array<int, 6> AllEnemy::CopyElit(int i) {
    return elit[i];
}

std::array<int, 6> AllEnemy::CopyBoss(int i) {
    return boss[i];
}