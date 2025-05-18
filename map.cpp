#include"map.h"


Map::Map() : rng(static_cast<unsigned>(time(0))), connDist(1, 2) {}


std::vector<std::vector<Room*>> Map::generate(int levels, int minRooms, int maxRooms) {
    layers.clear();
    idCounter = 1;

    std::uniform_int_distribution<int> roomCountDist(minRooms, maxRooms);
    std::uniform_int_distribution<int> probDist(0, 99);  // 用于概率判断

    // 定义房间类型的概率分布
    std::vector<RoomType> roomTypes = {
        RoomType::MONSTER, RoomType::MONSTER, RoomType::MONSTER, RoomType::MONSTER, RoomType::MONSTER,
        RoomType::ELITE_MONSTER, 
        RoomType::EVENT, 
        RoomType::SHOP, 
        RoomType::TREASURE, 
        RoomType::REST
    };

    // 生成第一层固定 3 个房间
    std::vector<Room*> firstLayer;
    for (int i = 0; i < 3; ++i) {
        firstLayer.push_back(new Room(idCounter++, 0, RoomType::MONSTER));
    }
    layers.push_back(firstLayer);

    // 生成后续层，房间数随机
    for (int depth = 1; depth < levels - 1; ++depth) {
        int roomCount = roomCountDist(rng);
        std::vector<Room*> layer;
        for (int i = 0; i < roomCount; ++i) {
            RoomType type = roomTypes[std::uniform_int_distribution<int>(0, roomTypes.size() - 1)(rng)];
            if(depth == levels - 2) type = RoomType::REST;
            layer.push_back(new Room(idCounter++, depth, type));
        }
        layers.push_back(layer);
    }

    // 生成最后一层，只有一个房间
    std::vector<Room*> lastLayer;
    lastLayer.push_back(new Room(idCounter++, levels - 1, RoomType::BOSS));
    layers.push_back(lastLayer);

    // 链接房间（只向下或右下，带随机性）
    for (int depth = 0; depth < levels - 2; ++depth) {
        int nextSize = layers[depth + 1].size();
        for (int i = 0; i < layers[depth].size(); ++i) {
            Room* room = layers[depth][i];

            // 向下（同列）
            if (i < nextSize && probDist(rng) < 70) {
                room->next.push_back(layers[depth + 1][i]);
            }

            // 向右下（下一列）
            if (i + 1 < nextSize && probDist(rng) < 50) {
                room->next.push_back(layers[depth + 1][i + 1]);
            }
            

            // 确保至少连接一个房间
            if (room->next.empty()) {
                int fallback = std::min(i, nextSize - 1);
                room->next.push_back(layers[depth + 1][fallback]);
            }
        }
    }

    // 连接倒数第二层的所有房间到最后一层
    int secondLastLayerIndex = levels - 2;  // 倒数第二层的索引
    for (Room* room : layers[secondLastLayerIndex]) {
        room->next.push_back(layers[levels - 1][0]);  // 最后一层的唯一房间
    }

    // 遍历并删除未访问的房间
    std::unordered_set<Room*> visited;
    std::function<void(Room*)> dfs = [&](Room* room) {
        if (visited.count(room)) return;
        visited.insert(room);
        for (Room* nextRoom : room->next) {
            dfs(nextRoom);
        }
    };

    // 从第一层的所有房间开始遍历
    for (Room* startRoom : layers[0]) {
        dfs(startRoom);
    }

    // 清理未被访问的房间
    for (auto& layer : layers) {
        std::vector<Room*> newLayer;
        for (Room* room : layer) {
            if (visited.count(room)) {
                // 清理它的 next，只保留指向 visited 的
                std::vector<Room*> newNext;
                for (Room* nextRoom : room->next) {
                    if (visited.count(nextRoom)) {
                        newNext.push_back(nextRoom);
                    }
                }
                room->next = std::move(newNext);
                newLayer.push_back(room);
            } else {
                delete room; // 删除无效房间，避免内存泄漏
            }
        }
        layer = std::move(newLayer);
    }

    return layers;
}