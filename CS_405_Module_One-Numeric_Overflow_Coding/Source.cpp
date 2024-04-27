// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // Standard input/output stream lib for console output
#include <limits>       // Standard limits lib for numeric limits
#include <stdexcept>    // Standard exceptions lib for overflow_error and underflow_error
#include <typeinfo>     // Standard typeinfo lib for typeid

/// <summary>
/// Modified to detect and prevent overflow.
/// Template function to abstract away the logic of: start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that supports basic math functions</typeparam>
/// <param name="start">The starting number</param>
/// <param name="increment">The amount to add at each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>The result of the addition or throws an overflow_error</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Overflow check before addition
        if (increment > 0 && result > std::numeric_limits<T>::max() - increment)
        {
            throw std::overflow_error("Overflow detected in add_numbers function");
        }
        result += increment;
    }
    return result;
}

/// <summary>
/// Modified to detect and prevent underflow.
/// Template function to abstract away the logic of: start - (decrement * steps)
/// </summary>
/// <typeparam name="T">A type that supports basic math functions</typeparam>
/// <param name="start">The starting number</param>
/// <param name="decrement">The amount to subtract at each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>The result of the subtraction or throws an underflow_error</returns>
template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Underflow check before subtraction
        if (decrement > 0 && result < std::numeric_limits<T>::min() + decrement)
        {
            throw std::underflow_error("Underflow detected in subtract_numbers function");
        }
        result -= decrement;
    }
    return result;
}

/// <summary>
/// Tests the add_numbers function for overflow. Modified to catch and report overflow exceptions.
/// </summary>
/// <typeparam name="T">Numeric type to test</typeparam>
template <typename T>
void test_overflow()
{
    const unsigned long int steps = 5;
    const T increment = std::numeric_limits<T>::max() / steps;
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;

    // Attempt to add numbers and catch overflow exceptions
    try
    {
        T result = add_numbers<T>(start, increment, steps);
        std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = " << +result << std::endl;
    }
    catch (const std::overflow_error& e)
    {
        std::cout << "\t" << e.what() << std::endl;
    }

    // Attempt to add numbers with an additional step to induce overflow
    try
    {
        T result = add_numbers<T>(start, increment, steps + 1);
        std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
        std::cout << +result << std::endl;
    }
    catch (const std::overflow_error& e)
    {
        std::cout << "\t" << e.what() << std::endl;
    }
}

/// <summary>
/// Tests the subtract_numbers function for underflow. Modified to catch and report underflow exceptions.
/// </summary>
/// <typeparam name="T">Numeric type to test</typeparam>
template <typename T>
void test_underflow()
{
    const unsigned long int steps = 5;
    const T decrement = std::numeric_limits<T>::max() / steps;
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;

    // Attempt to subtract numbers and catch underflow exceptions
    try
    {
        T result = subtract_numbers<T>(start, decrement, steps);
        std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = " << +result << std::endl;
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "\t" << e.what() << std::endl;
    }

    // Attempt to subtract numbers with an additional step to induce underflow
    try
    {
        T result = subtract_numbers<T>(start, decrement, steps + 1);
        std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
        std::cout << +result << std::endl;
    }
    catch (const std::underflow_error& e)
    {
        std::cout << "\t" << e.what() << std::endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Test various data types for overflow conditions
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Test various data types for underflow conditions
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    do_overflow_tests(star_line); // Run overflow tests
    do_underflow_tests(star_line); // Run underflow tests

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}
