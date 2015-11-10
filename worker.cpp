#include "worker.h"
#include <QTimer>
#include <QEventLoop>
#include <vector>

#include <QThread>
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
}

void Worker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

void Worker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}

void Worker::doWork()
{
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    // Checks if the process should be aborted
    mutex.lock();
    bool abort = _abort;
    mutex.unlock();

    if (abort) {
        qDebug()<<"Aborting worker process in Thread "<<thread()->currentThreadId();
    }
    start_main();

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}

void Worker::subsetData(double *input, double *training, double *testing, int cols, int rows, int trainsize, int *index)
{
  double rowV;
  int j;
  // Training partition
  for(unsigned int ind=0;ind<trainsize;ind++) {
    j = index[ind];
    for(unsigned int k=0; k<cols;k++) {
      rowV =  input[(k*rows)+j];
      training[(k*trainsize)+ind] = rowV;
    }
  }
  // Testing partition
  for(unsigned int ind=0;ind<(rows-trainsize);ind++) {
    j = index[trainsize+ind];
    for(unsigned int k=0; k<cols;k++) {
      rowV =  input[(k*rows)+j];
      testing[(k*(rows-trainsize))+ind] = rowV;
    }
  }
}
