TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

OPENCV_ROOT = $$(OPENCV_PATH)
INCLUDEPATH += $${OPENCV_ROOT}/include
LIBS += -L$${OPENCV_ROOT}/lib
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

message (Using OpenCV library in $${OPENCV_ROOT})

SOURCES += main.cpp \
    hulkinizer.cpp

HEADERS += \
    hulkinizer.h \
    nulldefs.h \
    mysqldatabase.hpp



