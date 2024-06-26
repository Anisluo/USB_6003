
#include "mainwindow.h"

#include <QApplication>
//#include"config.h"
#include"NIDAQmx.h"
#include<QDebug>
#include<QTextStream>


#define PI 3.1415926
#define DAQmxErrChk(functionCall) if (DAQmxFailed(error = (functionCall))) throw qDebug()<<(DAQmxGetErrorString(error, errBuff, 2048))

void generateSineWave(std::vector<float64>& data,
                      int numSamples,
                      float64 amplitude,
                      float64 frequency,
                      float64 sampleRate) {
    for (int i = 0; i < numSamples; ++i) {
        data[i] = amplitude * sin(2 * PI * frequency * i / sampleRate);
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    ///
    /// 配置AI通道
 /*

    TaskHandle taskHandle=0;
    int32 read;
    float64 data[1000];

    DAQmxCreateTask("",&taskHandle);


    DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai0",
                             "",
                             DAQmx_Val_Cfg_Default,
                             -10.0, 10.0,
                             DAQmx_Val_Volts,
                             NULL);




        DAQmxStartTask(taskHandle);
        DAQmxReadAnalogF64(taskHandle, 1000, 10.0,
                           DAQmx_Val_GroupByChannel,
                           data, 1000,
                           &read,
                           NULL);

    // Print data
    for (int i = 0; i < 1000; ++i) {
        qDebug()<<data[i];
    }

    // Clear the task
    DAQmxClearTask(taskHandle);

    */


    ///
    /// \brief DI通道
    ///
    TaskHandle taskHandle = 0;
    int32 read;
    uInt8 data[8]; // 数组大小应根据所读取的通道数量进行调整
    char errBuff[2048] = {'\0'};
    int32 error = 0;

    // 创建任务
    DAQmxErrChk(DAQmxCreateTask("", &taskHandle));

    // 添加数字输入通道
    DAQmxErrChk(DAQmxCreateDIChan(taskHandle, "Dev1/port0/line0:7", "", DAQmx_Val_ChanForAllLines));

    // 设置采样时钟
//    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", 1000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 1000));

    // 启动任务
//    DAQmxErrChk(DAQmxStartTask(taskHandle));

//    // 读取数据
//    while (true) {
//        DAQmxErrChk(DAQmxReadDigitalLines(taskHandle, 1, 10.0, DAQmx_Val_GroupByChannel, data, 8, &read, NULL, NULL));
//        if (read > 0) {
//            qDebug() << "Acquired " << read << " samples. Data: ";
//            for (int i = 0; i < read; ++i) {
//                qDebug() << static_cast<int>(data[i]) << " ";
//            }
//        } else {
//            qDebug() << "No samples acquired" ;
//        }
//    }

//    DAQmxStopTask(taskHandle);
//    DAQmxClearTask(taskHandle);

    w.show();
    return a.exec();
}
