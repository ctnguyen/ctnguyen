Test Maxeler Interview
07/03/2015
chithanhnguyen.math@gmail.com


ALL-IN-ONE folder project used for interviewś tests. There are two way to build

1- 	Use an IDE, include all *.h *.cpp files and build

2-	Use cmake for generating. Advantage of this way is this ensure cross plateform and automatically build test.
	Need to ensure to have cmake 3.0 at least, and to have boost library (use the test framework) 
	If use cmake, open the command console and type (depending of the OS)
	For Unix  
		prompt> cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 /path/to/source/code
	For Windows
		prompt> cmake -G"Visual Studio 12" -DCMAKE_BUILD_TYPE=Debug /path/to/source/code

The program compiled from main.cpp "prog" can be execute in command line. The one argument if exist is the 
input text file containing all integer number. If no input argument, the default input file will be used.

If test build is wished, the variable ${CTN_BUILD_TEST} in cmake file has to be setted to true
And an folder named exactly "test_data" has to be created, an put all *.bin and *.asm files into it.