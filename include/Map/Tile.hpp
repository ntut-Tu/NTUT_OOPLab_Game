//
// Created by 盧威任 on 2/29/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP

#include "Mechanics/GameObjectID.hpp"
#include "Selectable.hpp"
#include "Unit/Avatar.hpp"

#include "SpriteSheet.hpp"
#include "Structure/Structure.hpp"
#include "Unit/Avatar.hpp"
#include <unordered_map>
class TileClass {
public:
    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable, std::string tileimagepath)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_Clickable(clickable),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_TileImagePath(tileimagepath) {}

    TileClass(const unitType unittype, bool buildable, bool walkable,
              bool clickable)
        : m_Id(GameObjectID(unittype, HouseType::NONE)),
          m_TerrainBuildable(buildable),
          m_TerrainWalkable(walkable),
          m_Clickable(clickable),
          m_TileImagePath("") {}
    TileClass()
        : m_Id(GameObjectID(unitType::null, HouseType::NONE)),
          m_TerrainBuildable(true),
          m_TerrainWalkable(true),
          m_Clickable(true),
          m_TileImagePath(""){};
    ~TileClass() {}

    bool getWalkable() { return m_TerrainWalkable; };
    bool getBuildable() { return m_TerrainBuildable; };
    bool getClickable() { return m_Clickable; };
    std::string getTileImagePath() { return m_TileImagePath; }
    std::vector<std::shared_ptr<Selectable>> getSelectableObjects() {

        std::vector<std::shared_ptr<Selectable>> selectables;
        if (m_Avatars.size() >= 1) {
            for (auto i : m_Avatars) {
                selectables.push_back(i);
            }
        } else {
            selectables.push_back(m_Structure);
        }
        return selectables;
    }

    void setWalkable(bool value) { m_TerrainWalkable = value; };
    void setBuildable(bool value) { m_TerrainBuildable = value; };
    void setClickable(bool value) { m_Clickable = value; };
    void setTileImage(std::string path) { m_TileImagePath = path; };

    void setStructure(std::shared_ptr<Structure> structure) {
        m_Structure = structure;
    }
    void pushAvatars(std::shared_ptr<Avatar> avatar) {
        m_Avatars.push_back(avatar);
        if (m_Avatars.size() == 4) {
            setWalkable(false);
        }
    }

    std::vector<std::shared_ptr<Avatar>> getAvatars() { return m_Avatars; }

    void removeAvatar(std::shared_ptr<Avatar> avatar) {
        for (auto i : m_Avatars) {
            if (i == avatar) {
                std::remove(m_Avatars.begin(), m_Avatars.end(), i);
                if (m_Avatars.size() < 4) {
                    setWalkable(true);
                }
                return;
            }
        }
        LOG_DEBUG("Remove Avatar Failed");
    }

    void removeStructure() {
        m_Structure = std::make_shared<Structure>();
        setWalkable(true);
        setBuildable(true);
    }
    void clearAvatars() {
        m_Avatars.clear();
        setWalkable(true);
        setBuildable(true);
    }

    TileClass &operator=(const TileClass &tile) {
        this->m_TerrainWalkable = tile.m_TerrainWalkable;
        this->m_Clickable = tile.m_Clickable;
        this->m_TileImagePath = tile.m_TileImagePath;

        this->m_TerrainBuildable = tile.m_TerrainBuildable;
        this->m_Id = tile.m_Id;
        return *this;
    }

private:
    bool m_TerrainWalkable;
    bool m_TerrainBuildable;
    bool m_Clickable;
    std::shared_ptr<Structure> m_Structure = std::make_shared<Structure>();
    std::vector<std::shared_ptr<Avatar>> m_Avatars;

    std::string m_TileImagePath;
    GameObjectID m_Id;
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_TILE_HPP
