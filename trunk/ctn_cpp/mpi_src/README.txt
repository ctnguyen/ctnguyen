Assuming user has installed boost.mpi 
This project test if everything works well together

- cmake
- mpi
- boost.mpi

Run cmake, then compile and test the project by

mpiexec -n 2 ./mpi_test

====================================================
=== Build and Install Complete Boost on Ubuntu  ====
- Download Boost Source code and extract

cd $HOME/Downloads/boost_1_54_0
chmod -R u+x *
sudo apt-get install python-dev
sh bootstrap.sh
./b2                                                        # build boost library
sudo apt-get install mpich2 libmpich2-3 libmpich2-dev       # install mpi dev library
echo 'using mpi ;'>>$HOME/user-config.jam                   # config boost using boost mpi
sudo mkdir /home/common/boost_yourversion
sudo ./b2 --with-mpi --prefix=/home/common/boost_yourversion install  # install boost
cd /home/common/boost_your_version/
sudo mkdir bin                                              # create directory for boost dynamic library 
sudo mv lib/*.so lib/*.so.* bin/                            # move all dynamic library to bin directory
- for some reason, the boost install does not corrrectly move all the build files
- you can move manually all *.a files to lib folder and *.so.* to bin folder
mv $HOME/Downloads/boost_1_54_0/stage/lib/*.a /home/common/boost_1_54_0/lib
mv $HOME/Downloads/boost_1_54_0/stage/lib/*.so /home/common/boost_1_54_0/bin
mv $HOME/Downloads/boost_1_54_0/stage/lib/*.so.* /home/common/boost_1_54_0/bin

- Add "export BOOST_ROOT=/home/common/boost_yourversion" to your .profile file
- Add "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/common/boost_yourversion/bin" to your .profile file



Note that the standard tree archiv of boost is
_Boost_Root
_Boost_Root/include
_Boost_Root/include/boost (this folder contain all .h files)
_Boost_Root/lib           (this folder contain all static  lib : *.a  or *.lib)
_Boost_Root/bin           (this folder contain all dynamic lib : *.so or *.dll)

-Boost_Root ___            (BOOST_ROOT)
__________include/ ___
____________________boost/ (.h files)
_____________lib/          (static lib)
_____________bin/

User has to set 2 environment variables 
BOOST_ROOT=/path/to/boost_root_folder
PATH+=/path/to/boost_root-folder/bin
The first variable help cmake to automatically find boost
The second need when executing a program building with dynamic linking



