#CMAKE INITIALIZATION
cmake_minimum_required (VERSION 2.8)

project (cmake_template) 

## Automatically finding boost library if installed on the system
## Requirement : System must have defined the environment variables
## Boost_INCLUDE_DIRS and Boost_LIBRARY_DIRS
#find_package(Boost COMPONENTS chrono program_options filesystem serialization system thread)
#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})

include_directories(include)
add_subdirectory(modules)
add_subdirectory(prog)
