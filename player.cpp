#include"player.h"

Player::Player() {
    maxblood = 60;
    blood = 60;
    shield = 0;
    maxenergy = 3;
    energy = 3;
    money = 0;
    n = 6;
    y = 3;
    MyAllCards = {1,1,1,2,2,2};
}

void Player::RecBlood(int x) {
    blood += x;
    blood = std::min(blood, maxblood);
}

void Player::DecBlood(int x) {
    blood -= x;
}

void Player::RecShield(int x) {
    shield += x;
}

void Player::DecShield(int x) {
    shield -= x;
}

void Player::RecEnergy(int x) {
    energy += x;
}

void Player::RecMaxEnergy() {
    energy = maxenergy;
}

void Player::DecEnergy(int x) {
    energy -= x;
}

void Player::RecMoney(int x) {
    money += x;
}

void Player::DecMoney(int x) {
    money -= x;
}

void Player::DropCards(int i) {
    MyAllCards.erase(MyAllCards.begin() + i);
    n--;
}

std::vector<int> Player::ReturnPlayerCards() {
    return MyAllCards;
}

int Player::ReturnPlayerMaxBlood() {
    return maxblood;
}

int Player::ReturnPlayerBlood() {
    return blood;
}

int Player::ReturnPlayerEnergy() {
    return energy;
}

int Player::ReturnPlayerMoney() {
    return money;
}

int Player::ReturnPlayerY() {
    return y;
}

int Player::ReturnPlayerN() {
    return n;
}

Room* Player::ReturnPlayerLocation() const {
    return currentRoom;
}

bool Player::SetPlayerLocation(Room* room) {
    if (room) {
        currentRoom = room;
        return true;
    }
    return false;
}

bool Player::ChooseStartRoom(const std::vector<std::vector<Room*>>& layers) {
    if (layers.empty() || layers[0].empty()) return false;

    std::cout << "Please chose the room to start:\n";
    for (int i = 0; i < layers[0].size(); ++i) {
        Room* room = layers[0][i];
        std::cout << "  " << i << ". room " << room->id << " [" << roomTypeToString(room->type) << "]\n";
    }

    int choice;
    std::cout << "Please select the room code (0-" << layers[0].size() - 1 << "): ";
    std::cin >> choice;

    if (choice >= 0 && choice < layers[0].size()) {
        currentRoom = layers[0][choice];
        return true;
    }

    // std::cout << "无效选择，默认使用第一个房间。\n";
    currentRoom = layers[0][0];
    return false;
}