//
// Created by 盧威任 on 5/3/24.
//

#include "Mechanics/AvatarManager.hpp"

void AvatarManager::giveOrderToAvatar(std::shared_ptr<Avatar> unit) {

    auto queue = m_Navigator->findPath(unit->getCurrentCell(),
                                       unit->getDestinationCell());
    // unit
    unit->setMovePath(queue);
    unit->setNewDestinationIsSetted(false);

    if (m_Map->getTileByCellPosition(unit->getDestinationCell())
            ->ifEnemyAtTile()) {
        m_NemesisManager->addNemesis(
            unit, m_Map->getTileByCellPosition(unit->getDestinationCell())
                      ->getAvatars()[0]);
    } else {
        unit->setAvatarOrder(AvatarOrderType::MOVE);
    }
}
