Pratical works of Master Modelisation Aleatoire (Laure Elie) 2013-2014

Prof : SVEN DE Felice
Info : Go to ENT of Paris Diderot, search C++

- For working or testing this project, you'll need to have
- cmake
- boost
- an C++ IDE (Visual Studio C++, Xcode, Eclilpse CDT, or something else ...)


==  Instruction building project with cmake : ==

- Assuming user have downloaded all the sources code contained in a folder naming "src_m2mo"
- There are a file "default-config.cmake" in the root folder, DO NOT modify it
- Copy "default-config.cmake" to a file named exactly "user-config.cmake", modify this last adapting to your choice
- Create beside it a folder named "build_m2mo". Go in to the folder "build_m2mo" and execute the command
- (For Mac OS X user, use cmake GUI and choose simply the right sources directory and build directory)

prompt$> cmake ../src_m2mo      # build project
prompt$> make -j2               # build programmes
prompt$> ctest --extra-verbose  # if you have build with test

-   For windows or Mac OS X user, who don't use command line for running test,
- one should set the environment variable CTEST_OUTPUT_ON_FAILURE=1 before running test
- There will be a project named RUN Test on the projects tree, run it for testss

