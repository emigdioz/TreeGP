#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QMutex>
#include <iostream>
#include <vector>
#include <QVector>
#include <QString>

class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0);
    /**
     * @brief Requests the process to start
     *
     * It is thread safe as it uses #mutex to protect access to #_working variable.
     */
    void requestWork();
    /**
     * @brief Requests the process to abort
     *
     * It is thread safe as it uses #mutex to protect access to #_abort variable.
     */
    void abort();
    int start_main(void);
    int ngen;
    int popsize;
    int tournamentsize;
    int maxdepth;
    int mininitdepth;
    int maxinitdepth;
    float crossoverp;
    float crossoverdp;
    float mutationp;
    int mutationmaxr;
    int randomseed;
    double *dataset;
    int dataset_cols;
    int dataset_rows;
    int trainingP;    
    std::vector<bool> terminalselection;
    std::vector<bool> functionselection;

    void subsetData(double *input, double *training, double *testing, int cols, int rows, int trainsize, int *index);
    typedef struct
    {
      double train;
      double test;
      double avgsize;
      double maxsize;
      double minsize;
      double gen;
    } Stats;

    typedef struct
    {
      QVector<QString> mName;
      QVector<int> mNumberArguments;
      QVector<int> mSubTreeSize;
      QVector<float> posX;
      QVector<float> posY;
      QVector<int> index;
    } TreeStruct;

    struct fitnessdata {
      double **data;
    };

private:
    /**
     * @brief Process is aborted when @em true
     */
    bool _abort;
    /**
     * @brief @em true when Worker is doing work
     */
    bool _working;
    /**
     * @brief Protects access to #_abort
     */
    QMutex mutex;
    QString datar;


signals:
    /**
     * @brief This signal is emitted when the Worker request to Work
     * @sa requestWork()
     */
    void workRequested();
    /**
     * @brief This signal is emitted when counted value is changed
     */
    void valueChanged(const QString &value);
    void send_stats(Worker::Stats data);
    void send_stats_end(Worker::Stats data);
    void send_tree(Worker::TreeStruct data);
    void progressChanged(const int value);
    void GPstarted(const QString value);
    void plot3DSendData(Worker::fitnessdata data);
    void sendEvalFunc(unsigned long value);
    void send_tree_string(const QString data);
    /**
     * @brief This signal is emitted when process is finished (either by counting 60 sec or being aborted)
     */
    void finished();

public slots:
    /**
     * @brief Does something
     *
     * Counts 60 sec in this example.
     * Counting is interrupted if #_aborted is set to true.
     */
    void doWork();    
};

#endif // WORKER_H
