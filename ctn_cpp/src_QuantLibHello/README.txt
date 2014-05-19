This Tutorial is of date May 2014

This small project is to test a "hello world" project in C++ that use
- cmake
- boost
- QuantLib-1.4

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
For Eclipse CDT Linux . use the generator by "Eclipse CDT4 - Unix Makefiles"
For Mac OS Xcode       use the generator by "Xcode"

==========Installation QuantLib 1.4 Mac OS ==========
http://quantlib.org/install/macosx.shtml
By following the link of QuantLib and adapting for path similar to boost library

tar xzvf QuantLib-1.4.tar
cd QuantLib-1.4
./configure --enable-static --with-boost-include=/usr/local/opt/boost/include --with-boost-lib=/usr/local/opt/boost/lib --prefix=/usr/local/opt/QuantLib
make && sudo make install

setting QUANTLIB_ROOT environment variable by modifying /etc/launchd.conf file
setenv QUANTLIB_ROOT /usr/local/opt/QuantLib



==========Installation QuantLib 1.4 Windows ==========
Windows 7, Visual Studio Express 2012
Open the file .sln
Compile 4 times, Release, Release (Static Runtime), Debug, Debug (Static Runtime)
The result is in the lib folder, there are files as :









