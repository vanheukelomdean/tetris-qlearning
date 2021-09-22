project (unit_test)

find_package(SDL2 REQUIRED)
find_package (Boost COMPONENTS unit_test_framework REQUIRED)

add_library(testing_modules
INTERFACE
    ${CMAKE_SOURCE_DIR}/src/Utils.h
)

add_executable (unit_test UtilsTest.cpp)

target_include_directories(${PROJECT_NAME} 
PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PRIVATE
    testing_modules
PUBLIC 
    Boost::boost
    Boost::unit_test_framework
    ${SDL2_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME} 
PRIVATE
    BOOST_TEST_DYN_LINK
)

add_test (test_all unit_tests)