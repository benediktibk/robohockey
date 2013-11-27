set(COMMON_SRC
	compare.cpp
	point.cpp
	discretefunction.cpp
	rectangle.cpp
	circle.cpp
	watch.cpp
	robotposition.cpp
	angle.cpp
	path.cpp
)

set(COMMON_TEST_SRC
	comparetest.cpp
	pointtest.cpp
	discretefunctiontest.cpp
	rectangletest.cpp
	circletest.cpp
	watchtest.cpp
	robotpositiontest.cpp
	angletest.cpp
	pathtest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
