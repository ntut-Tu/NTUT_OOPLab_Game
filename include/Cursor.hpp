//
// Created by 盧威任 on 4/13/24.
//

#ifndef PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
#define PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
#include "DrawOverlays.hpp"
#include "Map/Map.hpp"
#include "Map/MapUtility.hpp"
#include "Structure/Structure.hpp"
class CursorClass {
public:
    CursorClass() {
        m_testdraw.Start(std::vector({glm::vec2(0.F, 0.F)}),
                         DrawOverlays::OverlayShapes::R_CROSS);
    }
    ~CursorClass() {}
    void Update(std::shared_ptr<TileClass> tile) {
        DrawWalkable(tile->getWalkable());
        ShowCursorSelectionRegion(&start_pos, &end_pos, ImGuiMouseButton_Left);
        Util::Transform trans2;
        trans2.translation = Structure::PositionStickToGrid(
            MapUtil::ScreenToGlobalCoord(Util::Input::GetCursorPosition()));
        m_testdraw.DrawUsingCamera(trans2, 1);
    }

    void DrawWalkable(bool tilewalkable) {
        if (tilewalkable) {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_BOXES);
        } else {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_CROSS);
        }
    }

    void DrawBuildable(bool tilebuildable) {
        if (tilebuildable) {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::B_SLATED);
        } else {
            m_testdraw.setDrawMode(DrawOverlays::OverlayShapes::R_SLATED);
        }
    }

    void ShowCursorSelectionRegion(ImVec2 *start_pos, ImVec2 *end_pos,
                                   ImGuiMouseButton mouse_button) {
        IM_ASSERT(start_pos != NULL);
        IM_ASSERT(end_pos != NULL);
        if (ImGui::IsMouseClicked(mouse_button))
            *start_pos = ImGui::GetMousePos();
        if (ImGui::IsMouseDown(mouse_button)) {
            *end_pos = ImGui::GetMousePos();
            ImDrawList *draw_list =
                ImGui::GetForegroundDrawList(); // ImGui::GetWindowDrawList();
            draw_list->AddRect(
                *start_pos, *end_pos,
                ImGui::GetColorU32(IM_COL32(255, 255, 255, 255))); // Border
        }
    }

private:
    DrawOverlays m_testdraw;
    ImVec2 start_pos;
    ImVec2 end_pos;
};
#endif // PRACTICALTOOLSFORSIMPLEDESIGN_CURSOR_HPP
