#ifndef FEATURES_H
#define FEATURES_H

#include <QDialog>

namespace Ui {
class Features;
}

class Features : public QDialog
{
    Q_OBJECT

public:
    explicit Features(QWidget *parent = 0);
    ~Features();

private slots:
    void receivemainwindow();

    void on_close_clicked();

    void on_red_max_sliderMoved(int position);

    void on_green_max_sliderMoved(int position);

    void on_red_min_sliderMoved(int position);

    void on_green_min_sliderMoved(int position);

    void on_blue_min_sliderMoved(int position);

    void on_blue_max_sliderMoved(int position);

    void on_h_middle_sliderMoved(int position);

    void on_h_range_sliderMoved(int position);

    void on_s_min_sliderMoved(int position);

    void on_l_min_sliderMoved(int position);

    void on_s_max_sliderMoved(int position);

    void on_l_max_sliderMoved(int position);

    void on_rgb_check_stateChanged(int arg1);

    void on_hsl_check_stateChanged(int arg1);

private:
    Ui::Features *ui;
};

#endif // FEATURES_H
