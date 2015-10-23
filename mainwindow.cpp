#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "optionsdialog.h"
#include <QDebug>
#include "SymbRegPrimits.hpp"
#include "worker.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsView>

Q_DECLARE_METATYPE(Worker::Stats);  // Needed for MetaType recognize new data type

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<OptionsDialog::Options>();    

    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(1);
    GPthreadstarted = false;

    thread = new QThread();
    worker = new Worker();

    qRegisterMetaType<Worker::Stats>();
    worker->moveToThread(thread);
    connect(worker, SIGNAL(valueChanged(QString)), ui->textEdit, SLOT(append(QString)));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished()), this, SLOT(thread_finished()), Qt::DirectConnection);
    connect(worker, SIGNAL(GPstarted(QString)), this, SLOT(received_GPstarted(QString)));
    //connect(worker, SIGNAL(send_best_fitness(double,double,double,int)), this, SLOT(received_best_fitness(double,double,double,int)));
    connect(worker, SIGNAL(send_stats(Worker::Stats)), this, SLOT(received_stats(Worker::Stats)));
    connect(worker, SIGNAL(progressChanged(int)), ui->progressBar, SLOT(setValue(int)));

    oDialog = new OptionsDialog(this);
    connect(worker, SIGNAL(sendSignal(int)), oDialog, SLOT(write_gen(int)));

    connect(oDialog, SIGNAL(send_data(OptionsDialog::Options)), this, SLOT(received_data(OptionsDialog::Options)));

    setupPlots();
    oDialog->accept(); // Send default data from options dialog
    worker->trainingP = ui->horizontalSlider->value(); // Training size in percentage

    // Tree graph
    QGraphicsScene *scene = new QGraphicsScene(ui->treeGraph);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    ui->treeGraph->setScene(scene);
    //ui->treeGraph->setCacheMode(QGraphicsView::CacheBackground);
    ui->treeGraph->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->treeGraph->setRenderHint(QPainter::Antialiasing);
    ui->treeGraph->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->treeGraph->scale(qreal(0.8), qreal(0.8));
    ui->treeGraph->setMinimumSize(300, 300);

    Node *node1 = new Node(ui->treeGraph);
    scene->addItem(node1);
    //scene->addItem(node2);
    //scene->addItem(new Edge(node1, node2));
    node1->setPos(-50, -50);
    //node2->setPos(0, -50);

}

void MainWindow::setupPlots()
{
  // Fitness plot
  ui->outputPlot->addGraph();
  ui->outputPlot->addGraph();
  // give the axes some labels:
  ui->outputPlot->xAxis->setLabel("Generations");
  ui->outputPlot->yAxis->setLabel("Fitness");
  // set axes ranges, so we see all data:
  ui->outputPlot->xAxis->setRange(1, worker->ngen);
  ui->outputPlot->yAxis->setRange(0, 1);
  QPen blueLinePen;
  QPen greenLinePen;
  blueLinePen.setColor(QColor(0, 173, 250, 255));
  blueLinePen.setWidth(2);
  greenLinePen.setColor(QColor(94, 179, 0, 255));
  greenLinePen.setWidth(2);
  ui->outputPlot->graph(0)->setPen(blueLinePen);
  ui->outputPlot->graph(1)->setPen(greenLinePen);
  ui->outputPlot->graph(0)->setName("Train data");
  ui->outputPlot->graph(1)->setName("Test data");
  ui->outputPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
  ui->outputPlot->axisRect()->setBackground(QColor(229, 229, 229, 255));
  ui->outputPlot->xAxis->grid()->setPen(QColor(255, 255, 255, 255));
  ui->outputPlot->yAxis->grid()->setPen(QColor(255, 255, 255, 255));
  ui->outputPlot->xAxis->setBasePen(QColor(255, 255, 255, 255));
  ui->outputPlot->yAxis->setBasePen(QColor(255, 255, 255, 255));
  ui->outputPlot->xAxis->setTickPen(QColor(127, 127, 127, 255));
  ui->outputPlot->xAxis->setSubTickPen(QColor(127, 127, 127, 255));
  ui->outputPlot->yAxis->setTickPen(QColor(127, 127, 127, 255));
  ui->outputPlot->yAxis->setSubTickPen(QColor(127, 127, 127, 255));

  // Size plot
  ui->sizePlot->addGraph();
  ui->sizePlot->addGraph();
  ui->sizePlot->addGraph();
  // give the axes some labels:
  ui->sizePlot->xAxis->setLabel("Generations");
  ui->sizePlot->yAxis->setLabel("Size");
  // set axes ranges, so we see all data:
  ui->sizePlot->xAxis->setRange(1, worker->ngen);
  ui->sizePlot->yAxis->setRange(0, 1);
  QPen orangeLinePen;
  orangeLinePen.setColor(QColor(248, 118, 109, 255));
  orangeLinePen.setWidth(1);
  ui->sizePlot->graph(0)->setPen(orangeLinePen);
  ui->sizePlot->graph(0)->setBrush(QBrush(QColor(248, 118, 109, 20)));
  ui->sizePlot->graph(0)->setName("Max pop size");
  ui->sizePlot->graph(0)->setAntialiasedFill(false);
  ui->sizePlot->graph(1)->setPen(orangeLinePen);
  ui->sizePlot->graph(1)->setName("Min pop size");
  ui->sizePlot->graph(0)->setChannelFillGraph(ui->sizePlot->graph(1));
  orangeLinePen.setWidth(2);
  ui->sizePlot->graph(2)->setPen(orangeLinePen);
  ui->sizePlot->graph(2)->setName("Average pop size");
  ui->sizePlot->legend->removeItem(0);
  ui->sizePlot->legend->removeItem(0);

  ui->sizePlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
  ui->sizePlot->axisRect()->setBackground(QColor(229, 229, 229, 255));
  ui->sizePlot->xAxis->grid()->setPen(QColor(255, 255, 255, 255));
  ui->sizePlot->yAxis->grid()->setPen(QColor(255, 255, 255, 255));
  ui->sizePlot->xAxis->setBasePen(QColor(255, 255, 255, 255));
  ui->sizePlot->yAxis->setBasePen(QColor(255, 255, 255, 255));
  ui->sizePlot->xAxis->setTickPen(QColor(127, 127, 127, 255));
  ui->sizePlot->xAxis->setSubTickPen(QColor(127, 127, 127, 255));
  ui->sizePlot->yAxis->setTickPen(QColor(127, 127, 127, 255));
  ui->sizePlot->yAxis->setSubTickPen(QColor(127, 127, 127, 255));

  ui->outputPlot->replot();
  ui->sizePlot->replot();
  maxSize = 0;
  maxFitness = 1;
}

void MainWindow::runGP()
{
    //ui->statusbar->showMessage("Progress");

    // To avoid having two threads running simultaneously, the previous thread is aborted.
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();
    GPthreadstarted = true;
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
    if(GPthreadstarted) {
      worker->abort();
      thread->wait(); // If the thread is not running, this will immediately return.
      ui->actionRun->setIconText("Run");
      GPthreadstarted = false;
    }
    else {
      ui->textEdit->clear();
      ui->outputPlot->graph(0)->clearData();
      ui->outputPlot->graph(1)->clearData();
      ui->sizePlot->graph(0)->clearData();
      ui->sizePlot->graph(1)->clearData();
      ui->sizePlot->graph(2)->clearData();
      maxSize = 0;
      Node *node2 = new Node(ui->treeGraph);
      ui->treeGraph->scene()->addItem(node2);
      //scene->addItem(node2);
      //node2->setPos(0, -50);
      runGP();
    }
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
    worker->functionselection = data.functionselection;
    ui->outputPlot->xAxis->setRange(1, worker->ngen);
    ui->outputPlot->graph(0)->clearData();
    ui->outputPlot->yAxis->setRange(0, 1);
    ui->outputPlot->replot();
    ui->sizePlot->xAxis->setRange(1, worker->ngen);
    ui->sizePlot->graph(0)->clearData();
    ui->sizePlot->graph(1)->clearData();
    ui->sizePlot->graph(2)->clearData();
    ui->sizePlot->replot();
}

void MainWindow::received_stats(Worker::Stats data)
{
  ui->outputPlot->graph(0)->addData(data.gen,data.train);
  ui->outputPlot->graph(1)->addData(data.gen,data.test);
  ui->outputPlot->legend->setVisible(true);
  ui->outputPlot->replot();
  ui->sizePlot->graph(0)->addData(data.gen,data.maxsize);
  ui->sizePlot->graph(1)->addData(data.gen,data.minsize);
  ui->sizePlot->graph(2)->addData(data.gen,data.avgsize);
  ui->sizePlot->legend->setVisible(true);

  if(data.train>maxFitness || data.test>maxFitness){
    if(data.test>data.train) {
      ui->outputPlot->yAxis->setRange(0, data.test);
      maxFitness = data.test;
    }
    else {
      ui->outputPlot->yAxis->setRange(0, data.train);
      maxFitness = data.train;
    }
  }
  else
    ui->outputPlot->yAxis->setRange(0, maxFitness);

  if(data.maxsize>maxSize){
    ui->sizePlot->yAxis->setRange(0, data.maxsize);
    maxSize = data.maxsize;
  }
  else
    ui->sizePlot->yAxis->setRange(0, maxSize);
  ui->sizePlot->replot();
}

void MainWindow::received_GPstarted(QString value)
{
    ui->actionRun->setIconText(value);
}

void MainWindow::on_actionLoad_file_triggered()
{
    int i,j;
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
    worker->dataset = new double[iRows*iCols];
    for(j = 0;j < iCols;j++) {
        for(i = 0;i < iRows;i++) {
            worker->dataset[(j*iRows)+i] = model->item(i,j)->text().toDouble();
        }
    }
    worker->dataset_cols = iCols;
    worker->dataset_rows = iRows;
    ui->actionRun->setEnabled(true);
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
    worker->trainingP = value;
}

void MainWindow::thread_finished()
{
  GPthreadstarted = false;
}
