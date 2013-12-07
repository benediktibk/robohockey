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
)

set(LAYER_AUTONOMOUS_TEST_SRC
	robottest.cpp
	fieldobjecttest.cpp
	robotmock.cpp
	fieldmock.cpp
	fieldtest.cpp
	borderstonetest.cpp
	borderstonedistancestest.cpp
	fielddetectortest.cpp
	routetest.cpp
	routertest.cpp
	fieldobjectdistancecomparetest.cpp
	routermock.cpp
)

add_library(layerautonomous ${LAYER_AUTONOMOUS_SRC})
add_library(layerautonomoustest ${LAYER_AUTONOMOUS_TEST_SRC})
