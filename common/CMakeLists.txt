set(COMMON_SRC
	compare.cpp
	point.cpp
	discretefunction.cpp
	rectangle.cpp
	circle.cpp
	robotposition.cpp
)

set(COMMON_TEST_SRC
	comparetest.cpp
	pointtest.cpp
	discretefunctiontest.cpp
	rectangletest.cpp
	circletest.cpp
	robotpositiontest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
