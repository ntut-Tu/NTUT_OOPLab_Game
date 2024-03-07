//
// Created by 盧威任 on 2/16/24.
//

#include "Grid.hpp"
#include "Core/Drawable.hpp"
#include <iostream>

void Grid::Start() {

    //debug grid:

    float cellWidth = 48.F;
    float cellHeight = 48.F;

    for (int i = (WINDOW_WIDTH / 2); i >= int(-(WINDOW_WIDTH / 2));
         i -= cellHeight) {
        // vertical
        m_lineVector.push_back(Line(glm::vec2(i, int(-(WINDOW_HEIGHT / 2))),
                                    glm::vec2(i, int(WINDOW_HEIGHT / 2))));
    }

    for (int i = (WINDOW_HEIGHT / 2); i >= int(-(WINDOW_HEIGHT / 2));
         i -= cellWidth) {
        // horz
        m_lineVector.push_back(Line(glm::vec2(int(-(WINDOW_WIDTH / 2)), i),
                                    glm::vec2(int(WINDOW_WIDTH / 2), i)));
    }

    // map grid

    /*
    m_lineVector.push_back(Line(glm::vec2(-640,0),glm::vec2(640,0)));
    m_lineVector.push_back(Line(glm::vec2(-50,3),glm::vec2(50,3)));
*/
    InitVertexAndColor();
}

void Grid::Draw(const Util::Transform &transform, const float zindex) {
    //nothing
}

void Grid::DrawUsingCamera(const Util::Transform &transform,
                           const float zIndex) {


    if (m_Activate == false) {
      //  return;
    }
    glLineWidth(m_lineWidth);

    m_Program.Bind();
    m_Program.Validate();
    m_VertexArray->Bind();

    auto cp=CameraClass::getProjectionMatrix();
    auto cv = CameraClass::getViewMatrix();

    constexpr glm::mat4 eye(1.F);


    auto view =
        glm::scale(eye, {1.F / WINDOW_WIDTH, 1.F / WINDOW_HEIGHT, 1.F}) *
        glm::translate(eye, {WINDOW_WIDTH, WINDOW_HEIGHT, 0});

    view*=CameraClass::getViewMatrix();
    auto projection=CameraClass::getProjectionMatrix();

    // TODO: TRS comment
    auto model = glm::translate(eye, {transform.translation, zIndex}) *
                 glm::rotate(eye, transform.rotation, glm::vec3(0, 0, 1)) *
                 glm::scale(eye, {transform.scale * glm::vec2{20.F,10.F}, 1});

     DrawLines data = {
        model,
        projection * view,
    };


    m_NewMatrices->SetData(0, data);
    m_VertexArray->Bind();

    m_VertexArray->DrawLines(m_lineVector.size() * 5 * 2);

}

void Grid::InitVertexAndColor() {
    int i=0;
    std::vector<float> vertex = {};
    std::vector<float> color = {};
    std::vector<unsigned int> index = {};
    for (auto line : m_lineVector) {
        vertex.push_back(line.getlineFrom().x);
        vertex.push_back(line.getlineFrom().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);

        vertex.push_back(line.getlineTo().x);
        vertex.push_back(line.getlineTo().y);
        color.push_back(line.getColor().x);
        color.push_back(line.getColor().y);
        color.push_back(line.getColor().z);


    }
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(vertex, 2));
    m_VertexArray->AddVertexBuffer(
        std::make_unique<Core::VertexBuffer>(color, 3));
}
