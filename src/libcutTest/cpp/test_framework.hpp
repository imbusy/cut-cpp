#ifndef TEST_FRAMEWORK_HPP
#define TEST_FRAMEWORK_HPP

#include <string>
#include <iostream>

class FailedTestException { };

template <typename T, typename U>
void test_true(T value, U expected, std::string test) {
   if(value == expected) {
      std::cout<<test<<": PASSED\n";
   } else {
      std::cout<<test<<": FAILED\n";
      std::cout<<"expected: "<<expected<<'\n';
      std::cout<<"got: "<<value<<'\n';
      throw FailedTestException();
   }
}


#endif
