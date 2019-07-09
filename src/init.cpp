#include <iostream>

#include "plant.h"
#include "garden.h"
#include "farmer.h"
#include <unordered_map>

int main(int argc, char const *argv[])
{
    std::cout << "Game start..." << std::endl;
    Garden g(30);
    Plant rose("Rose", 10, 10, 5, 3);

    Farmer f("Iosif", 50);
    f.receiveSeed(std::move(rose), 3);
    f.plantSeed();
    f.printGrowingPlants();

    f.removeTheCheapestPlant();
    f.printGrowingPlants();
    f.printAllPlants();

    return 0;
}
