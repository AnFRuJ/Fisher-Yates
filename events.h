#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>

enum class EventsType {
    MONSTER,       // 小怪事件
    BLOOD,         // 回血事件 
    MONEY,         // 加钱事件
    CARD,          // 抽牌事件
    TREASURE,      // 宝箱房
    REST,          // 休息房
    BOSS           // Boss 房间
};

inline std::string eventsTypeToString(EventsType type) {
    switch (type) {
        case EventsType::MONSTER:        return "small monster";
        case EventsType::BLOOD:       return "recover blood";
        case EventsType::MONEY:       return "add money    ";
        case EventsType::CARD:        return "Add card     ";
        case EventsType::TREASURE:       return "treasure     ";
        case EventsType::REST:           return "rest room    ";
        case EventsType::BOSS:           return "BOSS         ";
        default:                       return "?            ";
    }
}

class Events {
private:
    int n;

public:
    // Events();
    // int CallEvents();
};

#endif