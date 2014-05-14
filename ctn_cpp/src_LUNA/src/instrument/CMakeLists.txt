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

add_library(LMM_instrument
    "${CMAKE_SOURCE_DIR}/LMM/instrument/Caplet.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/CMS.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/instrument.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/LMMTenorStructure.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/Product.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/Tarn.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/TenorType.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/VanillaSwap.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/VanillaSwaption.h"
	"Caplet.cpp"
	"CMS.cpp"
	"instrument.cpp"
	"LMMTenorStructure.cpp"
	"Tarn.cpp"
	"TenorType.cpp"
	"VanillaSwap.cpp"
	"VanillaSwaption.cpp"
)