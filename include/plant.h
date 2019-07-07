/*
    An object of class Plant has name, value, needed water,
    watering frequency in days, time to qrow
*/

#pragma once

#include <string>
#include <iostream>

#include "seed.h"

class Plant : public Seed {
    public:
        explicit Plant(const std::string& name, int value, int consumedWater, int frequency, int growTime);
        Plant(const Seed &seed);
        Plant(const Plant& other);

        Plant& operator=(const Plant& other);

        ~Plant() {};

        bool getIsRipened() const;
        bool getIsAlive() const;

        void setIsRipened(bool value);
        void setIsAlive(bool value);

        bool operator==(const Plant& other);

        void watering(unsigned &water);

    private:
        bool isRipened;
        bool isAlive;
};

std::ostream &operator<<(std::ostream &out, Plant const &m);
