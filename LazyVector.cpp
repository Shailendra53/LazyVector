/**
 * 
 * LazyVector<T> class using std::vector<T>
 * 
 * author: github.com/Shailendra53
 * 
 */

#include <iostream>
#include <stdexcept>

// Operators available on LazyVector.
enum Operator {
    Add = 0,
    Subtract,
    Divide,
    Multiply,
    Unknown
};

// LazyVector class.
template <typename T>
class LazyVector {
public:
    // Default constructor.
    LazyVector() : m_eOperator (Operator::Unknown) {

    }

    // Move Constructor.
    LazyVector(LazyVector<T>&& other) {
        m_stlVector = other.m_stlVector;
        other.m_stlVector.clear();

        m_eOperator = other.m_eOperator;
        other.m_eOperator = Operator::Unknown;

        m_stlOtherVector = other.m_stlOtherVector;
        other.m_stlOtherVector.clear();
    }

    // Copy Constructor.
    LazyVector(const LazyVector<T>& other) {
        this->m_stlVector = other.m_stlVector;
        this->m_eOperator = other.m_eOperator;
        this->m_stlOtherVector = other.m_stlOtherVector;

        if (this->m_eOperator != Operator::Unknown) {
            this->performOperation();
        }
    }

    // Add value to vector.
    void PushValue(T value) {
        if (!m_stlOtherVector.empty()) {
            // TODO: change to this invalid operation or something similar.
            throw std::invalid_argument(
                "Invalid Operation: Vector should be operated on before new element can be added.");
        }

        m_stlVector.push_back(value);
    }

    // Addition Operator overloading.
    LazyVector<T> operator+(LazyVector<T>& otherVector) {
        if (m_stlVector.size() != otherVector.size()) {
            throw std::invalid_argument("Vectors to be added should have same size.");
        }

        this->m_eOperator = Operator::Add;
        this->m_stlOtherVector = otherVector.m_stlVector;
        return *this;
    }

    // Subtraction Operator overloading.
    LazyVector<T> operator-(LazyVector<T>& otherVector) {
        if (m_stlVector.size() != otherVector.size()) {
            throw std::invalid_argument("Vectors to be subtracted should have same size.");
        }

        this->m_eOperator = Operator::Subtract;
        this->m_stlOtherVector = otherVector.m_stlVector;
        return *this;
    }

    // Multiplication Operator overloading.
    LazyVector<T> operator*(LazyVector<T>& otherVector) {
        if (m_stlVector.size() != otherVector.size()) {
            throw std::invalid_argument("Vectors to be multiplied should have same size.");
        }

        this->m_eOperator = Operator::Multiply;
        this->m_stlOtherVector = otherVector.m_stlVector;
        return *this;
    }

    // Division Operator overloading.
    LazyVector<T> operator/(LazyVector<T>& otherVector) {
        if (m_stlVector.size() != otherVector.size()) {
            throw std::invalid_argument("Vectors to be divided should have same size.");
        }

        this->m_eOperator = Operator::Divide;
        this->m_stlOtherVector = otherVector.m_stlVector;
        return *this;
    }

    LazyVector<T>& operator=(LazyVector<T>& otherVector) {
        if (otherVector.m_eOperator == Operator::Unknown) {
            return *this;
        }

        this->m_stlVector = otherVector.m_stlVector;
        this->m_eOperator = otherVector.m_eOperator;
        this->m_stlOtherVector = otherVector.m_stlOtherVector;

        this->performOperation();

        otherVector.m_eOperator = Operator::Unknown;
        otherVector.m_stlOtherVector.clear();

        return *this;
    }

    size_t size() {
        return m_stlVector.size();
    }

    void PrintVector() {
        for (int i=0; i < m_stlVector.size(); i++) {
            std::cout << m_stlVector[i] << " ";
        }

        std::cout << std::endl;
    }

    std::vector<T> GetVector() {
        return m_stlVector;
    }

    T& operator[](int index) {
        return m_stlVector[index];
    }

private:
    // Add Vectors.
    void addVectors() {
        for (int i=0; i < m_stlVector.size(); i++) {
            m_stlVector[i] += m_stlOtherVector[i];
        }
    }

    // Subtract Vectors.
    void subtractVectors() {
        for (int i=0; i < m_stlVector.size(); i++) {
            m_stlVector[i] -= m_stlOtherVector[i];
        }
    }

    // Multiple Vectors.
    void multiplyVectors() {
        for (int i=0; i < m_stlVector.size(); i++) {
            m_stlVector[i] *= m_stlOtherVector[i];
        }
    }

    // Divide Vectors (m_stlVector / m_stlOtherVector).
    void divideVectors() {
        for (int i=0; i < m_stlVector.size(); i++) {
            m_stlVector[i] /= m_stlOtherVector[i];
        }
    }

    // Function to perform the arithmatic operation internally.
    void performOperation() {
        switch (m_eOperator) {
        case Operator::Add :
            this->addVectors();
            break;
        case Operator::Subtract :
            this->subtractVectors();
            break;
        case Operator::Multiply :
            this->multiplyVectors();
            break;
        case Operator::Divide :
            this->divideVectors();
            break;
        default :
            throw std::invalid_argument("Invalid Operation");
            break;
        }

        this->m_eOperator = Operator::Unknown;
        this->m_stlOtherVector.clear();
    }

private:
    std::vector<T> m_stlVector;
    Operator m_eOperator;
    std::vector<T> m_stlOtherVector;
};


int main(int argc, char const *argv[])
{
    LazyVector<int> intVector1;
    intVector1.PushValue(1);
    intVector1.PushValue(2);
    intVector1.PushValue(3);
    intVector1.PushValue(4);
    intVector1.PushValue(5);

    LazyVector<int> intVector2;
    intVector2.PushValue(6);
    intVector2.PushValue(7);
    intVector2.PushValue(8);
    intVector2.PushValue(9);
    intVector2.PushValue(10);

    LazyVector<int> added = (intVector1 + intVector2);
    LazyVector<int> subtracted = (intVector2 - intVector1);
    LazyVector<int> multiplied = (intVector1 * intVector2);
    LazyVector<int> divided = (intVector2 / intVector1);

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




















