#include "Mage.h"

void Mage::rangedAttack(Character& target) {
    int distance = std::abs(target.posX - posX) + std::abs(target.posY - posY);
    if (distance <= viewRange) {
        int damage = attack - target.defense;
        if (damage < 0) damage = 0;
        target.hp -= damage;
        if (target.hp < 0) target.hp = 0;
    }
}
