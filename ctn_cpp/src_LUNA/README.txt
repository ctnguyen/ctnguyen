This project is in C++ depend to external library
- boost
- QuantLib
and use cmake to generate the project from source code.

Ensure that you've fully built and installed boost, QuantLib library on your computer and cmake is installed.
Cmake can automatically find and link libraries boost, QuantLib to this project, in condition that libraries 
are installed in a 'standard' way. i.e you have the libraries contains as follows
$YOUR_BOOST_DIR\          # root     directory of boost library
.      |--------- boost   # include  directory of boost library
.      |--------- lib     # lib      directory of boost library

$YOUR_QUANLIB_DIR\    # root     directory of QuantLib library
.      |--------- ql  # include  directory of QuantLib library
.      |--------- lib # lib      directory of QuantLib library


Define your ENVIRONMENT VARIABLES (google to see how to define environment variable on your OS)
BOOST_ROOT    : path\to\your\boost_installed_version
QUANTLIB_ROOT : path\to\your\QuantLib_installed_version
(do not forget restarting your computer in order to taking in account the environment variable setting) 

Open a command terminal and go into the folder of this sources code. 
(For Windows user, open the developer Command Prompt of MVSC. 
May be you need to add 'path\to\your\cmake\binarydirectory' on you $PATH system variable. )

cd ..
mkdir build_Luna
cd build_Luna
cmake ..\src_Luna -G "YOUR_APPROPRIATED_CMAKE_GENERATOR"

For Visual Studio Express 2012, use the generator "Visual Studio 11" (for other version, google cmake generators)
cmake ..\src_Luna -G "Visual Studio 11"
Open build_Luna folder and the project is LunaLMM.sln

After that, for windows user, need just to right-click on the procLMM and "set as startup Project"












