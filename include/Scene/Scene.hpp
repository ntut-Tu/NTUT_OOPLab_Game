//
// Created by 盧威任 on 2/16/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
#include "Camera.hpp"
#include "Core/Context.hpp"
#include "Map/MapBinReader.hpp"
#include "Map/YAMLReader.hpp"
#include "Mechanics/GameObjectManager.hpp"

#include "Camera.hpp"
#include "DrawOverlays.hpp"
#include "Grid.hpp"
#include "Map/Map.hpp"
#include "SpriteSheet.hpp"
#include "Structure/AdvencePowerPlants.hpp"
#include "Structure/Barracks.hpp"
#include "Structure/IWayPoint.hpp"
#include "Structure/OreRefinery.hpp"
#include "Structure/PowerPlants.hpp"
#include "Structure/WarFactory.hpp"
#include "Structure/WayPoint.hpp"
#include "UI/UI.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Renderer.hpp"
#include <vector>
class Scene {
public:
    Scene() {}
    virtual ~Scene() {}
    void Init();
    virtual void Start() = 0;
    /*
    void addObjectToScene(std::shared_ptr<Object> object) {
        m_ObjectList.push_back(object);
        if (m_IsRunning) {
            object->Start();
        }
    }
     */
    virtual void Update() = 0;

    CameraClass getCamera() { return m_SceneCamera; };

protected:
    CameraClass m_SceneCamera;
    std::shared_ptr<MapClass> m_Map = std::make_shared<MapClass>();

    std::shared_ptr<GameObjectManager> m_GameObjectManager =
        std::make_shared<GameObjectManager>();
    Util::Renderer m_Renderer;
    UIClass m_UI;
    std::shared_ptr<Player> m_Player = std::make_shared<Player>();
};

#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SCENE_HPP
