#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QThread>
#include <QListWidget>
#include "worker.h"
#include "optionsdialog.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include "node.h"
#include "edge.h"
#include "qwt3d_gridplot.h"
#include "qwt3d_function.h"
#include "qwt3d_plot3d.h"
#include <qwt3d_scale.h>

//QT_BEGIN_NAMESPACE
//class QTextEdit;
//QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    Qwt3D::GridPlot* plot;
    ~MainWindow();

private:
    /**
     * @brief Thread object which will let us manipulate the running thread
     */
    QThread *thread;
    Worker *worker;
    Ui::MainWindow *ui;
    OptionsDialog *oDialog;
    QList<QStringList> csv;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;
    bool GPthreadstarted;
    void setupPlots();
    double maxSize;
    double maxFitness;
    QGraphicsScene *scene;
    int countLeaves(int index, int count);
    void positionLeaves(int index,int depth);
    void positionParents(int index,int depth);
    int nLeaves;
    Worker::TreeStruct selectedTree;
    int plot3D_width1;
    int plot3D_width2;

private slots:
    void runGP();
    void on_actionRun_triggered();
    void on_actionE_xit_triggered();
    void on_actionOptions_triggered();
    void received_data(OptionsDialog::Options data);
    void received_stats(Worker::Stats data);
    void received_tree(Worker::TreeStruct data);
    void on_actionLoad_file_triggered();
    void checkString(QString &temp, QChar character = 0);
    void received_GPstarted(QString value);
    void thread_finished();
    void on_horizontalSlider_valueChanged(int value);
    void plot3DUpdateData(Worker::fitnessdata data);
    void on_listWidget_2_itemClicked(QListWidgetItem *item);
};
Q_DECLARE_METATYPE(OptionsDialog::Options)
#endif // MAINWINDOW_H
