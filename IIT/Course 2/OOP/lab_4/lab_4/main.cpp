//
//  main.cpp
//  lab_4
//
//  Created by Alex Kuk on 29.04.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Point {
private:
    int x;
    int y;
public:
    Point(){};
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    };
    
    int GetX()
    {
        return x;
    };
    
    int GetY()
    {
        return y;
    };
    
    void Print()
    {
        cout << "x: " << x << ", y: " << y << endl;
    };
};

class TransparentTriangle {
protected:
    Point a, b, c;
public:
    TransparentTriangle(){};
    TransparentTriangle(Point a, Point b, Point c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    };
    
    void Print()
    {
        cout << "Point 1 - ";
        a.Print();
        cout << "Point 2- ";
        b.Print();
        cout << "Point 3 - ";
        c.Print();
    };
};

class ColoredTriangle : public TransparentTriangle {
protected:
    string color;
public:
    ColoredTriangle(Point a, Point b, Point c, string color) : TransparentTriangle(a, b, c)
    {
        this->color = color;
    };
    
    void Print()
    {
        TransparentTriangle::Print();
        cout << "Color: " << color << endl;
    };
};

class StrokeTriangle : public TransparentTriangle {
protected:
    string color;
    int size;
public:
    StrokeTriangle(Point a, Point b, Point c, string color, int size) : TransparentTriangle(a, b, c)
    {
        this->color = color;
        this->size = size;
    };
    
    void Print()
    {
        TransparentTriangle::Print();
        cout << "Color: " << color << endl;
        cout << "Size: " << size << endl;
    };
};

class Weapon {
protected:
    int attack;
    int defence;
public:
    Weapon(){};
    Weapon(int attack, int defence)
    {
        this->attack = attack;
        this->defence = defence;
    };
    virtual int Attack()
    {
        return rand() % attack;
    };
    
    virtual int Defence()
    {
        return rand() % defence;
    };
    
    virtual int Hit(Weapon & weapon)
    {
        return weapon.Defend(Attack());
    };
    
    virtual int Defend(int attakPoint)
    {
        int damage = attakPoint - Defence();
        
        if (damage > 0) return damage;
        return 0;
    }
};

class Shield : public Weapon {
public:
    Shield(int defence)
    {
        this->attack = 0;
        this->defence = defence;
    };
    
    int Attack()
    {
        return attack;
    };
};

class Sword : public Weapon {
public:
    Sword(int attack)
    {
        this->attack = attack;
        this->defence = 0;
    };
    
    int Defence()
    {
        return defence;
    };
};

class Mace : public Weapon {
public:
    Mace(int attack)
    {
        this->attack = attack;
        this->defence = 0;
    };
    
    int Defence()
    {
        return defence;
    };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    srand(time(NULL));
    
    Point p1(1,3), p2(4,5), p3(7,4);
    
    cout << "TransparentTriangle:" << endl;
    TransparentTriangle tt(p1, p2, p3);
    tt.Print();
    cout << endl << endl;
    
    cout << "ColoredTriangle:" << endl;
    ColoredTriangle ct(p1, p2, p3, "#ff00ff");
    ct.Print();
    cout << endl << endl;
    
    cout << "StrokeTriangle:" << endl;
    StrokeTriangle st(p1, p2, p3, "#ff00ff", 2);
    st.Print();
    cout << endl << endl;
    
    Shield shield(7);
    Sword sword1(10);
    Sword sword2(5);
    Mace mace(15);
    
    cout << "Weapons:" << endl;
    cout << "Sword 1 Hit the Shield, damage is - :" << sword1.Hit(shield) << endl;
    cout << "Sword 2 Hit the Shield, damage is - :" << sword2.Hit(shield) << endl;
    cout << "Mace Hit Shield, damage is - :" << mace.Hit(shield) << endl;
    cout << "Shield Hit Mace, damage is - :" << shield.Hit(mace) << endl;
    cout << "Sword 1 Hit Mace, damage is - :" << sword1.Hit(mace) << endl;
    
    return 0;
}
