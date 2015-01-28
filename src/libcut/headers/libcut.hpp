#ifndef LIBCUT_HPP
#define LIBCUT_HPP

#include <string>

namespace cut {
   std::string bytes(const std::string &line, const std::string &list, bool complement = false);
   std::string fields(const std::string &line, const std::string &list, char delimiter, bool complement = false);
}

#endif
