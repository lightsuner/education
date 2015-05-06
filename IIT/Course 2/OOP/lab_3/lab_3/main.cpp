//
//  main.cpp
//  lab_3
//
//  Created by Alex Kuk on 27.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>

class Pair {
private:
    char * key;
    int value;
public:
    Pair(){};
    
    Pair(const Pair & pair)
    {
        this->key = new char[strlen(pair.key) + 1];
        strcpy(this->key, pair.key);
        this->value = pair.value;
    };
    
    Pair(const char * key, int value)
    {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    };
    
    int GetValue()
    {
        return this->value;
    };
    
    char * GetKey()
    {
        return this->key;
    };
    
    void Print()
    {
        std::cout << key << " => " << value << std::endl;
    };
};

class Pairs {
private:
    unsigned int size;
    unsigned int position;
    Pair * container;
    
    void ImproveSize(unsigned int newSize)
    {
        unsigned int i;
        Pair * tmpContent =new Pair[newSize];
        
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
    
    void UnsafeAdd(const Pair & newPair)
    {
        this->container[this->position] = newPair;
        this->position++;
    };
    
public:
    Pairs(unsigned int size = 2) : position(0)
    {
        this->size = size > 0 ? size : 2;
        this->container = new Pair[this->size];
    };
    
    Pairs & Add(const Pair & newPair) {
        CheckForFreeSpace(1);
        UnsafeAdd(newPair);
        
        return *this;
    }
    
    Pairs & Merge(const Pairs & pairsToMerge)
    {
        CheckForFreeSpace(pairsToMerge.position);
        int i;
        
        for (i=0; i< pairsToMerge.position; i++) {
            UnsafeAdd(pairsToMerge.container[i]);
        }
        
        return *this;
    };
    
   Pairs & Replace(const Pairs & pairsToReplace)
    {
        if (this != &pairsToReplace) {
            delete this->container;
            this->size = pairsToReplace.size;
            this->position = pairsToReplace.position;
            int i;
            
            this->container = new Pair[this->size];
            
            for (i=0; i< pairsToReplace.position; i++) {
                this->container[i] = Pair(pairsToReplace.container[i]);
            }
            
        }
        
        return *this;
    };
    
    Pairs & operator+=(const Pair& pair) {
        return Add(pair);
    };
    
    Pairs & operator+=(const Pairs& pairsToMerge) {
        return Merge(pairsToMerge);
    }
    
    Pairs & operator=(const Pairs & pairsToReplace)
    {
        return Replace(pairsToReplace);
    };

    char * operator[](int search) {
        int i;
        
        for (i=0; i < this->position; i++) {
            if (this->container[i].GetValue() == search) {
                return this->container[i].GetKey();
            }
        }
        
        return NULL;
    };
    
    int operator[](const char * search)
    {
        int i;
        
        for (i=0; i < this->position; i++) {
            if (!strcmp(this->container[i].GetKey(), search)) {
                return this->container[i].GetValue();
            }
        }
        
        return 0;
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

class Matrix {
private:
    int rows;
    int cols;
    int ** data;
    void Init(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        this->data = new int*[this->rows]; //fill with zero
        int i;
        for (i = 0; i < this->rows; i++) {
            this->data[i] = new int[this->cols]();
        }
    };
public:
    Matrix();
    Matrix( int rows, int cols)
    {
        Init(rows, cols);
    };
    Matrix( int rows, int cols, int * data )
    {
        Init(rows, cols);
        int i, j;

        for (i = 0; i < this->rows; i++) {
            for (j = 0; j < this->cols; j++) {
                this->data[i][j] = data[i*this->rows+j];
            }
        }
    };
    
    Matrix( int rows, int cols, int ** data )
    {
        Init(rows, cols);
        int i, j;
        for (i = 0; i < this->rows; i++) {
            for (j = 0; j < this->cols; j++) {
                this->data[i][j] = data[i][j];
            }
        }
    };
    
    ~Matrix()
    {
        int i;
        for (i = 0; i < this->rows; i++) {
            delete[] this->data[i];
        }
        delete[] this->data;
    };
    
    Matrix & resize( int newRows, int newCols )
    {
        int ** oldData = this->data;
        int oldRows = this->rows;
        int oldCols = this->cols;
        int minR, minC, i, j;
        
        minR = newRows < oldRows ? newRows : oldRows;
        minC = newCols < oldCols ? newCols : oldCols;
        
        Init(newRows, newCols);
        
        for (i = 0; i < minR; i++) {
            for (j = 0; j < minC; j++) {
                this->data[i][j] = oldData[i][j];
            }
        }
        
        for (i = 0; i < oldRows; i++) {
            delete[] oldData[i];
        }
        delete[] oldData;
        
        return *this;
    };
    Matrix submatrix( int startRow, int startCol, int endRow, int endCol )
    {
        int rows = endRow - startRow;
        int cols = endCol - startCol;
        int i, j, newI, newJ;
        Matrix subM = Matrix(rows, cols);
        
        for (i = startRow; i < endRow; i++) {
            for (j = startCol; j < endCol; j++) {
                newI = i - startRow;
                newJ = j - startCol;
                subM[newI][newJ] = this->data[i][j];
            }
        }
        
        return subM;
    };
    
    Matrix submatrix( int startRow, int startCol)
    {
        return submatrix(startRow, startCol, this->rows, this->cols);
    };
    
    int * operator[](int i)
    {
        return this->data[i];
    };
    
    void Print()
    {
        int i, j;
        std::cout << "Matrix " << this->rows << "x" << this->cols << " :" << std::endl;
        for (i = 0; i < this->rows; i++) {
            for (j = 0; j < this->cols; j++) {
                std::cout << std::setw(4) << this->data[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Pair pr1("first", 1), pr2("second", 2), pr3("third", 3), pr4("fourth", 4), pr5("fifth", 5), pr6("sixth", 6);
    Pairs p1, p2, p3;
    
    p1 += pr1;
    p1 += pr2;
    
    p2 += pr3;
    p2 += pr4;
    
    p3 += pr5;
    p3 += pr6;
    
    p1.Print();
    
    std::cout << "Find key by value: " << p1[2] << std::endl;
    std::cout << "Find value by key: " << p1["second"] << std::endl;
    std::cout << std::endl << std::endl;
    
    p1 += p2;
    
    p1.Print();
    
    p1 = p3;
    
    p1.Print();
    
    p1 += p2;
    
    p1.Print();
    
    p3.Print();
    
    
    int rows = 8;
    int cols = 8;
    int i, total;
    
    total = rows*cols;
    
    int * dataForMatrix = new int[total];
    
    for (i = 0; i < total; i++) {
        dataForMatrix[i] = 1+i;
    }
    
    Matrix m1 = Matrix(rows, cols, dataForMatrix);
    
    m1.Print();
    
    m1.resize(5, 4);
    
    m1.Print();
    
    m1.resize(6, 6);
    
    m1.Print();
    
    m1.submatrix(1, 1, 5, 5).Print();
    
    m1.submatrix(1, 1).Print();
    
    return 0;
}
