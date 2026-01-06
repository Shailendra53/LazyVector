/**
 * LazyVector.h
 * 
 * Header file for LazyVector template class implementing lazy evaluation
 * for vector arithmetic operations.
 * 
 * author: github.com/Shailendra53
 */

#ifndef LAZYVECTOR_H
#define LAZYVECTOR_H

#include <iostream>
#include <vector>
#include <stdexcept>

/**
 * Enum representing the available arithmetic operations for LazyVector.
 * 
 * This enum defines the set of operations that can be performed on vectors:
 * - Add: Vector addition
 * - Subtract: Vector subtraction
 * - Divide: Element-wise division
 * - Multiply: Element-wise multiplication
 * - Unknown: No operation set (default state)
 */
enum Operator {
    Add = 0,        ///< Addition operation
    Subtract,       ///< Subtraction operation
    Divide,         ///< Division operation
    Multiply,       ///< Multiplication operation
    Unknown         ///< Unknown/no operation
};

/**
 * LazyVector class template.
 * 
 * A template class that implements lazy evaluation for vector arithmetic operations.
 * Operations are not immediately executed but stored as pending operations.
 * The actual computation happens only when the result is assigned or retrieved.
 * This approach optimizes memory and computation by deferring operations.
 * 
 * Template Parameters:
 *   T - The data type of elements stored in the vector (must support arithmetic operations)
 */
template <typename T>
class LazyVector {
public:
    /**
     * Default constructor.
     * Initializes an empty LazyVector with no pending operations.
     */
    LazyVector() : m_eOperator(Operator::Unknown) {}

    /**
     * Move constructor.
     * Transfers ownership of resources from another LazyVector to this one.
     * 
     * Parameters:
     *   other - The LazyVector to move from (will be left empty after construction)
     */
    LazyVector(LazyVector<T>&& other);

    /**
     * Copy constructor.
     * Creates a deep copy of another LazyVector.
     * If the source vector has pending operations, they are immediately executed.
     * 
     * Parameters:
     *   other - The LazyVector to copy from
     */
    LazyVector(const LazyVector<T>& other);

    /**
     * Adds a value to the vector.
     * 
     * Pushes a new element to the end of the vector.
     * Cannot add values if there are pending operations. Must complete or cancel
     * any pending operations first.
     * 
     * Parameters:
     *   value - The value to add to the vector
     * 
     * Throws:
     *   std::invalid_argument - If there are pending operations
     */
    void PushValue(T value);

    /**
     * Addition operator overload.
     * 
     * Performs lazy vector addition. Stores the operation and the second vector
     * without immediately computing the result.
     * 
     * Parameters:
     *   otherVector - The vector to add to this vector
     * 
     * Returns:
     *   A reference to this LazyVector with the pending operation stored
     * 
     * Throws:
     *   std::invalid_argument - If vectors have different sizes
     */
    LazyVector<T> operator+(LazyVector<T>& otherVector);

    /**
     * Subtraction operator overload.
     * 
     * Performs lazy vector subtraction. Stores the operation and the second vector
     * without immediately computing the result.
     * 
     * Parameters:
     *   otherVector - The vector to subtract from this vector
     * 
     * Returns:
     *   A reference to this LazyVector with the pending operation stored
     * 
     * Throws:
     *   std::invalid_argument - If vectors have different sizes
     */
    LazyVector<T> operator-(LazyVector<T>& otherVector);

    /**
     * Multiplication operator overload.
     * 
     * Performs lazy element-wise vector multiplication. Stores the operation
     * and the second vector without immediately computing the result.
     * 
     * Parameters:
     *   otherVector - The vector to multiply with this vector
     * 
     * Returns:
     *   A reference to this LazyVector with the pending operation stored
     * 
     * Throws:
     *   std::invalid_argument - If vectors have different sizes
     */
    LazyVector<T> operator*(LazyVector<T>& otherVector);

    /**
     * Division operator overload.
     * 
     * Performs lazy element-wise vector division. Stores the operation
     * and the second vector without immediately computing the result.
     * 
     * Parameters:
     *   otherVector - The vector to divide this vector by
     * 
     * Returns:
     *   A reference to this LazyVector with the pending operation stored
     * 
     * Throws:
     *   std::invalid_argument - If vectors have different sizes
     */
    LazyVector<T> operator/(LazyVector<T>& otherVector);

    /**
     * Assignment operator overload.
     * 
     * Assigns values from another LazyVector. If the source has pending operations,
     * they are executed before assignment.
     * 
     * Parameters:
     *   otherVector - The vector to assign from
     * 
     * Returns:
     *   A reference to this LazyVector after assignment
     */
    LazyVector<T>& operator=(LazyVector<T>& otherVector);

    /**
     * Returns the size of the vector.
     * 
     * Returns:
     *   The number of elements in the vector
     */
    size_t size();

    /**
     * Prints all elements of the vector to standard output.
     * 
     * Outputs each element separated by a space, followed by a newline.
     */
    void PrintVector();

    /**
     * Returns a copy of the internal vector.
     * 
     * Returns:
     *   A std::vector<T> containing all elements
     */
    std::vector<T> GetVector();

    /**
     * Subscript operator overload for element access.
     * 
     * Provides index-based access to vector elements.
     * 
     * Parameters:
     *   index - The zero-based index of the element
     * 
     * Returns:
     *   A reference to the element at the specified index
     */
    T& operator[](int index);

private:
    /**
     * Performs element-wise addition of vectors.
     * 
     * Adds each element of m_stlOtherVector to the corresponding element
     * in m_stlVector.
     */
    void addVectors();

    /**
     * Performs element-wise subtraction of vectors.
     * 
     * Subtracts each element of m_stlOtherVector from the corresponding element
     * in m_stlVector.
     */
    void subtractVectors();

    /**
     * Performs element-wise multiplication of vectors.
     * 
     * Multiplies each element of m_stlVector by the corresponding element
     * in m_stlOtherVector.
     */
    void multiplyVectors();

    /**
     * Performs element-wise division of vectors.
     * 
     * Divides each element of m_stlVector by the corresponding element
     * in m_stlOtherVector.
     */
    void divideVectors();

    /**
     * Executes the pending arithmetic operation.
     * 
     * Checks the stored operator and calls the appropriate operation function.
     * After execution, clears the pending operation and the temporary vector.
     * 
     * Throws:
     *   std::invalid_argument - If the operator is invalid/unknown
     */
    void performOperation();

private:
    std::vector<T> m_stlVector;         ///< The main vector storing elements
    Operator m_eOperator;               ///< The pending arithmetic operation
    std::vector<T> m_stlOtherVector;    ///< Temporary vector for the second operand
};

// Include the implementation file
#include "LazyVector.cc"

#endif // LAZYVECTOR_H
