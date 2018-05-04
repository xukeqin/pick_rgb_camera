#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <qdebug.h>
#include <qlabel.h>
#include "QMouseEvent"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    cv::Mat frame;
    cv::Mat frame_1;
    cv::Mat frame_gray;
    cv::VideoCapture capture;
    QImage  image;
    QImage  img;
    QImage  img_1;
    QTimer *timer;
    double rate; //FPS

    cv::VideoWriter writer;   //make a video record

protected:
 //   void paintEvent(QPaintEvent * e);

private slots:
   void nextFrame();
   void on_open_clicked();
   void on_close_clicked();
   void on_begin_clicked();
   void hsl_release(Mat& inputImage, Mat& outputImage);
   void color_release(Mat& inputImage, Mat& outputImage);
   int max_hsv(int b, int g, int r);
   int min_hsv(int b, int g, int r);

   void on_comboBox_activated(int index);

   void on_action_triggered();

signals:
    void showfeatures();
    void showhelp();
};



#endif // MAINWINDOW_H
