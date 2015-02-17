TEMPLATE = lib
DEFINES += HULKINIZER_LIBRARY
TARGET	= hulkinizer
DESTDIR = ../build
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

OPENCV_ROOT = $$(OPENCV_PATH)
isEmpty(OPENCV_ROOT){
  error( You must set OPENCV_PATH variable to your opencv location)
}
INCLUDEPATH += $${OPENCV_ROOT}/include
LIBS += -L$${OPENCV_ROOT}/lib
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

message (Using OpenCV library in: $${OPENCV_ROOT})

HEADERS += \
    hulkinizer.h \
    mysqldatabase.hpp \
    nulldefs.h

SOURCES += \
    hulkinizer.cpp
