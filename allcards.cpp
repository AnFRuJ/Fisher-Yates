#include"allcards.h"

AllCards::AllCards() {
    n = 6;         //花费，攻击，护盾， 回血， 掉血， 回能量， 抽卡， 弃牌 
    molds.push_back({0,   0,    0,    0,     0,     0,      0,    0});   //nothing
    molds.push_back({1,   6,    0,    0,     0,     0,      0,    0});   //最基本的攻击牌
    molds.push_back({1,   0,    6,    0,     0,     0,      0,    0});   //最基本的护盾牌
    molds.push_back({1,   12,   0,    0,     2,     0,      0,    0});   //掉两滴血，双倍伤害
    molds.push_back({1,   0,    12,   0,     0,     0,      0,    1});   //弃一张牌，两倍护盾
    molds.push_back({1,   0,    0,    0,     0,     0,      2,    0});   //抽两张卡
}

int AllCards::ReturnCardCost(int x) {
    if(x < n && x >= 0)
        return molds[x][0];
    else
        return 100;
}

int AllCards::ReturnCardAttack(int x) {
    return molds[x][1];
}

int AllCards::ReturnCardShield(int x) {
    return molds[x][2];
}