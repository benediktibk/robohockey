set(LAYER_DATAANALYSIS_SRC
	engineimpl.cpp
	odometryimpl.cpp
	lidarimpl.cpp
	sonarimpl.cpp
	cameraimpl.cpp
	dataanalyserimpl.cpp
	lidarobject.cpp
	lidarobjects.cpp
	lidarobjectdistancecomparator.cpp
)

set(LAYER_DATAANALYSIS_TEST_SRC
	enginemock.cpp
	odometrystub.cpp
	lidarstub.cpp
	sonarmock.cpp
	camerastub.cpp
	dataanalysermock.cpp
	dataanalysertest.cpp
	cameratest.cpp
	enginetest.cpp
	lidartest.cpp
	odometrytest.cpp
	sonartest.cpp
	lidarobjecttest.cpp
	lidarobjectstest.cpp
	lidarobjectdistancecomparatortest.cpp
)

add_library(layerdataanalysis ${LAYER_DATAANALYSIS_SRC})
add_library(layerdataanalysistest ${LAYER_DATAANALYSIS_TEST_SRC})
