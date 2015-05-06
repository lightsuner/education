//
//  city.cpp
//  lab_2
//
//  Created by Alex Kuk on 26.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include "city.h"
#include <string>


City::City(const char * name , int population, int square)
{
    this->name.assign(name);
    this->population = population;
    this->square = square;
};

std::string City::GetName()
{
    return name;
};

int City::GetPopulation()
{
    return population;
};

int City::GetSquare()
{
    return square;
};