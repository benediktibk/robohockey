set(LAYER_STRATEGY_SRC
	state.cpp
	statemachine.cpp
)

set(LAYER_STRATEGY_TEST_SRC
	statemock.cpp
	statemachinetest.cpp
)

add_library(layerstrategy ${LAYER_STRATEGY_SRC})
add_library(layerstrategytest ${LAYER_STRATEGY_TEST_SRC})
