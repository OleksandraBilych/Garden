/*
    An object of class Seed has name, value, needed water,
    watering frequency in days, time to qrow
*/

#pragma once

#include <string>

class Seed {
    public:
        explicit Seed(const std::string& name, int value, int consumedWater, int frequency, int growTime);
        Seed(const Seed& other);

        Seed& operator=(const Seed& other);

         Seed() {};

        const std::string& getName() const;
        int getValue() const;
        int getConsumedWater() const;
        int getFrequency() const;
        int getGrowTime() const;

        void setName(const std::string& name);
        void setValue(int value);
        void setConsumedWater(int value);
        void setFrequency(int value);
        void setGrowTime(int value);

        bool operator==(const Seed& other);

    protected:
        std::string name;
        int value;
        int consumedWater;
        int frequency; // frequency watering
        int growTime;
};
