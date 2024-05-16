//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP
#include "Avatar/PathUtility.hpp"
#include "Display/Grid.hpp"
#include "Display/Line.hpp"
#include "Map/MapUtility.hpp"
#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "glm/glm.hpp"

#define SPEED 1

class Moving {
protected:
    std::deque<MoveDirection> m_MovePath;

    std::vector<Line> m_lineVector;
    glm::vec2 m_CurrentLocation;
    glm::vec2 m_DestinationLocation;

    MoveDirection m_CurrentDir = MoveDirection::IDLE;

    float m_MovementSpeed = 1.F;
    glm::vec2 m_PrevCell;

public:
    enum class AvatarStandingCorner {
        CENTER,
        UPPER_LEFT,
        UPPER_RIGHT,
        LOWER_LEFT,
        LOWER_RIGHT
    };

    Moving(){};
    virtual ~Moving(){};

    glm::vec2 getCurrentCell() {
        return MapUtil::GlobalCoordToCellCoord(getCurrentLocation());
    }
    glm::vec2 getCurrentLocation() { return m_CurrentLocation; }
    void setCurrentLocation(glm::vec2 location) {
        m_CurrentLocation = location;
    }
    MoveDirection getCurrentDir() { return m_CurrentDir; }

    void moveToNextCell();
    void moveToCellCorner(AvatarStandingCorner corner);
    bool ifArrivedAtNextCell();

    void setMovePath(std::deque<MoveDirection> movepath) {
        m_MovePath = movepath;
        m_CurrentDir = m_MovePath.front();
        m_MovePath.pop_front();
        m_PrevCell = getCurrentCell();
    }

    void setMovementSpeed(float speed) { m_MovementSpeed = speed; }

    glm::vec2 getDestinationCell() {
        return MapUtil::CellCoordToGlobal(m_DestinationLocation);
    }
    void setDestinationCell(glm::vec2 destination) {
        m_DestinationLocation = MapUtil::GlobalCoordToCellCoord(destination);
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_MOVING_HPP