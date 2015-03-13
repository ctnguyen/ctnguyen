Test ADG holdings Interview
13/03/2015
chithanhnguyen.math@gmail.com

== Idea of Answer ==

Question 1 :
- First run, iterate the string
	.use a std::map that map the character to its frequency
	.use a max_frequency tracker track the max frequency
- Second run, iterate the std::map, save the element that have max_frequency 

Question 2 :
- The sum of whole set is know, then precompute it.
- iterate the array, compute the "running sum".
- the difference is the missing number

Question 3 :
- The question comes down to run the data and track max-min element
- The profit is the difference max-min.

Question 4 :
- run with odd indices, compute the "odd sum"
- run with even indices, compute the "even sum"
- compare the two sum, and choose the appropriate set
- When running the array, negative numbers will not count. If the 
  array contain all negative number, the biggest one is choosen for the result
  
  
=========================================
== building and run the project in C++ ==
Info tools :
- cmake 3.1.3
- Windows 8.1, Visual Studio Express 2013
- Ubuntu 14.04, g++4.8.2 

The project can be checked out from google code svn server

svn checkout http://chithanhnguyen.googlecode.com/svn/trunk/ctn_cpp/tempo/adgholdings chithanhnguyen-read-only 


ALL-IN-ONE folder project used for interview's tests. There are two ways to compile

1- 	Use an IDE, include all *.h *.cpp files and build. DO NOT include unittest*.cpp files.

2-	Use cmake for generating the project. Advantage of this way is this ensure cross plateform and automatically build test.
	Need to ensure to have cmake 3.0 at least, and to have boost library (use the test framework) 
	If use cmake, open the command console and type (depending of the OS)
	For Unix  
		prompt> cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 /path/to/source/code
	For Windows
		prompt> cmake -G"Visual Studio 12" -DCMAKE_BUILD_TYPE=Debug /path/to/source/code

If tests are desirable, set the variable ${CTN_BUILD_TEST} in cmake file has to be setted to "true"

After building and compiling, there will be a executable programme "prog.exe".
./prog.exe <id_of_question>
id_of_question should be 1 to 4

