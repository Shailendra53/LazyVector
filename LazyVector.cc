/**
 * LazyVector.cc
 * 
 * Implementation file for LazyVector template class.
 * Contains the definitions of all member functions and operator overloads.
 * 
 * author: github.com/Shailendra53
 */

// Move constructor implementation
template <typename T>
LazyVector<T>::LazyVector(LazyVector<T>&& other) {
    m_stlVector = other.m_stlVector;
    other.m_stlVector.clear();

    m_eOperator = other.m_eOperator;
    other.m_eOperator = Operator::Unknown;

    m_stlOtherVector = other.m_stlOtherVector;
    other.m_stlOtherVector.clear();
}

// Copy constructor implementation
template <typename T>
LazyVector<T>::LazyVector(const LazyVector<T>& other) {
    this->m_stlVector = other.m_stlVector;
    this->m_eOperator = other.m_eOperator;
    this->m_stlOtherVector = other.m_stlOtherVector;

    if (this->m_eOperator != Operator::Unknown) {
        this->performOperation();
    }
}

// PushValue implementation
template <typename T>
void LazyVector<T>::PushValue(T value) {
    if (!m_stlOtherVector.empty()) {
        throw std::invalid_argument(
            "Invalid Operation: Vector should be operated on before new element can be added.");
    }

    m_stlVector.push_back(value);
}

// Addition operator implementation
template <typename T>
LazyVector<T> LazyVector<T>::operator+(LazyVector<T>& otherVector) {
    if (m_stlVector.size() != otherVector.size()) {
        throw std::invalid_argument("Vectors to be added should have same size.");
    }

    this->m_eOperator = Operator::Add;
    this->m_stlOtherVector = otherVector.m_stlVector;
    return *this;
}

// Subtraction operator implementation
template <typename T>
LazyVector<T> LazyVector<T>::operator-(LazyVector<T>& otherVector) {
    if (m_stlVector.size() != otherVector.size()) {
        throw std::invalid_argument("Vectors to be subtracted should have same size.");
    }

    this->m_eOperator = Operator::Subtract;
    this->m_stlOtherVector = otherVector.m_stlVector;
    return *this;
}

// Multiplication operator implementation
template <typename T>
LazyVector<T> LazyVector<T>::operator*(LazyVector<T>& otherVector) {
    if (m_stlVector.size() != otherVector.size()) {
        throw std::invalid_argument("Vectors to be multiplied should have same size.");
    }

    this->m_eOperator = Operator::Multiply;
    this->m_stlOtherVector = otherVector.m_stlVector;
    return *this;
}

// Division operator implementation
template <typename T>
LazyVector<T> LazyVector<T>::operator/(LazyVector<T>& otherVector) {
    if (m_stlVector.size() != otherVector.size()) {
        throw std::invalid_argument("Vectors to be divided should have same size.");
    }

    this->m_eOperator = Operator::Divide;
    this->m_stlOtherVector = otherVector.m_stlVector;
    return *this;
}

// Assignment operator implementation
template <typename T>
LazyVector<T>& LazyVector<T>::operator=(LazyVector<T>& otherVector) {
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

// size implementation
template <typename T>
size_t LazyVector<T>::size() {
    return m_stlVector.size();
}

// PrintVector implementation
template <typename T>
void LazyVector<T>::PrintVector() {
    for (int i = 0; i < m_stlVector.size(); i++) {
        std::cout << m_stlVector[i] << " ";
    }

    std::cout << std::endl;
}

// GetVector implementation
template <typename T>
std::vector<T> LazyVector<T>::GetVector() {
    return m_stlVector;
}

// Subscript operator implementation
template <typename T>
T& LazyVector<T>::operator[](int index) {
    return m_stlVector[index];
}

// Private: addVectors implementation
template <typename T>
void LazyVector<T>::addVectors() {
    for (int i = 0; i < m_stlVector.size(); i++) {
        m_stlVector[i] += m_stlOtherVector[i];
    }
}

// Private: subtractVectors implementation
template <typename T>
void LazyVector<T>::subtractVectors() {
    for (int i = 0; i < m_stlVector.size(); i++) {
        m_stlVector[i] -= m_stlOtherVector[i];
    }
}

// Private: multiplyVectors implementation
template <typename T>
void LazyVector<T>::multiplyVectors() {
    for (int i = 0; i < m_stlVector.size(); i++) {
        m_stlVector[i] *= m_stlOtherVector[i];
    }
}

// Private: divideVectors implementation
template <typename T>
void LazyVector<T>::divideVectors() {
    for (int i = 0; i < m_stlVector.size(); i++) {
        m_stlVector[i] /= m_stlOtherVector[i];
    }
}

// Private: performOperation implementation
template <typename T>
void LazyVector<T>::performOperation() {
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
