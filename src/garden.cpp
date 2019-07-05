#include <functional>

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

void Garden::addPlant(Plant& plant)
{
    if (!freeSpots)
    {
        return;
    }

    plants.push_back(plant);
    freeSpots--;
}

void Garden::removePlant(Plant& plant)
{
    if (!plants.empty()) {
        plants.remove(std::ref(plant));
    }
}
