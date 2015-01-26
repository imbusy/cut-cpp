# cut-cpp

Linux command-line tool "cut" implementation in C++. Supports
only the -f, -d, -b and --complement arguments. More about
cut tool: [linux.die.net/man/1/cut](http://linux.die.net/man/1/cut)

The source is split into a library, called _libcut_, that provides
string processing functionality and an executable, called _cut_,
that parses out the parameters and runs the input through the line
processors.

Unit testing is done on the library part only.
