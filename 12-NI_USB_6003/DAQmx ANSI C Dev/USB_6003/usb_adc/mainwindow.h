#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QScrollArea>
#include<qcustomplot.h>
#include<QSpinBox>
#include"serthrd.h"
#include"workthrd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    serThrd* srtThrd;
    WorkThrd* workThrd;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initWidget();
    void initThrd();

    QScrollArea* main_left_area;
    QWidget*     main_wnd_portName;
    QComboBox*   main_cbx_portName;

    QWidget*     main_wnd_connect;
    QPushButton* main_btn_connect;
    QPushButton* main_btn_disconnect;
    QWidget*     main_wnd_freq;
    QSpinBox*    main_freq_sp;
    QPushButton* main_freq_set;
    QWidget*     main_wnd_cnt;
    QSpinBox*    main_cnt_sp;
    QPushButton* main_cnt_set;
    QWidget*     main_wnd_read;
    QPushButton* main_btn_read;
    QPushButton* main_btn_stopRead;
    QWidget*     main_wnd_calc;
    QPushButton* main_btn_calculate;//计算
    QPushButton* main_btn_clear;//清空

    QScrollArea* main_right_area;
    QCustomPlot* main_wave_0;//origin data
    QCustomPlot* main_wave_1;//statical data
    QCustomPlot* main_wave_2;//DNL
    QCustomPlot* main_wave_3;//INL
    QCustomPlot* main_wave_4;//SINAD
public slots:
    void on_btn_clicked_connect();
    void on_btn_clicked_set_freq();
    void on_btn_clicked_set_cnt();
    void on_btn_clicked_disconnect();
    void on_btn_clicked_sample_stop();
    void on_btn_clicked_sample();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
