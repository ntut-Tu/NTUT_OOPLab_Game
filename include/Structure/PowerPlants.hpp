#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_STRUCTURE_PowerPlants_HPP

#include "Structure.hpp"

class PowerPlants : public Structure {
public:
    PowerPlants(float electricPower = 100.F, float buildingTime = 15.F * CHEAT,
                float buildingCost = 300.F, float buildingHp = 400.F,
                HouseType house = HouseType::MY)
        : Structure(electricPower, buildingTime, buildingCost, buildingHp,
                    GameObjectID(UnitType::POWER_PLANT, house)){
              //        SetDrawable(
              //            std::make_unique<Util::Image>("../assets/sprites/PowerPlants.png"));
          };
    PowerPlants(HouseType house)
        : Structure(100.F, 15.F * CHEAT, 300.F,400.F,
                    GameObjectID(UnitType::POWER_PLANT, house)){};
    void SetSpriteSheet() override {
        m_StructureSpriteSheet->Start(
            "../assets/sprites/PowerPlants_SpriteSheet.png", 48, 48, 13, 0);
        m_RelativeOccupiedArea = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    }
    void SetObjectLocation(glm::vec2 location) override {
        location = MapUtil::PositionStickToGrid(location);
        m_ObjectLocation = location;
        m_DrawLocation = {location.x + 1 * CELL_SIZE.x,
                          location.y + 1 * CELL_SIZE.y};
        m_Transform.translation = m_DrawLocation;
    }
};

#endif
