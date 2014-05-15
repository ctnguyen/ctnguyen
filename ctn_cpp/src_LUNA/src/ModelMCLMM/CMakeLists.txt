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
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/Correlation.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/Dispersion.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/HGVolatilityFunction.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/Lmm.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/LMMTenorStructure.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/McLmm.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/McSpotLmm.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/McTerminalLmm.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/PCA.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/RobonatoAngle.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/VolatilityFunction.h"
	"${CMAKE_SOURCE_DIR}/LMM/ModelMCLMM/VolatilityGridBuilder.h"
	"Correlation.cpp"
	"Dispersion.cpp"
	"HGVolatilityFunction.cpp"
	"Lmm.cpp"
	"LMMTenorStructure.cpp"	
	"McLmm.cpp"
	"McSpotLmm.cpp"
	"McTerminalLmm.cpp"
	"PCA.cpp"
	"RobonatoAngle.cpp"
	"VolatilityFunction.cpp"
	"VolatilityGridBuilder.cpp"
)

target_link_libraries(LMM_ModelMCLMM LMM_instrument LMM_helper ${QuantLib_LIBRARY})