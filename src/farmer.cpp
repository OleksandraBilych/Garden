#include <climits>
#include <fstream>

#include "farmer.h"
#include "globalVariables.h"
#include "objectConverter.hpp"
#include "log.h"

Farmer::Farmer(const std::string& name, unsigned water)
    : name(name), water(water)
{
    garden.reset(new Garden(globVar::gardenSize));
    init();
}

Farmer::Farmer(Farmer&& other) noexcept
{
    name = other.name;
    water = other.water;
    journal = std::move(other.journal);
    garden = std::move(other.garden);
    receivedSeeds = std::move(other.receivedSeeds);
    seedsToSend = std::move(other.seedsToSend);
}

Farmer& Farmer::operator=(Farmer&& other) noexcept
{
    name = other.name;
    water = other.water;
    journal = std::move(other.journal);
    garden = std::move(other.garden);
    receivedSeeds = std::move(other.receivedSeeds);
    seedsToSend = std::move(other.seedsToSend);

    return *this;
}

void Farmer::init()
{
    PRINT("init farmer");
    std::ifstream initPlants;
    json j;

    try {
        initPlants.open(globVar::initSettingsFile, std::ifstream::in);
    } catch (std::ios_base::failure& e) {
        PRINT(e.what());
    }

    initPlants >> j;
    json plants = j.at("plants");

    for (auto& plant : plants) {
        addSeedToSend(Converter::toPlant(plant)
                            , Converter::toAmount(plant));
    }
    
    initPlants.close();
    PRINT("exit init");
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

        // TO DO: add dependency with the journal
        rating = plant.getValue() / plant.getGrowTime() / plant.getFrequency() * plant.getConsumedWater();
        if (minRating < rating) {
            minRating = rating;
            minPos = pos;
        }
    }

    garden->removePlant(minPos);
    journal.erase(minPos);
}

std::string Farmer::getSeed()
{
    std::string seed;
    if (seedsToSend.empty()) {
        PRINT("seedsToSend is empty");
        return seed;
    }

    seed = Converter::toJson(seedsToSend.back()).dump();
    PRINT("Sending:\n" + seed);
    seedsToSend.pop_back();

    return seed;
}

void Farmer::addReceivedSeed(Plant&& sort, unsigned amount)
{
    receivedSeeds.push_back(FuturePlant(std::move(sort), amount));
}

void Farmer::addSeedToSend(Plant&& sort, unsigned amount)
{
    seedsToSend.push_back(FuturePlant(std::move(sort), amount));
}

void Farmer::plantSeed()
{
    PRINT("Plant seed");

    if (!garden->hasFreeSpots()) {
        return;
    }

    //determine which seed is the best
    unsigned bestRating{0};
    unsigned rating{0};
    unsigned pos{0};

    for (int i = receivedSeeds.size() - 1; i >= 0; --i) {
        auto& plant = receivedSeeds[i].sort;
        rating = plant.getValue() / plant.getGrowTime() / plant.getFrequency() * plant.getConsumedWater();

        if (bestRating > rating) {
            bestRating = rating;
            pos = i;
        }
    }

    //plant seed
    unsigned short plantPos = garden->addPlant(std::move(receivedSeeds[pos].sort));
    receivedSeeds[pos].amount--;

    //add to journal
    journal.emplace(plantPos,Days(garden->getLastPlant().getFrequency()
                                , garden->getLastPlant().getGrowTime()));

    //remove seed if its amount = 0
    if (!receivedSeeds[pos].amount) {
        receivedSeeds.erase(receivedSeeds.begin() + pos);
    }
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
    std::cout << "List of all plants" << std::endl;
    garden->printAllPlants();
}
