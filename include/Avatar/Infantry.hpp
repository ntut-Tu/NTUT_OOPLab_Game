//
// Created by nudle on 2024/3/22.
//
#include "Avatar/Avatar.hpp"
#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP

class Infantry : public Avatar {
public:
    Infantry()
        : Avatar() {
        setMovementSpeed(4),
            m_Health = std::make_shared<Health>(
                std::make_shared<LivingStatus>(LivingStatus::NOT_BORN_YET), 100,
                0.5);
    }

private:
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_INFANTRY_HPP
