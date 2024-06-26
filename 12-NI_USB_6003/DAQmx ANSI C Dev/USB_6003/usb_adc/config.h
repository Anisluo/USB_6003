#ifndef CONFIG_H
#define CONFIG_H
#include<QQueue>

typedef enum{
    tsk_set_freq,
    tsk_set_cnt,
    tsk_read,
    tsk_sample,
}TASK_ENUM;

typedef struct{
    TASK_ENUM tskType;
    int value;
}TASK_CONFIG;


typedef struct{
    QString portName;
    int databit;
    int stopbit;
    int parity;
}SERIAL_CONFIG;


#define PACK_ACK_HEAD           0x7C
#define PACK_ACK_TAIL           0x7E

#define PACK_ACK_FREQ           0x10
#define PACK_ACK_CNT            0x20
#define PACK_ACK_ADC            0x30
#define PACK_ACK_SAMPLE_START   0x40
#define PACK_ACK_SAMPLE_FINISH  0x50




#endif // CONFIG_H
