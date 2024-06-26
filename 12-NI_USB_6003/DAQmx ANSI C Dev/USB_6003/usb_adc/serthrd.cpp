#include "serthrd.h"
#include<QDebug>

serThrd::serThrd(QObject *parent)
    : QThread{parent}
{

}
void serThrd::disconnect(){

}
void serThrd::sendData(QByteArray data){
    if(serial!=nullptr&&serial->isOpen()){
        serial->write(data);
    }
}

bool serThrd::process_sample_start(int pack_length,
                                   char chksum){
    char dataL= msgQ.dequeue();
    chksum+=dataL;
    char dataH= msgQ.dequeue();
    chksum+=dataH;
    char data_res=msgQ.dequeue();
    chksum+=data_res;
    char data_parity=msgQ.dequeue();
    chksum+=data_parity;
    char data_tail=msgQ.dequeue();
    chksum+=data_tail;
    if(chksum==data_parity){return true;}
    else{ return false; }
}



bool serThrd::process_sample_finish(int pack_length,
                                    char chksum){
    char dataL= msgQ.dequeue();
    chksum+=dataL;
    char dataH= msgQ.dequeue();
    chksum+=dataH;
    char data_res=msgQ.dequeue();
    chksum+=data_res;
    char data_parity=msgQ.dequeue();
    chksum+=data_parity;
    char data_tail=msgQ.dequeue();
    chksum+=data_tail;
    if(chksum==data_parity){return true;}
    else{ return false; }

}
bool serThrd::process_adc(int pack_length,
                          char chksum){
    char dataL= msgQ.dequeue();
    chksum+=dataL;
    char dataH= msgQ.dequeue();
    chksum+=dataH;
    int cnt=0;

    for(int i=0;i<cnt;i++){
       //处理adc数据，16bit
    }


    char data_res=msgQ.dequeue();
    chksum+=data_res;
    char data_parity=msgQ.dequeue();
    chksum+=data_parity;
    char data_tail=msgQ.dequeue();
    chksum+=data_tail;
    if(chksum==data_parity){return true;}
    else{ return false; }


}

bool serThrd::process_freq(int pack_length,
                           char chksum){
    char dataL= msgQ.dequeue();
    chksum+=dataL;
    char dataH= msgQ.dequeue();
    chksum+=dataH;
    char data_res=msgQ.dequeue();
    chksum+=data_res;
    char data_parity=msgQ.dequeue();
    chksum+=data_parity;
    char data_tail=msgQ.dequeue();
    chksum+=data_tail;
    if(chksum==data_parity){return true;}
    else{ return false; }

}

bool serThrd::process_cnt(int pack_length,
                          char chksum){
    char dataL= msgQ.dequeue();
    chksum+=dataL;
    char dataH= msgQ.dequeue();
    chksum+=dataH;
    char data_res=msgQ.dequeue();
    chksum+=data_res;
    char data_parity=msgQ.dequeue();
    chksum+=data_parity;
    char data_tail=msgQ.dequeue();
    chksum+=data_tail;
    if(chksum==data_parity){return true;}
    else{ return false; }


}

bool serThrd::open(SERIAL_CONFIG* cfg){
    if(serial==nullptr){
        serial=new QSerialPort;
        connect(serial,
                SIGNAL(readyRead()),
                this,
                SLOT(readData()));
    }
    if(serial->isOpen()){serial->close();}
    serial->setPortName(cfg->portName);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    if(serial->open(QIODevice::ReadWrite)){
        return true;
    }
    else{
        return false;
    }
}

//初始化串口通信

void serThrd::readData(){
    QByteArray data=serial->readAll();
    for(auto c:data){ msgQ.enqueue(c); }
}


void serThrd::run(){

    while(true) {
        if(serial==nullptr){QThread::msleep(50);continue;}
        if(!serial->isOpen()){QThread::msleep(50);continue;}
        if(!msgQ.isEmpty()){
            char data_head=msgQ.dequeue();
            qDebug()<<data_head;
            if(data_head==PACK_ACK_HEAD){
                char data_pack_L=msgQ.dequeue();
                char data_pack_H=msgQ.dequeue();
                int data_pack_length=(data_pack_H<<8)&data_pack_L;
                char data_pack_cmd=msgQ.dequeue();
                char chksum=0;
                switch(data_pack_cmd){
                case PACK_ACK_SAMPLE_START:
                    process_sample_start(data_pack_length,chksum);
                    break;
                case PACK_ACK_SAMPLE_FINISH:
                    process_sample_finish(data_pack_length,chksum);
                    break;
                case PACK_ACK_FREQ:
                    process_freq(data_pack_length,chksum);
                    break;
                case PACK_ACK_CNT:
                    process_cnt(data_pack_length,chksum);
                    break;
                case PACK_ACK_ADC:
                    process_adc(data_pack_length,chksum);
                    break;
                }
            }
        }
    }
}
