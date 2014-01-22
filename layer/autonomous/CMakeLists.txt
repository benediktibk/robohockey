set(LAYER_AUTONOMOUS_SRC
	robotimpl.cpp
	fieldobject.cpp
	fieldimpl.cpp
	borderstone.cpp
	borderstonedistances.cpp
	fielddetector.cpp
	routerimpl.cpp
	route.cpp
	fieldobjectdistancecompare.cpp
	routelengthcompare.cpp
	routingobstacle.cpp
	routingresult.cpp
	fielddetectionresult.cpp
	fieldobjectcolorcompare.cpp
)

set(LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	fieldobjecttest.cpp
	fieldmock.cpp
	fieldtest.cpp
	borderstonetest.cpp
	borderstonedistancestest.cpp
	fielddetectortest.cpp
	routetest.cpp
	routertest.cpp
	fieldobjectdistancecomparetest.cpp
	routermock.cpp
	routelengthcomparetest.cpp
	routingobstacletest.cpp
	routingresulttest.cpp
	fielddetectionresulttest.cpp
	fieldlivedatatest.cpp
	robotmock.cpp
	sensordataplayer.cpp
	fieldobjectcolorcomparetest.cpp
)

add_library(layerautonomous ${LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${LAYER_AUTONOMOUS_TEST_SRC})
