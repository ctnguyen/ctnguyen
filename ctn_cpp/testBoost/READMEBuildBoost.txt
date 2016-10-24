http://stackoverflow.com/questions/2629421/how-to-use-boost-in-visual-studio-2010

bootstrap.bat
b2  toolset=msvc-12.0 --build-type=complete architecture=x86 address-model=64 -s BZIP2_BINARY=libbz2 -s BZIP2_INCLUDE="E:\Libraries\bzip2" -s BZIP2_LIBPATH="E:\Libraries\bzip2" -s ZLIB_BINARY=zlib -s ZLIB_INCLUDE="E:\Libraries\zlib" -s ZLIB_LIBPATH="E:\Libraries\zlib"  --stagedir=. stage 

b2 toolset=msvc-12.0 --with-iostreams architecture=x86 address-model=64 -sBZIP2_SOURCE="E:\Libraries\bzip2-1.0.6" -sBZIP2_INCLUDE="E:\Libraries\bzip2-1.0.6"  -s ZLIB_BINARY=zlib -s ZLIB_INCLUDE="E:\Libraries\zlib" -s ZLIB_LIBPATH="E:\Libraries\zlib" --stagedir=. stage


b2 toolset=msvc-12.0 --with-iostreams --build-type=complete architecture=x86 address-model=64 -sBZIP2_SOURCE="E:\Libraries\bzip2-1.0.6" -sBZIP2_INCLUDE="E:\Libraries\bzip2-1.0.6" -sZLIB_BINARY="zlib" -sNO_ZLIB=1 --stagedir=. stage

https://svn.boost.org/trac/boost/ticket/12128
b2 variant=debug,release link=shared,static runtime-link=shared --with-date_time --with-thread threading=multi toolset=msvc-12.0 optimization=speed debug-symbols=on architecture=x86 address-model=64 
copy /Y bin.v2\libs\serialization\build\msvc-12.0\debug\optimization-speed\threading-multi\*.pdb stage\lib\
copy /Y bin.v2\libs\serialization\build\msvc-12.0\release\debug-symbols-on\threading-multi\*.pdb stage\lib\

b2 variant=debug,release link=shared,static runtime-link=shared toolset=msvc-12.0 optimization=speed debug-symbols=on architecture=x86 address-model=64 --with-serialization --stagedir=. stage
