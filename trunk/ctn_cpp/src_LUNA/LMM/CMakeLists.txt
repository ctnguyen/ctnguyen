#add_executable(_test_QuantLib _test_QuantLib.cpp)
## Explicite List all dependencies files
add_executable(LunaLMM 
    "${CMAKE_SOURCE_DIR}/LMM/Test.h"
    "${CMAKE_SOURCE_DIR}/LMM/Printer.h"
	"${CMAKE_SOURCE_DIR}/LMM/NumericalMethods.h"
	"Printer.cpp"
	"NumericalMethods.cpp"	
	"Test_BlackGreek.cpp"
	"Main.cpp"
)

target_link_libraries(LunaLMM ${QuantLib_LIBRAIRES})
