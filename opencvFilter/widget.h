#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_openButton_clicked();
    QImage Mat2QImage(const cv::Mat &mat);
    void display(QImage image);
    void salt(cv::Mat &image, int n);


    void on_saltButton_clicked();
    void on_reduceButton_clicked();
    void colorReduce0(cv::Mat &image, int div);


    void on_originalButton_clicked();

    void on_reduce0Button_clicked();



    void on_redButton_clicked();

    void on_grayButton_clicked();



    //void on_horizontalSlider_actionTriggered(int action);

private:
    Ui::Widget *ui;
    cv::Mat image;
    cv::Mat originalimg; //store the original img
    QImage qimg;
    QImage imgScaled;
    cv::Mat rgb;
};

#endif // WIDGET_H
