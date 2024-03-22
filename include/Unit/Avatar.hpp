//
// Created by nudle on 2024/3/15.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP
#include "Unit/PathfindingUnit.hpp"
#include "Unit/WayPointUnit.hpp"

class Avatar : public PathfindingUnit {
private:
    WayPointUnit m_wayPointUnit;
    bool b_SelectedByCursor = true;
    bool b_justStarted = true;

public:
    Avatar()
        : PathfindingUnit(){};
    ~Avatar() override{};

    virtual void Start(glm::vec2 destination) { // destination = Barrack's
                                                // waypointLocation
        // setCurrentCell()  //CurrentCell = Structure's Location
        this->SetDrawable(
            std::make_unique<Util::Image>("../assets/sprites/capybara.png"));
        SetVisible(true);
        m_grid.SetActivate(true);

        setCurrentCell(destination);
        setNextCell(destination);
        m_wayPointUnit.setCurrentCell(destination);
        m_wayPointUnit.setNextCell(destination);
        setNewDestination(getCurrentCell());

        setMovementSpeed(4);
    }
    virtual void aliveUpdate() {
        if (walkTowardNextCell() || b_justStarted) {
            b_justStarted = false;
            setCurrentCell(
                MapClass::GlobalCoordToCellCoord(getCurrentLocation()));
            setCurrentDir(m_wayPointUnit.getFirstCellDir());
            UpdateNextCell();
            printf("(aliveUpdate) getting new dir\n");
        }
        m_wayPointUnit.Update();
        m_Transform.translation = getCurrentLocation();
        Draw();
        cursorSetNewDest();
        printf("-----------------------------\n");
    }
    virtual void Update() override {
        switch (m_currentMode) {
        case (UnitMode::DEAD): {
            SetVisible(false);
        }
        case (UnitMode::ALIVE): {
            aliveUpdate();
        }
        }
    }
    void setNewDestination(glm::vec2 destination) {
        setDestinationCell(destination.x, destination.y);
        m_wayPointUnit.resetQueue();
        m_wayPointUnit.setCurrentCell(getNextCell());
        m_wayPointUnit.setNextCell(getNextCell());
        m_wayPointUnit.findPath(getDestinationCell());
        // setCurrentDir(m_wayPointUnit.getFirstCellDir());
    }
    void cursorSetNewDest() {
        if (b_SelectedByCursor &&
            Util::Input::IsKeyPressed(Util::Keycode::MOUSE_RB)) {
            this->setNewDestination(
                MapClass::GlobalCoordToCellCoord(MapClass::ScreenToGlobalCoord(
                    Util::Input::GetCursorPosition())));
        }
    }
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_DUMMY_HPP