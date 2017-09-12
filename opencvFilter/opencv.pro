#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T10:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
INCLUDEPATH+=C:\OpenCV\include\opencv\
                    C:\OpenCV\include\opencv2\
                    C:\OpenCV\include
LIBS+=C:\OpenCV\lib\libopencv_calib3d249.dll.a\
        C:\OpenCV\lib\libopencv_contrib249.dll.a\
        C:\OpenCV\lib\libopencv_core249.dll.a\
        C:\OpenCV\lib\libopencv_features2d249.dll.a\
        C:\OpenCV\lib\libopencv_flann249.dll.a\
        C:\OpenCV\lib\libopencv_gpu249.dll.a\
        C:\OpenCV\lib\libopencv_highgui249.dll.a\
        C:\OpenCV\lib\libopencv_imgproc249.dll.a\
        C:\OpenCV\lib\libopencv_legacy249.dll.a\
        C:\OpenCV\lib\libopencv_ml249.dll.a\
        C:\OpenCV\lib\libopencv_objdetect249.dll.a\
        C:\OpenCV\lib\libopencv_video249.dll.a

RESOURCES += \
    pic.qrc