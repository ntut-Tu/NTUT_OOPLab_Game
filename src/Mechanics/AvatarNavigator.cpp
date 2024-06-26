//
// Created by 盧威任 on 4/12/24.
//

#include "Mechanics/AvatarNavigator.hpp"

std::deque<MoveDirection> AvatarNavigator::findPath(glm::vec2 currentcell,
                                                    glm::vec2 destinationcell) {
    glm::vec2 ogcell = currentcell;

    std::vector<std::deque<MoveDirection>> dirQueComp = {
        std::deque<MoveDirection>(), std::deque<MoveDirection>()};

    if (m_Map->getTileByCellPosition(destinationcell)->getWalkable() == false) {
        return dirQueComp[0];
    }

    for (int s = 0; s < 2; s++) {
        Side whichSideToTouchObstacle = static_cast<Side>(s);
        int count = 0;
        currentcell = ogcell;
        while (currentcell != destinationcell && count < 10) {
            printf("(findPath)\n");
            count++;
            std::vector<MoveDirection> staightDirque;
            bool canFindStraightPath =
                findStraightPath(currentcell, destinationcell, &staightDirque);

            // push newdirque into dirque and update current cell and current
            // dir

            if (canFindStraightPath) {
                for (auto i : staightDirque) {
                    dirQueComp[s].push_back(i);
                    currentcell =
                        PathUtility::getNextCellByCurrent(i, currentcell);
                }
            } else {

                auto facingDir = PathUtility::getDirByRelativeCells(
                    currentcell, destinationcell);
                // turn
                MoveDirection turndir;
                if (m_Map->ifWalkable(PathUtility::getNextCellByCurrent(
                        facingDir, currentcell)) == false) {
                    turndir = findNewDirWhenCrash(whichSideToTouchObstacle,
                                                  currentcell, facingDir);
                };

                std::vector<MoveDirection> movealong =
                    moveAlongsideObstacle(whichSideToTouchObstacle, currentcell,
                                          turndir, destinationcell);

                for (auto i : movealong) {
                    dirQueComp[s].push_back(i);
                    currentcell =
                        PathUtility::getNextCellByCurrent(i, currentcell);
                }
            }
        }
    }

    if (dirQueComp[0].size() > dirQueComp[1].size() && !dirQueComp[1].empty()) {
        return dirQueComp[1];
    } else {
        return dirQueComp[0];
    }
}

std::vector<MoveDirection>
AvatarNavigator::moveAlongsideObstacle(Side side, glm::vec2 currentcell,
                                       MoveDirection currentdir,
                                       glm::vec2 destinationcell) {
    glm::vec2 ogcell = currentcell;

    std::vector<MoveDirection> path;
    while (!(canResumeWalkingStraight(currentcell, destinationcell) ||
             currentcell == destinationcell)) {
        printf("(moveAlongsideObstacle)\n");
        // if next is not touched by obstacle, turn
        if (!isTouchedByObstacle(side, currentcell, currentdir)) {
            currentdir = PathUtility::findNewDirWhenNotTouchedByObstacle(
                side, currentcell, currentdir);
        }

        // if next to be obstacle, turn findNewDirWhenCrash
        currentdir = findNewDirWhenCrash(side, currentcell, currentdir);

        // walk along
        path.push_back(currentdir);
        currentcell =
            PathUtility::getNextCellByCurrent(currentdir, currentcell);

        if (path.size() > 30 || ogcell == currentcell) {

            return path;
        }
    }
    // std::vector<sp> findStraightPath(currentcell, destinationcell, )

    if (path.size() == 1) {
        return std::vector<MoveDirection>();
    } else {
        return path;
    }
}

MoveDirection AvatarNavigator::findNewDirWhenCrash(Side side,
                                                   glm::vec2 currentcell,
                                                   MoveDirection currentdir) {
    MoveDirection newdir = currentdir;
    int crashCount = 0;
    while (m_Map
               ->getTileByCellPosition(
                   PathUtility::getNextCellByCurrent(newdir, currentcell))
               ->getWalkable() == false) {
        switch (newdir) {
        case MoveDirection::RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_RIGHT;
            }
        } break;

        case MoveDirection::LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_LEFT;
            }
            break;
        }
        case MoveDirection::UP: {
            if (side == Side::R) {
                newdir = MoveDirection::UP_LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP_RIGHT;
            }
            break;
        }
        case MoveDirection::DOWN: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN_RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN_LEFT;
            }
            break;
        }
        case MoveDirection::UP_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::UP;
            } else if (side == Side::L) {
                newdir = MoveDirection::RIGHT;
            }
            break;
        }
        case MoveDirection::DOWN_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::DOWN;
            } else if (side == Side::L) {
                newdir = MoveDirection::LEFT;
            }
            break;
        }
        case MoveDirection::DOWN_RIGHT: {
            if (side == Side::R) {
                newdir = MoveDirection::RIGHT;
            } else if (side == Side::L) {
                newdir = MoveDirection::DOWN;
            }
            break;
        }
        case MoveDirection::UP_LEFT: {
            if (side == Side::R) {
                newdir = MoveDirection::LEFT;
            } else if (side == Side::L) {
                newdir = MoveDirection::UP;
            }
            break;
        }
        case MoveDirection::IDLE: {
            // printf("Direction debug didn't move\n");
            break;
        }
        }
        //        newdir=recursionCrashHandler(newdir,crashCount);
        crashCount++;
    }
    return newdir;
}
MoveDirection AvatarNavigator::recursionCrashHandler(MoveDirection currentDir,
                                                     int count) {
    int enumSize = 8;
    int newDirValue = (static_cast<int>(currentDir) + count) % enumSize;
    if (newDirValue < 0) {
        newDirValue += enumSize;
    }
    printf("(recursionCrashHandler)crashCount : %d\n", count);
    return static_cast<MoveDirection>(newDirValue);
}
bool AvatarNavigator::isTouchedByObstacle(Side side, glm::vec2 currentcell,
                                          MoveDirection currentdir) {
    currentcell = PathUtility::getNextCellByCurrent(currentdir, currentcell);
    // abs
    std::shared_ptr<TileClass> upTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x, currentcell.y + 1));
    std::shared_ptr<TileClass> downTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x, currentcell.y - 1));
    std::shared_ptr<TileClass> rightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y));
    std::shared_ptr<TileClass> leftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y));

    std::shared_ptr<TileClass> upRightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y + 1));
    std::shared_ptr<TileClass> downRightTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x + 1, currentcell.y - 1));
    std::shared_ptr<TileClass> upLeftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y + 1));
    std::shared_ptr<TileClass> downLeftTile = m_Map->getTileByCellPosition(
        glm::vec2(currentcell.x - 1, currentcell.y - 1));

    std::shared_ptr<TileClass> checkedTile = std::make_shared<TileClass>();
    switch (currentdir) {
    case MoveDirection::RIGHT:
        if (side == Side::R) {
            checkedTile = downTile;
        } else if (side == Side::L) {
            checkedTile = upTile;
        }
        break;

    case MoveDirection::LEFT:
        if (side == Side::R) {
            checkedTile = upTile;
        } else if (side == Side::L) {
            checkedTile = downTile;
        }
        break;

    case MoveDirection::UP:
        if (side == Side::R) {
            checkedTile = rightTile;
        } else if (side == Side::L) {
            checkedTile = leftTile;
        }
        break;

    case MoveDirection::DOWN:
        if (side == Side::R) {
            checkedTile = leftTile;
        } else if (side == Side::L) {
            checkedTile = rightTile;
        }
        break;

    case MoveDirection::UP_RIGHT:
        if (side == Side::R) {
            checkedTile = rightTile;
        } else if (side == Side::L) {
            checkedTile = upTile;
        }
        break;

    case MoveDirection::DOWN_LEFT:
        if (side == Side::R) {
            checkedTile = leftTile;
        } else if (side == Side::L) {
            checkedTile = downTile;
        }
        break;

    case MoveDirection::DOWN_RIGHT:
        if (side == Side::R) {
            checkedTile = downTile;
        } else if (side == Side::L) {
            checkedTile = rightTile;
        }
        break;

    case MoveDirection::UP_LEFT:
        if (side == Side::R) {
            checkedTile = upTile;
        } else if (side == Side::L) {
            checkedTile = leftTile;
        }
        break;

    case MoveDirection::IDLE:
        // printf("Direction debug didn't move\n");
        break;
    }

    if (checkedTile->getWalkable() == true) {
        return false;
    } else {
        return true;
    }
}

bool AvatarNavigator::findStraightPath(glm::vec2 currentcell,
                                       glm::vec2 destinationcell,
                                       std::vector<MoveDirection> *path) {
    bool ifwalked = false;
    while (currentcell != destinationcell) {
        printf("(findStraightPath)\n");
        MoveDirection followingDir =
            PathUtility::getDirByRelativeCells(currentcell, destinationcell);

        if (m_Map->ifWalkable(
                PathUtility::getNextCellByCurrent(followingDir, currentcell))) {
            path->push_back(followingDir);
            currentcell =
                PathUtility::getNextCellByCurrent(followingDir, currentcell);
            ifwalked = true;
        } else {
            return ifwalked;
        }
    }
    if (path->size() > 1 || currentcell == destinationcell) {
        return ifwalked;
    } else {
        return false;
    }
}

bool AvatarNavigator::canResumeWalkingStraight(glm::vec2 currentcell,
                                               glm::vec2 destinationcell) {
    std::vector<MoveDirection> path;
    auto walkedS = findStraightPath(currentcell, destinationcell, &path);
    if (walkedS && path.size() > 3) {
        return true;
    }
    return false;
}

Side AvatarNavigator::randomlyChooseSide() {
    // Create a random number generator engine
    std::random_device rd;  // Obtain a random seed from the hardware
    std::mt19937 gen(rd()); // Initialize the Mersenne Twister
                            // pseudo-random number generator

    // Define a distribution (uniform distribution in this case)
    std::uniform_int_distribution<int> distribution(
        0, 1); // Uniform distribution between 1 and 6 (inclusive)

    // Generate a random number
    int random_number = distribution(gen); // Generate a random number using
                                           // the generator and distribution

    switch (random_number) {
    case 0:
        return Side::R;
    case 1:
        return Side ::L;
    }
}
