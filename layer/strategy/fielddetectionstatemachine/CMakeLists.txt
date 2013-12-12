set(LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_SRC
	initialstate.cpp
	detectfield.cpp
	checkgoalcolor.cpp
	turnangle.cpp
	calibrationfinished.cpp
)

set(LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TEST_SRC
	initialstatetest.cpp
	detectfieldtest.cpp
	checkgoalcolortest.cpp
	turnangletest.cpp
	calibrationfinishedtest.cpp
)

add_library(layerstrategyfielddetectionstatemachine ${LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_SRC})
add_library(layerstrategyfielddetectionstatemachinetest ${LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TEST_SRC})
