#include <iostream>
#include <memory>

#include "plant.h"
#include "garden.h"
#include "farmer.h"
#include "objectConverter.hpp"
#include "appServer.h"
#include "globalVariables.h"

int main(int argc, char const *argv[])
{
    auto port {std::atoi(argv[1])};
    std::cout << port << std::endl;
    
    std::unique_ptr<AppServer> app(new AppServer(port, globVar::sendingFrequency));
    app->start();

    std::cout << "Game start..." << std::endl;

    return 0;
}
