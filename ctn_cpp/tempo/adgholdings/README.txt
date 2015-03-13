Test ADG holdings Interview
13/03/2015
chithanhnguyen.math@gmail.com

Info tools :
- cmake 3.1.3
- Windows 8.1, Visual Studio Express 2013
- Ubuntu 14.04, g++4.8.2 

The project can be checked out from google code svn server

svn checkout http://chithanhnguyen.googlecode.com/svn/trunk/ctn_cpp/tempo/adgholdings chithanhnguyen-read-only 


ALL-IN-ONE folder project used for interview's tests. There are two ways to compile

1- 	Use an IDE, include all *.h *.cpp files and build. In this case, do not include unittest*.cpp files.

2-	Use cmake for generating. Advantage of this way is this ensure cross plateform and automatically build test.
	Need to ensure to have cmake 3.0 at least, and to have boost library (use the test framework) 
	If use cmake, open the command console and type (depending of the OS)
	For Unix  
		prompt> cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 /path/to/source/code
	For Windows
		prompt> cmake -G"Visual Studio 12" -DCMAKE_BUILD_TYPE=Debug /path/to/source/code

If tests are desirable, set the variable ${CTN_BUILD_TEST} in cmake file has to be setted to "true"

After building and compiling, there will be a executable programme "prog.exe".

