#include "plant.h"

Plant::Plant(const std::string& name, int value, unsigned consumedWater, int frequency, int growTime)
    : name{name}, value{value}, consumedWater{consumedWater}, frequency{frequency}
    , growTime{growTime}, isAlive{true}, isRipened{false}
{}

Plant::Plant(const Plant& other)
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;
    isRipened = other.isRipened;
    isAlive = other.isAlive;
}

Plant::Plant(Plant&& other) noexcept
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;
    isRipened = other.isRipened;
    isAlive = other.isAlive;

    other.clear();
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

Plant& Plant::operator=(Plant&& other) noexcept
{
    name = other.name;
    value = other.value;
    consumedWater = other.consumedWater;
    frequency = other.frequency;
    growTime = other.growTime;
    isRipened = other.isRipened;
    isAlive = other.isAlive;

    other.clear();

    return *this;
}

void Plant::clear()
{
    name = "";
    value = 0;
    consumedWater = 0;
    frequency = 0;
    growTime = 0;
    isRipened = 0;
    isAlive = 0;
}

const std::string& Plant::getName() const
{
    return name;
}

int Plant::getValue() const
{
    return value;
}

unsigned Plant::getConsumedWater() const
{
    return consumedWater;
}

int Plant::getFrequency() const
{
    return frequency;
}

int Plant::getGrowTime() const
{
    return growTime;
}

bool Plant::getIsRipened() const
{
    return isRipened;
}

bool Plant::getIsAlive() const
{
    return isAlive;
}

void Plant::setName(const std::string& name)
{
    this->name = name;
}

void Plant::setValue(int value)
{
    this->value = value;
}

void Plant::setConsumedWater(unsigned value)
{
    consumedWater = value;
}

void Plant::setFrequency(int value)
{
    frequency = value;
}

void Plant::setGrowTime(int value)
{
    growTime = value;
}

void Plant::setIsRipened(bool value)
{
    isRipened = value;
}

void Plant::setIsAlive(bool value)
{
    isAlive = value;
}

void Plant::watering(unsigned& water)
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