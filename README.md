__This is a C++ class definition for a String class. The class provides various functionalities for manipulating and working with strings. Here's a breakdown of the code:__

__Header:__
* Includes necessary header files for `ala_exception`, `allocator`, `input_iterator`, and `string_character_traits`.
* Defines include guards to prevent multiple inclusions of the header file.

__Class definition:__
* Template class String with three template parameters:
    * E: The type of characters stored in the string.
    * T: The character traits type for E.
    * A: The allocator type for memory allocation.
* __public section__: 
 It contains various member functions and type definitions for interacting with the string:
    * __Type aliases__:
        *  `value_type`: Alias for the type of characters stored in the string.
        *  `size_type`: Alias for the type of size and position values.
        *  `difference_type`: Alias for the type of differences between positions.
        *  `reference`: Alias for a reference to a character in the string.
        *  `const_reference`: Alias for a constant reference to a character in the string.
        *  `pointer`: Alias for a pointer to a character in the string.
        *  `const_pointer`: Alias for a constant pointer to a character in the string.
        *  `iterator`: Alias for an iterator type that iterates over characters in the string.
    * `_NPOS_string`: Constant value representing "not found" position (npos).
    * __Constructors__:
        * Default constructor: Initializes an empty string.
        * Constructor with `size` parameter: Initializes a string with the given size filled with E's default value.
        * Copy constructor: Creates a new string from another string.
        * Constructor with `pointer` and `size` parameters: Initializes a string from an existing character array.
        * Constructor with `pointer`: Initializes a string from an existing null-terminated character array.
        * Constructor with `size` and `value_type` parameters: Initializes a string with the given size filled with the specified character.
        * __Additional constructors for converting numbers to strings__:
            * Converts a signed integer to a string.
            * Converts an unsigned integer to a string.
    * __Member functions__:
        * `data()`: Returns a constant pointer to the underlying character array.
        * `c_str()`: Returns a null-terminated C-style string.
        * `capacity()`: Returns the capacity of the string (allocated memory).
        * `size()`: Returns the size of the string (number of characters).
        * `max_size()`: Returns the maximum size the string can hold.
        * `resize(size_type n, value_type c)`: Changes the size of the string to n and fills the new characters with c.
        * `operator=(String<E, T, A>& ref)`: Assignment operator that copies the contents of another string.
        * `operator+=(E c)`: Appends a character to the string.
        * `operator-=(size_type n)`: Increases the capacity of the string by n.
        * `operator+(const String<E, T, A>& ref)`: Concatenates two strings.
        * `substr(size_type pos = 0, size_type len = npos)`: Returns a substring from the string.
        * `operator[](size_type pos)`: Returns the character at a specific position.
        * `erase(size_type pos = 0, size_type len = npos)`: Erases a substring from the string.
        * `replace(size_type pos, size_type len, size_type n, E c)`: Replaces a substring with a specified character repeated a certain number of times.
        * `find(const_pointer s, size_type pos, size_type n)`: Finds the first occurrence of a substring in the string.
        * `find(const String<E, T, A>& str, size_type pos = 0)`: Finds the first occurrence of another string in the string.
* __Private members__:
    * `str`: Pointer to the underlying character array.
    * `size_of_str`: Size of the string (number of characters).
    * `capacity_of_str`: Capacity of the string (allocated memory).

Overall, this class provides a comprehensive and efficient implementation for handling strings in C++.

## Dependencies

This library has a dependency on the allocator class, which is available in the [KHAAdotPK/allocator](https://github.com/KHAAdotPK/allocator) repository. Ensure that you have the allocator library installed or included in your project before using this string library. You can achieve this by cloning the [KHAAdotPK/allocator](https://github.com/KHAAdotPK/allocator) repository into your project's lib folder/directory.

__Example Usage__:
```C++
/*
 * string/main.cpp
 * Wrintten by Q@khaa.pk
 */
#include <iostream>
#include "src/String.hh"
using namespace::cc_tokenizer;

int main(int argc, char* argv[])
{
    String<char> ss("NLP using Transformers");
    std::cout<< ss.c_str() << std::endl;
    /*
        10 is starting index into the target string
        12 is the size of the target string
        5 is the number of replacements in the target string
        'Q' is the replacing 
     */
    ss.replace(10, 12, 5, 'Q');
    std::cout<< ss.c_str() << std::endl;

    String<char> obj("help");
    String<char> obj1("help");
    std::cout<< obj.compare(obj1) << std::endl;

    obj1.replace(3, 1, 1, '2');
    std::cout<< obj1.c_str() << std::endl;
    std::cout<< obj1.compare(obj) << std::endl;

    String<char> tmm("Transformer model is CNN with memory");
    std::cout<< tmm.size() << std::endl;
    // Find 'C' from index 0 to 22, if found return the index of the vector 'C' from the begining of the string(index 0)
    std::cout<< tmm.rfind('C', 22) << std::endl;

    String<char> N("Transformer model");
  
    String<char> L(" is CNN with");
    String<char> P(" memory.");

    N + L + P; //N = N + L + P;

    std::cout<< N.c_str() << std::endl;

    return 0;
}
```

### License
This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.' Please refer to this file for comprehensive information.


