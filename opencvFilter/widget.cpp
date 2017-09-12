#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), //打开本地文件
                                ".",tr("Image Files (*.png *.jpg *.bmp)"));//设置可以打开的本地文件格式
    qDebug()<<"filenames:"<<fileName;
    image = cv::imread(fileName.toLatin1().data());
    ui->imgfilelabel->setText(fileName);
    //两个方法去制作副本
    image.copyTo(originalimg);
   // originalimg = image.clone();        //方法一 方法二： image.copyTo(originalimg);
    qimg = Widget::Mat2QImage(image);
    display(qimg);                      //显示
    if(image.data)
    {
        ui->saltButton->setEnabled(true);
        ui->originalButton->setEnabled(true);
        ui->reduceButton->setEnabled(true);
    }
}

QImage Widget::Mat2QImage(const cv::Mat &mat)    //图片初始化
{
    QImage img;
    if(mat.channels()==3)
    {
        cvtColor(mat,rgb,CV_BGR2RGB);
        img =QImage((const unsigned char*)(rgb.data),
                    rgb.cols,rgb.rows,
                    rgb.cols*rgb.channels(),
                    QImage::Format_RGB888);
    }
    else
    {
        img =QImage((const unsigned char*)(mat.data),
                    mat.cols,mat.rows,
                    mat.cols*mat.channels(),
                    QImage::Format_RGB888);
    }
    return img;
}

void Widget::display(QImage img)    //显示图片
{
    QImage imgScaled;
    imgScaled = img.scaled(ui->imagelabel->size(),Qt::KeepAspectRatio);
    ui->imagelabel->setPixmap(QPixmap::fromImage(imgScaled));
}

void Widget::on_originalButton_clicked()    //还原图片按钮
{
    qimg = Widget::Mat2QImage(originalimg);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setEnabled(false);
    ui->imagelabel->setGraphicsEffect(effect);
    display(qimg);
}

void Widget::on_saltButton_clicked()    //雪花按钮
{

    qimg = Widget::Mat2QImage(originalimg);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setEnabled(false);
    ui->imagelabel->setGraphicsEffect(effect);
    display(qimg);//上面四行取自还原函数


    salt(image,3000);
    qimg = Widget::Mat2QImage(image);
    display(qimg);
}
void Widget::on_reduceButton_clicked()   //失真按钮
{
    colorReduce0(image,64);
    qimg = Widget::Mat2QImage(image);
    display(qimg);
}
void Widget::on_reduce0Button_clicked()  //背景失真
{
    colorReduce0(image,20);
    qimg = Widget::Mat2QImage(image);
    display(qimg);
}
void Widget::on_redButton_clicked()     //变黄按钮
{
    qimg = Widget::Mat2QImage(image);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setColor(QColor(192,192,0));
    ui->imagelabel->setGraphicsEffect(effect);
    display(qimg);

}
void Widget::on_grayButton_clicked()    //变灰按钮
{
    qimg = Widget::Mat2QImage(image);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);

    effect->setColor(QColor(0,0,0));
    ui->imagelabel->setGraphicsEffect(effect);
    display(qimg);
}

void Widget::salt(cv::Mat &image, int n)   //雪花
{

    int i,j;
    for (int k=0; k<n; k++)
    {

        i= qrand()%image.cols;
        j= qrand()%image.rows;

        if (image.channels() == 1)
        { // 灰白

            image.at<uchar>(j,i)= 255;

        }
        else if (image.channels() == 3)
        { // 彩色

            image.at<cv::Vec3b>(j,i)[0]= 255;
            image.at<cv::Vec3b>(j,i)[1]= 255;
            image.at<cv::Vec3b>(j,i)[2]= 255;
        }
    }
}









void Widget::colorReduce0(cv::Mat &image, int div)
{

      int nl= image.rows; // 总行数
      int nc= image.cols * image.channels(); // 每行元素总数

      for (int j=0; j<nl; j++)
      {

          uchar* data= image.ptr<uchar>(j);

          for (int i=0; i<nc; i++)
          {

            // 遍历每一个像素 ---------------------
                data[i]= data[i]/div*div+div/2;

            // 处理结束 ----------------

          } // 最后一行结束
      }
}














/*void Widget::on_horizontalSlider_actionTriggered(int action)     //待开发
{

    QSlider *pSlider = new QSlider(this);
    pSlider->setMinimum(200);  // 最小值
    pSlider->setMaximum(500);  // 最大值
    pSlider->setSingleStep(10);  // 步长

    qimg = Widget::Mat2QImage(image);


    display(qimg);
}*/
