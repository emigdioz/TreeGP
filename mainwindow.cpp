#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "optionsdialog.h"
#include <QDebug>
#include "SymbRegPrimits.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<OptionsDialog::Options>();

    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(1);


    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(valueChanged(QString)), ui->textEdit, SLOT(append(QString)));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(GPstarted(QString)), this, SLOT(received_GPstarted(QString)));
    connect(worker, SIGNAL(send_best_fitness(double,int)), this, SLOT(received_best_fitness(double,int)));
    connect(worker, SIGNAL(progressChanged(int)), ui->progressBar, SLOT(setValue(int)));

    oDialog = new OptionsDialog(this);
    connect(worker, SIGNAL(sendSignal(int)), oDialog, SLOT(write_gen(int)));

    connect(oDialog, SIGNAL(send_data(OptionsDialog::Options)), this, SLOT(received_data(OptionsDialog::Options)));

    ui->outputPlot->addGraph();
    // give the axes some labels:
    ui->outputPlot->xAxis->setLabel("Generations");
    ui->outputPlot->yAxis->setLabel("Fitness");
    // set axes ranges, so we see all data:
    ui->outputPlot->xAxis->setRange(1, worker->ngen);
    ui->outputPlot->yAxis->setRange(0, 1);
    QPen blueLinePen;
    blueLinePen.setColor(QColor(0, 173, 250, 255));
    blueLinePen.setWidth(2);
    ui->outputPlot->graph(0)->setPen(blueLinePen);
    //ui->outputPlot->setBackground(Qt::lightGray);
    ui->outputPlot->axisRect()->setBackground(QColor(229, 229, 229, 255));
    ui->outputPlot->xAxis->grid()->setPen(QColor(255, 255, 255, 255));
    ui->outputPlot->yAxis->grid()->setPen(QColor(255, 255, 255, 255));
    ui->outputPlot->xAxis->setBasePen(QColor(255, 255, 255, 255));
    ui->outputPlot->yAxis->setBasePen(QColor(255, 255, 255, 255));
    ui->outputPlot->xAxis->setTickPen(QColor(127, 127, 127, 255));
    ui->outputPlot->xAxis->setSubTickPen(QColor(127, 127, 127, 255));
    ui->outputPlot->yAxis->setTickPen(QColor(127, 127, 127, 255));
    ui->outputPlot->yAxis->setSubTickPen(QColor(127, 127, 127, 255));
    ui->outputPlot->replot();

    oDialog->accept(); // Send default data from options dialog

}

//void MainWindow::createToolBars()
//{
//    fileToolBar = addToolBar(tr("Tools"));
//    fileToolBar->addAction(runAct);
//}

//void MainWindow::createActions()
//{
//    runAct = new QAction(QIcon(""), tr("&Run"), this);

//    connect(runAct, SIGNAL(triggered()), this, SLOT(runGP()));
//}

void MainWindow::runGP()
{
    //ui->statusbar->showMessage("Progress");

    // To avoid having two threads running simultaneously, the previous thread is aborted.
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();
    //ui->statusbar->showMessage("");
}

MainWindow::~MainWindow()
{
    worker->abort();
    thread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete thread;
    delete worker;
    delete ui;
}

void MainWindow::on_actionRun_triggered()
{
    ui->textEdit->clear();
    ui->outputPlot->graph(0)->clearData();
    runGP();
}

void MainWindow::on_actionE_xit_triggered()
{
    qApp->exit();
}

void MainWindow::on_actionOptions_triggered()
{
    //oDialog->moveToThread();

    //oDialog.setModal(false);
    //oDialog.exec();
    oDialog->show();

}

void MainWindow::received_data(OptionsDialog::Options data)
{
    worker->ngen = data.ngen;
    worker->popsize = data.popsize;
    worker->tournamentsize = data.tournamentsize;
    worker->maxdepth = data.maxdepth;
    worker->mininitdepth = data.mininitdepth;
    worker->maxinitdepth = data.maxinitdepth;
    worker->crossoverp = data.crossoverp;
    worker->crossoverdp = data.crossoverdp;
    worker->mutationp = data.mutationp;
    worker->mutationmaxr = data.mutationmaxr;
    worker->randomseed = data.randomseed;
    ui->outputPlot->xAxis->setRange(1, worker->ngen);
    ui->outputPlot->graph(0)->clearData();
    ui->outputPlot->replot();
}

void MainWindow::received_best_fitness(double value, int gen)
{
//        QVector<double> x(101), y(101); // initialize with entries 0..100
//        for (int i=0; i<101; ++i)
//        {
//          x[i] = i/50.0 - 1; // x goes from -1 to 1
//          y[i] = x[i]*x[i]; // let's plot a quadratic function
//        }
        // create graph and assign data to it:
        ui->outputPlot->graph(0)->addData(gen,value);
        ui->outputPlot->replot();
}

void MainWindow::received_GPstarted(QString value)
{
    ui->actionRun->setIconText(value);
}

void MainWindow::on_actionLoad_file_triggered()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }
    int iRows = model->rowCount();
    int iCols = model->columnCount();
    if(iCols == 2) {
        ui->lineEdit->setText("1");
    }
    else {
        ui->lineEdit->setText("1:" + QString::number(iCols-1));
    }
    ui->lineEdit_2->setText(QString::number(iCols));
    ui->lineEdit_3->setText("1:" + QString::number(iRows));
}

void MainWindow::checkString(QString &temp, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
             temp.remove( QRegExp("^\"") );
             temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_5->setText("Training/Testing (" + QString::number(value) + "/" + QString::number(100-value) + ")");
}
