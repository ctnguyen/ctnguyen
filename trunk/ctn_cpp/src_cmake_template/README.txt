/************************************************
*     Mini Porject helloworld for cmake         *
*     @authors Chi Thanh NGUYEN                 *
*     contact chithanhnguyen.math@gmail.com     *
*************************************************/

I created this project as an example of how to start a cpp project using cmake. 
It can be seen as a helloworld project of cmake. This tell also a little way of organizing 
the project (include folder, *.hpp files *.cpp files) on the way that i usually work during 
my 3 years experience.

This use a very minimal knowing of cmake : 
- link to the include directories containing all .hpp files
- link to the library or binary files
- compile the executable files ensuring good linking.

In term of C++, it is a simplest project. Where there a a base abstract class named Base_Hello.
Three module herite from this base class, saying hello in different languages : English, French, Vietnamese. 
An executable file build theses three objects and say hello in three languages in the output.

How does it works :
- Of course you are supposed installed cmake on your computer
- Once downloading the sources code, you have the folder named src_cmake_template.
- Create a folder and name it build_cmake_template (the best way is creating side-by-side with the sources folder).
- Open your terminal, go into the build folder
- Execute your cmake command in the form
		cmake -G"THE_GENERATOR_YOU_WANT" -D CMAKE_BUILD_TYPE=Debug PATH_TO_THE_SOURCES_DIRECTORY
		
In my case, i used		

		cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../src_cmake_template
		
Because i want to generate the project for working with Eclipse on Unix. As i've create the build_directory 
side-by-side to the sources_directory, then the path go to source is simple.