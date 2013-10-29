set(LAYER_DATAANALYSIS_SRC
	engineimpl.cpp
	odometryimpl.cpp
	lidarimpl.cpp
	sonarimpl.cpp
)

set(LAYER_DATAANALYSIS_TEST_SRC
	enginestub.cpp
	odometrystub.cpp
	lidarstub.cpp
	sonarstub.cpp
)
add_library(layerdataanalysis ${LAYER_DATAANALYSIS_SRC})
add_library(layerdataanalysistest ${LAYER_DATAANALYSIS_TEST_SRC})
