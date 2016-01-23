#pragma once

#include <atomic>
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <SFML/Window.hpp>
#include <mingw.thread.h> //both these are a patch to fix threads with mingw!! you can remove these when you merge plz
#include <mingw.mutex.h> //both these are a patch to fix threads with mingw!! you can remove these when you merge plz
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
