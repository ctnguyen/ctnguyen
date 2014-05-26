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
#################################################

add_library(LMM_calibration
	"${CMAKE_SOURCE_DIR}/LMM/calibration/Calibration.h"
	"${CMAKE_SOURCE_DIR}/LMM/calibration/SwaptionApproxCostFunction.h"
	"${CMAKE_SOURCE_DIR}/LMM/calibration/TestCostFunction.h"
	"Calibration.cpp"
	"SwaptionApproxCostFunction.cpp"
	"TestCostFunction.cpp"
)

target_link_libraries(LMM_calibration LMM_pricer LMM_ModelMCLMM LMM_instrument LMM_numeric LMM_helper)