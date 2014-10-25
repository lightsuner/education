//
//  main.cpp
//  Lab_3
//
//  Created by Alex Kuk on 26.05.14.
//  Copyright (c) 2014 Alex. All rights reserved.
//

#include <iostream>

#define PRIORITY_SIZE 10

struct Message {
    const char *data = nullptr;
    struct Message *next = nullptr;
};

class WeightedFairQueing
{
protected:
    struct Message *queue;
    struct Message *priority_queue[PRIORITY_SIZE];
    
    void push_to_queue(struct Message **queue, const char *data)
    {
        struct Message **walker = queue;
        
        while (*walker != nullptr) {
            walker = &(*walker)->next;
        }
        
        *walker = new Message();
        (*walker)->data = data;
        
    }
    
    void print_queue(const struct Message *queue)
    {
        while (queue != nullptr) {
            std::cout << queue->data << ", ";
            queue = queue->next;
        }
    }
    
    struct Message * remove()
    {
        struct Message *tmp = nullptr;
        
        for (int i = PRIORITY_SIZE-1; i >= 0; i--) {
            if (priority_queue[i] != nullptr) {
                tmp = priority_queue[i];
                priority_queue[i] = tmp->next;
                
                return  tmp;
            }
        }
        
        if (queue != nullptr) {
            tmp = queue;
            queue = tmp->next;
            
            return  tmp;
        }
        
        return nullptr;
    }
    
    struct Message * _find(const char *data)
    {
        struct Message *walker = nullptr;
        
        for (int i = PRIORITY_SIZE-1; i >= 0; i--) {
            if (priority_queue[i] != nullptr) {
                walker = priority_queue[i];
                
                while (walker != nullptr) {
                    if (strcmp(walker->data, data) == 0) {
                        return walker;
                    }
                    
                    walker = walker->next;
                }
                
            }
        }
        
        walker = queue;
        
        while (walker != nullptr) {
            if (strcmp(walker->data, data) == 0) {
                return walker;
            }
            
            walker = walker->next;
        }
        
        return nullptr;
    }
    
public:
    
    WeightedFairQueing()
    {
        std::fill_n(priority_queue, PRIORITY_SIZE, nullptr);
        queue = nullptr;
    }
    
    void push(const char *data)
    {
        push_to_queue(&queue, data);
    }
    
    void push(const char *data, unsigned int priority)
    {
        unsigned short priority_level = priority % PRIORITY_SIZE;
        
        push_to_queue(&priority_queue[priority_level], data);
    }
    
    bool has_item()
    {
        for (int i = PRIORITY_SIZE-1; i >= 0; i--) {
            if (priority_queue[i] != nullptr) {
                return  true;
            }
        }
        
        if (queue != nullptr) {
            return  true;
        }
        
        return false;
    }
    
    const char * pop()
    {
        struct Message *tmp = remove();
        if (tmp == nullptr) {
            return nullptr;
        }
        return tmp->data;
    }
    
    void find(const char *data)
    {
        struct Message *finded_element = nullptr;
        
        finded_element = _find(data);
        
        if (finded_element == nullptr) {
            std::cout << "Element '" << data << "' not found!\n";
            return;
        }
        std::cout << "Element '" << data << "' found!\n";
        
    }
    
    void print()
    {
     
        std::cout << "Priority Queue:\n";
        
        for (int i = PRIORITY_SIZE-1; i >= 0; i--) {
            std::cout << "Queue #" << i << ": ";
            print_queue(priority_queue[i]);
            std::cout << "\n";
        }
        
        std::cout << "\nUsual Queue: ";
        print_queue(queue);
        std::cout << "\n";
        
    }
    
    
};

int main(int argc, const char * argv[])
{

    WeightedFairQueing queue;
    
    std::cout << "Show empty queue: \n\n";
    queue.print();
    
    queue.push("usual 1");
    queue.push("usual 2");
    queue.push("usual 3");
    queue.push("usual 4");
    queue.push("usual 5");
    queue.push("usual 6");
    
    
    std::cout << "\n\nTry to find 'usual 1':\n";
    queue.find("usual 1");
    
    std::cout << "\n";
    
    std::cout << "\n\nTry to find 'usual 77':\n";
    queue.find("usual 77");
    std::cout << "\n";
    
    
    queue.push("priority - 0", 0);
    queue.push("priority - 2", 2);
    queue.push("priority - 4", 4);
    queue.push("priority - 5", 5);
    queue.push("priority - 3", 3);
    queue.push("priority - 1", 1);
    queue.push("priority - 1,1", 1);
    queue.push("priority - 1,2", 1);
    
    std::cout << "\n\nShow filled queue: \n\n";
    queue.print();
    
    std::cout << "\n\nFetch all items: \n\n";
    
    while (queue.has_item()) {
        std::cout << queue.pop() << "\n";
    }
    
    std::cout << "Show empty queue: \n\n";
    queue.print();
    
    return 0;
}

