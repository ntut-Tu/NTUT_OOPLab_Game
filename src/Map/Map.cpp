//
// Created by 盧威任 on 3/30/24.
//

#include "Map/Map.hpp"

void MapClass::setTileByCellPosition(glm::vec2 position,
                                     std::shared_ptr<TileClass> tile) {

    if (position.x > m_MapWdith - 1 || position.y > m_MapHeight - 1 ||
        position.x < 0 || position.y < 0) {
        LOG_DEBUG("False Position Setting");
        return;
    }
}

void MapClass::InitGrid() {
    std::vector<Line> lineV;

    auto width = CELL_SIZE.x * m_MapWdith;
    auto height = CELL_SIZE.y * m_MapHeight;
    for (int i = 0; i < m_MapWdith + 1; i++) {
        // horz
        lineV.push_back(Line(glm::vec2(0, i * CELL_SIZE.y),
                             glm::vec2(width, i * CELL_SIZE.y)));
    }
    for (int j = 0; j < m_MapHeight + 1; j++) {
        // height
        lineV.push_back(Line(glm::vec2(j * CELL_SIZE.x, 0),
                             glm::vec2(j * CELL_SIZE.x, height)));
    }

    m_Grid.Start(lineV);
    m_Grid.SetActivate(true);
}

std::shared_ptr<TileClass> MapClass::getTileByCellPosition(glm::vec2 position) {

    if (position.x > m_MapWdith - 1 || position.y > m_MapHeight - 1 ||
        position.x < 0 || position.y < 0) {
        LOG_DEBUG("False Position Getting");
        return std::make_shared<TileClass>(unitType::null, 0, 0, 0, "");
    }
    return m_Map[position.x][position.y];
}

void MapClass::Draw(const Util::Transform &trans, const float zindex) {

    Util::Transform mapTrans;

    mapTrans.translation = m_MapPosition;
    for (auto i : m_Images) {
        i->DrawUsingCamera(mapTrans, 1);
    }
    m_Grid.DrawUsingCamera(mapTrans, zindex);
}

void MapClass::Init(std::vector<std::vector<std::shared_ptr<TileClass>>> map,
                    unsigned int width, unsigned int height) {

    m_MapWdith = width;
    m_MapHeight = height;
    m_Map = map;

    // m_Map = map;

    InitGrid();

    for (int i = 0; i < m_Map.size(); i++) {
        for (int j = 0; j < m_Map[i].size(); j++) {

            auto findResult = m_Tiles.find(m_Map[i][j]->getTileImagePath());
            if (findResult != m_Tiles.end()) {
                m_Tiles[m_Map[i][j]->getTileImagePath()].push_back(
                    glm::vec2(i, m_MapHeight - j));
            } else {
                m_Tiles[m_Map[i][j]->getTileImagePath()] =
                    std::vector<glm::vec2>({glm::vec2(i, m_MapHeight - j)});
            }
        }
    }

    for (auto pair : m_Tiles) {
        m_Images.push_back(std::make_shared<Util::ImageArray>(
            m_spriteFolder + pair.first, pair.second));
    }
}

void MapClass::Init(unsigned int width, unsigned int height) {
    m_MapWdith = width;
    m_MapHeight = height;
    for (int i = 0; i < m_MapHeight; i++) {
        std::vector<std::shared_ptr<TileClass>> row;
        for (int j = 0; j < m_MapWdith; j++) {
            row.push_back(std::make_shared<TileClass>());
        }
        MapClass::m_Map.push_back(row);
    }
    InitGrid();
}
