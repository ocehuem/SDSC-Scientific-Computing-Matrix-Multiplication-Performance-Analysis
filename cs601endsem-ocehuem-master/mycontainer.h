#ifndef MYCONTAINER_H
#define MYCONTAINER_H

#include <stdexcept>
#include <string>
int numLinesOfCodeAdded = 70; 
std::string me = "Harshitha(220010015)";  

template <typename T>
class MyContainer {
private:
    int len;    // Length of the container
    T* data;    // Dynamically allocated array for storing elements

public:
    // Constructor
    MyContainer(int _len) : len(_len), data(new T[_len]) {}

    // Copy Constructor
    MyContainer(const MyContainer<T>& initializer) : len(initializer.len), data(new T[initializer.len]) {
        for (int i = 0; i < len; i++) {
            this->data[i] = initializer.data[i];
        }
    }

    // Copy Assignment Operator
    MyContainer& operator=(const MyContainer<T>& rhs) {
        if (this != &rhs) {
            delete[] data; // Free existing memory
            len = rhs.len;
            data = new T[len];
            for (int i = 0; i < len; i++) {
                this->data[i] = rhs.data[i];
            }
        }
        return *this;
    }

    // Destructor
    ~MyContainer() {
        delete[] data;
    }

    // Subscript operator for non-const access
    T& operator[](int index) {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Subscript operator for const access
    const T& operator[](int index) const {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Concatenation operator (Q3)
    MyContainer<T>& operator+(const T& value) {
        if (len == 0) {
            throw std::runtime_error("Container is empty");
        }

        // Ensure that the last element exists and is concatenated with `value`.
        data[len - 1] += "_"+value;

        return *this; // Return the modified container
    }
};

#endif // MYCONTAINER_H
