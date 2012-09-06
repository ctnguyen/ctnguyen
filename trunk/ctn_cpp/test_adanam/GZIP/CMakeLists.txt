cmake_minimum_required(VERSION 2.8)

if(UNIX)
set(CMAKE_GENERATOR "Unix Makefiles") 
set(CMAKE_EXTRA_GENERATOR "Eclipse CDT4" CACHE STRING  "Gerator for Eclipse CDT" FORCE)
endif()

project(test_GZIP)

configure_file("${CMAKE_SOURCE_DIR}/CaptureEcran.png" "${CMAKE_CURRENT_BINARY_DIR}/CaptureEcran.png" @ONLY)

add_executable(
	test_gzip
	adler32.c
	compress.c
	Compression.cpp
	crc32.c
	deflate.c
	deflate.h
	gzio.c
	GZipHelper.h
	infblock.c
	infblock.h
	infcodes.c
	infcodes.h
	inffast.c
	inffast.h
	inffixed.h
	inflate.c
	inftrees.c
	inftrees.h
	infutil.c
	infutil.h
	maketree.c
	trees.c
	trees.h
	uncompr.c
	zconf.h
	zlib.h
	zutil.c
	zutil.h
)
