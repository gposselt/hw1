#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

int main(int argc, char* argv[])
{
    auto testing = ("WHY HELLO THERE!!!");

    ULListStr testString;
    testString.push_back(testing);

    std::cout << testString.get(0) << std::endl;



}
