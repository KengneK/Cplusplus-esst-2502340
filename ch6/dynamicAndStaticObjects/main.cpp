#include <iostream>

#define test 1

#include "calculator.h"

void performTasks(Calculator &calc)
{
    calc.doSomeMath();
    calc.showResults();
}

Calculator *tempCalc = nullptr;


void executeCalcs()
{
#if test == 1
    {
        // Static case
        Calculator calc1("Calc1");
        performTasks(calc1);
    }
#else
    // Static case
    Calculator calc1("Calc1");
    performTasks(calc1);
#endif

    // Dynamic case
    Calculator *calc2 = new Calculator("Calc2");
    performTasks(*calc2);

    tempCalc = calc2;

    // calc1 is automatically destroyed
    // but calc2 only gets destroyed when delete is called
}


int main()
{
    executeCalcs();
    std::cout << "Nach executable"<< std::endl;

    // Since tempCalc points to the same object as calc2, we
    // can use it for deletion.
    delete tempCalc;

    return 0;
}
