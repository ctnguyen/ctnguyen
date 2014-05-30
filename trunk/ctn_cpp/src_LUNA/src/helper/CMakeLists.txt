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
	"${CMAKE_SOURCE_DIR}/LMM/helper/LMMTenorStructure.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/MarketInfoCollector.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/MarketInfoHandler.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/EqualOperator.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/McGenerator.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/Printer.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/QMcGenerator.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/RNGenerator.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/StaticReplicationFormula.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/TenorType.h"
	"${CMAKE_SOURCE_DIR}/LMM/helper/TypeConverter.h"	
	"CombinationOperator.cpp"
    "DerivatibleFunction.cpp"
	"LMMTenorStructure.cpp"
	"MarketInfoCollector.cpp"
	"MarketInfoHandler.cpp"
	"McGenerator.cpp"
	"Printer.cpp"
	"QMcGenerator.cpp"
	"StaticReplicationFormula.cpp"
	"TenorType.cpp"
	"TypeConverter.cpp"	
)
target_link_libraries(LMM_helper LMM_numeric)