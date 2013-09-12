#include "Error.h"
#include <sstream>
#include <cstdlib>
#include <iostream>
//------------------------------------------------------------------------------
void ERR::Report(const char* filename, int line, const char* message)
{
    std::stringstream final;
    final << "Error" << std::endl;
    final << "Filename: " << filename << std::endl;
    final << "Line: " << line << std::endl;
    final << "Error Message: " << message << std::endl;
    std::cout << final.str() << std::endl;
    exit(1); // not really elegant ...
}
//------------------------------------------------------------------------------
void ERR::Warning(const char* filename, int line, const char* message)
{
    std::stringstream final;
    final << "Warning: " << std::endl;
    final << "Filename: " << filename << std::endl;
    final << "Line: " << line << std::endl;
    final << "Warning Message: " << message << std::endl;
    std::cout << final.str() << std::endl;
}
//------------------------------------------------------------------------------
void ERR::Assert(const char* expr, const char* filename, int line)
{
    std::stringstream final;
    final << "Assertion " << expr << " failed" << std::endl;
    final << "Filename: " << filename << std::endl;
    final << "Line: " << line << std::endl;
    std::cerr << final.str() << std::endl;
    exit(1);
}
//------------------------------------------------------------------------------