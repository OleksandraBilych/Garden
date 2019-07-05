/*
    An object Garden has size(all and free) and list of plants
    You can add/remove plant
    Check if there is a free spot for a new plant
*/

#pragma once

#include <list>
#include <string>

#include "plant.h"

class Garden {
    public:
        explicit Garden(unsigned short size);
        Garden(const Garden& other);
        Garden(Garden&& other) noexcept;

        Garden& operator=(const Garden& other);
        Garden& operator=(Garden&& other) noexcept;

        ~Garden();

        unsigned short getSize() const;
        void setSize(unsigned short newSize);

        // does a free spot for new plant exist
        bool hasFreeSpots() const;
        // calculate value of all plants
        int calculateValue() const;

        void addPlant(Plant& plant);
        void removePlant(Plant& plant);

    private:
        unsigned short size; // max amount of plants
        unsigned short freeSpots; // avaliable amount of plants
        std::list<Plant> plants;
};