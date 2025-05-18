#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include<functional>
#include <random>
#include <ctime>
#include<unordered_set>

enum class RoomType {
    MONSTER,       // 小怪房
    ELITE_MONSTER, // 精英怪房
    EVENT,         // 事件房
    SHOP,          // 商店房
    TREASURE,      // 宝箱房
    REST,          // 休息房
    BOSS           // Boss 房间
};

inline std::string roomTypeToString(RoomType type) {
    switch (type) {
        case RoomType::MONSTER:        return "small monster";
        case RoomType::ELITE_MONSTER:  return "elite monster";
        case RoomType::EVENT:          return "event room   ";
        case RoomType::SHOP:           return "shop         ";
        case RoomType::TREASURE:       return "treasure     ";
        case RoomType::REST:           return "rest room    ";
        case RoomType::BOSS:           return "BOSS         ";
        default:                       return "?            ";
    }
}

struct Room {
    int id;
    int depth;
    int pos;
    RoomType type;  // 新增房间类型
    std::vector<Room*> next;

    Room(int id, int depth, RoomType type, int pos = 0)
        : id(id), depth(depth), type(type), pos(pos) {}
};

template <typename T>
T clamp(T val, T low, T high) {
    return std::max(low, std::min(val, high));
}

class Map {
private:
    int idCounter = 1;
    std::mt19937 rng;
    std::uniform_int_distribution<int> connDist;
    std::vector<std::vector<Room*>> layers;
public:
    Map();
    std::vector<std::vector<Room*>> generate(int levels, int minRoomsPerLevel, int maxRoomsPerLevel);   //层，每层房间数量
};

#endif