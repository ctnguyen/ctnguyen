Pratical works of Master Modelisation Aleatoire (Laure Elie) 2013-2014

Prof : SVEN DE Felice
Info : Go to ENT of Paris Diderot, search C++

Instruction building project with cmake :

- Assuming user have downloaded all the sources code contained in a folder naming "src_m2mo"
- There are a file "config.cmake" in the root folder, DO NOT modify it
- Copy "config.cmake" to a file named exactly "user-config.cmake", modify this last adapting to your choice
- Create beside it a folder named "build_m2mo". Go in to the folder "build_m2mo" and execute the command

prompt$> cmake ../src_m2mo  # build project
prompt$> make -j2           # build programmes
prompt$> make test          # if you have build with test
