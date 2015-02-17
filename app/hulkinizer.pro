TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9

INCLUDEPATH += $${PWD}/../lib
LIBS += -L$${PWD}/../build -lhulkinizer
QMAKE_RPATHDIR += $${PWD}/../build
DEPENDPATH += $${PWD}/../lib

OPENCV_ROOT = $$(OPENCV_PATH)
isEmpty(OPENCV_ROOT){
  error( You must set OPENCV_PATH variable to your opencv location)
}
INCLUDEPATH += $${OPENCV_ROOT}/include
LIBS += -L$${OPENCV_ROOT}/lib
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect

message (Using OpenCV library in $${OPENCV_ROOT})

SOURCES += main.cpp




