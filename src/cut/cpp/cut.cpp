#include <iostream>

#include <libcut.hpp>

int main(int argc, char *argv[]) {
   std::cout<<"Cutting you is easy cause you're beautiful"<<std::endl;
   std::cout<<cut::bytes("hello", "world")<<std::endl;
   return 0;
}
