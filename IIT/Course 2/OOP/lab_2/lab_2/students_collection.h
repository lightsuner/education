//
//  students_collection.h
//  lab_2
//
//  Created by Alex Kuk on 25.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#ifndef __lab_2__students_collection__
#define __lab_2__students_collection__

#include <stdio.h>
#include "student.h"
#include <list>

class StudentsCollection
{
private:
    std::list<Student> * list;
public:
    StudentsCollection();
    StudentsCollection(int count, ...);
    ~StudentsCollection();
    StudentsCollection & SortByPhone();
    StudentsCollection & SortByLastName();
    StudentsCollection & Add(Student);
    Student * SearchByLastName(const char *);
    void Print();
};

#endif /* defined(__lab_2__students_collection__) */
