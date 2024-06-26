cmake_minimum_required(VERSION 3.16)
project(PracticalToolsForSimpleDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    set(TARGET_COMPILE_OPTIONS
            /W4
    )

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build)
else ()
    set(TARGET_COMPILE_OPTIONS
            -Wall -Wextra -pedantic
    )
endif ()

if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # see https://github.com/ntut-open-source-club/practical-tools-for-simple-design/issues/22
    set(CMAKE_RC_FLAGS="-C 1252")
endif ()

option(PTSD_ENABLE_PCH "Turn on PCH to increase compilation speed" OFF)


## yaml
include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_GetProperties(yaml-cpp)

if (NOT yaml-cpp_POPULATED)
    message(STATUS "Fetching yaml-cpp...")
    FetchContent_Populate(yaml-cpp)
    add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif ()


include(cmake/Dependencies.cmake)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_FILES
        ${SRC_DIR}/Core/Context.cpp
        ${SRC_DIR}/Core/DebugMessageCallback.cpp
        ${SRC_DIR}/Core/VertexArray.cpp
        ${SRC_DIR}/Core/VertexBuffer.cpp
        ${SRC_DIR}/Core/IndexBuffer.cpp
        ${SRC_DIR}/Core/Shader.cpp
        ${SRC_DIR}/Core/Program.cpp
        ${SRC_DIR}/Core/Texture.cpp
        ${SRC_DIR}/Core/TextureUtils.cpp


        ${SRC_DIR}/Util/LoadTextFile.cpp
        ${SRC_DIR}/Util/Logger.cpp
        ${SRC_DIR}/Util/Time.cpp
        ${SRC_DIR}/Util/Input.cpp
        ${SRC_DIR}/Util/SFX.cpp
        ${SRC_DIR}/Util/BGM.cpp
        ${SRC_DIR}/Util/Image.cpp
        ${SRC_DIR}/Util/Text.cpp
        ${SRC_DIR}/Util/TransformUtils.cpp
        ${SRC_DIR}/Util/GameObject.cpp
        ${SRC_DIR}/Util/Renderer.cpp
        ${SRC_DIR}/Util/Color.cpp
        ${SRC_DIR}/Util/Animation.cpp
        ${SRC_DIR}/Util/MissingTexture.cpp


        ${SRC_DIR}/Display/ImageArray.cpp
        ${SRC_DIR}/Display/CustomizableImage.cpp
        ${SRC_DIR}/Display/SpriteSheetAnimation.cpp

        ${SRC_DIR}/Display/Grid.cpp
        ${SRC_DIR}/Display/SpriteSheet.cpp


        ${SRC_DIR}/App.cpp

        ${SRC_DIR}/AI/AI.cpp
        ${SRC_DIR}/AI/AIScripts.cpp
        ${SRC_DIR}/AI/AIGroupCommander.cpp

        ${SRC_DIR}/Structure/Structure.cpp
        ${SRC_DIR}/Structure/WayPoint.cpp
        ${SRC_DIR}/Structure/HighLight.cpp
        ${SRC_DIR}/UI/UIScriptProcess.cpp

        ${SRC_DIR}/Structure/Barracks.cpp
        ${SRC_DIR}/Structure/OreRefinery.cpp
        ${SRC_DIR}/Structure/PowerPlants.cpp
        ${SRC_DIR}/Structure/WarFactory.cpp
        ${SRC_DIR}/Structure/WayPointStructure.cpp

        ${SRC_DIR}/Scene/MapScene.cpp
        ${SRC_DIR}/Scene/TutorialScene.cpp
        ${SRC_DIR}/Scene/SandBoxScene.cpp

        ${SRC_DIR}/Avatar/Avatar.cpp
        ${SRC_DIR}/Avatar/PathUtility.cpp
        ${SRC_DIR}/Avatar/Moving.cpp

        ${SRC_DIR}/Scene/DefaultScene.cpp
        ${SRC_DIR}/Camera.cpp

        ${SRC_DIR}/UI/IngameUI.cpp

        ${SRC_DIR}/Map/YAMLReader.cpp
        ${SRC_DIR}/Map/TerrainConfig.cpp
        ${SRC_DIR}/Map/MapbinReader.cpp
        ${SRC_DIR}/Map/Map.cpp

        ${SRC_DIR}/Mechanics/AvatarNavigator.cpp
        ${SRC_DIR}/Mechanics/GameObjectID.cpp
        ${SRC_DIR}/Mechanics/CursorSelection.cpp
        ${SRC_DIR}/Mechanics/AvatarManager.cpp
        ${SRC_DIR}/Mechanics/UnitManager.cpp
        ${SRC_DIR}/Mechanics/BuiltStructure.cpp
        ${SRC_DIR}/Mechanics/NemesisManager.cpp

)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_FILES
        ${INCLUDE_DIR}/Map/Map.hpp
        ${INCLUDE_DIR}/Map/MapUtility.hpp
        ${INCLUDE_DIR}/Util/AssetStore.hpp
        ${INCLUDE_DIR}/Map/MapbinReader.hpp
        ${INCLUDE_DIR}/Map/YAMLReader.hpp

        ${INCLUDE_DIR}/Core/Context.hpp
        ${INCLUDE_DIR}/Core/DebugMessageCallback.hpp
        ${INCLUDE_DIR}/Core/VertexArray.hpp
        ${INCLUDE_DIR}/Core/VertexBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.inl
        ${INCLUDE_DIR}/Core/IndexBuffer.hpp
        ${INCLUDE_DIR}/Core/Shader.hpp
        ${INCLUDE_DIR}/Core/Program.hpp
        ${INCLUDE_DIR}/Core/Texture.hpp
        ${INCLUDE_DIR}/Core/TextureUtils.hpp
        ${INCLUDE_DIR}/Core/Drawable.hpp
        ${INCLUDE_DIR}/Structure/WayPointStructure.hpp


        ${INCLUDE_DIR}/Util/LoadTextFile.hpp
        ${INCLUDE_DIR}/Util/Logger.hpp
        ${INCLUDE_DIR}/Util/Time.hpp
        ${INCLUDE_DIR}/Util/Input.hpp
        ${INCLUDE_DIR}/Util/Keycode.hpp
        ${INCLUDE_DIR}/Util/SFX.hpp
        ${INCLUDE_DIR}/Util/BGM.hpp
        ${INCLUDE_DIR}/Util/Text.hpp
        ${INCLUDE_DIR}/Util/Transform.hpp
        ${INCLUDE_DIR}/Util/TransformUtils.hpp
        ${INCLUDE_DIR}/Util/GameObject.hpp
        ${INCLUDE_DIR}/Util/Renderer.hpp
        ${INCLUDE_DIR}/Util/Color.hpp
        ${INCLUDE_DIR}/Util/Image.hpp
        ${INCLUDE_DIR}/Util/Animation.hpp
        ${INCLUDE_DIR}/Util/MissingTexture.hpp


        ${INCLUDE_DIR}/Display/SpriteSheetAnimation.hpp
        ${INCLUDE_DIR}/Display/ImageArray.hpp
        ${INCLUDE_DIR}/Display/CustomizableImage.hpp
        ${INCLUDE_DIR}/Display/DrawOverlays.hpp

        ${INCLUDE_DIR}/Scene/MapScene.hpp


        ${INCLUDE_DIR}/App.hpp
        ${INCLUDE_DIR}/Tile.hpp
        ${INCLUDE_DIR}/config.hpp


        ${INCLUDE_DIR}/config.hpp


        ${INCLUDE_DIR}/Sprite.hpp
        ${INCLUDE_DIR}/Settings.hpp
        ${INCLUDE_DIR}/Camera.hpp
        ${INCLUDE_DIR}/DrawOverlays.hpp
        ${INCLUDE_DIR}/Task.hpp

        ${INCLUDE_DIR}/Structure/Structure.hpp
        ${INCLUDE_DIR}/Structure/WayPoint.hpp
        ${INCLUDE_DIR}/Structure/IWayPointStructure.hpp
        ${INCLUDE_DIR}/HighLight.h
        ${INCLUDE_DIR}/House.hpp

        ${INCLUDE_DIR}/DrawOverlays.hpp

        ${INCLUDE_DIR}/Player.hpp

        ${INCLUDE_DIR}/Structure/Barracks.hpp
        ${INCLUDE_DIR}/Structure/OreRefinery.hpp
        ${INCLUDE_DIR}/Structure/PowerPlants.hpp
        ${INCLUDE_DIR}/Structure/WarFactory.hpp
        ${INCLUDE_DIR}/Structure/ADVPowerPlants.hpp
        ${INCLUDE_DIR}/Structure/SandBag.hpp

        ${INCLUDE_DIR}/Avatar/Moving.hpp
        ${INCLUDE_DIR}/Avatar/Avatar.hpp
        ${INCLUDE_DIR}/Avatar/WayPointUnit.hpp
        ${INCLUDE_DIR}/Avatar/Runner.hpp
        ${INCLUDE_DIR}/Avatar/Hunter.hpp

        ${INCLUDE_DIR}/UI/UIScriptProcess.hpp
        ${INCLUDE_DIR}/UI/UI.hpp
        ${INCLUDE_DIR}/UI/IngameUI.hpp
        ${INCLUDE_DIR}/UI/UIStatus.hpp


        ${INCLUDE_DIR}/Scene/Scene.hpp
        ${INCLUDE_DIR}/Scene/TutorialScene.hpp
        ${INCLUDE_DIR}/Scene/SandBoxScene.hpp


        ${INCLUDE_DIR}/AI/AI.hpp
        ${INCLUDE_DIR}/AI/AIScripts.hpp
        ${INCLUDE_DIR}/AI/AIGroupCommander.hpp


        ${INCLUDE_DIR}/Core/Context.hpp
        ${INCLUDE_DIR}/Core/DebugMessageCallback.hpp
        ${INCLUDE_DIR}/Core/VertexArray.hpp
        ${INCLUDE_DIR}/Core/VertexBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.hpp
        ${INCLUDE_DIR}/Core/UniformBuffer.inl
        ${INCLUDE_DIR}/Core/IndexBuffer.hpp
        ${INCLUDE_DIR}/Core/Shader.hpp
        ${INCLUDE_DIR}/Core/Program.hpp
        ${INCLUDE_DIR}/Core/Texture.hpp

        ${INCLUDE_DIR}/Mechanics/GameObjectManager.hpp
        ${INCLUDE_DIR}/Mechanics/NemesisManager.hpp
        ${INCLUDE_DIR}/Mechanics/GameObjectID.hpp
        ${INCLUDE_DIR}/Mechanics/CursorSelection.hpp
        ${INCLUDE_DIR}/Mechanics/Spawn.hpp
        ${INCLUDE_DIR}/Mechanics/AvatarNavigator.hpp

)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)


set(TEST_FILES
        ${TEST_DIR}/SimpleTest.cpp
        ${TEST_DIR}/NotSimpleTest.cpp
        ${TEST_DIR}/TransformTest.cpp
)

add_executable(Sample
        ${SRC_FILES}
        ${SRC_DIR}/main.cpp
)
target_link_libraries(Sample
yaml-cpp::yaml-cpp
        SDL2::SDL2main # IDK what happens if we don't link SDL2main
        ${DEPENDENCY_LINK_LIBRARIES}
)
##yaml

target_include_directories(Sample SYSTEM PRIVATE 
        ${DEPENDENCY_INCLUDE_DIRS}
)
target_include_directories(Sample PRIVATE
        ${INCLUDE_DIR}
)


if (${PTSD_ENABLE_PCH})
    target_precompile_headers(Sample PRIVATE
            include/pch.hpp
    )


endif ()
target_compile_options(Sample PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)


enable_testing()

add_executable(Tests
        ${TEST_FILES}
        ${SRC_FILES}
)
target_link_libraries(Tests
        GTest::gtest_main
yaml-cpp::yaml-cpp
        ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(Tests SYSTEM PRIVATE
        ${DEPENDENCY_INCLUDE_DIRS}
        lib/googletest/googletest/include
        lib/googletest/googlemock/include
)
target_include_directories(Tests PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(Tests PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)

add_executable(AudioTest
        ${TEST_DIR}/Interactive/Audio.cpp
        ${SRC_FILES}
)
target_link_libraries(AudioTest
        GTest::gtest_main
yaml-cpp::yaml-cpp
        ${DEPENDENCY_LINK_LIBRARIES}
)
target_include_directories(AudioTest SYSTEM PRIVATE
        ${DEPENDENCY_INCLUDE_DIRS}
        lib/googletest/googletest/include
        lib/googletest/googlemock/include
)
target_include_directories(AudioTest PRIVATE
        ${INCLUDE_DIR}
)
target_compile_options(AudioTest PRIVATE
        ${TARGET_COMPILE_OPTIONS}
)


include(GoogleTest)
gtest_discover_tests(Tests)
