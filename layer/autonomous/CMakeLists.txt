set(LAYER_AUTONOMOUS_SRC
	robotimpl.cpp
	fieldobject.cpp
	fieldimpl.cpp
)

set(LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	fieldobjecttest.cpp
	robotmock.cpp
	fieldmock.cpp
	fieldtest.cpp
)

add_library(layerautonomous ${LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${LAYER_AUTONOMOUS_TEST_SRC})
