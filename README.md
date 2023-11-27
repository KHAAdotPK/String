** CPP string class **

To do everyday text parsing in style, with much ease and comfort. Parsing is ugly, and this git repository attempts at pushing that ugly under a layer of abstraction.  

## Usage

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
This project is licensed under a license, the copy of which can be found in file - see the file named LICENSE for details. 


