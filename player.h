#ifndef PLAYER_H
#define PLAYER_H

#include<vector>
#include"map.h"

class Player {
    private:
        int maxblood;
        int blood;
        int shield;
        int maxenergy;
        int energy;
        int money;
        int n;  //n张卡牌
        int y;  //每次抽y张卡
        std::vector<int> MyAllCards;

        Room* currentRoom = nullptr;
    public:
        Player();
        void RecBlood(int x);
        void DecBlood(int x);
        void RecShield(int x);
        void DecShield(int x);
        void RecEnergy(int x);
        void RecMaxEnergy();
        void DecEnergy(int x);
        void RecMoney(int x);
        void DecMoney(int x);
        void DropCards(int i);
        std::vector<int> ReturnPlayerCards();
        int ReturnPlayerMaxBlood();
        int ReturnPlayerBlood();
        int ReturnPlayerEnergy();
        int ReturnPlayerMoney();
        int ReturnPlayerY();
        int ReturnPlayerN();

        Room* ReturnPlayerLocation() const;
        bool SetPlayerLocation(Room* room);
        bool ChooseStartRoom(const std::vector<std::vector<Room*>>& layers);
    };

#endif