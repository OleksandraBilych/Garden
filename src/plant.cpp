#include "plant.h"

Plant::Plant(const std::string& name, int value, int consumedWater, int frequency, int growTime)
    : Seed(name, value, consumedWater, frequency, growTime),
    isAlive{true}, isRipened{false}
{}

Plant::Plant(const Plant& other)
    : Seed(other.name, other.value, other.consumedWater, other.frequency, other.growTime)
{
    isRipened = other.isRipened;
    isAlive = other.isAlive;
}


Plant& Plant::operator=(const Plant& other)
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;
    isRipened = other.isRipened;
    isAlive = other.isAlive;

    return *this;
}

bool Plant::getIsRipened() const
{
    return isRipened;
}

bool Plant::getIsAlive() const
{
    return isAlive;
}

void Plant::setIsRipened(bool value)
{
    isRipened = value;
}

void Plant::setIsAlive(bool value)
{
    isAlive = value;
}

void Plant::watering(unsigned &water)
{
    if (water >= consumedWater) {
        water-= consumedWater;
    } else {
        isAlive = false;
    }
}

bool Plant::operator==(const Plant& other)
{
    bool isEqual{true};

    if (name != other.name
        || value != other.value || consumedWater != other.consumedWater
        || frequency != other.frequency || growTime != other.growTime
        || isRipened != other.isRipened || isAlive != other.isAlive)
    {
        isEqual = false;
    }

    return isEqual;
}

std::ostream &operator<<(std::ostream &out, Plant const &m)
{ 
    out << m.getName() << "\nValue: " << m.getValue()
            << ", consumed water: " << m.getConsumedWater()
            << ", frequency watering water: " << m.getFrequency()
            << ", qrowing time: " << m.getGrowTime() << "\n";

    return out;
}