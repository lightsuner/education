//
//  main.cpp
//  lab_5
//
//  Created by Alex Kuk on 28.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <iostream>
#include <string>


template <class TK, class TV>
class Pair {
private:
    TK key;
    TV value;
public:
    Pair(){};
    Pair(TK key, TV value)
    {
        this->key = key;
        this->value = value;
    };
    
    TV GetValue()
    {
        return this->value;
    };
    
    TK GetKey()
    {
        return this->key;
    };
    
    void Print()
    {
        std::cout << key << " => " << value << std::endl;
    };
};

template <class TK, class TV>
class Pairs {
private:
    unsigned int size;
    unsigned int position;
    Pair<TK, TV> * container;
    
    void ImproveSize(unsigned int newSize)
    {
        unsigned int i;
        Pair<TK, TV> * tmpContent = new Pair<TK, TV>[newSize];
        
        for (i=0; i< position; i++) {
            tmpContent[i] = this->container[i];
        }
        if(this->container) {
            delete this->container;
        }
        
        this->container = tmpContent;
        this->size = newSize;
    };
    
    void CheckForFreeSpace(unsigned int addSize)
    {
        if (position + addSize >= size) {
            int newSize = (size + addSize) * 2;
            ImproveSize(newSize);
        }
    };
    
    void UnsafeAdd(const Pair<TK, TV> & newPair)
    {
        this->container[this->position] = newPair;
        this->position++;
    };
    
public:
    Pairs(unsigned int size = 2) : position(0)
    {
        this->size = size > 0 ? size : 2;
        this->container = new Pair<TK, TV>[this->size];
    };
    
    Pairs & operator+=(const Pair<TK, TV> & pair) {
        CheckForFreeSpace(1);
        UnsafeAdd(pair);
        
        return *this;
    };

    
    void Print()
    {
        int i;
        std::cout << "Pairs: " << std::endl;
        for (i=0; i < this->position; i++) {
            this->container[i].Print();
        }
        std::cout << std::endl << std::endl;
    };
};



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Pair<int, double> pr1(1, 1.5), pr2(2, 2.3);
    Pairs<int, double> p1;
    
    p1 += pr1;
    p1 += pr2;
    
    p1.Print();
    
    
    return 0;
}
