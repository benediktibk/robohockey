set(LAYER_AUTONOMOUS_SRC
	robotimpl.cpp
)

set(LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
)

add_library(layerautonomous ${LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${LAYER_AUTONOMOUS_TEST_SRC})
