cmake_minimum_required(VERSION 3.4)

#Configuration parameters of cmake
set(CMAKE_CXX_COMPILER g++)#requires g++ to be available on PATH
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(projekt_biblioteka)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

#Source files here
set(SOURCE_FILES

        include/Shelf.h
        include/Book.h
        include/Element.h
        include/Magazine.h
        include/RentManager.h
        include/ClientRepository.h
        include/Client.h
        include/Rent.h
        include/RentRepository.h
        include/Employee.h
        include/EmployeeRepository.h
        include/Address.h



        src/main.cpp
        src/Shelf.cpp
        src/Book.cpp
        src/Element.cpp
        src/Magazine.cpp
        src/RentManager.cpp
        src/ClientRepository.cpp
        src/Client.cpp
        src/Rent.cpp
        src/RentRepository.cpp
        src/Employee.cpp
        src/EmployeeRepository.cpp
        src/Address.cpp )
#add following files to executable file 'projekt_biblioteka'
add_executable(projekt_biblioteka ${SOURCE_FILES})

#add header files from 'include' directory of main project
target_include_directories(projekt_biblioteka PUBLIC include)

#TESTs
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

#Test source files here
set(SOURCE_TEST_FILES
        test/master.cpp
        test/ShelfTest.cpp
        test/BookTest.cpp
        test/MagazineTest.cpp
        test/ClientTest.cpp
        test/ClientRepositoryTest.cpp
        test/RentTest.cpp
        test/EmployeeTest.cpp
        test/RentRepositoryTest.cpp
        test/EmployeeRepositoryTest.cpp
        test/RentManagerTest.cpp

        src/Magazine.cpp
        src/Book.cpp
        src/Client.cpp
        src/Shelf.cpp
        src/Element.cpp
        src/RentManager.cpp
        src/ClientRepository.cpp
        src/Rent.cpp
        src/RentRepository.cpp
        src/Employee.cpp
        src/EmployeeRepository.cpp
        src/Address.cpp)

add_executable(TestProject ${SOURCE_TEST_FILES})

target_include_directories(TestProject PUBLIC include)

target_link_libraries (TestProject
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

enable_testing()

add_test(NAME Test COMMAND TestProject
        --report_level=detailed
        --log_level=all
        --color_output=yes)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
