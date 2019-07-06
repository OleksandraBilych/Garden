#include <climits>

#include "farmer.h"
#include "globalVariables.h"

Farmer::Farmer(const std::string& name, unsigned int water)
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
}

void Farmer::removeTheCheapestPlant()
{
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
