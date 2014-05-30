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

add_library(LMM_pricer
    "${CMAKE_SOURCE_DIR}/LMM/pricer/LmmApproxVanillaSwaptionPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/LmmCapletPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/LmmSwaptionPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/LmmTarnPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/McLmmVanillaSwapPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/McLmmVanillaSwaptionPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/McPricer.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/StaticReplicationCMS.h"
	"${CMAKE_SOURCE_DIR}/LMM/pricer/VanillaSwapPricer.h"
	"LmmApproxVanillaSwaptionPricer.cpp"
	"LmmCapletPricer.cpp"
	"LmmSwaptionPricer.cpp"
	"LmmTarnPricer.cpp"
	"McLmmVanillaSwapPricer.cpp"
	"McLmmVanillaSwaptionPricer.cpp"
	"McPricer.cpp"
	"StaticReplicationCMS.cpp"
	"VanillaSwapPricer.cpp"
)

target_link_libraries(LMM_pricer LMM_ModelMCLMM LMM_instrument LMM_helper)