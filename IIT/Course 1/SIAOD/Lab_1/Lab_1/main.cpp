//
//  main.cpp
//  Lab_1
//
//  Created by Alex Kuk on 21.05.14.
//  Copyright (c) 2014 Alex. All rights reserved.
//

#include <math.h>
#include <iostream>

struct Polynomial {
    int power;
    int multiplier;
    struct Polynomial *next;
};

struct Child {
    unsigned int number;
    struct Child *next;
    struct Child *prev;
};

struct Polynomial * polynomialFactory(int multiplier, int power)
{
    struct Polynomial *polynomial = new Polynomial();
    
    polynomial->multiplier = multiplier;
    polynomial->power = power;
    polynomial->next = nullptr;
    
    return polynomial;
}

void polynomialOnePrinter(const struct Polynomial *polynomial)
{
    if (!polynomial) {
        return;
    }
    if (polynomial->multiplier == 0) {
        return;
    }
    
    if (polynomial->multiplier != 1) {
        printf("%d", polynomial->multiplier);
    }
    
    
    
    if (polynomial->power == 0) {
        printf("1");
        return;
    }
    
    printf("x");
    
    if (polynomial->power != 1) {
        printf("^%d", polynomial->power);
    }
    
}

void polynomialPrinter(const struct Polynomial *polynomial)
{
    
    unsigned int i = 0;
    
    while (polynomial != nullptr) {
        if (i > 0 && polynomial->multiplier >= 0) {
            printf("+");
        }
        
        polynomialOnePrinter(polynomial);
        
        polynomial = polynomial->next;
        i++;
    }
    
}

bool polynomial_equality(const struct Polynomial *p_first, const struct Polynomial *p_second)
{
    
    if (p_first->power == p_second->power && p_first->multiplier == p_second->multiplier) {
        if (p_first->next == nullptr && p_second->next == nullptr) {
            return true;
        } else if (p_first->next == nullptr || p_second->next == nullptr) {
            return false;
        }
        
        return polynomial_equality(p_first->next, p_second->next);
    }
    
    return false;
}

int polynomial_meaning(const struct Polynomial *p, int x){
    if (p == nullptr) {
        return 0;
    }
    
    return (p->multiplier * pow(x, p->power)) + polynomial_meaning(p->next, x);
}

void polynomial_add_current_or_next(struct Polynomial *p, int multiplier, int power)
{
    if (p == nullptr) {
        p = polynomialFactory(multiplier, power);
    } else {
        p->next = polynomialFactory(multiplier, power);
        p = p->next;
    }
}

void polynomial_add(
                    const struct Polynomial *p_first,
                    const struct Polynomial *p_second,
                    struct Polynomial **p_result
                    )
{
    struct Polynomial *prev = nullptr, *cursor = *p_result = polynomialFactory(0, 1);
    
    while (p_first != nullptr || p_second != nullptr) {
        
        if (p_first != nullptr && p_second != nullptr) {
            if (p_first->power == p_second->power) {
                cursor->multiplier = p_first->multiplier + p_second->multiplier;
                cursor->power = p_first->power;
                
                p_first = p_first->next;
                p_second = p_second->next;
            } else if (p_first->power > p_second->power) {
                cursor->multiplier = p_first->multiplier;
                cursor->power = p_first->power;

                p_first = p_first->next;
            } else {
                cursor->multiplier = p_second->multiplier;
                cursor->power = p_second->power;
                
                p_second = p_second->next;
            }
        } else if (p_first == nullptr) {
            cursor->multiplier = p_second->multiplier;
            cursor->power = p_second->power;
            
            p_second = p_second->next;
        } else {
            cursor->multiplier = p_first->multiplier;
            cursor->power = p_first->power;
            
            p_first = p_first->next;
        }
      
        cursor->next = polynomialFactory(0, 1);
        prev = cursor;
        cursor = cursor->next;
    }
    
    if (prev != nullptr) {
        delete prev->next;
        prev->next = nullptr;
    }
     
}

void case_1()
{
    struct Polynomial *first_formula = nullptr, *second_formula = nullptr, *third_formula = nullptr, *fourth_formula = nullptr;
    int x_1 = 10, x_2 = 1, meaning_result_1 = 29505, meaning_result_2 = -6;
    
    // '3x^4-5x^2+x-5'
    first_formula = polynomialFactory(3, 4);
    first_formula->next = polynomialFactory(-5, 2);
    first_formula->next->next = polynomialFactory(1, 1);
    first_formula->next->next->next = polynomialFactory(-5, 0);
    
    
    // '-8x^7-5x^4+x+6'
    second_formula = polynomialFactory(-8, 7);
    second_formula->next = polynomialFactory(-5, 4);
    second_formula->next->next = polynomialFactory(1, 1);
    second_formula->next->next->next = polynomialFactory(6, 0);
    
    // '-8x^7-5x^4+x+6'
    third_formula = polynomialFactory(-8, 7);
    third_formula->next = polynomialFactory(-5, 4);
    third_formula->next->next = polynomialFactory(1, 1);
    third_formula->next->next->next = polynomialFactory(6, 0);
    

    std::cout << "Equal method ------------------------\n";
    
    std::cout << "Is '";
    polynomialPrinter(second_formula);
    std::cout << "' equal to '";
    polynomialPrinter(third_formula);
    std::cout << "' ?? - ";
    std::cout << (polynomial_equality(second_formula, third_formula) ? "Yes" : "No");
    std::cout << "\n";
    
    std::cout << "Is '";
    polynomialPrinter(first_formula);
    std::cout << "' equal to '";
    polynomialPrinter(third_formula);
    std::cout << "' ?? - ";
    std::cout << (polynomial_equality(first_formula, third_formula) ? "Yes" : "No");
    std::cout << "\n";
    std::cout << "-------------------------------------\n";
    
    std::cout << "\n\n";

    std::cout << "Meaning method ------------------------\n";
    std::cout << "The ";
    polynomialPrinter(first_formula);
    std::cout << " with x = " << x_1;
    std::cout << "! should be equal " << meaning_result_1;
    std::cout << "! Got -  " << polynomial_meaning(first_formula, x_1);
    std::cout << "\n\n";
    std::cout << "The ";
    polynomialPrinter(first_formula);
    std::cout << " with x = " << x_2;
    std::cout << "! should be equal " << meaning_result_2;
    std::cout << "! Got -  " << polynomial_meaning(first_formula, x_2);
    std::cout << "\n";
    std::cout << "-------------------------------------\n";

    std::cout << "\n\n";
    
    std::cout << "Add method ------------------------\n";
    std::cout << "Calculate ";
    polynomialPrinter(first_formula);
    std::cout << " and ";
    polynomialPrinter(second_formula);
    std::cout << "!\n Got - ";
    
    polynomial_add(first_formula, second_formula, &fourth_formula);
    
    polynomialPrinter(fourth_formula);
    std::cout << "\n";
    std::cout << "-------------------------------------\n";

}

struct Child * child_factory(unsigned int number)
{
    struct Child * child = new Child();
    child->number = number;
    child->next = nullptr;
    child->prev = nullptr;
    
    return child;
}

void generate_children(struct Child *first_child, unsigned int count)
{
    
    struct Child *cursor = first_child;
    
    cursor->next = first_child;
    
    for (unsigned int i = 2; i <= count; i++) {
        cursor->next = child_factory(i);
        cursor->next->prev = cursor;
        cursor = cursor->next;
    }
    
    first_child->prev = cursor;
    cursor->next = first_child;
}

void case_2()
{
    
    unsigned short k = 3;
    unsigned short counter;
    
    struct Child *cursor_prev;
    struct Child *cursor_next;
    struct Child *cursor;
    
    for (unsigned int i = 1; i <= 64; i++) {
        
        cursor = child_factory(1);
        generate_children(cursor, i);
        
        counter = 1;
        
        std::cout << "Children count - " << i << "\n";
        std::cout << "Leavers - ";
        
        while(true) {
            if (cursor == cursor->next) {
                break;
            }
            
            if (counter == k) {
                
                cursor_prev = cursor->prev;
                cursor_next = cursor->next;
                
                cursor_prev->next = cursor_next;
                cursor_next->prev = cursor_prev;
                
                std::cout << cursor->number << ",";
                
                counter = 1;
                cursor = cursor->next;
                continue;
            }

            cursor = cursor->next;

            counter++;
        }
        
        
        std::cout << "\n" << "Winner - " << cursor->number << "!\n";
        
        std::cout << "\n";

        
    }
    
}


struct Phones {
    const char *phone;
    const char *name;
    struct Phones *next;
};

struct Phones * phones_factory(const char *phone, const char *name)
{
    struct Phones * phone_item = new Phones();
    phone_item->name = name;
    phone_item->phone = phone;
    phone_item->next = nullptr;
    
    return phone_item;
}

void search_phones_by_name(const struct Phones *phone_item, const char *name)
{
    while (phone_item != nullptr) {
        if (strstr(phone_item->name, name) != NULL) {
            std::cout << "Finded phone: " << phone_item->phone << "\n";
        }
        
        phone_item = phone_item->next;
    }
}

void search_names_by_pnone(const struct Phones *phone_item, const char *phone)
{
    while (phone_item != nullptr) {
        if (strstr(phone_item->phone, phone) != NULL) {
            std::cout << "Finded name: " << phone_item->name << "\n";
        }
        
        phone_item = phone_item->next;
    }
}

void case_3()
{
    
    struct Phones * phone_item;
    
    phone_item = phones_factory("2976833", "alex");
    phone_item->next = phones_factory("2976452", "dob");
    phone_item->next->next = phones_factory("2976268", "mick");
    phone_item->next->next->next = phones_factory("2976236", "donald");
    phone_item->next->next->next->next = phones_factory("2976223", "alexandr");
    
    std::cout << "Finded phones by name 'alex'\n";
    search_phones_by_name(phone_item, "alex");
    
    std::cout << "\n";
    
    std::cout << "Finded names by phone '29762'\n";
    search_names_by_pnone(phone_item, "29762");
    
    std::cout << "\n";
    
}

struct DoubleDirectionPhones {
    unsigned int phone;
    struct DoubleDirectionPhones *next;
    struct DoubleDirectionPhones *prev;
};

struct SingleDirectionPhones {
    unsigned int phone;
    struct SingleDirectionPhones *next;
};

struct DoubleDirectionPhones * double_direction_phones_factory(unsigned int phone)
{
    struct DoubleDirectionPhones *p = new DoubleDirectionPhones();
    p->phone = phone;
    
    return p;
}

struct SingleDirectionPhones * single_direction_phones_factory(unsigned int phone)
{
    struct SingleDirectionPhones *p = new SingleDirectionPhones();
    p->phone = phone;
    
    return p;
}

void case_4()
{
    unsigned int phones[] = {2976833,2976452,2976268,2976236,101,102,103,104,2976223,2976205,2976140,2976121};
    unsigned int all_phones_count = sizeof(phones)/sizeof(phones[0]);
    
    struct DoubleDirectionPhones *first_phone, *double_cursor;
    struct SingleDirectionPhones *first_single_phone = nullptr, *single_cursor = nullptr;
    
    first_phone = double_direction_phones_factory(phones[0]);
    double_cursor = first_phone;
    
    for (unsigned i=1; i < all_phones_count; i++) {
        double_cursor->next = double_direction_phones_factory(phones[i]);
        double_cursor->next->prev = double_cursor;
        double_cursor = double_cursor->next;
    }
    
    first_phone->prev = double_cursor;
    double_cursor->next = first_phone;
    
    double_cursor = first_phone;
    
    do {
        if (double_cursor->phone > 999) {
            if (first_single_phone == nullptr) {
                first_single_phone = single_direction_phones_factory(double_cursor->phone);
                single_cursor = first_single_phone;
            } else {
                single_cursor->next = single_direction_phones_factory(double_cursor->phone);
                single_cursor = single_cursor->next;
            }
        }
        double_cursor = double_cursor->prev;
    } while (double_cursor != first_phone);
    
    std::cout << "Display usual phones:\n";
    while (first_single_phone != nullptr) {
        std::cout << first_single_phone->phone << "\n";
        first_single_phone = first_single_phone->next;
    }
    std::cout << "\n";

    
}

void menu()
{
    unsigned short lab_num;
    
    std::cout << "Please input number of case!\n";
    std::cin >> lab_num;
    
    switch (lab_num) {
        case 0:
            return;
        case 1:
            case_1();
            break;
        case 2:
            case_2();
            break;
        case 3:
            case_3();
            break;
        case 4:
            case_4();
            break;
            
        default:
            std::cout << "Case not found!\n";
            break;
    }
    
    menu();
}

int main(int argc, const char * argv[])
{

    
    
    
    menu();
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    return 0;
}

