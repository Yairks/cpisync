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
        tests/CommDummy.cpp
)

include_directories(include)
include_directories(/opt/local/include)
include_directories(${cppunit_INCLUDE_DIR})
link_directories(/opt/local/lib)

# Add libs and exes
add_library(cpisynclib ${SOURCE_FILES})
target_link_libraries(cpisynclib ntl cppunit gmp pthread)

# add_executable(systemTest tests/cpi_system_test.cpp)
# target_link_libraries(systemTest cpisynclib ntl cppunit gmp pthread)

#################
### Add tests ###
#################
# Following : https://cmake.org/pipermail/cmake/2007-March/013361.html

ADD_EXECUTABLE(LoggerTest.exe
        ${TEST_DIR}/LoggerTestRunner.cpp
        ${TEST_DIR}/LoggerTest.cpp
)
target_link_libraries(LoggerTest.exe cpisynclib ntl cppunit gmp)
ADD_TEST(LoggerTest LoggerTest.exe)

ADD_EXECUTABLE(DataObjectTest.exe
        ${TEST_DIR}/DataObjectTestRunner.cpp
        ${TEST_DIR}/DataObjectTest.cpp
)
target_link_libraries(DataObjectTest.exe cpisynclib ntl cppunit gmp)
ADD_TEST(DataObjectTest DataObjectTest.exe)

ADD_EXECUTABLE(CommunicantTest.exe
        ${TEST_DIR}/CommunicantTestRunner.cpp
        ${TEST_DIR}/CommunicantTest.cpp
)
target_link_libraries(CommunicantTest.exe cpisynclib ntl cppunit gmp)
ADD_TEST(CommunicantTest CommunicantTest.exe)

ADD_EXECUTABLE(CommStringTest.exe
        ${TEST_DIR}/CommStringTestRunner.cpp
        ${TEST_DIR}/CommStringTest.cpp
)
target_link_libraries(CommStringTest.exe cpisynclib ntl cppunit gmp)
ADD_TEST(CommStringTest CommStringTest.exe)

ADD_EXECUTABLE(CommSocketTest.exe
        ${TEST_DIR}/CommSocketTestRunner.cpp
        ${TEST_DIR}/CommSocketTest.cpp
)
target_link_libraries(CommSocketTest.exe cpisynclib ntl cppunit gmp)
ADD_TEST(CommSocketTest CommSocketTest.exe)

# TODO: Add all testa automagically
# FILE(GLOB UnitTests_SRCS ${TEST_DIR} "*TestRunner.cpp" )
# FOREACH(test ${UnitTests_SRCS})
#         GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
#         ADD_EXECUTABLE(UnitTester test_runner.cpp ${UnitTests_SRCS})
#         ADD_TEST(${TestName} UnitTester ${TestName})
# ENDFOREACH(test)