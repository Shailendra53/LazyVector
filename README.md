# LazyVector - Template Class for Lazy Vector Operations

## Overview

`LazyVector` is a C++ template class that implements **lazy evaluation** for vector arithmetic operations. Instead of immediately computing the result of arithmetic operations, LazyVector stores the operation and second operand, deferring the actual computation until the result is needed. This approach optimizes memory and computation by reducing unnecessary intermediate calculations.

## Features

- **Lazy Evaluation**: Operations are stored and executed only when results are assigned or retrieved
- **Template-Based**: Works with any data type that supports arithmetic operations (`int`, `float`, `double`, etc.)
- **Full Arithmetic Support**: Addition, subtraction, multiplication, and division operations
- **Vector Validation**: Ensures vectors have compatible sizes before operations
- **Move and Copy Semantics**: Efficient resource management with move and copy constructors

## File Structure

- `LazyVector.h` - Header file containing the class declaration and enum definition
- `LazyVector.cc` - Implementation file containing all member function definitions
- `main.cc` - Example program demonstrating LazyVector usage

## Class Components

### Enum: `Operator`

Defines the available arithmetic operations:
- `Add` - Vector addition
- `Subtract` - Vector subtraction  
- `Multiply` - Element-wise multiplication
- `Divide` - Element-wise division
- `Unknown` - No pending operation (default state)

### LazyVector Class

#### Public Members

| Method | Description |
|--------|-------------|
| `LazyVector()` | Default constructor - creates an empty vector |
| `LazyVector(LazyVector&&)` | Move constructor - transfers resources |
| `LazyVector(const LazyVector&)` | Copy constructor - creates a deep copy and executes pending operations |
| `void PushValue(T value)` | Adds a value to the end of the vector |
| `LazyVector operator+()` | Stores pending addition operation |
| `LazyVector operator-()` | Stores pending subtraction operation |
| `LazyVector operator*()` | Stores pending multiplication operation |
| `LazyVector operator/()` | Stores pending division operation |
| `LazyVector& operator=()` | Assignment operator with operation execution |
| `size_t size()` | Returns the number of elements |
| `void PrintVector()` | Prints all elements to stdout |
| `std::vector<T> GetVector()` | Returns a copy of the internal vector |
| `T& operator[]()` | Index-based element access |

#### Private Members

| Method | Description |
|--------|-------------|
| `void addVectors()` | Executes element-wise addition |
| `void subtractVectors()` | Executes element-wise subtraction |
| `void multiplyVectors()` | Executes element-wise multiplication |
| `void divideVectors()` | Executes element-wise division |
| `void performOperation()` | Dispatches and executes the pending operation |

## Usage Example

```cpp
#include "LazyVector.h"

int main() {
    // Create and populate vectors
    LazyVector<int> vec1, vec2;
    
    vec1.PushValue(1);
    vec1.PushValue(2);
    vec1.PushValue(3);
    
    vec2.PushValue(4);
    vec2.PushValue(5);
    vec2.PushValue(6);
    
    // Lazy operations - computation deferred
    LazyVector<int> result = (vec1 + vec2);  // Stores operation
    
    // Print result
    std::cout << "Result: ";
    result.PrintVector();  // Outputs: 5 7 9
    
    return 0;
}
```

## How Lazy Evaluation Works

1. When an arithmetic operator is invoked (e.g., `vec1 + vec2`), the operation is **not** immediately performed
2. Instead, the operation type and the second vector are **stored** in member variables
3. The actual computation happens when:
   - The result is assigned to another vector via the assignment operator
   - The result is copied via the copy constructor
   - Other methods requiring the computed result are called

## Important Notes

- **Size Matching**: Both vectors must have the same size for any arithmetic operation
- **Vector Modification**: Cannot add new values to a vector with pending operations (must complete the operation first)
- **Error Handling**: Uses `std::invalid_argument` exceptions for size mismatches and invalid operations
- **Performance**: Lazy evaluation is beneficial when operations are chained or intermediate results aren't needed

## Compilation

To compile with the reorganized files:

```bash
g++ -std=c++11 -o lazy_vector main.cc
./lazy_vector
```

Or with other C++ compilers:
```bash
clang++ -std=c++11 -o lazy_vector main.cc
```

## Author

github.com/Shailendra53

## License

Please refer to the repository for license information.
