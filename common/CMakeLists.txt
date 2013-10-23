set(COMMON_SRC
	compare.cpp
	point.cpp
)

set(COMMON_TEST_SRC
	comparetest.cpp
	pointtest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
