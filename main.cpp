#include "mainwindow.h"
#include "features.h"
#include "help.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <qdebug.h>
#include <qlabel.h>
using namespace cv;
using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Features f;
    help h;
    w.show(); //Ä¬ÈÏÖ÷´°¿Ú
    QObject::connect(&w,SIGNAL(showfeatures()),&f,SLOT(receivemainwindow()));
    QObject::connect(&w,SIGNAL(showhelp()),&h,SLOT(receivemainwindow()));

    waitKey(0);
    return a.exec();
}
