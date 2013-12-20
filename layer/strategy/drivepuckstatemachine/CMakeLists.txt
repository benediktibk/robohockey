set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC
	initialstate.cpp
	findpuckstate.cpp
	collectpuckstate.cpp
	drivetopositionstate.cpp
	drivetocollectpuckstate.cpp
	leavepuckstate.cpp
)

set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC
	initialstatetest.cpp
	findpuckstatetest.cpp
	collectpuckstatetest.cpp
	drivetopositionstatetest.cpp
	drivetocollectpuckstatetest.cpp
	leavepuckstatetest.cpp
)

add_library(layerstrategydrivepuckstatemachine ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC})
add_library(layerstrategydrivepuckstatemachinetest ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC})
