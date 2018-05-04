#include "mainwindow.h"
#include "features.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <QTimer>
#include <iostream>


using namespace cv;
using namespace std;

extern int red_max;
extern int green_max;
extern int blue_max;
extern int red_min;
extern int green_min;
extern int blue_min;
extern bool rgb_mode;
extern bool hsl_mode;
extern int s_max;
extern int l_max;
extern int s_min;
extern int l_min;
extern int h_middle;
extern int h_range;

int video_id;

QImage  Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_1->setScaledContents(true);   //图像自适应label的宽度
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nextFrame()
{
    capture >> frame;

    if (!frame.empty())
    {
        cvtColor( frame, frame, CV_BGR2RGB );
        if(rgb_mode==true)
        {
            color_release(frame,frame);
        }
        if(hsl_mode==true)
        {
            hsl_release(frame,frame);
        }
        img = QImage( (const unsigned char*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888 );
        ui->label_1->setPixmap(QPixmap::fromImage(img));

    }

}

void MainWindow::on_open_clicked()
{

    if (capture.isOpened())
        capture.release();     //decide if capture is already opened; if so,close it
    capture.open(video_id);           //open the default camera

    if (capture.isOpened())
    {
        capture >> frame;
        if (!frame.empty())
        {

            timer = new QTimer(this);
            timer->setInterval(1);   //set timer match with FPS
            connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            timer->start();
        }
    }

}

void MainWindow::on_close_clicked()
{
    close();
}

void MainWindow::on_begin_clicked()
{
    emit showfeatures();  //激活信号
}


int MainWindow::max_hsv(int b, int g, int r)
{
    if (b >= g&&b >= r)
        return b;
    if (g > b&&g >= r)
        return g;
    if (r > g&&r > b)
        return r;

}

int MainWindow::min_hsv(int b, int g, int r)
{
    if (b <= g&&b <= r)
        return b;
    if (g < b&&g <= r)
        return g;
    if (r < g&&r < b)
        return r;

}

void MainWindow::hsl_release(Mat& inputImage, Mat& outputImage)
{
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols*outputImage.channels();
    float max_c;
    float min_c;
    float H;
    float l;
    float s;
    float sum;

    for (int i = 0; i < rowNumber; i++)
    {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++)
        {
            if (j % 3 == 0 )
            {
                max_c = max_hsv(data[j], data[j + 1], data[j + 2]);
                min_c = min_hsv(data[j], data[j + 1], data[j + 2]);
                if (max_c != min_c)
                {
                    if (data[j + 2] == max_c)   //R
                    {
                        H = 60*(data[j + 1] - data[j]) / (max_c - min_c);
                    }
                    if (data[j + 1] == max_c)   //G
                    {
                        H = 60*(data[j] - data[j + 2]) / (max_c - min_c)+120;
                    }
                    if (data[j] == max_c)   //B
                    {
                        H = 60*(data[j + 2] - data[j + 1]) / (max_c - min_c)+240;
                    }
                    if (H < 0)
                    {
                        H = H + 360;
                    }

                    s = (max_c - min_c) / max_c*100;
                    sum = data[j] + data[j + 1] + data[j + 2];
                    l = sum / 765*100;
                    if (H>(h_middle+h_range) || H< (h_middle-h_range) || s>s_max || s<s_min || l>l_max || l<l_min)
                    {
                        data[j] = 0;
                        data[j + 1] = 0;
                        data[j + 2] = 0;
                    }
                }
                if (max_c == min_c)
                {
                    data[j] = 0;
                    data[j + 1] = 0;
                    data[j + 2] = 0;
                }

            }
        }
    }
}

void MainWindow::color_release(Mat& inputImage, Mat& outputImage)
{
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols*outputImage.channels();

    for (int i = 0; i < rowNumber; i++)
    {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j = 0; j < colNumber; j++)
        {
            if (j % 3 == 0 )
            {
                if (data[j]<red_min || data[j+1]<blue_min || data[j+2]<green_min)
                {
                    data[j] = 0;
                    data[j+1] = 0;
                    data[j+2] = 0;
                }
                if (data[j]>red_max || data[j+1]>blue_max || data[j+2]>green_max)
                {
                    data[j] = 0;
                    data[j+1] = 0;
                    data[j+2] = 0;
                }
            }
        }
    }
}


void MainWindow::on_comboBox_activated(int index)
{
    video_id=index;
}

void MainWindow::on_action_triggered()
{
    emit showhelp();
}
