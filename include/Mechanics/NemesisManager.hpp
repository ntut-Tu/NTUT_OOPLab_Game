//
// Created by 盧威任 on 5/3/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
#include "Avatar/Avatar.hpp"
#include "Map/MapUtility.hpp"

class NemesisManager {
public:
    NemesisManager() {}
    ~NemesisManager() {}
    void addNemesis(std::shared_ptr<Avatar> avatar,
                    std::shared_ptr<Huntable> nemesis) {
        m_Nemesis[avatar] = nemesis;
    }

    void removeNemesis(std::shared_ptr<Avatar> avatar) {
        if (ifAvatarHasNemesis(avatar)) {
            m_Nemesis.erase(avatar);
        }
    }

    bool ifAvatarHasNemesis(std::shared_ptr<Avatar> avatar) {
        if (m_Nemesis.count(avatar)) {
            return true;
        } else {
            return false;
        }
    }
    glm::vec2 getNemesisCell(std::shared_ptr<Avatar> avatar) {
        if (!ifAvatarHasNemesis(avatar)) {
            return {-1.f, -1.f};
        }
        return m_Nemesis[avatar]->getCurrentLocationInCell();
    }
    bool ifNemesisWithinWeaponRange(std::shared_ptr<Avatar> hunter);

    void Update();

private:
    std::unordered_map<std::shared_ptr<Avatar>, std::shared_ptr<Huntable>>
        m_Nemesis;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_NEMESISMANAGER_HPP
