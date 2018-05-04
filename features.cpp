#include "mainwindow.h"
#include "features.h"
#include "ui_features.h"
#include <iostream>

int red_max=255;
int green_max=255;
int blue_max=255;
int red_min=0;
int green_min=0;
int blue_min=0;
bool rgb_mode=false;
bool hsl_mode=false;
int s_max=100;
int l_max=100;
int s_min=0;
int l_min=0;
int h_middle=180;
int h_range=180;

Features::Features(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Features)
{
    ui->setupUi(this);
}

Features::~Features()
{
    delete ui;
}


void Features::receivemainwindow()
{
   this->show();
}


void Features::on_close_clicked()
{
    close();
}

void Features::on_red_min_sliderMoved(int position)
{
    red_min=position;
    QString str;
    str.setNum(red_min);
    ui->label_red_min->setText(str);
}

void Features::on_green_min_sliderMoved(int position)
{
    green_min=position;
    QString str;
    str.setNum(green_min);
    ui->label_green_min->setText(str);
}

void Features::on_blue_min_sliderMoved(int position)
{
    blue_min=position;
    QString str;
    str.setNum(blue_min);
    ui->label_blue_min->setText(str);
}

void Features::on_red_max_sliderMoved(int position)
{
    red_max=position;
    QString str;
    str.setNum(red_max);
    ui->label_red_max->setText(str);
}

void Features::on_green_max_sliderMoved(int position)
{
    green_max=position;
    QString str;
    str.setNum(green_max);
    ui->label_green_max->setText(str);
}

void Features::on_blue_max_sliderMoved(int position)
{
    blue_max=position;
    QString str;
    str.setNum(blue_max);
    ui->label_blue_max->setText(str);
}

void Features::on_h_middle_sliderMoved(int position)
{
    h_middle=position;
    QString str;
    str.setNum(h_middle);
    ui->label_h_middle->setText(str);
}

void Features::on_h_range_sliderMoved(int position)
{
    h_range=position;
    QString str;
    str.setNum(h_range);
    ui->label_h_range->setText(str);
}

void Features::on_s_min_sliderMoved(int position)
{
    s_min=position;
    QString str;
    str.setNum(s_min);
    ui->label_s_min->setText(str);
}

void Features::on_l_min_sliderMoved(int position)
{
    l_min=position;
    QString str;
    str.setNum(l_min);
    ui->label_l_min->setText(str);
}

void Features::on_s_max_sliderMoved(int position)
{
    s_max=position;
    QString str;
    str.setNum(s_max);
    ui->label_s_max->setText(str);
}

void Features::on_l_max_sliderMoved(int position)
{
    l_max=position;
    QString str;
    str.setNum(l_max);
    ui->label_l_max->setText(str);
}

void Features::on_rgb_check_stateChanged(int arg1)
{
    rgb_mode=!rgb_mode;
    ui->rgb_check->setChecked(rgb_mode);
}

void Features::on_hsl_check_stateChanged(int arg1)
{
    hsl_mode=!hsl_mode;
    ui->hsl_check->setChecked(hsl_mode);
}
