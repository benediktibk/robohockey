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
	cameraobject.cpp
	cameraobjects.cpp
)

set(LAYER_DATAANALYSIS_TEST_SRC
	enginemock.cpp
	odometrymock.cpp
	lidarmock.cpp
	sonarmock.cpp
	cameramock.cpp
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
	cameraobjecttest.cpp
	cameraobjectstest.cpp
)

add_library(layerdataanalysis ${LAYER_DATAANALYSIS_SRC})
add_library(layerdataanalysistest ${LAYER_DATAANALYSIS_TEST_SRC})
