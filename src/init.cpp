#include <iostream>
#include <memory>

#include "plant.h"
#include "garden.h"
#include "farmer.h"
#include "objectConverter.hpp"
#include "appServer.h"

int main(int argc, char const *argv[])
{
    auto port {std::atoi(argv[1])};
    std::cout << port << std::endl;
    
    std::unique_ptr<AppServer> app(new AppServer(port));
    app->start();

    std::cout << "Game start..." << std::endl;
    Plant rose("Rose", 10, 10, 5, 3);

    Farmer f("Iosif", 50);
    f.plantSeed();
    f.plantSeed();
    f.printGrowingPlants();
    //f.sendSeed();

    return 0;
}
