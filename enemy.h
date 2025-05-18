#ifndef ENEMY_H  // 头文件保护符，防止重复包含
#define ENEMY_H

#include <vector>
#include <array>
#include"allenemy.h"
#include <iostream>

class Enemy {
private:
    int n;
    std::vector<std::array<int, 6>> count;
public:
    Enemy();
    Enemy(AllEnemy allenemy, int c);  // 构造函数声明
    int ReturnEnemyCounts();
    void attacked(int i, int x);
    int ReturnEnemyBlood(int i);
    int ReturnEnemyShield(int i);
    int attack();
    void RecShield();
};

#endif