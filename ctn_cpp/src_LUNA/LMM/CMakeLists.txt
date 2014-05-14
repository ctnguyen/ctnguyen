#add_executable(_test_QuantLib _test_QuantLib.cpp)
## Explicite List all dependencies files
add_executable(LunaLMM 
    "${CMAKE_SOURCE_DIR}/LMM/helper/Printer.h"
	"${CMAKE_SOURCE_DIR}/src/helper/Printer.cpp"
	"${CMAKE_SOURCE_DIR}/LMM/numeric/NumericalMethods.h"
	"${CMAKE_SOURCE_DIR}/src/numeric/NumericalMethods.cpp"	
    "${CMAKE_SOURCE_DIR}/LMM/Test.h"
	"Test_BlackGreek.cpp"
	"Main.cpp"
)

target_link_libraries(LunaLMM ${QuantLib_LIBRARY})
