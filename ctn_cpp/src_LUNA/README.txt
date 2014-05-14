This project is in C++ depend to external library
- cmake
- boost
- QuantLib
and use cmake to generate the project.

Ensure that you've fully built and installed boost and QuantLib library on your computer.

Define your ENVIRONMENT VARIABLES 
(do not forget restarting your computer in order to taking in account the environment variable setting) 
BOOST_ROOT    : path\to\your\boost_installed_version
QUANTLIB_ROOT : path\to\your\QuantLib_installed_version

Open a command terminal and go into the folder of this sources code. For Windows user, open the developer Command Prompt for VS-version

cd ..
mkdir build_Luna
cd build_Luna
cmake ..\src_Luna -G "YOUR_APPROPRIATED_CMAKE_GENERATOR"

For Visual studio 2012, use the generator by "Visual Studio 11"
cmake ..\src_Luna -G "Visual Studio 11"

After that, for windows user, need just to right-click on the LunaLMM and "set as startup Project"












