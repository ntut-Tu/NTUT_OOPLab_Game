//
// Created by nudle on 2024/4/28.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP
#include "AI/EnemyScripts.hpp"
#include "Cursor.hpp"
#include "Scene.hpp"
#include "Util/Prop.hpp"
#include <glm/glm.hpp>

#define DEBUG_KEY P

class SandBoxScene : public Scene {
    enum class Stages { STAGE1, STAGE2, STAGE3, STAGE4, START, END };

public:
    SandBoxScene(){};
    ~SandBoxScene(){};
    void Start() override;
    void Update() override;
    void stageStart();
    void stageUpdate();

private:
    SpriteSheet m_SpriteSheet;
    std::shared_ptr<CursorClass> m_Cursor = std::make_shared<CursorClass>();
    Grid testGrid;
    std::shared_ptr<EnemyPlayer> m_Enemy =
        std::make_shared<EnemyPlayer>(SceneMode::TUTORIAL);
    std::shared_ptr<EnemyScripts> m_EnemyScripts =
        std::make_shared<EnemyScripts>();
    Stages m_stage = Stages::START;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_SANDBOXSCENE_HPP