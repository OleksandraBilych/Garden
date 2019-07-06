/*
    An object of class Plant has name, value, needed water,
    watering frequency in days, time to qrow
*/

#pragma once

#include <string>
#include <iostream>

class Plant {
    public:
        explicit Plant(const std::string& name, int value, int consumedWater, int frequency, int growTime);
        Plant(const Plant& other);

        Plant& operator=(const Plant& other);

        ~Plant() {};

        const std::string& getName() const;
        int getValue() const;
        int getConsumedWater() const;
        int getFrequency() const;
        int getGrowRime() const;
        bool getIsRipened() const;
        bool getIsAlive() const;

        void setName(const std::string& name);
        void setValue(int value);
        void setConsumedWater(int value);
        void setFrequency(int value);
        void setGrowTime(int value);
        void setIsRipened(bool value);
        void setIsAlive(bool value);

        bool operator==(const Plant& other);

        // TO DO: how indicate that a plant needs water?

    private:
        std::string name;
        int value;
        int consumedWater;
        int frequency; // frequency watering
        int growTime;
        bool isRipened;
        bool isAlive;
};

std::ostream &operator<<(std::ostream &out, Plant const &m);
