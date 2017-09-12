#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsColorizeEffect>

#include <QWidget>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //---------------------------------------------------  计时器
    countTemp=0;
    startTemp=0;
    endTemp=0;

    msTimer = new QTimer(this);  //this说明是当前类对象的定时器
    //把信号与槽进行连接
    connect(msTimer,SIGNAL(timeout()),this,SLOT(TimeSlot()));
//--------------------------------------------------------------------------照相机
    camera = new QCamera(this);
    viewfinder = new QCameraViewfinder(this);
    imageCapture = new QCameraImageCapture(camera);

    ui->ImageView->addWidget(viewfinder);
    ui->ImageCapture->setScaledContents(true);

    camera->setViewfinder(viewfinder);
    camera->start();

    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(displayImage(int,QImage)));
    connect(ui->reduce0Button, SIGNAL(clicked()), this, SLOT(on_openButton_clicked()));


    connect(ui->buttonCapture, SIGNAL(clicked()), this, SLOT(captureImage()));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(ui->buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    //--------------------


}

MainWindow::~MainWindow()
{
        msTimer->stop();//停止计时器
        delete msTimer;//释放计时器内存
        delete ui;
}



void MainWindow::captureImage()      //singal
{
    ui->statusBar->showMessage(tr("capturing..."), 1000);
    imageCapture->capture();


}



void MainWindow::displayImage(int , QImage image)   //slot
{
    ui->ImageCapture->setPixmap(QPixmap::fromImage(image));
    ui->statusBar->showMessage(tr("完成拍摄"), 5000);

}



void MainWindow::saveImage()           //保存
{
    QString fileName=QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));
    if(fileName.isEmpty())
    {
        ui->statusBar->showMessage(tr("save cancel"), 5000);
        return;
    }
    const QPixmap* pixmap=ui->ImageCapture->pixmap();
    if(pixmap)
    {
        pixmap->save(fileName);
        ui->statusBar->showMessage(tr("save OK"), 5000);
    }
}



void MainWindow::on_photocut_clicked()        //截图并自动保存
{
    QPixmap pixmap;
    QDir *list = new QDir;
    bool exist = list->exists("D:\\photos");
    if(!exist)
        list->mkdir("D:\\photos");

    QDateTime time = QDateTime::currentDateTime();
    QString str = QString("D:\\photos\\"+time.toString("yyyyMMddhhmmss")+".png");
    QFile file;
    file.open(QIODevice::WriteOnly);
    if(!file.isOpen())
    {
        QMessageBox::information(this,tr("提示"),tr("成功，已保存到相册"));
        pixmap = QPixmap::grabWindow(ui->label->winId(),0,0,641,481);
        pixmap.save(str);
    }
    else
    {
        QMessageBox::warning(this,tr("错误"),tr("失败"));
        file.close();
    }
}



//计时器自动拍照保存
 void MainWindow::TimeSlot()
 {

     //------------------------------------------------------------------------------自动拍照
     QImage image;
     imageCapture->capture();
     ui->ImageCapture->setPixmap(QPixmap::fromImage(image));
     ui->statusBar->showMessage(tr("完成拍摄"), 5000);


    //------------------------------------------自动保存到相册
    // const QPixmap* pixmap;
     QDir *list = new QDir;
     bool exist = list->exists("D:\\photos2");
     if(!exist)
         list->mkdir("D:\\photos2");

     QDateTime time = QDateTime::currentDateTime();

     QString str = QString("D:\\photos\\"+time.toString("yyyyMMddhhmmss")+".png");

      //QString str=QFileDialog::getSaveFileName(this, tr("save file"), QDir::homePath(), tr("jpegfile(*.jpg)"));

     qDebug() << "aaaaaaaaaaaaa";
    // const QPixmap* pixmap=ui->ImageCapture->pixmap();
     QFile file("D:\\photos2");

     file.open(QIODevice::WriteOnly);
     if(!file.isOpen())
     {

      //   pixmap = ui->ImageCapture->pixmap();
        image.save(str);
     }
     else
     {
         QMessageBox::warning(this,tr("错误"),tr("保存失败"));
         file.close();
     }
 }



 //连拍按钮
void MainWindow::on_shoot_clicked()
{
    ui->statusBar->showMessage(tr("capturing..."), 1000);
    msTimer->start(500);  //10ms
}



//结束连拍
void MainWindow::on_stopShoot_clicked()
{
     msTimer->stop();
     QMessageBox::information(this,tr("提示"),tr("成功，已保存到相册"));
}
//------------------------------------------------------------------------------------------滤镜
void MainWindow::on_grayButton_clicked()//灰白
{
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setColor(QColor(0,0,0));
    ui->ImageCapture->setGraphicsEffect(effect);
}

void MainWindow::on_redButton_clicked()//暖色
{
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);

    effect->setColor(QColor(180,25,0));
    ui->ImageCapture->setGraphicsEffect(effect);
}
QImage MainWindow::Mat2QImage(const cv::Mat &mat)    //图片初始化
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

void MainWindow::display(QImage img)    //显示图片
{
    QImage imgScaled;
    imgScaled = img.scaled(ui->ImageCapture->size(),Qt::KeepAspectRatio);
    ui->ImageCapture->setPixmap(QPixmap::fromImage(imgScaled));
}

void MainWindow::on_originalButton_clicked()    //还原图片按钮
{
    qimg = MainWindow::Mat2QImage(originalimg);
    QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
    effect->setEnabled(false);
    ui->ImageCapture->setGraphicsEffect(effect);
    display(qimg);
}
void MainWindow::on_reduce0Button_clicked()  //背景失真
{
    colorReduce0(image,20);



    qimg = MainWindow::Mat2QImage(image);
    display(qimg);
}
void MainWindow::colorReduce0(cv::Mat &image, int div)
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
void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), //打开本地文件
                                ".",tr("Image Files (*.png *.jpg *.bmp)"));//设置可以打开的本地文件格式
    qDebug()<<"filenames:"<<fileName;
    image = cv::imread(fileName.toLatin1().data());

    //两个方法去制作副本
    image.copyTo(originalimg);
   // originalimg = image.clone();        //方法一 方法二： image.copyTo(originalimg);
    qimg = MainWindow::Mat2QImage(image);
    display(qimg);                      //显示

}


