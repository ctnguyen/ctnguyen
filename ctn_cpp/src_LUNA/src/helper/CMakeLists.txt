#################################################
#   chithanhnguyen.math@gmail.com               #
#                                               #
#   Lunalogic intership project 2014            #
#   LIBOR Market Model                          #
#   Technologies:                               #
#   - cmake                                     #
#   - boost                                     #
#   - QuantLib                                  #
#                                               #
#   14.Mai.2014                                 #
#################################################


add_library(LMM_helper
    "${CMAKE_SOURCE_DIR}/LMM/helper/CombinationOperator.h"
    "${CMAKE_SOURCE_DIR}/LMM/helper/DerivatibleFunction.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/EqualOperator.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/Printer.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/TypeConverter.h"
    "CombinationOperator.cpp"
    "DerivatibleFunction.cpp"
	"Printer.cpp"
	"TypeConverter.cpp"	
)