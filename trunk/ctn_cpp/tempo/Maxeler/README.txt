Test Maxeler Interview
07/03/2015
chithanhnguyen.math@gmail.com

Info tools :
- cmake 3.1.3
- Windows 8.1, Visual Studio Express 2013
- Ubuntu 14.04, g++4.8.2 

ALL-IN-ONE folder project used for interview's tests. There are two ways to compile

1- 	Use an IDE, include all *.h *.cpp files and build. In this case, do not include unittest*.cpp files, 
	compile "task1.cpp" first time, reset the project and compile "task2.cpp" the second time. They contain
	all "main" function so can not compile together.

2-	Use cmake for generating. Advantage of this way is this ensure cross plateform and automatically build test.
	Need to ensure to have cmake 3.0 at least, and to have boost library (use the test framework) 
	If use cmake, open the command console and type (depending of the OS)
	For Unix  
		prompt> cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 /path/to/source/code
	For Windows
		prompt> cmake -G"Visual Studio 12" -DCMAKE_BUILD_TYPE=Debug /path/to/source/code

If tests are desirable, the variable ${CTN_BUILD_TEST} in cmake file has to be setted to "true"
And an folder named exactly "test_data" has to be created, an put all *.bin and *.asm files into it.

After building and compiling, there will be two executable programme "task1.exe" and "task2.exe".
These two program execute in command line, and could take one argument, which is a *.bin file.
If no argument is given to the command, a default argument will be setted : "task1.exe" take task1.bin",  "task2.exe" take task2.bin"

