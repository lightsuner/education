//
//  student.h
//  lab_2
//
//  Created by Alex Kuk on 25.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#ifndef __lab_2__student__
#define __lab_2__student__

#include <stdio.h>
#include <string>

class Student
{
private:
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
public:
    Student(const char *, const char *, const char *);
    std::string GetFirstName();
    std::string GetLastName();
    std::string GetPhoneNumber();
};

#endif /* defined(__lab_2__student__) */
