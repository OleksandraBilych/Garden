#include "seed.h"

Seed::Seed(const std::string& name, int value, int consumedWater, int frequency, int growTime)
    : name{name}, value{value}, consumedWater{consumedWater}, frequency{frequency}
    , growTime{growTime}
{}

Seed::Seed(const Seed& other)
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;
}


Seed& Seed::operator=(const Seed& other)
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;

    return *this;
}

const std::string& Seed::getName() const
{
    return name;
}

int Seed::getValue() const
{
    return value;
}

int Seed::getConsumedWater() const
{
    return consumedWater;
}

int Seed::getFrequency() const
{
    return frequency;
}

int Seed::getGrowTime() const
{
    return growTime;
}

void Seed::setName(const std::string& name)
{
    this->name = name;
}

void Seed::setValue(int value)
{
    this->value = value;
}

void Seed::setConsumedWater(int value)
{
    consumedWater = value;
}

void Seed::setFrequency(int value)
{
    frequency = value;
}

void Seed::setGrowTime(int value)
{
    growTime = value;
}
