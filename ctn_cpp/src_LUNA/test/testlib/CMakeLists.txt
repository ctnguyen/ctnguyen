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


add_library(LMM_testlib
	"${CMAKE_SOURCE_DIR}/test/testlib/CapletTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/LiborSimulationTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/SwaptionPricingTests.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/Test.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/TestCostFunction.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/TestOptimizer.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/TestPricing.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/Test_Correlation.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/Test_PCA.h"
	"${CMAKE_SOURCE_DIR}/test/testlib/VolatilityTests.h"
	"CapletTests.cpp"
	"LiborSimulationTests.cpp"
	"SwaptionPricingTests.cpp"
	"TestCostFunction.cpp"
	"TestPricing.cpp"
	"Test_BlackGreek.cpp"
	"Test_Correlation.cpp"
	"Test_DerivatibleFunction.cpp"
	"Test_Instrument.cpp"
	"Test_IntegrationMethod.cpp"
	"Test_PCA.cpp"
	"Test_VanillaSwapPricer.cpp"
	"Test_VanillaSwaptionPricer.cpp"
	"VolatilityTests.cpp"
)

target_link_libraries(LMM_testlib LMM_pricer LMM_ModelMCLMM LMM_instrument LMM_numeric LMM_helper)