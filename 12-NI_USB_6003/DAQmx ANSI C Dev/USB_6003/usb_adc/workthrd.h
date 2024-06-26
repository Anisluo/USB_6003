#ifndef WORKTHRD_H
#define WORKTHRD_H

#include <QThread>
#include"config.h"

class WorkThrd : public QThread
{
public:
    explicit WorkThrd(QObject *parent = nullptr);
    void run()override;
    bool continueRun();
    bool stop_tasks();
    void addTask(TASK_CONFIG* tsk);


};

#endif // WORKTHRD_H
