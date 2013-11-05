SET(robohockey_SOURCES viewer.cpp)
SET(robohockey_HEADERS viewer.h)
SET(robohockey_FORMS viwer.ui)

QT4_WRAP_CPP(robohockey_HEADERS_MOC ${robohockey_HEADERS})
QT4_WRAP_UI(robohockey_FORMS_HEADERS ${robohockey_FORMS})
