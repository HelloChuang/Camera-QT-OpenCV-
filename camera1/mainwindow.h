#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>

#include<QTimer>

//---------------------
#include <QWidget>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class MainWindow;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void TimeSlot();
    void captureImage();
    void displayImage(int,QImage);
    void saveImage();

    void on_photocut_clicked();

    void on_shoot_clicked();

    void on_stopShoot_clicked();

    void on_grayButton_clicked();

    void on_redButton_clicked();
    //------------------
    QImage Mat2QImage(const cv::Mat &mat);
    void display(QImage image);
    void colorReduce0(cv::Mat &image, int div);

    void on_reduce0Button_clicked();
    void on_originalButton_clicked();
void on_openButton_clicked();
private:
    Ui::MainWindow *ui;
    int startTemp;
    int endTemp;
    int countTemp;
    QTimer *msTimer;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;
    //--------------------
    cv::Mat image;
    cv::Mat originalimg; //store the original img
    QImage qimg;
    QImage imgScaled;
    cv::Mat rgb;
};

#endif // MAINWINDOW_H
