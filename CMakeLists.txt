# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
cmake_minimum_required(VERSION 3.10)
# set the project name
project(ClassicSVfit VERSION 1.0 DESCRIPTION "ClassicSVfit shared lib")
# Sets up global settings
# include("${ROOT_USE_FILE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
find_package(ROOT REQUIRED MathCore Hist Physics Graf Tree)
find_package(Boost REQUIRED)

add_library(${PROJECT_NAME} SHARED
    src/ClassicSVfit.cc
    src/ClassicSVfitBase.cc
    src/ClassicSVfitIntegrand.cc
    src/ClassicSVfitIntegrandBase.cc
    src/FittedTauLepton.cc
    src/MeasuredTauLepton.cc
    src/SVfitIntegratorMarkovChain.cc
    src/svFitAuxFunctions.cc
    src/svFitHistogramAdapter.cc
)

target_link_libraries(${PROJECT_NAME} PUBLIC ROOT::Graf ROOT::Tree ROOT::Physics)
# for using __sincos from glibc
target_link_libraries(${PROJECT_NAME} PUBLIC m)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER interface/mylib.h)

target_include_directories(${PROJECT_NAME} PRIVATE interface)
target_include_directories(${PROJECT_NAME} PRIVATE src)

include(GNUInstallDirs)

# install rules
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
