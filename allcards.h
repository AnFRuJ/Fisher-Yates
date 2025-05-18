#ifndef ALLCARDS_H
#define ALLCARDS_H

#include<vector>
#include<array>

class AllCards {
    private:
        int n;
        std::vector<std::array<int, 8>> molds;    //花费，攻击，护盾， 回血， 掉血， 回能量， 抽卡， 弃牌 
    
    public:
        AllCards();
        int ReturnCardCost(int x);
        int ReturnCardAttack(int x);
        int ReturnCardShield(int x);
    };

#endif