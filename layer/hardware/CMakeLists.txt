set(LAYER_HARDWARE_SRC
	robotimpl.cpp
	sonarimpl.cpp
	lidarimpl.cpp
	cameraimpl.cpp
	odometryimpl.cpp
)

set(LAYER_HARDWARE_TEST_SRC
	sonarstub.cpp
	lidarstub.cpp
	robotstub.cpp
	camerastub.cpp
	odometrystub.cpp
)
include(UsePlayerC++)
include_directories(${PLAYERCPP_INCLUDE_DIRS})
add_library(layerhardware ${LAYER_HARDWARE_SRC})
add_library(layerhardwaretest ${LAYER_HARDWARE_TEST_SRC})
