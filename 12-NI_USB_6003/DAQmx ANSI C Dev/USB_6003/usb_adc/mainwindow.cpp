#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    initWidget();
    initThrd();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initThrd(){
    workThrd=new WorkThrd;
    srtThrd=new serThrd;
    srtThrd->start();
    workThrd->start();
}



void MainWindow::on_btn_clicked_connect(){
    SERIAL_CONFIG* scfg=new SERIAL_CONFIG;

    scfg->portName=main_cbx_portName->currentText();
//    scfg-

    if(srtThrd!=nullptr){srtThrd->open(scfg);}
    srtThrd->sendData("hello world");
    delete scfg;
}

void MainWindow::on_btn_clicked_disconnect(){
//    if(srtThrd!=nullptr){srtThrd->disconnect();}
}



void MainWindow::on_btn_clicked_sample(){
    if(workThrd!=nullptr){
        TASK_CONFIG* tsk=new TASK_CONFIG;
        tsk->tskType=TASK_ENUM::tsk_sample;
        workThrd->addTask(tsk);
    }
}

void MainWindow::on_btn_clicked_sample_stop(){

}

void MainWindow::on_btn_clicked_set_cnt(){
     if(workThrd!=nullptr){
        TASK_CONFIG* tsk=new TASK_CONFIG;
        tsk->tskType=TASK_ENUM::tsk_set_cnt;
        workThrd->addTask(tsk);
    }
}

void MainWindow::on_btn_clicked_set_freq(){
     if(workThrd!=nullptr){
        TASK_CONFIG* tsk=new TASK_CONFIG;
        tsk->tskType=TASK_ENUM::tsk_set_freq;
        workThrd->addTask(tsk);
    }
}


//
void MainWindow::initWidget() {

//    ui->tabWidget->addTab()
    ui->tabWidget->setCurrentIndex(0);
    QHBoxLayout* layoutMain=new QHBoxLayout(ui->tab_1);
    main_left_area=new QScrollArea(ui->tab_1);
    main_right_area=new QScrollArea(ui->tab_1);
    QVBoxLayout* layoutLeft=new QVBoxLayout(main_left_area);
    main_left_area->setFixedWidth(290);


    //串口
    main_wnd_portName=new QWidget(main_left_area);
    QHBoxLayout*   layoutName=new QHBoxLayout(main_wnd_portName);
    QLabel*  main_lb_portName=new QLabel(main_wnd_portName);
    //    main_lb_portName->setText("端口号");
    main_lb_portName->setText("端口:");
    main_cbx_portName=new QComboBox(main_wnd_portName);
    layoutName->addWidget(main_lb_portName);
    layoutName->addWidget(main_cbx_portName);
    layoutLeft->addWidget(main_wnd_portName);

    main_cbx_portName->clear();
    const auto infos=QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo& info:infos){
        main_cbx_portName->addItem(info.portName());
    }



    main_wnd_freq=new QWidget(main_left_area);
    QHBoxLayout* layoutFreq=new QHBoxLayout(main_wnd_freq);
    QLabel* main_lb_freq=new QLabel(main_wnd_freq);
    main_lb_freq->setText("采样频率:");
    main_freq_sp=new QSpinBox(main_wnd_freq);
    main_freq_set=new QPushButton(main_wnd_freq);
    connect(main_freq_set,SIGNAL(clicked()),this,SLOT(on_btn_clicked_set_freq()));
    main_freq_set->setText("set");
    //main_freq_sp->setFixedWidth(100);
    main_freq_set->setFixedWidth(40);
    layoutFreq->addWidget(main_lb_freq);
    layoutFreq->addWidget(main_freq_sp);
    layoutFreq->addWidget(main_freq_set);
    layoutLeft->addWidget(main_wnd_freq);


    main_wnd_cnt=new QWidget(main_left_area);
    QHBoxLayout* layoutCnt=new QHBoxLayout(main_wnd_cnt);
    QLabel* main_lb_cnt=new QLabel(main_wnd_cnt);
    main_lb_cnt->setText("采样总数:");
    main_cnt_sp=new QSpinBox(main_wnd_cnt);
    //  main_cnt_sp->setFixedWidth(100);
    main_cnt_set=new QPushButton(main_wnd_cnt);
    connect(main_cnt_set,SIGNAL(clicked()),this,SLOT(on_btn_clicked_set_cnt()));
    main_cnt_set->setText("set");
    main_cnt_set->setFixedWidth(40);
    layoutCnt->addWidget(main_lb_cnt);
    layoutCnt->addWidget(main_cnt_sp);
    layoutCnt->addWidget(main_cnt_set);
    layoutLeft->addWidget(main_wnd_cnt);


    main_wnd_connect=new QWidget(main_left_area);
    QHBoxLayout* layoutConnect=new QHBoxLayout(main_wnd_connect);
    main_btn_connect=new QPushButton(main_left_area);
    main_btn_disconnect=new QPushButton(main_left_area);
    main_btn_connect->setText("连接");
    main_btn_disconnect->setText("断开");
    layoutConnect->addWidget(main_btn_connect);
    layoutConnect->addSpacing(20);
    layoutConnect->addWidget(main_btn_disconnect);
    layoutLeft->addWidget(main_wnd_connect);

    connect(main_btn_connect,SIGNAL(clicked()),this,SLOT(on_btn_clicked_connect()));


    main_wnd_read=new QWidget(main_left_area);
    QHBoxLayout* layoutRead=new QHBoxLayout(main_wnd_read);
    main_btn_read=new QPushButton(main_wnd_read);
    main_btn_read->setText("读取数据");
    main_btn_stopRead=new QPushButton(main_wnd_read);
    main_btn_stopRead->setText("停止读取");

    connect(main_btn_read,SIGNAL(clicked()),this,SLOT(on_btn_clicked_sample()));
    connect(main_btn_stopRead,SIGNAL(clicked()),this,SLOT(on_btn_clicked_sample_stop()));
    layoutRead->addWidget(main_btn_read);
    layoutRead->addSpacing(20);
    layoutRead->addWidget(main_btn_stopRead);

    layoutLeft->addWidget(main_wnd_read);

    main_wnd_calc=new QWidget(main_left_area);
    QHBoxLayout* layoutCalc=new QHBoxLayout(main_wnd_calc);
    main_btn_calculate=new QPushButton(main_wnd_calc);
    main_btn_clear=new QPushButton(main_wnd_calc);
    main_btn_calculate->setText("计算");
    main_btn_clear->setText("清空");
    layoutCalc->addWidget(main_btn_calculate);
    layoutCalc->addWidget(main_btn_clear);
    layoutLeft->addWidget(main_wnd_calc);


    QSpacerItem* verticalSpacer=new QSpacerItem(20,
                                                20,
                                                QSizePolicy::Minimum,
                                                QSizePolicy::MinimumExpanding);

    layoutLeft->addItem(verticalSpacer);
    QFont* font = new QFont;
    font->setPointSize(12); // 设置字体大小为 12
    main_left_area->setFont(*font);


    QVBoxLayout* layoutRight=new QVBoxLayout(main_right_area);
    main_wave_0=new QCustomPlot(main_right_area);
    main_wave_1=new QCustomPlot(main_right_area);
    main_wave_2=new QCustomPlot(main_right_area);
    main_wave_3=new QCustomPlot(main_right_area);
    main_wave_4=new QCustomPlot(main_right_area);

    main_wave_0->plotLayout()->insertRow(0); // 在顶部插入一行
    QCPTextElement *title = new QCPTextElement(main_wave_0,
                                               "原始数据",
                                               QFont("sans",
                                                     17,
                                                     QFont::Bold));
    main_wave_0->plotLayout()->addElement(0, 0, title);


    main_wave_1->plotLayout()->insertRow(0); // 在顶部插入一行
    QCPTextElement *title1 = new QCPTextElement(main_wave_1,
                                                "统计数据",
                                                QFont("sans",
                                                      17,
                                                      QFont::Bold));
    main_wave_1->plotLayout()->addElement(0, 0, title1);



    main_wave_2->plotLayout()->insertRow(0); // 在顶部插入一行
    QCPTextElement *title2 = new QCPTextElement(main_wave_2,
                                                "DNL",
                                                QFont("sans",
                                                      17,
                                                      QFont::Bold));

    main_wave_2->plotLayout()->addElement(0, 0, title2);


    main_wave_3->plotLayout()->insertRow(0); // 在顶部插入一行
    QCPTextElement *title3 = new QCPTextElement(main_wave_3,
                                                "INL",
                                                QFont("sans",
                                                      17,
                                                      QFont::Bold));
    main_wave_3->plotLayout()->addElement(0, 0, title3);


    main_wave_4->plotLayout()->insertRow(0); // 在顶部插入一行
    QCPTextElement *title4 = new QCPTextElement(main_wave_4,
                                                "SINAD",
                                                QFont("sans",
                                                      17,
                                                      QFont::Bold));

    main_wave_4->plotLayout()->addElement(0, 0, title4);


    layoutRight->addWidget(main_wave_0);
    layoutRight->addWidget(main_wave_1);
    layoutRight->addWidget(main_wave_2);
    layoutRight->addWidget(main_wave_3);
    layoutRight->addWidget(main_wave_4);


    layoutMain->addWidget(main_left_area);
    layoutMain->addWidget(main_right_area);
}

