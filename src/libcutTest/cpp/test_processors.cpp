#include <iostream>
#include <string>

#include <libcut.hpp>

#include "test_framework.hpp"

int main(int, char* []) {
   try {
      testEqual(cut::bytes("Hello, World", "2"), "e", "single byte");
      testEqual(cut::bytes("Hello, World", "2,5"), "eo", "list of bytes");
      testEqual(cut::bytes("Hello, World", "5,2"), "eo", "list of bytes reversed");
      testEqual(cut::bytes("Hello, World", "-3"), "Hel", "list of bytes from start");
      testEqual(cut::bytes("Hello, World", "3-"), "llo, World", "list of bytes to end");
      testEqual(cut::bytes("Hello, World", "3-5"), "llo", "single range of bytes");
      testEqual(cut::bytes("Hello, World", "3-5,4-6"), "llo,", "two ranges of bytes");
      testEqual(cut::bytes("Hello, World", "2", true), "Hllo, World", "single byte complement");
      testEqual(cut::bytes("Hello, World", "2,5", true), "Hll, World", "list of bytes complement");
      testEqual(cut::bytes("Hello, World", "3-5", true), "He, World", "single range of bytes complement");
      testEqual(cut::bytes("Hello, World", "3-5,4-6", true), "He World", "two ranges of bytes complement");
      
      testEqual(cut::fields("this,is,amazing,isn't it?", "1", ','), "this", "single field");
      testEqual(cut::fields("this,is,amazing,isn't it?", "1,2", ','), "this,is", "list of fields");
      testEqual(cut::fields("this,is,amazing,isn't it?", "2,1", ','), "this,is", "list of fields reversed");
      testEqual(cut::fields("this,is,amazing,isn't it?", "2-4", ','), "is,amazing,isn't it?", "single range of fields");
      testEqual(cut::fields("this,is,amazing,isn't it?", "1-2,2-4", ','), "this,is,amazing,isn't it?", "two ranges of fields");
      testEqual(cut::fields("this,is,amazing,isn't it?", "1", ',', true), "is,amazing,isn't it?", "single field complement");
      testEqual(cut::fields("this,is,amazing,isn't it?", "1,2", ',', true), "amazing,isn't it?", "list of fields complement");
      testEqual(cut::fields("this,is,amazing,isn't it?", "2-4", ',', true), "this", "single range of fields complement");
      testEqual(cut::fields("this,is,amazing,isn't it?", "1-2,2-4", ',', true), "", "two ranges of fields complement");
   } catch(FailedTestException e) {
      std::cout<<"Stopping testing with failure."<<std::endl;
      return -1;
   }
   
   std::cout<<"All tests passed succesfully!"<<std::endl;
   return 0;
}
