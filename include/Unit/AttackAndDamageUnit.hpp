//
// Created by 盧威任 on 3/22/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
<<<<<<< HEAD

class AttackAndDamageUnit {
public:
    AttackAndDamageUnit() {}
    virtual ~AttackAndDamageUnit() {}
=======
#include "Avatar.hpp"
class AttackAndDameageUnit {
public:
    AttackAndDameageUnit() {}
    ~AttackAndDameageUnit() {}
>>>>>>> ae90c3b (attack and damage)

    int getHP() { return m_HP; }
    int getArmorRate() { return m_ArmorRate; }
    int getSoftAttack() { return m_SoftAttack; }
    int getHardAttack() { return m_HardAttack; }

    void setHP(int hp) { m_HP = hp; }
    void setArmorRate(int armor) { m_ArmorRate = armor; }
    void setSoftAttack(int softattack) { m_SoftAttack = softattack; }
    void setHardAttack(int hardattack) { m_SoftAttack = hardattack; }

    void takeDamage(int softattack, int hardattack) {
<<<<<<< HEAD
=======

>>>>>>> ae90c3b (attack and damage)
        m_HP -= (100 - m_ArmorRate) * (1 / 100) * softattack +
                m_ArmorRate * (1 / 100) * hardattack;
    }

<<<<<<< HEAD
    void ForceAttackUnit(std::shared_ptr<AttackAndDamageUnit> target) {
=======
    void ForceAttackUnit(std::shared_ptr<AttackAndDameageUnit> target) {
>>>>>>> ae90c3b (attack and damage)
        // check withinrange
        // cd time
        target->takeDamage(m_SoftAttack, m_HardAttack);
        return;
    }

private:
    int m_HP;
    float m_ArmorRate;
    int m_SoftAttack;
    int m_HardAttack;
    float m_AttackRange;
<<<<<<< HEAD
    float cd; // count as seconds
=======
    int cd;
>>>>>>> ae90c3b (attack and damage)
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_ATTACKANDDAMAGEUNIT_HPP
