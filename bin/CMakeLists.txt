cmake_minimum_required(VERSION 3.10)
# set the project name
# find_package(ClassicSVfit REQUIRED)

file(GLOB SRC_FILES *.cc)
foreach(testsourcefile ${SRC_FILES})
    get_filename_component(tmpTestname ${testsourcefile} NAME)
    string( REPLACE ".cc" "" testname ${tmpTestname} )
    add_executable( ${testname} ${tmpTestname} )
    target_link_libraries(${testname} PUBLIC ClassicSVfit)
    target_link_libraries(${testname} PUBLIC m)
endforeach(testsourcefile)