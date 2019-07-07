/*
    An object of class Farmer takes care about the garden and plants
    He decided when add and remove plants
    He decided when water plants
    He checked plants constantly
    He receive new seeds and send seeds back
    He stasts his job in separate thread
*/

#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "garden.h"

struct Days {
    short daysToWatering{0};
    short daysToRipe{0};
};

class Farmer {
    public:
        explicit Farmer(const std::string& name, unsigned water);
        Farmer(const Farmer& other) = delete;
        Farmer(Farmer&& other) noexcept;

        Farmer& operator=(const Farmer& other) = delete;
        Farmer& operator=(Farmer&& other) noexcept;

        ~Farmer() {};

        const std::string& getName() const;
        unsigned getWater() const;

        void setName(const std::string& name);
        void setWater(unsigned value);

        // check if plants need watering
        void checkPlants();
        // remove plant with the lovest ratio
        // depends on the needed amount of water to ripen  
        void removeTheCheapestPlant();

        // void plantSeed(Seed&& sd);
        // TO DO: how to receive and send seeds

        void printRipePlants();
        void printGrowingPlants();
        void printRipeandGrowingPlants();
        //print ripe, growing and died plants
        void printAllPlants();

    private:
        std::string name;
        std::unique_ptr<Garden> garden;
        // plant's position in garen vector plants and days to watering
        // journal contains only qrowin plants
        std::unordered_map<unsigned short, Days> journal;
        unsigned water;

        // std::vector<Seed> seeds;
};