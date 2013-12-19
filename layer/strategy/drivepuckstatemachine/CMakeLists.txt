set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC
	initialstate.cpp
	findpuckstate.cpp
	collectpuckstate.cpp
	drivetopositionstate.cpp
	checkpuckcolorstate.cpp
)

set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC
	initialstate.cpp
	findpuckstatetest.cpp
	collectpuckstatetest.cpp
	drivetopositionstatetest.cpp
	checkpuckcolorstatetest.cpp
)

add_library(layerstrategydrivepuckstatemachine ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC})
add_library(layerstrategydrivepuckstatemachinetest ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC})
