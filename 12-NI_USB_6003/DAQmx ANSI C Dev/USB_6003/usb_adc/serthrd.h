#ifndef SERTHRD_H
#define SERTHRD_H

#include <QThread>
#include"config.h"
#include<QtSerialPort/QSerialPort>

class serThrd : public QThread
{
    Q_OBJECT

private:
    QQueue<char> msgQ;
    QSerialPort* serial=nullptr;
public:
    explicit serThrd(QObject *parent = nullptr);
    void run()override;
    //    void init();
    //    void connect(SERIAL_CONFIG* cfg);
    void disconnect();
    bool open(SERIAL_CONFIG* cfg);
    void sendData(QByteArray data);
    bool process_sample_start(int pack_length,char chksum);
    bool process_sample_finish(int pack_length,char chksum);
    bool process_adc(int pack_length,char chksum);
    bool process_freq(int pack_length,char chksum);
    bool process_cnt(int pack_length,char chksum);
public slots:
    void readData();
};

#endif // SERTHRD_H
