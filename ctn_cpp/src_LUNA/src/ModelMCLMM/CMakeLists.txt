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

add_library(LMM_ModelMCLMM
    "${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/LMMTenorStructure.h"
	"LMMTenorStructure.cpp"	
)