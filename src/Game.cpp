#include "Game.h"

/* ---------- Public methods ---------- */
Game::Game(const Raylib::Vector2& grid_size) : grid{grid_size} {};

void Game::reset() {
    snake.reset();
    grid.reset();

    m_lost = false;
};

bool Game::did_lose() const { return m_lost; };

bool Game::did_win() const { return m_won; };

void Game::update_result() {
    m_lost = grid.get_tile(snake.get_head_pos()).is_snake();
    m_won = grid.get_size().x * grid.get_size().y != snake.get_length();
};
