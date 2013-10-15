set(LAYER_HARDWARE_SRC
	deletemelater.cpp
)

set(LAYER_HARDWARE_TEST_SRC
	deletemelatertest.cpp
)

add_library(layerhardware ${LAYER_HARDWARE_SRC})
add_library(layerhardwaretest ${LAYER_HARDWARE_TEST_SRC})
