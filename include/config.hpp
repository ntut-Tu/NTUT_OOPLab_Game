#ifndef CONFIG_H
#define CONFIG_H

#include "pch.hpp" // IWYU pragma: export

#include "Util/Logger.hpp"

constexpr const char *TITLE = "Practical Tools for Simple Design";

constexpr int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
constexpr int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;

constexpr Util::Logger::Level DEFAULT_LOG_LEVEL = Util::Logger::Level::DEBUG;

/**
 * @brief FPS limit
 *
 * Set value to 0 to turn off FPS cap
 */
constexpr unsigned int FPS_CAP = 60;

/**
 * @brief Avatar limit for player
 */

constexpr unsigned int CAP_LIMIT = 200;

/**
 * @brief CELL_SIZE
 */
constexpr glm::vec2 CELL_SIZE = {48.F, 48.F};

const std::string PATH_TO_TEMPERAT_TILESET_YAML = "../assets/map/temperat.yaml";

#endif
