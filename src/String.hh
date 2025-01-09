/* src/String.hh
   Written by, Q@khaa.pk */

#include "./../../ala_exception/ala_exception.hh"
#include "./../../allocator/allocator.hh"
#include "input_iterator.hh"   
#include "string_character_traits.hh"

/* Include guards */
#ifndef	CC_TOKENIZER_STRING_HH
#define	CC_TOKENIZER_STRING_HH

#ifndef CC_TOKENIZER_PRECISION_OF_DOUBLE_TO_STRING_HH
#define CC_TOKENIZER_PRECISION_OF_DOUBLE_TO_STRING_HH 6
#endif

namespace cc_tokenizer {

template < typename E, class T = string_character_traits<E>, class A = allocator<E> >
class String {

   public:
 
      /*
      // old way of doing "type aliases", newer way is 
      // using value_type = typename A::value_type;
       */
      typedef	typename A::value_type		value_type; 
      typedef	typename A::size_type		size_type; 
      typedef	typename A::difference_type	difference_type;
      typedef	typename A::reference		reference;
      typedef	typename A::const_reference	const_reference;
      typedef	typename A::pointer 		pointer;
      typedef	typename A::const_pointer 	const_pointer;

      /*
      // old way of doing "type aliases", newer way is 
      // using iterator = typename std::iterator_traits<input_iterator<E, String<E, T, A> > >::value_type;
       */      
      typedef typename std::iterator_traits<input_iterator<E, String<E, T, A> > >::value_type iterator;
      
      enum _NPOS_string { npos = (static_cast<typename A::size_type>(0) + static_cast<typename A::size_type>(-1))/sizeof(E)  };
   
      /* Constructors, default constructible */
      String(void) : str(NULL), size_of_str(size_type(0)), capacity_of_str(size_type(0)) {
      }

/*
      String(size_type n) {

          allocator<E> alloc_obj;

          try {

              str = alloc_obj.allocate(n);

              if ( str ) {                           
                  size_of_str = n;
                  capacity_of_str = n;
               }
               else {            
                    str = NULL;
                    size_of_str = size_type(0);
                    capacity_of_str = size_type(0);
               }

          }
          catch (std::bad_alloc& e) {
            size_of_str = size_type(0);
            capacity_of_str = size_type(0); 
         }
         catch(std::length_error& e) {         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }    
      }
*/      
     
      /* Constructors, copy constructor */ 
      String(const String<E, T, A>& ref) {
      
         allocator<E> alloc_obj;
         
         try {
         
            str = alloc_obj.allocate(ref.capacity());
            
            if ( str ) {
            
               T::copy(str, ref.str, ref.size());
               size_of_str = ref.size();
               capacity_of_str = ref.capacity();
            }
            else {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
             
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0); 
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
      }
      
      String(const String<E, T, A>& ref, size_type pos, size_type n ) {
      
         if ( ( pos + n ) <= ref.capacity() ) {
         
            allocator<E> alloc_obj;
           
            try {   
               str = alloc_obj.allocate(n);
            
               if ( str ) {
               
                  T::copy(str, ref.str + pos, n);
                  size_of_str = n;
                  capacity_of_str = n;
               }
               else {
            
                  str = NULL;
                  size_of_str = size_type(0);
                  capacity_of_str = size_type(0);
               }
            } 
            catch(std::bad_alloc& e) {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
            catch(std::length_error& e) {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
         }
         else {
      
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
        }       
      }
      
      String(const_pointer ptr, size_type n) {
      
         allocator<E> alloc_obj;
         /* SONI-NOW */
         //std::cout<<"In String(const_pointer, size_type), n = "<<n<<std::endl;
         try {
         
            str = alloc_obj.allocate(n);
            
            if ( str ) {
            
               T::copy(str, ptr, n);
               size_of_str = size_type(n);
               capacity_of_str = size_type(n);   
            }
            else {
            
               str = NULL;
               size_of_str = size_type(0);
               capacity_of_str = size_type(0);
            }
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = size_type(0);
            capacity_of_str = size_type(0);
         }
         
      }

      String(const_pointer ptr) {
      
         allocator<E> alloc_obj;
        
         size_of_str = T::length(ptr);
         capacity_of_str = size_of_str + size_type(1);
         
         try {
         
            str = alloc_obj.allocate(capacity_of_str);
            
            if ( str ) {
            
               value_type eos = T::eos();   
            
               T::copy(str, ptr, size());
               T::assign(str[size()], eos);               
            }
            else {
            
               str = NULL;
               size_of_str = 0;
               capacity_of_str = 0;
            }
            
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
      }
      
      String(size_type n, value_type c) {
      
         cc_tokenizer::allocator<E> alloc_obj;
         
         try {
         
            str = alloc_obj.allocate(n);
            
            if ( str && n ) {
               
               for ( size_type i = 0; i < n; i++ ) {
               
                  T::assign(str[i], c);
               }
               
               size_of_str = n;
               capacity_of_str = n;

               //std::cout<<"DIDO = capacity = "<<capacity_of_str<<", size = "<<size_of_str<<std::endl;
            }
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
      }

      /**
       * Constructor: String(double n, unsigned int precision = 12)
       * 
       * This constructor initializes a String object by converting a double-precision
       * floating-point number into its character (string) representation, with an
       * optional precision for the fractional part. The resulting string is stored 
       * in dynamically allocated memory.
       * 
       * Parameters:
       * - n: The double value to be converted into a string.
       * - precision (optional): Specifies the number of digits to retain in the 
       *   fractional part of the number. Defaults to `CC_TOKENIZER_PRECISION_OF_DOUBLE_TO_STRING_HH` if not provided.
       * 
       * Functionality:
       * - Handles both positive and negative numbers. If the input number is negative, 
       *   the minus sign is added to the string at the end.
       * - Separates the integer part and fractional part of the number.
       * - The fractional part is calculated by multiplying by powers of 10 up to the 
       *   specified precision.
       * - Memory is dynamically allocated to store the resulting string, including 
       *   space for leading/trailing zeros and the decimal point.
       * - Exception handling is implemented to catch bad memory allocations and 
       *   length errors.
       * 
       * Edge Cases:
       * - Handles small fractions by adding leading zeros in the fractional part.
       * - Correctly handles numbers with a large number of trailing zeros.
       * - If the precision exceeds the significant digits, additional zeros are added 
       *   to the fractional part as necessary.
       * 
       * Exceptions:
       * - If memory allocation fails (std::bad_alloc), the string is set to NULL.
       * - If a length error occurs (std::length_error), the string is also set to NULL.
       * Note:
       * - `CC_TOKENIZER_PRECISION_OF_DOUBLE_TO_STRING_HH` is a macro defined in the same file (String.hh) to set the default precision.
       */
      String(double n, unsigned int precision = CC_TOKENIZER_PRECISION_OF_DOUBLE_TO_STRING_HH)
      {
          unsigned int i = 0, j = 0; // `i` keeps track of leading zeros in the fractional part, `j` controls the loop
          bool negative_or_not_flag = (n < 0) ? true : false; // Flag for negative number
          pointer new_str = NULL; // New string pointer for storing result

          str = NULL; // Initialize member variables
          size_of_str = 0;
          capacity_of_str = 0;

          if (negative_or_not_flag)
          {
              n = (-1) * n; // If the number is negative, make it positive for easier processing
          }

          long long int_part = static_cast<long long>(n); // Extract the integer part of `n`         
          long long multiplier = 1;

          // Loop to handle precision and determine leading zeros in the fractional part  
          for (; i < precision;)
          {
              multiplier = multiplier * 10; // Increment multiplier by 10 to scale the fractional part

              // Check if the fractional part is non-zero at a certain precision level
              if (static_cast<long long>((n - int_part)*multiplier) != 0)
              {                 
                  break; // Stop if fractional part is non-zero                 
              }

              i++; // Count how many leading zeros are in the fractional part
          }

          multiplier = 1;

          // Set the multiplier for extracting the fractional part based on precision  
          for (; j < precision;)
          {
              multiplier = multiplier * 10; 
              j++;
          }

          j = 0;

          long long fractional_part = static_cast<long long>((n - int_part)*multiplier); // Compute fractional part
                                        
          try 
          {               
               // Process the fractional portion and append it to the string
	            do 
               {
                    // Allocate space for the new string with one additional character 
	                 new_str = cc_tokenizer::allocator<char>().allocate(size_of_str + 1); 
	                 T::copy(new_str + 1, str, size_of_str); // Copy old string to the new allocated space
                    value_type rem = value_type(fractional_part % 10 + '0'); // Get the least significant digit
	                 T::assign(*new_str, rem); // Assign the remainder to the new string

                    // Deallocate the old string memory 
                    if ( str ) 
                    {
	                     cc_tokenizer::allocator<char>().deallocate(str, size_of_str);
	                 }

	                 str = new_str; // Update the string pointer to the new string
	                 size_of_str = size_of_str + 1; // Update the size of the string
	                 capacity_of_str = size_of_str; // Update capacity
	            } while( (fractional_part = fractional_part / 10) > 0 ) /* Deducts multiple of 10 and stores back the remainder */; 
               if (i > 0) // Handle leading zeros in fractional part
               {
                  new_str = cc_tokenizer::allocator<char>().allocate(size_of_str + i);
                  T::copy(new_str + i, str, size_of_str); 

                  // Add leading zeros
                  for (; j < i;)
                  {
                     new_str[j] = '0'; // Append '0' for each leading zero

                     j++;
                  }

                  if ( str ) 
                  {
	                  cc_tokenizer::allocator<char>().deallocate(str, size_of_str);
	               }

                  str = new_str;
	               size_of_str = size_of_str + i; // Update size with leading zeros
	               capacity_of_str = size_of_str;

                  i = 0;
               }

               // Add the decimal point
               new_str = cc_tokenizer::allocator<char>().allocate(size_of_str + 1);
               T::copy(new_str + 1, str, size_of_str);                              
               new_str[0] = '.';
               if ( str ) 
               {
	               cc_tokenizer::allocator<char>().deallocate(str, size_of_str);
	            }
               str = new_str;
	            size_of_str = size_of_str + 1;
	            capacity_of_str = size_of_str;
               
               // Process the integer part and append it to the string
               do 
               {
	                 new_str = cc_tokenizer::allocator<char>().allocate(size_of_str + 1); 
	                 T::copy(new_str + 1, str, size_of_str);
                    value_type rem = value_type(int_part % 10 + '0'); // Get the least significant digit
	                 T::assign(*new_str, rem); // Assign the remainder to the new string

                    if ( str ) 
                    {
	                     cc_tokenizer::allocator<char>().deallocate(str, size_of_str);
	                 }

	                 str = new_str;
	                 size_of_str = size_of_str + 1; // Update size with each digit
	                 capacity_of_str = size_of_str;
	            } while( (int_part = int_part / 10) > 0 ); // Continue until all digits are processed

               // Handle the negative sign if the number was negative
               if (negative_or_not_flag) 
               {
                   new_str = cc_tokenizer::allocator<char>().allocate(size_of_str + 1);
                   T::copy(new_str + 1, str, size_of_str);                              
                   new_str[0] = '-';
                   if ( str ) 
                   {
	                   cc_tokenizer::allocator<char>().deallocate(str, size_of_str);
	                }
                   str = new_str;
	                size_of_str = size_of_str + 1; // Update size to include the negative sign
	                capacity_of_str = size_of_str;
               }            
          }
          catch (std::bad_alloc &e) 
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }
	       catch (std::length_error &e)
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }     
      }
      
      /* --------------------------------------------------------- */
      /*     Converts a number into an instance of String<...>     */
      /* The following two constructors does as stated previously  */
      /* --------------------------------------------------------- */
      /* n, a signed number */
      String(typename string_character_traits<E>::int_type n)
      {
          pointer new_str = NULL;
	       cc_tokenizer::allocator<E> alloc_obj;

          str = NULL;
	       size_of_str = 0;
	       capacity_of_str = 0;  

          try 
          {
	            /* Generate ASCII representation of the number in the reverse order */
	            do 
               {
	                 new_str = alloc_obj.allocate(size_of_str + 1); 
	                 T::copy(new_str + 1, str, size_of_str);
                    value_type rem = value_type(n % 10 + '0') /* get remainder for the unit place */;
	                 T::assign(*new_str, rem);

                    if ( str ) 
                    {
	                     alloc_obj.deallocate(str, size_of_str);
	                 }

	                 str = new_str;
	                 size_of_str = size_of_str + 1;
	                 capacity_of_str = size_of_str;

	            } while( (n = n / 10) > 0 ) /* Deducts multiple of 10 and stores back the remainder */;

	       }
	       catch (std::bad_alloc &e) 
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }
	       catch (std::length_error &e)
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }
      }

      /* pos, an unsigned number */
      String(typename cc_tokenizer::String<E, T, A>::size_type pos)
      {
	       pointer new_str = NULL;
	       cc_tokenizer::allocator<E> alloc_obj;

	       str = NULL;
	       size_of_str = 0;
	       capacity_of_str = 0;
          
	       try 
          {
	            /* Generate ASCII representation of the number in the reverse order */
	            do
               {

	                new_str = alloc_obj.allocate(size_of_str + 1); 
	                T::copy(new_str + 1, str, size_of_str);
                   value_type rem = value_type(pos % 10 + '0') /* get remainder for the unit place */;
	                T::assign(*new_str, rem);

                   if ( str )
                   {
	                    alloc_obj.deallocate(str, size_of_str);
	                }
	                str = new_str;
	                size_of_str = size_of_str + 1;
	                capacity_of_str = size_of_str;

	            } while( (pos = pos / 10) > 0 ) /* Deducts multiple of 10 and stores back the remainder */;
	       }
	       catch (std::bad_alloc &e)
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }
	       catch (std::length_error &e)
          {
	           str = NULL;
	           size_of_str = 0;
	           capacity_of_str = 0;
	       }
      }
      
      const_pointer data(void) const {

         return str;
      }
      
      const_pointer c_str(void) {
      
         const_pointer ret = NULL;
         
         //std::cout<<"In c_str()-> capacity() = "<<capacity()<<", size() = "<<size()<<std::endl;
         
         if ( capacity() > size() ) {
         
            //std::cout<<"- 1"<<std::endl;
         
            if ( T::ne(str[size()], T::eos()) ) {
            
               //std::cout<<"- 2"<<std::endl;
              
               value_type eos = T::eos();  
               T::assign(str[size()], eos);               
            }
            
            //std::cout<<"Here ,,,,,,,,,,"<<std::endl;              
            ret = str;
         }
         else { /* resize. Capacity is equal(atleast and atmost) to size, as capacity can never be less than of size, ever */
         
            //std::cout<<"- 3"<<std::endl;
            resize(size() + 1, T::eos());
            size_of_str = size_of_str - 1; /* because, the end of line character is not a part of the actual E array */
            ret = str;
         } 
         
         //std::cout<<"AND HERE......."<<std::endl;
         return ret;
      } 
      
      size_type capacity(void) const {
      
         return capacity_of_str;
      }
      
      size_type size(void) const {
      
         return size_of_str;
      }
      
      size_type max_size(void) const { 
      
         allocator<E> alloc_obj;
      
         return alloc_obj.max_size() - static_cast<size_type>(1);
      }
      
      void resize(size_type n, value_type c) throw (std::length_error) {
      
         if ( n > max_size() ) {
         
            throw std::length_error("cc_tokenizer::String<>::resize() - Integer overflow");
         }
         
         if ( n > size() ) {
         
            if ( n > capacity() ) { /*  */
            
               allocator<E> alloc_obj;
               
               try {
               
                  pointer new_str = alloc_obj.allocate(n);
                  
                  if ( new_str ) {
                  
                     size_type i = 0;
                  
                     for ( ; i < size(); ) {
                     
                        T::assign(new_str[i], str[i]);
                        i++;
                     }
                     for ( ; i < n; ) {
                     
                        T::assign(new_str[i], c); 
                        i++;
                     }
                     
                     alloc_obj.deallocate(str);
                     
                     str = new_str;
                     size_of_str = n;
                     capacity_of_str = n;   
                  }
                  
               }
               catch(std::bad_alloc& e) {
               }
               catch(std::length_error& e) {
               }
            }
            else { /* n is capacity(), atmost */
            
               for ( size_type i = size(); i < n; i++ ) {
               
                  T::assign(str[i], c);
               }
            }
         }
         else { /* n is atmost size(), we'll truncate the string, atmost */
         
            size_of_str = n;
            /* capacity_of_str remains unchanged */
         }
         
      }

      /* TODO, to be implemented. If need arrises */
      String<E, T, A>& operator=(const_pointer ptr)
      {                          
         size_of_str = T::length(ptr);
         capacity_of_str = size_of_str + size_type(1);
         
         try {
         
            str = cc_tokenizer::allocator<E>().allocate(capacity_of_str);
            
            if (str) {
            
               value_type eos = T::eos();   
            
               T::copy(str, ptr, size());
               T::assign(str[size()], eos);               
            }
            else {
            
               str = NULL;
               size_of_str = 0;
               capacity_of_str = 0;
            }
            
         }
         catch(std::bad_alloc& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }
         catch(std::length_error& e) {
         
            str = NULL;
            size_of_str = 0;
            capacity_of_str = 0;
         }

         return *this;
      }

      String<E, T, A> operator=(String<E, T, A>& ref)
      {          
          cc_tokenizer::allocator<E> alloc_obj;
            
          try  
          {   
              //std::cout<< " -> ref.capacity() = " << ref.capacity() << std::endl;               
              this->str = alloc_obj.allocate(ref.capacity());
              //this->str = cc_tokenizer::allocator<E>().allocate();
              this->size_of_str = ref.size();
              this->capacity_of_str = ref.capacity();                            
          }
          catch (const std::bad_alloc& e)
          {
              //std::cout<<"In assignment operator: "<<e.what()<<std::endl;
              throw ala_exception(cc_tokenizer::String<E>("In assignment operator: ") + cc_tokenizer::String<E>(e.what()));
          }
          catch (const std::length_error& e)
          {
              //std::cout<<"In assignment operator: "<<e.what()<<std::endl;
              throw ala_exception(cc_tokenizer::String<E>("In assignment operator: ") + cc_tokenizer::String<E>(e.what()));
          }
          
          /*
               Avoid unnecessary copying: In the current implementation, the loop iterates ref.size() times and calls the copy function for each iteration.
               This can result in redundant copying of the same characters.
               To optimize this, you can directly copy the entire character array using a more efficient method, such as std::memcpy.
               This will avoid redundant function calls and improve performance. Here's an example of how you can modify the loop: std::memcpy(this->str, ref.c_str(), ref.size());
           */  
          /*
          size_type i = 0;                            
          for ( ; i < ref.size(); ) 
          {                     
              T::copy(this->str, ref.c_str(), ref.size());
              i++;              
          }
           */
          std::memcpy(this->str, ref.c_str(), ref.size());
                    
          return *this;
      }

      bool operator==(const String<E, T, A>& ref)
      {
         bool ret = false;

         //std::cout<< "Literla = " << str << " ==== " << ref.str << std::endl;

         if (!compare(ref))
         {
             ret = true;
         }  

         return ret;
      }
                  
      void operator+=(E c)
      {
         //std::cout<<"-> "<<c<<std::endl;

         /*if (capacity())
         {
            if (capacity() > size())
         }*/

         if (capacity() > 0) 
         {
            //str[size() - capacity()] = c;
            T::assign(str[size() - capacity()], c);
            capacity_of_str -= 1;
         }

         //std::cout<<"capacity_of_str = "<<capacity_of_str<<std::endl;
      }

      void operator-=(size_type n)
      {
         //std::cout<<"capacity = "<<capacity_of_str<<", size = "<<size()<<std::endl;   

         if ((capacity_of_str + n) <= size_of_str)
         {
            capacity_of_str += n;
         }

         //std::cout<<"capacity = "<<capacity_of_str<<", size = "<<size_of_str<<std::endl; 
      }

      String<E, T, A> operator+(const String<E, T, A>& ref) throw(std::length_error, std::bad_alloc) {
      
         pointer new_str;
         allocator<E> alloc_obj;
         
         if ( (size() + ref.size()) > max_size() ) {
           
            throw std::length_error("cc_tokenizer::String<>::operator+(const String<>&) - Integer overflow.");   
         }

         //std::cout<< "The size = " << size() + ref.size() << ", max_size() = " << max_size() << std::endl;
         
         /*try*/ {                                                      
            new_str = alloc_obj.allocate(size() + ref.size());
            
            if ( new_str ) {
            
               T::copy(new_str, str, size());
               T::copy(new_str + size(), ref.str, ref.size());
               
               alloc_obj.deallocate( str );
           
               str = new_str;    
               size_of_str = size() + ref.size();
               capacity_of_str = size();
            }            
         }

         //std::cout<< str << std::endl;

         /*catch(std::bad_alloc& e) {
            std::cout<<" Caught it......." << std::endl;
         }
         catch(std::length_error& e) {
         }*/
         
         return *this;
      }
      
      String<E, T, A> substr(size_type pos = 0, size_type len = npos) const throw(std::out_of_range){
      
      
         //std::cout<<"pos = "<<pos<<", len = "<<len<<std::endl;
         
         /* If pos is greater than the string length, it throws out_of_range */
         if (pos > size()) {
         
            /* TODO, it is causing segmentation fault */
            throw new std::out_of_range((String<E, T, A>("Index(pos) = ") + String<E, T, A>(pos) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str() );
         }
         
         if (pos == size()) {
         
            return String<E, T, A>();
         }
         
         /* TODO, When len equals npos then, following code block does not get executed */
         if ((pos + len) > size()) {
                     
            len = size() - pos;
         }
        //std::cout<<"pos = "<<pos<<", len = "<<len<<std::endl;                                         
         return String<E, T, A>(this->data() + pos, len);
      }
      
      value_type operator[](size_type pos) const {
      
         return data()[pos];
      }
      
      /* Modifiers begin here */
      /* -------------------- */
      String<E, T, A>& erase(size_type pos = 0, size_type len = npos) throw(std::out_of_range)
      {
          /* pos, originates at zero */
	  /* TODO, consider using capacity() in place of size() */
          if (pos + len > size())
	  {
	      throw std::out_of_range((String<E, T, A>("Index(pos + len) = ") + String<E, T, A>(pos + len) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str());
	  }

	  allocator<E> alloc_obj;
	  pointer new_str = alloc_obj.allocate(size() - len);

	  T::copy(new_str, str, pos);
	  T::copy(new_str + pos, str + pos + len, size() - (pos + len));

	  alloc_obj.deallocate(str);
	  size_of_str = size() - len;
	  capacity_of_str = size_of_str;
	  str = new_str;

          return *this;
      }

      /* 
       * pos, position of the first character of type T to be replaced. If it is greater than the size/length of the string then out_of_range exception is thrown
       * len, number of characters to be replaced with the "T c". If string is shorter, as many characters as possible are replaced. A value of String<...>::npos indicates all characters untill the end of string(The sub-string of the whole string relative to "pos" that will be replaced by the "n" copies of the "c")
       * n, size of "T c"(number of characters to copy)
       * c, character value repeated n times
       */ 
      String<E, T, A>& replace(size_type pos, size_type len, size_type n, E c) throw(std::out_of_range) {

         /* pos, originates at zero */
	 /* TODO, consider using capacity() in place of size() */
         if ( pos >= size() ) {

	    throw std::out_of_range((String<E, T, A>("Index(pos) = ") + String<E, T, A>(pos) + String<E, T, A>(" is out of the upper-bound of the string(where upper-bound = ") + String<E, T, A>(size()) + String<E, T, A>(")")).c_str() );
	 }

         /* If string is shorter than the number of replacements relative to pos  then, adust the len. len can be equal to String<...>::npos as well */
         if ( len == npos ) {

	    len = size() - pos;  

	 } else if ( ( pos + len ) > size() ) {

	    len = len - ( ( pos + len ) - size() );
	 }

         /* Note:- "len" and "n" are mutually exclusive */ 
	 /* Note:- len, length of the portion/part of the string that will be replaced by the n copies of "c" */

	 if ( len == n ) {

	    for ( size_type i = pos; i < pos + n; i++ ) {

	       T::assign(str[i], c);  
	    }

	    return *this;
	 }

         /* len and n can now be not equal */  
	 if ( size() > ( size() - len + n ) ) { /* happens when len > n */

	    for ( size_type i = pos; i < (pos + n); i++ ) {

	       T::assign(str[i], c);
	    }
            for ( size_type i = pos + len; i < size(); i++ ) {
	      
	       T::assign(str[i - (len - n)], str[i]);
	    }

	    size_of_str = size() - len + n;
	    /* capacity_of_str, it remains unchanged. It atleast is equal to the previous size of the now changed string */

	 }
	 else if ( capacity() > ( size() - len + n ) ) { /* happens if len < n */
            for ( size_type i = pos + len; i < size() + (n - len); i++ ) {

	       T::assign(str[i + (n - len)], str[i]);
            }

	    for ( size_type i = pos; i < pos + n; i++ ) {

               T::assign(str[i], c); 
	    }

	    size_of_str = size_of_str + (n - len);
            /* capacity_of_str, it remains unchanged. All changes were in the outer bounds of the capacity */
	 } 
	 else { /* Reallocate, n > len and size of new string is capacity() + (n - len)  */
	    allocator<E> alloc_obj;
	    pointer new_str = alloc_obj.allocate(capacity() + ( n - len ));
            
            T::copy(new_str, str, pos);

	    for ( size_type i = pos; i < pos + n; i++ ) {

               T::assign(new_str[i], c);
	    }

	    for ( size_type i = pos + len; i < size() ; i++ ) {

               /* pos + n + ( i - ( pos + len ) ) */ 
               T::assign(new_str[n + i - len], str[i] );     
	    }

	    if ( str ) {

	       alloc_obj.deallocate(str, capacity());
	    }

            str = new_str; 
	    size_of_str = capacity() + ( n - len );
	    capacity_of_str = size_of_str;
	 }

         return *this;
      }
      /* Modifiers end here */
      
      size_type find(const_pointer s, size_type pos, size_type n) const {
      
         String<E, T, A> str(s, n);
         
         return find(str, pos);
      } 
      
      size_type find(value_type c, size_type pos = 0) const {
     
         /*
	       * TODO, sizeof of value_type should be a function
	       */
         String<E, T, A> str(1, c);
               
         return find(str, pos);
      }  
      
      size_type find(const String<E, T, A>& str, size_type pos = 0) const
      {      
         size_type ret = cc_tokenizer::String<E, T, A>::npos; 
                           
         if ( pos < size() && str.size() <= (size() - pos) ) {
         
            size_type i = pos, idx = pos, j = 0;
            
            for (; i < size();) {
            
               if ( T::eq(this->str[i], str[i - idx]) ) {
               
                  if ( j == (str.size() - 1) ) {
                  
                     ret = idx;
                     break;
                  }
                  
                  j++;
               }
               else {
               
                  i = idx;
                  idx = idx + 1;
                  j = 0;
               }
               
               i++;
            } 
         }
         
         return ret;    
      }

      size_type rfind(const String<E, T, A>& str, size_type pos = String<E, T, A>::npos) const {

         size_type ret = String<E, T, A>::npos, idx = 0;
         
         if (pos >= size()) {
            pos = size() - 1;
         }
         
         if (str.size() > 0 && pos >= (str.size() - 1)) {
            
            while ((idx=find(str, idx)) < pos) {
            
               ret = idx;
               idx = idx + str.size();
            }                                    
         }
                  
	     return ret;
      }

      size_type rfind(value_type c, size_type pos = String<E, T, A>::npos) const {

         /*
	  * TODO, sizeof value_type should be the function
	  */ 
         String<E, T, A> str(1, c); 


	 return rfind(str, pos);
      }

      typename T::int_type compare(const String<E, T, A>& ref) const {

         typename T::int_type ret = size() - ref.size();

         if ( !ret ) 
	 {
            ret = T::compare(data(), ref.data(), size());    
         }

         return ret;
      }

      /*
       *  @brief Compare substring to a string
       *  @pos Index of first character of substring
       *  @n Number of characters in substring
       *  @str String to compare against
       *  @return <0, 0, >0
      */
      typename T::int_type compare(size_type pos, size_type n, const String<E, T, A>& ref) const {

         String<E, T, A> str(*this, pos, n);

         return str.compare(ref);
      }

      void toUpper(void)
      {
         size_type i = 0;

         for (;i < size();)
         {
            str[i] = T::toUpper(str[i]);

            i++;
         }         
      }

      ~String()
      {
          cc_tokenizer::allocator<E> alloc_obj;
       
          alloc_obj.deallocate(str);
          size_of_str = 0;
          capacity_of_str = 0;
                                
          //std::cout<<"I wan in destrutor"<<std::endl;
      }   
   
   private:      
      pointer str;
      size_type size_of_str;
      size_type capacity_of_str;    
};
};

#endif
