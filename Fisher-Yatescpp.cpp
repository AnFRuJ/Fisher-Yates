#include <iostream>
#include <vector>
#include<array>
#include<set>
#include <algorithm>
#include <random>
#include <ctime>
#include<windows.h>

#include"playerlocation.h"
#include"shuffler.h"
#include"map.h"
#include"player.h"
#include"allcards.h"
#include"allenemy.h"
#include"enemy.h"
#include"events.h"

using namespace std;

void UponTheMap(Map& map, std::vector<std::vector<Room*>>& layers, Player& player) {
    for (const auto& layer : layers) {
        for (Room* room : layer) {
            std::cout << "Room " << room->id << " (Depth " << room->depth << ", " << roomTypeToString(room->type) << ")  -> ";
            for (Room* next : room->next) {
                std::cout << next->id << " ";
            }
            std::cout << "\n";
        }
        std::cout << "-------------------------\n";
    }
}

void MovePlayer(Player& player, std::vector<std::vector<Room*>>& layers) {
    if(player.ReturnPlayerLocation() == nullptr)    player.ChooseStartRoom(layers);  // 从第一层开始
    else{
        Room* cur = player.ReturnPlayerLocation();
        if (!cur) return;

        if (cur->next.empty()) {
            std::cout << "no room can go to!\n";
            return;
        }

        std::cout << "you can chose the room follows:\n";
        for (int i = 0; i < cur->next.size(); ++i) {
            std::cout << i << ". room " << cur->next[i]->id
                    << " [" << roomTypeToString(cur->next[i]->type) << "]\n";
        }

        int choice;
        std::cout << "Please enter the number: ";
        std::cin >> choice;

        if (choice >= 0 && choice < cur->next.size()) {
            player.SetPlayerLocation(cur->next[choice]);
        } else {
            std::cout << "invalid input. \n";
        }
    }
}

void InTheFight(Player& player, AllCards& allcards, AllEnemy& allenemy, int degree) {
    cout << "Initial Enemy" << endl;
    Enemy enemy;
    if (degree == 1) {
        enemy = Enemy(allenemy, 1);
    } else if (degree == 2) {
        enemy = Enemy(allenemy, 2);
    } else {
        enemy = Enemy(allenemy, 3);
    }

    Shuffler shuffler;
    shuffler.shuffle(player.ReturnPlayerCards());

    cout << "Initial shuffled" << endl;

    // system("cls");
    shuffler.PrintDeck();

    int x = player.ReturnPlayerN();
    int y = player.ReturnPlayerY();

    while (1) {
        if(shuffler.DiscardRemaining() == x){
            cout << endl << "\n=============================================================" 
                            << "\nAll cards are in the discard pile. Reshuffling the deck.   ||\n";
            shuffler.shuffle(player.ReturnPlayerCards());

            cout << "Initial shuffled deck" << endl;
            shuffler.PrintDeck();
        }

        int flag = 0;
        for(int i = 1; i <= enemy.ReturnEnemyCounts(); ++i){
            cout << "\n(the " << i << " enemy blood: "
            << enemy.ReturnEnemyBlood(i - 1) << "   shield: " << enemy.ReturnEnemyShield(i - 1) << ")" << endl;
        }
        cout << " (your blood: " << player.ReturnPlayerBlood() << "   your energy: " << player.ReturnPlayerEnergy() << ")\n";
        cout << "\n\n*********************************\nPlease select an option:\n"
            << "1: Draw cards\n"
            << "2: Discard cards\n"
            << "3: View hand\n"
            << "4: View deck\n"
            << "5: View discard pile\n"
            << "6: End your turn\n"
            << "0: Exit\n"
            << "*********************************" << endl;
        cin >> flag;
        system("cls");
        if(flag == 1){
            int drawCount = min(y, shuffler.DeckRemaining());
            if(drawCount != 0 && player.ReturnPlayerEnergy() != 0){
                vector<int> drawnCards = shuffler.draw(drawCount);

                cout << "Drew cards: ";
                for (int card : drawnCards) {
                    cout << card << " ";
                }
                player.DecEnergy(1);
            }else if(drawCount == 0){
                cout << "The deck is empty." << endl;
            }else{
                cout << "You haven't enough energy to draw card." << endl;
            }
        }else if(flag == 2){
            cout << "Enter the number of cards to discard: (-1 to return)" << endl ;
            shuffler.PrintHand();
            cout << endl;

            int pushCount;
            cin >> pushCount;
            while ((!shuffler.InHand(pushCount) || allcards.ReturnCardCost(pushCount) > player.ReturnPlayerEnergy()) && pushCount != -1) {  // 判断牌是否在手牌中
                if(allcards.ReturnCardCost(pushCount) > player.ReturnPlayerEnergy())
                    cout << "You haven't enough energy to push card" << pushCount << ". Please try again." <<endl;
                else
                    cout << "Card " << pushCount << " is not in your hand. Please try again." << endl;  // 不在手牌中
                cin >> pushCount;
            }
            if(pushCount != -1){
                cout << "Push cards: ";
                cout << pushCount << " ";
                shuffler.dis(pushCount);
                player.DecEnergy(allcards.ReturnCardCost(pushCount));
                enemy.attacked(1, allcards.ReturnCardAttack(pushCount));
            }else{
                system("cls");
            }
        }else if(flag == 3){
            shuffler.PrintHand();

            vector<int> v1 = shuffler.ReturnHand();
            set<int> s1(v1.begin(), v1.end());
            v1.assign(s1.begin(), s1.end());
            cout << "\n\n******************************************\n";
            for(auto i : v1){
                cout << "Card" << i << ": cost " << allcards.ReturnCardCost(i) << "   attack " << allcards.ReturnCardAttack(i) << endl;
            }
            cout << "******************************************\n";

        }else if(flag == 4){
            shuffler.PrintDeck();
        }else if(flag == 5){
            shuffler.PrintDiscard();
        }else if(flag == 6){
            // 将所有手牌丢弃
            vector<int> allCards;
            for (int card : shuffler.ReturnHand()) {
                allCards.push_back(card);
            }
            vector<int> pushCards = shuffler.disAll(allCards);
    
            cout << "All cards discarded: ";
            for (int card : pushCards) {
                cout << card << " ";
            }
            player.RecMaxEnergy(); //回复能量

            player.DecBlood(enemy.attack());    //被攻击
            

        }else if(flag == 0){
            break;
        }
    }

}

void InTheShop(Player& player, AllCards& allcards) { 
    int flag = 0;
    cout << "\n\n*********************************\nPlease select an option:\n"
    << "1: Recover blood for 30%  (your blood: " << player.ReturnPlayerBlood() << "/" << player.ReturnPlayerMaxBlood() << ")\n"
    << "2: Drop cards\n"
    << "0: Do nothing\n"
    << "*********************************" << endl;
}

void InTheLounge(Player& player) {
    int flag = 0;
    cout << "\n\n*********************************\nPlease select an option:\n"
    << "1: Recover blood for 30%  (your blood: " << player.ReturnPlayerBlood() << "/" << player.ReturnPlayerMaxBlood() << ")\n"
    << "2: Drop cards\n"
    << "0: Do nothing\n"
    << "*********************************" << endl;
    cin >> flag;
    if(flag == 0){

    }else if(flag == 1){
        int temp = player.ReturnPlayerBlood();
        temp = (int)temp *0.3;
        player.RecBlood(temp);
        cout << "(your blood: " << player.ReturnPlayerBlood() << "/" << player.ReturnPlayerMaxBlood() << ")\n";
        cout << "Press any number to continue\n";
        cin >> temp;
    }else if(flag == 2){
        int k = 0;
        for(auto i : player.ReturnPlayerCards()){
            ++k;
            if(k == 6){
                cout << endl;
                k = 0;
            }
            cout << i << "  ";
        }
        cout << "\nPlease select a cards to drop\n";
        int j = 0;
        cin >> j;
        while (j < 0 || j >= player.ReturnPlayerN()) {
            cout << "Please select the right number\n";
            cin >> j;
        }
        player.DropCards(j);
    }
}

void InTheEvent(Player& player) {
    // Events events;
}

void InTheTreasure() {

}

int main() {
    cout << "Welcome to the Fisher-Yates (Press 'Enter' to continue)" << endl;
    getchar();
    system("cls");

    cout << "Initial map" << endl;
    Map map;
    std::vector<std::vector<Room*>> tmp = map.generate(5, 3, 5);

    cout << "Initial all cards" << endl;
    AllCards allcards;

    cout << "Initial all enemys" << endl;
    AllEnemy allenemy;

    cout << "Initial Player" << endl;
    Player player;
    while(1){
        UponTheMap(map, tmp, player);
        MovePlayer(player, tmp);

        // 获取当前房间的类型
        Room* currentRoom = player.ReturnPlayerLocation();
        if (!currentRoom) {
            std::cout << "Unknow player location!\n";
            break;
        }
        switch (currentRoom->type) {
            case RoomType::MONSTER:
                InTheFight(player, allcards, allenemy, 1);
                break;
            case RoomType::ELITE_MONSTER:
                InTheFight(player, allcards, allenemy, 2);
                break;
            case RoomType::EVENT:
                InTheEvent(player);
                break;
            case RoomType::SHOP:
                InTheShop(player, allcards);
                break;
            case RoomType::TREASURE:
                InTheTreasure();
                break;
            case RoomType::REST:
                InTheLounge(player);
                break;
            case RoomType::BOSS:
                InTheFight(player, allcards, allenemy, 3);
                break;
            default:
                std::cout << "Unknow room.\n";
                break;
        }
    }

    return 0;
}
