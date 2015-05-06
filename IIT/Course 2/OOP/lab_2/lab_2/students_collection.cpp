//
//  students_collection.cpp
//  lab_2
//
//  Created by Alex Kuk on 25.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include "students_collection.h"
#include "student.h"
#include <list>
#include <iostream>
#include <iomanip>

bool comparePhoneAsc(Student & first, Student & second)
{
    return (first.GetPhoneNumber().compare(second.GetPhoneNumber()) < 0);
}

bool compareLastNameAsc(Student & first, Student & second)
{
    return (first.GetLastName().compare(second.GetLastName()) < 0);
}


StudentsCollection::~StudentsCollection()
{
    delete list;
};
StudentsCollection::StudentsCollection()
{
    list = new std::list<Student>;
}
StudentsCollection::StudentsCollection(int count, ...)
{
    list = new std::list<Student>;
    int i;
    va_list ap;
    va_start(ap, count);
    
    for (i = 0; i< count; i++) {
        Student * s = va_arg(ap, Student *);
        list->push_back(*s);
    }
    va_end(ap);
    
};

StudentsCollection & StudentsCollection::Add(Student student)
{
    list->push_back(student);
    return *this;
};

StudentsCollection & StudentsCollection::SortByPhone()
{
    list->sort(comparePhoneAsc);
    return *this;
};

StudentsCollection & StudentsCollection::SortByLastName()
{
    list->sort(compareLastNameAsc);
    return *this;
};

void  StudentsCollection::Print()
{
    std::list<Student>::iterator it;
    int separators = 4 + (3 * 15);
    
    std::cout << std::string(separators, '_') << std::endl;
    printf("|%15s|%15s|%15s|", "First name", "Last name", "Phone");
    std::cout << std::string(separators, '_') << std::endl;
    
    for (it=list->begin(); it != list->end(); ++it) {
        std::cout << '|' << std::setw(15) << it->GetFirstName();
        std::cout << '|' << std::setw(15) << it->GetLastName();
        std::cout << '|' << std::setw(15) << it->GetPhoneNumber();
        std::cout << '|' << std::endl;

        std::cout << std::string(separators, '_') << std::endl;
    }
};

Student * StudentsCollection::SearchByLastName(const char * text)
{
    std::list<Student>::iterator it;

    for (it=list->begin(); it != list->end(); ++it) {
        if (it->GetLastName().find(text) != std::string::npos) {
            return &*it;
        }
    }
    return NULL;
};

