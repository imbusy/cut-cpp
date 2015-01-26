#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include "libcut.hpp"

using namespace std;

// split a string into multiple strings using a delimiter character
vector<string> split(string input, char delim) {
   vector<string> result;
   int start = 0;
   int end = input.find(delim, start);
   while(end != string::npos) {
      result.push_back(input.substr(start, end-start));
      start = end + 1;
      end = input.find(delim, start);
   }
   result.push_back(input.substr(start));
   return result;
}

typedef vector<pair<int, int>> Ranges;

// get a list of ranges to go through
Ranges getRanges(string list) {
   Ranges result;
   int rangeStart = -1, rangeEnd = -1;
   
   for(auto range : split(list, ',')) {
      auto digits = split(range, '-');
      if(digits.size() == 1) {
         result.push_back(make_pair<int, int>(atoi(digits[0].c_str()), atoi(digits[0].c_str())));
      } else if(digits.size() == 2) {
         result.push_back(make_pair<int, int>(atoi(digits[0].c_str()), atoi(digits[1].c_str())));
      } else {
         // raise error
      }
      if(result.back().first == 0 || result.back().second == 0) {
         // raise error
         // some characters were non-numeric
      }
   }
   return result;
}

// create the mask to use when selecting characters/fields
unique_ptr<bool []> getMask(string list, int size) {
   auto mask = unique_ptr<bool []>(new bool[size]);
   fill(mask.get(), mask.get()+size, false);
   
   for(auto val : getRanges(list)) {
      for(int cur = val.first-1; cur < val.second; cur++) {
         if(cur >= size) break;
         mask[cur] = true;
      }
   }
   
   return mask;
}

string cut::bytes(string line, string list, bool complement) {
   auto mask = getMask(list, line.size());
   string result = "";
   
   // merge selected characters back
   for(int i = 0; i < line.size(); i++) {
      if((mask[i] && !complement) || (!mask[i] && complement)) {
         result += line[i];
      }
   }
   
   return result;
}

string cut::fields(string line, string list, char delimiter, bool complement) {
   auto fields = split(line, delimiter);
   auto mask = getMask(list, fields.size());
   string result = "";
   
   // merge selected fields back
   for(int i = 0; i < fields.size(); i++) {
      if((mask[i] && !complement) || (!mask[i] && complement)) {
         if(result.length() > 0) {
            result += delimiter;
         }
         result += fields[i];
      }
   }
   
   return result;
}
