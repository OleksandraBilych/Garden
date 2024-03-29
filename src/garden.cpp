#include <functional>
#include <iostream>

#include "garden.h"

Garden::Garden(unsigned short size) : size{size}, freeSpots{size}
{}

Garden::Garden(const Garden& other)
{
    size = other.size;
    freeSpots = other.size;
    plants = other.plants;
}

Garden::Garden(Garden&& other) noexcept
{
    size = other.size;
    freeSpots = other.size;
    plants = std::move(other.plants);
}

Garden& Garden::operator=(const Garden& other)
{
    size = other.size;
    freeSpots = other.size;
    plants = other.plants;

    return *this;
}

Garden& Garden::operator=(Garden&& other) noexcept
{
    size = other.size;
    freeSpots = other.size;
    plants = std::move(other.plants);

    return *this;
}

Garden::~Garden()
{
    size = 0;
    freeSpots = 0;
    plants.clear();
}

unsigned short Garden::getSize() const
{
    return size;
}

void Garden::setSize(unsigned short newSize)
{
    size = newSize;
}

bool Garden::isEmpty() const
{
    return !freeSpots;
}

bool Garden::hasFreeSpots() const
{
    return freeSpots;
}

int Garden::calculateValue() const
{
    int sum{0};

    for (auto& plant : plants) {
        if (plant.getIsRipened()) {
            sum += plant.getValue();
        }
    }

    return sum;
}

unsigned short Garden::addPlant(Plant&& plant)
{
    if (!freeSpots)
    {
        return -1;
    }

    plants.push_back(plant);
    freeSpots--;

    return plants.size() - 1;
}

void Garden::removePlant(unsigned short position)
{
    try {
        plants.at(position).setIsAlive(false);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
}

Plant& Garden::getPlantWithPos(unsigned position)
{
    try {
        plants.at(position);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }

    return plants.at(position);
}

Plant& Garden::getLastPlant() {
    return getPlantWithPos(plants.size() - 1);
}

void Garden::printRipePlants()
{
    for (auto& pl : plants) {
        if (pl.getIsRipened()) {
            std::cout << pl;
        }
    }
}

void Garden::printGrowingPlants()
{
    for (auto& pl : plants) {
        if (pl.getIsAlive() && !pl.getIsRipened()) {
            std::cout << pl;
        }
    }
}

void Garden::printAllPlants()
{
    for (auto& pl : plants) {
            std::cout << pl;
    }
}
