I created this project as an example of how to start a cpp project using cmake

This use a very minimal knowing of cmake : 
- link to the include directories containing all .h files
- link to the modules as library
- compile the executable files.

This template also show how to link to an external library. Here, as boost is a very 
know library in the C++ community, cmake support a special tool for linking to this libray.

How does it works :
Assuming you have the source folder of a c++ project, in the present case, it is src_cmake_template
Create an other folder named build_cmake_template ( the easiest way is to create side by side with the src_folder).
Then use the shell command, go into the build_folder.

The idea we create a project "hello world" in different languages.
