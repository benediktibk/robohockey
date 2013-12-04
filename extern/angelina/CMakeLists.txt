find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(MOC_H
  hermes.h
  referee.h
)

set(SRC_H
  hermescodes.h
  hermes.h
  referee.h
)

set(SRC_CPP
  hermes.cpp
  referee.cpp
)

qt4_wrap_cpp(MOC_CPP ${MOC_H})

add_library(referee STATIC
	${SRC_CPP}
	${SRC_H}
	${MOC_CPP}
)

target_link_libraries(referee
	${QT_LIBRARIES}
)

