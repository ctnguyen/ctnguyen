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


add_library(LMM_testlib
	"${CMAKE_SOURCE_DIR}/test/testlib/CapletTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/LiborSimulationTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/SwaptionPricingTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/TestOptimizer.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/TestPricing.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/VolatilityTests.h"
	"CapletTests.cpp"
	"LiborSimulationTests.cpp"
	"SwaptionPricingTests.cpp"
	"TestPricing.cpp"
	"Test_Instrument.cpp"
	"VolatilityTests.cpp"
)

target_link_libraries(LMM_testlib LMM_pricer LMM_ModelMCLMM LMM_instrument LMM_numeric LMM_helper)