#include "Error.h"
#include <sstream>
#include <cstdlib>
#include <iostream>

void Error::Report(const char* filename, int line, const char* message)
{
    std::stringstream final;
    final << "Error" << std::endl;
    final << "Filename: " << filename << std::endl;
    final << "Line: " << line << std::endl;
    final << "Error Message: " << message << std::endl;
    std::cout << final.str() << std::endl;
    exit(1); // not really elegant ...
}

void Error::Warning(const char* filename, int line, const char* message)
{
    std::stringstream final;
    final << "Warning: " << std::endl;
    final << "Filename: " << filename << std::endl;
    final << "Line: " << line << std::endl;
    final << "Warning Message: " << message << std::endl;
    std::cout << final.str() << std::endl;
}