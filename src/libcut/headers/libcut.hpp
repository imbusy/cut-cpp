#ifndef LIBCUT_HPP
#define LIBCUT_HPP

#include <string>

namespace cut {
   std::string bytes(std::string line, std::string list, bool complement = false);
   std::string fields(std::string line, std::string list, char delimiter, bool complement = false);
}

#endif
