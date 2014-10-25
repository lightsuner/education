//
//  main.cpp
//  Lab_4
//
//  Created by Alex Kuk on 28.05.14.
//  Copyright (c) 2014 Alex. All rights reserved.
//

#include <iostream>
#include <stack>

class PolishNotationer
{
protected:
    std::stack <char> *stack;
    std::string valid_characters = "()+-*/^0123456789 ";
    std::string operators = "+-*/^";
    std::string numbers = "0123456789";
    
    bool is_numeric(const char *c)
    {
        if (numbers.find_first_of(*c) != std::string::npos) {
            return true;
        }
        return false;
    }
    
    bool is_operator(const char *c)
    {
        if (operators.find_first_of(*c) != std::string::npos) {
            return true;
        }
        return false;
    }
    
    unsigned char operator_priority(const char *op)
    {
        switch (*op) {
           case '^':
                return 3;
           case '*':
           case '/':
                return 2;
            case '+':
            case '-':
                return 1;
        }
        
        return 0;
    }
    
    bool is_expression_valid(const std::string *expression)
    {
        unsigned int open_parentheses_count = 0,
        close_parentheses_count = 0,
        operators_count = 0,
        numbers_count = 0;
        std::string::const_iterator next_c;
        
        if (expression->empty()) {
            return false;
        }
        
        for(std::string::const_iterator c = expression->begin(), end = expression->end(); c != end; ++c) {
            if (valid_characters.find_first_of(*c) == std::string::npos) {
                return false;
            }
            
            if (is_operator(&(*c))) {
                operators_count++;
                continue;
            }
            
            if (is_numeric(&(*c))) {
                
                next_c = c+1;
                if (next_c != end && is_numeric(&(*next_c))) {
                    continue;
                }
                
                numbers_count++;
                continue;
            }

            
            switch (*c) {
                case '(':
                    open_parentheses_count++;
                    break;
                case ')':
                    close_parentheses_count++;
                    break;
            }
        }
        
        if (open_parentheses_count != close_parentheses_count) {
            return  false;
        }
        
        if (operators_count+1 != numbers_count) {
            return false;
        }
        
        return true;
    }
    
    void clear_stack()
    {
        while (!stack->empty() )
        {
            stack->pop();
        }
    }
    
    std::string reverse(const std::string *expression)
    {
        std::string output_string;
        std::stack <char> tmp_stack;
        bool is_prev_numeric = false;
        
        if (expression->empty()) {
            output_string = *expression;
            return output_string;
        }
        
        for(std::string::const_iterator c = expression->end()-1, begin = expression->begin(); c >= begin; --c) {
            if (!is_numeric(&(*c))) {
                
                if (is_prev_numeric) {
                    while (!tmp_stack.empty()) {
                        output_string += tmp_stack.top();
                        tmp_stack.pop();
                    }
                }
                
                output_string += *c;
                
                is_prev_numeric = false;
                continue;
            }
            
            tmp_stack.push(*c);
            is_prev_numeric = true;
            
        }
        
        while (!tmp_stack.empty()) {
            output_string += tmp_stack.top();
            tmp_stack.pop();
        }
        
        return output_string;
    }
    
public:
    PolishNotationer(std::stack <char> *composition_stack)
    {
        stack = composition_stack;
    }
    
    std::string toPostfix(const std::string *expression)
    {
        std::string output;
        char tmp_char;
        bool is_prev_numeric = true;
        
        
        clear_stack();
        
        if (!is_expression_valid(expression)) {
            output = "Invalid expression.";
            return output;
        }
        
        
        
        for(const char &c : *expression) {
            if (is_numeric(&c)) {
                if (!is_prev_numeric) {
                    output += ' ';
                }
                output += c;
                
                is_prev_numeric = true;
                continue;
            }
            
            is_prev_numeric = false;
            
            if (c == '(') {
                stack->push(c);
                continue;
            }
            
            if (c == ')') {
                while (!stack->empty()) {
                    tmp_char = stack->top();
                    stack->pop();
                    if (tmp_char == '(') {
                        break;
                    }
                    
                    output += ' ';
                    output += tmp_char;
                }
            }
            
            if (is_operator(&c)) {
                while (!stack->empty()) {
                    tmp_char = stack->top();
                    if (operator_priority(&c) <= operator_priority(&tmp_char)) {
                        stack->pop();
                        output += ' ';
                        output += tmp_char;
                    } else {
                        break;
                    }
                }
                
                stack->push(c);
                continue;
            }
        }
        
        while (!stack->empty()) {
            tmp_char = stack->top();
            stack->pop();
            
            output += ' ';
            output += tmp_char;
        }
        
        
        return output;
    }
    
    std::string toPrefix(const std::string *expression)
    {
        std::string prefix_result;
        
        if (!is_expression_valid(expression)) {
            return std::string("Invalid expression.");
        }
        
        prefix_result = toPostfix(expression);
        
        return reverse(&prefix_result);
    }
    
    
};

int main(int argc, const char * argv[])
{
    std::stack <char> stack;
    PolishNotationer polishNotationer(&stack);
    
    std::string expression = "15 / (78 - (199 + 1)) * 3 - (2 + (1 + 1)^4)";
    
    std::cout << "Prefix: " << polishNotationer.toPrefix(&expression) << "\n\n";
    std::cout << "Postfix: " << polishNotationer.toPostfix(&expression) << "\n\n";
    
    return 0;
}

