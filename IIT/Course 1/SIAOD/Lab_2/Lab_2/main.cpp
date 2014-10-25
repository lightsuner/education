//
//  main.cpp
//  Lab_2
//
//  Created by Alex Kuk on 21.05.14.
//  Copyright (c) 2014 Alex. All rights reserved.
//

#include <iostream>

#define HASH_SIZE 3

struct Word {
    const char *text;
    struct Word *next;
};

class Vocabulary
{
public:
    struct Word *hash_tables[HASH_SIZE];
    
    Vocabulary () {
        std::fill_n(hash_tables, HASH_SIZE, nullptr);
    }
    
    int hash(const char * key)
    {
        unsigned int sum = 0;
        for (unsigned int i = 0; key[i] != '\0'; i++){
            sum += static_cast<int>(key[i]);
        }
        
        return sum % HASH_SIZE;
    }
    void add(const char * word)
    {
        unsigned int key = hash(word);
        
        struct Word * word_item = new Word();
        word_item->text = word;
        
        if (hash_tables[key] == nullptr) {
            hash_tables[key] = word_item;
        } else {
            word_item->next = hash_tables[key];
            hash_tables[key] = word_item;
        }
        
    }
    void remove(const char * word)
    {
        unsigned int key = hash(word);
        struct Word *cursor, *prev_cursor;
        
        cursor = prev_cursor = hash_tables[key];
        
        std::cout << "Removing word: " <<word << "\n";
        
        if (cursor == nullptr) {
            std::cout << "Word not found!\n";
            return;
        }
        while (cursor != nullptr) {
            if (strcmp(cursor->text, word) == 0) {
                if (prev_cursor == cursor) {
                    if (cursor->next != nullptr) {
                        hash_tables[key] = cursor->next;
                    } else {
                        hash_tables[key] = nullptr;
                    }
                } else {
                    prev_cursor->next = cursor->next;
                }
                return;
            }
            prev_cursor = cursor;
            cursor = cursor->next;
        }
    }
    void find(const char * word)
    {
        unsigned int key = hash(word);
        struct Word *cursor = hash_tables[key];
        
        std::cout << "Finding word: " <<word << "\n";
        
        if (cursor == nullptr) {
            std::cout << "Word not found!\n";
            return;
        }
        
        
        while (cursor != nullptr) {
            if (strcmp(cursor->text, word) == 0) {
                std::cout << "Word successfully found!\n";
                return;
            }
            cursor = cursor->next;
        }
        
        std::cout << "Word not found!\n";
    }
    void print()
    {
        struct Word *cursor = nullptr;
        
        for (unsigned int i = 0; i < HASH_SIZE; i++) {
            std::cout << "Key - " << i << ":\n";
            cursor = hash_tables[i];
            
            while (cursor != nullptr) {
                std::cout << "Word: " << cursor->text << ", ";
                cursor = cursor->next;
            }
            
            std::cout << "\n";
        }
    }
    
};

int main(int argc, const char * argv[])
{

    Vocabulary vocabulary;
    
    vocabulary.add("First word");
    
    vocabulary.add("Second word");
    
    vocabulary.add("third word");
    
    std::cout << "==================\n\n";
    
    vocabulary.print();
    
    std::cout << "==================\n\n";
    
    vocabulary.find("First word");
    vocabulary.find("First word1");
    
    vocabulary.remove("First word");
    vocabulary.find("First word");
    
    std::cout << "==================\n\n";
    
    vocabulary.print();
    
    return 0;
}

