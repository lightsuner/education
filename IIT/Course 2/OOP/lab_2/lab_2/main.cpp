//
//  main.cpp
//  lab_2
//
//  Created by Alex Kuk on 25.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <iostream>
#include <array>
#include "city.h"
#include "student.h"
#include "students_collection.h"


int main(int argc, const char * argv[]) {
   
    City cities[] = {
        City("Minsk", 1935000, 348),
        City("Amsterdam", 821926, 219),
        City("Berlin", 3419623, 891),
        City("Bucharest", 1883425, 238),
        City("Madrid", 3041579, 607),
        City("Minsk", 2870493, 1287),
        City("Moscow", 12197, 2511)
    };
    int citiesCount = sizeof(cities)/sizeof(cities[0]);
    int i;
    int totalSquare = 0;
    int millionaireCitiesCount = 0;
    
    for (i=0; i< citiesCount; i++) {
        totalSquare += cities[i].GetSquare();
        if (cities[i].GetPopulation() >= 1000000) {
            millionaireCitiesCount++;
        }
    }
    
    std::cout << "Cities==============" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Total square: " << totalSquare << std::endl;
    std::cout << "Millionaire Cities Count: " << millionaireCitiesCount << std::endl;
    
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "STUDENTS==============" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    // insert code here...
    Student student1 = Student("Pavel", "Pretov", "345 39 63");
    Student student2 = Student("Nikita", "Gurinenko", "462 29 31");
    Student student3 = Student("Dmitriy", "Kurach", "373 19 42");
    Student student4 = Student("Vladimir", "Labaza", "376 09 33");
    Student student5 = Student("Anton", "Domashkevich", "275 59 34");
    Student student6 = Student("Diana", "Korotchenko", "277 58 65");
    Student student7 = Student("Maria", "Kukareko", "246 57 36");
        
    StudentsCollection group63 = StudentsCollection(4, &student4, &student5, &student6, &student7);
    StudentsCollection group64 = StudentsCollection();
    
    group64.Add(student1).Add(student2).Add(student3);
    
    std::cout << "Group 63" << std::endl;
    group63.Print();

    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "Group 64" << std::endl;
    group64.Print();
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "Sorted Group 63" << std::endl;
    group63.SortByLastName().Print();

    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "Search for dfdsf" << std::endl;
    Student * searched = group63.SearchByLastName("Kukareko");
    std::cout << "First Name: " <<  searched->GetFirstName() << std::endl;
    std::cout << "Last Name: " <<  searched->GetLastName() << std::endl;
    
    return 0;
}
