set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_library(CPPUNIT_LIBRARY cppunit)
find_library(PLAYER_LIBRARY playerc++)

set(LIBRARIES
	layerhardware
	common
)

set(LIBRARIES_TEST
	commontest
	layerhardwaretest
)

add_executable(robot main.cpp)
add_executable(testrunner testregistration.cpp testrunner.cpp)
target_link_libraries(robot ${LIBRARIES} ${PLAYER_LIBRARY})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES} ${CPPUNIT_LIBRARY} ${PLAYER_LIBRARY})
