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

add_library(LMM_instrument
	"${CMAKE_SOURCE_DIR}/LMM/Name.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/Caplet.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/CMS.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/instrument.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/Product.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/Tarn.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/VanillaSwap.h"
	"${CMAKE_SOURCE_DIR}/LMM/instrument/VanillaSwaption.h"
	"Caplet.cpp"
	"CMS.cpp"
	"instrument.cpp"
	"Tarn.cpp"
	"VanillaSwap.cpp"
	"VanillaSwaption.cpp"
)

target_link_libraries(LMM_instrument LMM_helper)