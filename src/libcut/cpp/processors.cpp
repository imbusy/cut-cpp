#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <climits>
#include <cstdlib>

#include "libcut.hpp"

using namespace std;

// split a string into multiple strings using a delimiter character
vector<string> split(const string &input, char delim) {
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
Ranges getRanges(const string &list) {
   Ranges result;
   
   for(auto range : split(list, ',')) {
      if(range.size() > 0) {
         auto digits = split(range, '-');
         if (digits.size() == 1) {
            // N
            result.push_back(make_pair<int, int>(atoi(digits[0].c_str()), atoi(digits[0].c_str())));
         } else if(digits.size() == 2 && digits[0] == "") {
            // -M
            result.push_back(make_pair<int, int>(1, atoi(digits[1].c_str())));
         } else if (digits.size() == 2 && digits[1] == "") {
            // N-
            result.push_back(make_pair<int, int>(atoi(digits[0].c_str()), INT_MAX));
         } else if(digits.size() == 2) {
            // N-M
            result.push_back(make_pair<int, int>(atoi(digits[0].c_str()), atoi(digits[1].c_str())));
         } else {
            // raise error
         }
         if(result.back().first == 0 || result.back().second == 0) {
            // raise error
            // some characters were non-numeric
         }
      }
   }
   return result;
}

// create the mask to use when selecting characters/fields
unique_ptr<bool []> getMask(const string &list, int size) {
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

string cut::bytes(const string &line, const string &list, bool complement) {
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

string cut::fields(const string &line, const string &list, char delimiter, bool complement) {
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
