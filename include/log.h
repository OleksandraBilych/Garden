#pragma once

#include <iostream>

#ifdef DEBUG_PRINT

#define DEBUG(x) do { std::cout << x << std::endl; } while (0)
#define PRINT(x) DEBUG(x)

#else

#define DEBUG(x)
#define PRINT(x) do { } while (0)

#endif