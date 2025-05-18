#include"enemy.h"

Enemy::Enemy() {

}

Enemy::Enemy(AllEnemy allenemy, int c) {
    n = 1;
    if(c == 1){
        count.push_back(allenemy.CopyEnemy(2));
    }else if(c == 2){
        count.push_back(allenemy.CopyElit(1));
    }else{
        count.push_back(allenemy.CopyBoss(1));
    }
}

int Enemy::ReturnEnemyCounts() {
    return n;
}

void Enemy::attacked(int i, int x) {
    if(count[i][3] != 0){
        if(count[i][3] >= x){
            count[i][3] -= x;
        }else{
            x -= count[i][3];
            count[i][3] = 0;
            count[i][1] -= x;
        }
    }else{
        count[i][1] -= x;
    }
}

int Enemy::ReturnEnemyBlood(int i) {
    return count[i][1];
}

int Enemy::ReturnEnemyShield(int i) {
    return count[i][2];
}

int Enemy::attack() {
    int res = 0;
    for (int i = 0; i <= n; ++i) {
        res += count[i][2];
    }
    return res;
}

void Enemy::RecShield(){
    for(int i = 0; i <= n; ++i){
        count[i][3] = count[i][4];
    }
}