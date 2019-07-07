#include <climits>

#include "farmer.h"
#include "globalVariables.h"

Farmer::Farmer(const std::string& name, unsigned water)
    : name(name), water(water)
{
    garden.reset(new Garden(gardenSize));
}

Farmer::Farmer(Farmer&& other) noexcept
{
    name = other.name;
    water = other.water;
    journal = std::move(other.journal);
    garden = std::move(other.garden);
}

Farmer& Farmer::operator=(Farmer&& other) noexcept
{
    name = other.name;
    water = other.water;
    journal = std::move(other.journal);
    garden = std::move(other.garden);

    return *this;
}

const std::string& Farmer::getName() const
{
    return name;
}

unsigned int Farmer::getWater() const
{
    return water;
}

void Farmer::setName(const std::string& name)
{
    this->name = name;
}

void Farmer::setWater(unsigned value)
{
    this->water = value;
}

void Farmer::checkPlants()
{
    if (garden->isEmpty())
        return;

    for(auto& [pos, d] : journal) {
        auto& plant = garden->getPlantWithPos(pos);

        // check if the plant is alive
        if (!plant.getIsAlive()) {
            garden->removePlant(pos);
            journal.erase(pos);
        }

        // check if the plant is ripened
        if (d.daysToRipe == 0) {
            plant.setIsRipened(true);
            garden->removePlant(pos);
            journal.erase(pos);
        }

        // check if the plant needs watering
        if (d.daysToWatering == 0) {
            plant.watering(water);
            d.daysToWatering = plant.getFrequency();
            d.daysToRipe--;
        } else if (d.daysToWatering > 0) {
            d.daysToWatering--;
            d.daysToRipe--;
        }
    }
}

void Farmer::removeTheCheapestPlant()
{
    if (garden->isEmpty())
        return;

    unsigned minRating{UINT_MAX};
    int minPos{0};
    unsigned rating{0};

    for(auto& [pos, days] : journal) {
        auto& plant = garden->getPlantWithPos(pos);

        rating = plant.getGrowTime() / plant.getFrequency() * plant.getConsumedWater();
        if (minRating > rating) {
            minRating = rating;
            minPos = pos;
        }
    }

    garden->removePlant(minPos);
    journal.erase(minPos);
}

void Farmer::printRipePlants()
{
    std::cout << "List of ripe plants, total value is " << garden->calculateValue() << std::endl;
    garden->printRipePlants();
}

void Farmer::printGrowingPlants()
{
    std::cout << "List of qrowing plants" << std::endl;
    garden->printGrowingPlants();
}

void Farmer::printRipeandGrowingPlants()
{
    std::cout << "List of ripe and qrowing plants" << std::endl;
    std::cout << "Ripe:\n";
    garden->printRipePlants();

    std::cout << "Growing:\n";
    garden->printGrowingPlants();
}

void Farmer::printAllPlants()
{
    std::cout << "List of qrowing plants" << std::endl;
    garden->printAllPlants();
}
