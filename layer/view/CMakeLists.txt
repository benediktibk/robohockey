FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(LAYER_VIEW_SRC
	controller.cpp
	model.cpp
	robotdriver.cpp
	robotdriverloop.cpp
	graph.cpp
)

SET(LAYER_VIEW_TEST_SRC
	modeltest.cpp
	robotdrivertest.cpp
)

SET(LAYER_VIEW_HEADER
	controller.h
	robotdriverloop.h
	model.h
	graph.h
	modeltest.h
)

SET(LAYER_VIEW_FORMS
	view.ui
)

QT4_WRAP_CPP(LAYER_VIEW_HEADER_MOC ${LAYER_VIEW_HEADER})
QT4_WRAP_UI(LAYER_VIEW_FORMS_MOC ${LAYER_VIEW_FORMS})

add_library(layerview ${LAYER_VIEW_SRC} ${LAYER_VIEW_HEADER_MOC} ${LAYER_VIEW_FORMS_MOC})
add_library(layerviewtest ${LAYER_VIEW_TEST_SRC})
