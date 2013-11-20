set(LAYER_HARDWARE_SRC
	robotimpl.cpp
	sonarimpl.cpp
	lidarimpl.cpp
	cameraimpl.cpp
	odometryimpl.cpp
	engineimpl.cpp
	lidar.cpp
	sonar.cpp
)

set(LAYER_HARDWARE_TEST_SRC
	sonarmock.cpp
	lidarmock.cpp
	robotmock.cpp
	cameramock.cpp
	odometrymock.cpp
	enginemock.cpp
)

include(UsePlayerC++)
include_directories(${PLAYERCPP_INCLUDE_DIRS})

add_library(layerhardware ${LAYER_HARDWARE_SRC})
add_library(layerhardwaretest ${LAYER_HARDWARE_TEST_SRC})
