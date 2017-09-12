#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T10:46:15
#
#-------------------------------------------------

QT       += core gui


QT       += multimedia
QT       += multimediawidgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = camera1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    heihei.qrc


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
