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


add_library(LMM_numeric
    "${CMAKE_SOURCE_DIR}/LMM/numeric/BilinearInterpolation.h"
	"${CMAKE_SOURCE_DIR}/LMM/numeric/Interpolation.h"
    "${CMAKE_SOURCE_DIR}/LMM/numeric/NumericalMethods.h"
	"BilinearInterpolation.cpp"
	"Interpolation.cpp"
	"NumericalMethods.cpp"	
)

target_link_libraries(LMM_numeric ${QuantLib_LIBRARY})