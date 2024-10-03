#include <cstdio>
#include <iostream>
#include <cmath>
#include "vm.hpp"


void vm::interpret(Chunk& _chunk) 
{
    chunk = std::move(_chunk);
    ip = chunk.code;
    try
    {
        run();
    }
    catch(const RunTimeException& e)
    {
        std::cerr << "[Runtime Expection] : "<<e.what()<<"\n";
    }
}

void vm::run() 
{


#define READ_BYTE() (*ip++)
#define READ_CONSTANT() (chunk.constants.values[READ_BYTE()]);
#define BINARY(op)\
    do\
    {\
        double b = stack.top();\
        stack.pop();\
        double a = stack.top();\
        stack.pop();\
        stack.push(a op b);\
    }\
    while(false)\
    

    for(;;)
    {
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {

            case OP_ADD:
                BINARY(+);
                break;
            
            case OP_SUB:
                BINARY(-);
                break;

            case OP_MUL:
                BINARY(*);
                break;
            
            case OP_DIV:
            {
                double b = stack.top();
                stack.pop();
                double a = stack.top();
                stack.pop();

                if(b == 0) throw RunTimeException("Divide by Zero");
                stack.push(a/b);
                break;
            }

            case OP_NEG:
            {
                double a = stack.top();
                stack.pop();
                stack.push(-a);
                break;
            }

            case OP_EXPO:
            {
                double p = stack.top();
                stack.pop();
                double base = stack.top();
                stack.pop();

                if(base == 0 && p == 0)
                {
                    throw RunTimeException("zero power zero is Undefined.");
                }
                else if(base ==0 && p < 0)
                {
                    throw RunTimeException("zero power " + std::to_string(p) +" is undefined.");
                }
                else
                {
                    stack.push(std::pow(base , p));
                }
                break;
            }

            case OP_SIN:
            {
                double a = stack.top();
                stack.pop();
                stack.push(std::sin(a));
                break;
            }

            case OP_COS:
            {
                double a = stack.top();
                stack.pop();
                stack.push(std::cos(a));
                break;
            }

            case OP_TAN:
            {
                double a = stack.top();
                stack.pop();

                double epsilon = 1e-9;
                if(std::abs(std::cos(a)) > epsilon)
                {
                    stack.push(std::tan(a));
                }
                else
                {
                    throw RunTimeException("Tan "+std::to_string(a)+" is undefined.");
                }
                break;
            }

            case OP_LN:
            {
                double a = stack.top();
                stack.pop();

                if(a > 0)
                {
                    stack.push(std::log10(a));
                }
                else
                {
                    throw RunTimeException("ln "+ std::to_string(a) 
                        + " is undefined.\n ln is defined for x if and only if x > 0.");
                }
                break;
            }

            case OP_CONSTANT:
            {
                double constant = READ_CONSTANT();
                stack.push(constant);
                break;
            }

            case OP_PRINT:
            {
                if(!stack.empty())
                {
                    printf("%g\n" , stack.top());
                    stack.pop();
                    return;
                }
                printf("%s\n","nil");
                return;
            }

            default:
                printf("Unknown Instruction\n");
                break;
        }

    }
#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY


}
