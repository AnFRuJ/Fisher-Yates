#ifndef ALLENEMY_H
#define ALLENEMY_H

#include<vector>
#include<array>

class AllEnemy {
private:
    int modles_n;
    int elit_n;
    int boss_n;
    std::vector<std::array<int, 6>> molds;
    std::vector<std::array<int, 6>> elit;
    std::vector<std::array<int, 6>> boss;
public:
    AllEnemy();
    std::array<int, 6> CopyEnemy(int i);
    std::array<int, 6> CopyElit(int i);
    std::array<int, 6> CopyBoss(int i);


};

#endif