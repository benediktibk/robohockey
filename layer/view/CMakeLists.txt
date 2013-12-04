find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(LAYER_VIEW_SRC
	controller.cpp
	model.cpp
	robotdriver.cpp
	robotdriverloop.cpp
	graph.cpp
)

set(LAYER_VIEW_TEST_SRC
	modeltest.cpp
	robotdrivertest.cpp
)

set(LAYER_VIEW_HEADER
	controller.h
	robotdriverloop.h
	model.h
	graph.h
	modeltest.h
)

set(LAYER_VIEW_FORMS
	view.ui
)

qt4_wrap_cpp(LAYER_VIEW_HEADER_MOC ${LAYER_VIEW_HEADER})
qt4_wrap_ui(LAYER_VIEW_FORMS_MOC ${LAYER_VIEW_FORMS})

add_library(layerview ${LAYER_VIEW_SRC} ${LAYER_VIEW_HEADER_MOC} ${LAYER_VIEW_FORMS_MOC})
add_library(layerviewtest ${LAYER_VIEW_TEST_SRC})
