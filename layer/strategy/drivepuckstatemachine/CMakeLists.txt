set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC
	initialstate.cpp
	findpuckstate.cpp
	collectpuckstate.cpp
	drivepucktopositionstate.cpp
	drivetocollectpuckstate.cpp
	leavepuckstate.cpp
	drivepucktoenemythirdstate.cpp
	verifypuckstate.cpp
	findpuckturntostate.cpp
)

set(LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC
	initialstatetest.cpp
	findpuckstatetest.cpp
	collectpuckstatetest.cpp
	drivepucktopositionstatetest.cpp
	drivetocollectpuckstatetest.cpp
	leavepuckstatetest.cpp
	drivepucktoenemythirdstatetest.cpp
	verifypuckstatetest.cpp
	findpuckturntostatetest.cpp
)

add_library(layerstrategydrivepuckstatemachine ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_SRC})
add_library(layerstrategydrivepuckstatemachinetest ${LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_TEST_SRC})
