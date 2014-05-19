#################################################
#   chithanhnguyen.math@gmail.com               #
#################################################

# https://github.com/jppm/QuantLib-cmake/blob/master/Examples/CMakeLists.txt
# use a macro to simplify things

macro ( add_ql_example name )
    set ( ql_rname example_${name} )
    set ( ql_files ${CMAKE_CURRENT_SOURCE_DIR}/${name}/${name}.cpp )
    add_executable ( ${ql_rname} ${ql_files} )
    target_link_libraries ( ${ql_rname} ${QuantLib_LIBRARY} ${Boost_LIBRARIES})
    add_test(test_${ql_rname} ${CMAKE_CURRENT_BINARY_DIR}/${ql_rname} "--log_level=message")

    unset ( ql_rname )
    unset ( ql_files )
endmacro ()

add_ql_example ( BermudanSwaption )
add_ql_example ( Bonds )
add_ql_example ( CallableBonds )
add_ql_example ( CDS )
add_ql_example ( ConvertibleBonds )
add_ql_example ( DiscreteHedging )
add_ql_example ( EquityOption )
add_ql_example ( FittedBondCurve )
add_ql_example ( FRA )
add_ql_example ( MarketModels )
add_ql_example ( Replication )
add_ql_example ( Repo )
add_ql_example ( Swap )