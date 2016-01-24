#pragma once

#include <atomic>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <mingw.thread.h>
#include <mingw.mutex.h>
#include <SFML/Window.hpp>
#include "Mouse.hpp"
#include "Snake.hpp"

class MouseSpawner
{
public:

    MouseSpawner(sf::RenderWindow* window);
    ~MouseSpawner();

    void spawn();
    void checkCollisions(Snake& snake);

    void draw() const;

    std::size_t size();

    bool active();

private:

    std::mt19937                                   randomEngine;
    std::uniform_int_distribution<int>             xDistribution;
    std::uniform_int_distribution<int>             yDistribution;
    std::map<std::uint8_t, std::unique_ptr<Mouse>> spawnedMice;
    std::unique_ptr<std::thread>                   timedSpawner;
    sf::RenderWindow*                              window;
    std::atomic_bool                               threadActive;
    std::uint8_t                                   nextId;
    std::mutex                                     mutex;
};
