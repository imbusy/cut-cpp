#include <iostream>
#include <fstream>
#include <string>

#include <libcut.hpp>

int main(int argc, char *argv[]) {
   // arguments to parse out
   bool bytes = false;
   bool fields = false;
   bool complement = false;
   std::string list = "";
   char delimiter = '\t';
   std::string input = "";
   
   // parse all the arguments
   for(int param = 1; param < argc; param++) {
      auto arg = std::string(argv[param]);
      std::cout<<arg<<' '<<param<<' '<<argc<<'\n';
      if(arg == "-b" && param+1 < argc) {
         bytes = true;
         list = std::string(argv[param+1]);
         param++;
      } else if(arg == "-f" && param+1 < argc) {
         fields = true;
         list = std::string(argv[param+1]);
         param++;
      } else if(arg == "--complement") {
         complement = true;
      } else if(arg == "-d" && param+1 < argc) {
         delimiter = argv[param+1][0];
         param++;
      } else {
         input = arg;
         break;
      }
   }
   if((bytes && fields) || (!bytes && !fields)) {
      std::cout<<"Either bytes or fields should be selected."<<std::endl;
      return -1;
   }
   
   // process the input file
   std::ifstream file(input, std::ifstream::in);
   std::string line;
   while(getline(file, line)) {
      if(bytes) {
         std::cout<<cut::bytes(line, list, complement)<<std::endl;
      } else if(fields) {
         std::cout<<cut::fields(line, list, delimiter, complement)<<std::endl;
      }
   }
   
   return 0;
}
