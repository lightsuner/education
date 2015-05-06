//
//  city.h
//  lab_2
//
//  Created by Alex Kuk on 26.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#ifndef __lab_2__city__
#define __lab_2__city__

#include <stdio.h>
#include <string>

class City
{
private:
    std::string name;
    int population;
    int square;
public:
    City(const char *, int, int);
    std::string GetName();
    int GetPopulation();
    int GetSquare();
};

#endif /* defined(__lab_2__city__) */
