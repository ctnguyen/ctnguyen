This small project is to test a "hello world" project in C++ that use
- cmake
- boost
- QuantLib

Ensure that you've fully built and installed boost and QuantLib library on your computer.

Define your environment variable 
BOOST_ROOT    : path\to\your\boost_installed_version
QUANTLIB_ROOT : path\to\your\QuantLib_installed_version

Open a command terminal and go into the folder of this sources code.
cd ..
mkdir build_QuantLibHello
cd build_QuantLibHello
cmake ..\src_QuantLibHello -G "YOUR_APPROPRIATED_CMAKE_GENERATOR"

For Visual studio 2012, use the generator by "Visual Studio 11"















