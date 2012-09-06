build instructions (out-of-sources)

1.create a folder side by side with GZIP, name it buildGZIP
2.by terminal, go to the folder buildGZIP and type the command

cmake ../GZIP/ -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

3.open Eclipse CDT and import the project from the folder buildGZIP
