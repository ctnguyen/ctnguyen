#################################################
#                                               #
#   C++ PROGRAMMING                             #
#   MASTER LAURE ELIE 2013-2014                 #
#   Student Chi Thanh NGUYEN                    # 
#                                               #
#   chithanhnguyen.math@gmail.com               #
#################################################

# Test batteries is build using boost library, so if you dont have boost, tests can not be build
if(Boost_FOUND)
    add_subdirectory(unit)
    #add_subdirectory(functional)    #todo
    #add_subdirectory(integration)   #todo
else()
    message("${M2MO_HEAD_MESSAGE}You can build test only if you have boost library -- test IS NOT BUILD")
endif()
