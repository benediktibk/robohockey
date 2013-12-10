set(LAYER_STRATEGY_MAINSTATEMACHINE_SRC
	initialstate.cpp
	achievegoals.cpp
	calibrate.cpp
	pause.cpp
	hideenemypucks.cpp
	drivetofinalposition.cpp
)

set(LAYER_STRATEGY_MAINSTATEMACHINE_TEST_SRC
	initialstatetest.cpp
	calibratetest.cpp
	achievegoalstest.cpp
	hideenemypuckstest.cpp
	pausetest.cpp
	drivetofinalpositiontest.cpp
)

add_library(layerstrategymainstatemachine ${LAYER_STRATEGY_MAINSTATEMACHINE_SRC})
add_library(layerstrategymainstatemachinetest ${LAYER_STRATEGY_MAINSTATEMACHINE_TEST_SRC})
