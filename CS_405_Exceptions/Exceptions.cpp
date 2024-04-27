// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>

// Custom exception class derived from std::exception
class CustomException : public std::exception {
public:
    // Constructor that takes an error message
    CustomException(const char* message) : std::exception(message) {}
};

bool do_even_more_custom_application_logic() {
    // Throw a standard exception to simulate an error
    throw std::runtime_error("An error occurred in even more custom logic");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic() {
    std::cout << "Running Custom Application Logic." << std::endl;

    // Exception handler for the code that might throw std::exception
    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    // Catch block for standard exceptions
    catch (const std::exception& e) {
        // Display a message and the content of the exception
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    // Throw a custom exception to demonstrate custom exception handling
    throw CustomException("Custom exception in custom logic");

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den) {
    // Check for divide by zero and throw a standard exception if true
    if (den == 0)
        throw std::invalid_argument("Denominator cannot be zero");

    return (num / den);
}

void do_division() noexcept {
    float numerator = 10.0f;
    float denominator = 0;

    // Exception handler for the divide function
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    // Catch block for standard exceptions
    catch (const std::exception& e) {
        // Display a message and the content of the exception
        std::cout << "Exception caught in division: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Exceptions Tests!\n\n" << std::endl;
    // Main try block to catch exceptions from the entire program
    try {
        do_division();
        do_custom_application_logic();
    }
    // Catch block for the custom exception
    catch (const CustomException& e) {
        std::cout << "Custom Exception caught: " << e.what() << std::endl;
    }
    // Catch block for standard exceptions
    catch (const std::exception& e) {
        std::cout << "Standard Exception caught: " << e.what() << std::endl;
    }
    // Catch-all handler for any uncaught exceptions
    catch (...) {
        std::cout << "Unknown exception caught" << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu