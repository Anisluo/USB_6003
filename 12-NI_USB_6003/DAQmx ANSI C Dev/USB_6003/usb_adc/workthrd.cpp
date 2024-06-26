#include "workthrd.h"

WorkThrd::WorkThrd(QObject *parent)
    : QThread{parent} {



}


//main run stack
void WorkThrd::run(){




}


void WorkThrd::addTask(TASK_CONFIG* tsk){

}

bool WorkThrd::continueRun(){
   return true;
}
