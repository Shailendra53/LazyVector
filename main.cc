/**
 * main.cc
 * 
 * Example program demonstrating the usage of LazyVector template class.
 * Shows how to create vectors, perform lazy arithmetic operations,
 * and display the results.
 * 
 * author: github.com/Shailendra53
 */

#include "LazyVector.h"

/**
 * Main entry point of the program.
 * 
 * Demonstrates the LazyVector class by:
 * 1. Creating two integer vectors
 * 2. Populating them with values
 * 3. Performing various lazy arithmetic operations (add, subtract, multiply, divide)
 * 4. Displaying both original and computed vectors
 * 
 * Returns:
 *   0 on successful execution
 */
int main(int argc, char const *argv[])
{
    // Create first vector and populate with values
    LazyVector<int> intVector1;
    intVector1.PushValue(1);
    intVector1.PushValue(2);
    intVector1.PushValue(3);
    intVector1.PushValue(4);
    intVector1.PushValue(5);

    // Create second vector and populate with values
    LazyVector<int> intVector2;
    intVector2.PushValue(6);
    intVector2.PushValue(7);
    intVector2.PushValue(8);
    intVector2.PushValue(9);
    intVector2.PushValue(10);

    // Perform lazy arithmetic operations
    LazyVector<int> added = (intVector1 + intVector2);
    LazyVector<int> subtracted = (intVector2 - intVector1);
    LazyVector<int> multiplied = (intVector1 * intVector2);
    LazyVector<int> divided = (intVector2 / intVector1);

    // Display results
    std::cout << "Original Vector 1: ";
    intVector1.PrintVector();
    std::cout << "Original Vector 2: ";
    intVector2.PrintVector();
    std::cout << "Added: ";
    added.PrintVector();
    std::cout << "Subtracted: (Vec2 - Vec1) ";
    subtracted.PrintVector();
    std::cout << "Multiplied: ";
    multiplied.PrintVector();
    std::cout << "Divided: (Vec2 / Vec1) ";
    divided.PrintVector();

    return 0;
}
