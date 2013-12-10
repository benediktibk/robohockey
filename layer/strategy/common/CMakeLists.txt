set(LAYER_STRATEGY_COMMON_SRC
	state.cpp
	statemachine.cpp
)

set(LAYER_STRATEGY_COMMON_TEST_SRC
	statemock.cpp
	statemachinetest.cpp
)

add_library(layerstrategycommon ${LAYER_STRATEGY_COMMON_SRC})
add_library(layerstrategycommontest ${LAYER_STRATEGY_COMMON_TEST_SRC})
