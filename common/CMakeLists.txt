set(COMMON_SRC
	deletemelater.cpp
)

set(COMMON_TEST_SRC
	deletemelatertest.cpp
)

add_library(common ${COMMON_SRC})
add_library(commontest ${COMMON_TEST_SRC})
