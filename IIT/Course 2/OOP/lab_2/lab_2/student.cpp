//
//  student.cpp
//  lab_2
//
//  Created by Alex Kuk on 25.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <string>
#include "student.h"


Student::Student(const char * _firstName, const char * _lastName, const char * _phoneNumber):
firstName(_firstName), lastName(_lastName), phoneNumber(_phoneNumber) {};

std::string Student::GetFirstName()
{
    return firstName;
};

std::string Student::GetLastName()
{
    return lastName;
};

std::string Student::GetPhoneNumber()
{
    return phoneNumber;
};