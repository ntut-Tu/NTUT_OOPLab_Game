//
// Created by 盧威任 on 2/15/24.
//
#include "Scene/MapScene.hpp"
#include "DrawOverlays.hpp"
#include <iostream>
void MapScene::Start() {

    m_Map = reading.readBin("../assets/map/europe/map.bin", 204, 161);
    // OccupiedID::InitID();
    //  image.SetImage("../assets/sprites/Shapes/B_Box.png");
    /*

    LOG_TRACE("Start");

    m_GameObjectList[0]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/Raccoon3.jpg"));
    m_GameObjectList[0]->SetZIndex(10);

    m_GameObjectList[1]->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/capybara.png"));

    m_Structure->SetDrawable(
        std::make_unique<Util::Image>("../assets/sprites/barracks.png"));
    m_Structure->SetZIndex(0);
    m_Structure->SetObjectLocation({0, 0});
    m_Structure->Start();
    m_Structure->SetCurrentUpdateMode(Structure::updateMode::Moveable);
    m_Renderer.AddChild(m_Structure);

    m_Inf->Start();

    for (auto i : m_GameObjectList) {
        i->Start();
    }

    m_Renderer.AddChild(m_Structure);

    // init map
    m_TileSetSpriteSheet->Start("../assets/sprites/TILESET_Field.png", 24, 24,
                                20, 0);

    m_OgMap = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    m_OgMap = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<std::shared_ptr<TileClass>> maps;
    for (unsigned int i = 0; i < 10; i++) {
        maps.push_back(std::make_shared<TileClass>("rock-" + std::to_string(i),
                                                   false, false, true, i));
    }
 doing some weird stuff, fix is needed
    std::vector<std::shared_ptr<TileClass>> maps =
        m_Map.readMapAndTileSet(m_OgMap, m_tileSets);


    m_Map.Init(255, 255);
    m_UI.Start();
    m_testdraw.Start(std::vector({glm::vec2(0.F, 0.F)}),
                     DrawOverlays::OverlayShapes::R_CROSS);
    // m_GameObjectManager.Start();
    */
}

void MapScene::Update() {
    m_SceneCamera.Update();
    Util::Transform trans;
    trans.scale = {1, 1};
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 30; j++) {
            trans.translation = {i * 24.F, j * 24.F};
            m_Map[i][j]->drawTileImage(trans, 1);
        }
    }
}
