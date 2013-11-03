set(THREADING_SRC
	threadreadloop.cpp
	thread.cpp
	mutex.cpp
	signal.cpp
	lock.cpp
)

set(THREADING_TEST_SRC
	threadtest.cpp
	mutextest.cpp
	signaltest.cpp
	locktest.cpp
)

add_library(threading ${THREADING_SRC})
add_library(threadingtest ${THREADING_TEST_SRC})
