cmake_minimum_required(VERSION 3.6)
project(cpisynclib)
set(CMAKE_CXX_STANDARD 11)

# Set project directory strucuture
set(SRC_DIR src)
set(TEST_DIR tests)

# Set file config
set(SOURCE_FILES
        src/CommSocket.cpp
        src/CommString.cpp
        src/Communicant.cpp
        src/CPISync.cpp
        src/DataObject.cpp
        src/GenSync.cpp
        src/InterCPISync.cpp
        src/Logger.cpp
        src/probCPISync.cpp
        src/SyncMethod.cpp
        src/UID.cpp
        src/testFunctions.cpp
        src/murmurhash3.cpp
        src/utilstrencodings.cpp
        src/iblt.cpp
        src/IBLTSync.cpp
)

include_directories(include)
include_directories(/opt/local/include)
include_directories(${cppunit_INCLUDE_DIR})
link_directories(/opt/local/lib)

# Add libs and exes
add_library(cpisynclib ${SOURCE_FILES})
target_link_libraries(cpisynclib ntl cppunit gmp pthread)

add_executable(systemTest tests/cpi_system_test.cpp)
target_link_libraries(systemTest cpisynclib ntl cppunit gmp pthread)

#################
### Add tests ###
#################
# Following : https://cmake.org/pipermail/cmake/2007-March/013361.html

#ADD_EXECUTABLE(CommunicantTest.exe
#        ${TEST_DIR}/CommunicantTestRunner.cpp
#        ${TEST_DIR}/CommunicantTest.cpp
#)
#target_link_libraries(CommunicantTest.exe cpisynclib ntl cppunit gmp)
#ADD_TEST(CommunicantTest CommunicantTest.exe)

#ADD_EXECUTABLE(AuxiliaryTest.exe
#        ${TEST_DIR}/AuxiliaryTestRunner.cpp
#        ${TEST_DIR}/AuxiliaryTest.cpp
#)
#target_link_libraries(AuxiliaryTest.exe cpisynclib ntl cppunit gmp)
#ADD_TEST(AuxiliaryTest AuxiliaryTest.exe)

ADD_EXECUTABLE(IBLTTester.exe
        ${TEST_DIR}/IBLTTester.cpp
)
target_link_libraries(IBLTTester.exe cpisynclib ntl cppunit gmp)
ADD_TEST(IBLTTester IBLTTester.exe)
# TODO: Add all testa automagically
# FILE(GLOB UnitTests_SRCS ${TEST_DIR} "*TestRunner.cpp" )
# FOREACH(test ${UnitTests_SRCS})
#         GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
#         ADD_EXECUTABLE(UnitTester test_runner.cpp ${UnitTests_SRCS})
#         ADD_TEST(${TestName} UnitTester ${TestName})
# ENDFOREACH(test)