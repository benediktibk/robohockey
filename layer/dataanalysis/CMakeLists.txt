set(LAYER_DATAANALYSIS_SRC
	engineimpl.cpp
)

set(LAYER_DATAANALYSIS_TEST_SRC
	enginestub.cpp
)
add_library(layerdataanalysis ${LAYER_DATAANALYSIS_SRC})
add_library(layerdataanalysistest ${LAYER_DATAANALYSIS_TEST_SRC})
