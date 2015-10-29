#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include "SymbRegPrimits.hpp"
#include "worker.h"
#include "node.h"
#include "edge.h"
#include <QGraphicsView>

Q_DECLARE_METATYPE(Worker::Stats);  // Needed for MetaType recognize new data type
Q_DECLARE_METATYPE(Worker::TreeStruct);
Q_DECLARE_METATYPE(Worker::fitnessdata);

class Rosenbrock : public Qwt3D::Function
{
public:

  Rosenbrock(Qwt3D::GridPlot& pw)
    :Qwt3D::Function(pw)
  {
  }

  double operator()(double x, double y)
  {
    return log((1-x)*(1-x) + 100 * (y - x*x)*(y - x*x)) / 8;
  }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setMinimum(1);
    // Limit numeric values for parameter inputs
    QRegExp Integer("^[0-9]{1,5}$");
    QRegExp Floating("^[0-9]\.?[0-9]{1,5}$");
    ui->lineEdit_5->setValidator(new QRegExpValidator(Integer, ui->lineEdit_5));
    ui->lineEdit_9->setValidator(new QRegExpValidator(Integer, ui->lineEdit_9));
    ui->lineEdit_4->setValidator(new QRegExpValidator(Integer, ui->lineEdit_4));
    ui->lineEdit_6->setValidator(new QRegExpValidator(Integer, ui->lineEdit_6));
    ui->lineEdit_8->setValidator(new QRegExpValidator(Integer, ui->lineEdit_8));
    ui->lineEdit_12->setValidator(new QRegExpValidator(Integer, ui->lineEdit_12));
    ui->lineEdit_13->setValidator(new QRegExpValidator(Integer, ui->lineEdit_13));
    ui->lineEdit_10->setValidator(new QRegExpValidator(Floating, ui->lineEdit_10));
    ui->lineEdit_7->setValidator(new QRegExpValidator(Floating, ui->lineEdit_7));
    ui->lineEdit_11->setValidator(new QRegExpValidator(Floating, ui->lineEdit_11));

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    ui->listWidget->setCurrentRow(0);
    GPthreadstarted = false;

    thread = new QThread();
    worker = new Worker();
    timerGP = new QTimer();

    qRegisterMetaType<Worker::Stats>();
    qRegisterMetaType<Worker::TreeStruct>();
    qRegisterMetaType<Worker::fitnessdata>();

    worker->moveToThread(thread);
    connect(worker, SIGNAL(valueChanged(QString)), ui->textEdit, SLOT(append(QString)));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    connect(worker, SIGNAL(finished()), this, SLOT(thread_finished()), Qt::DirectConnection);
    connect(worker, SIGNAL(GPstarted(QString)), this, SLOT(received_GPstarted(QString)));
    connect(worker, SIGNAL(send_stats(Worker::Stats)), this, SLOT(received_stats(Worker::Stats)));
    connect(worker, SIGNAL(send_tree(Worker::TreeStruct)), this, SLOT(received_tree(Worker::TreeStruct)));
    connect(worker, SIGNAL(progressChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(worker, SIGNAL(plot3DSendData(Worker::fitnessdata)), this, SLOT(plot3DUpdateData(Worker::fitnessdata)));
    connect(worker, SIGNAL(sendEvalFunc(unsigned long)), this, SLOT(receivedEvalFunc(unsigned long)));
    connect(worker, SIGNAL(send_tree_string(QString)), this, SLOT(received_tree_string(QString)));
    // Timer for running time
    connect(timerGP, SIGNAL(timeout()), this, SLOT(showElapsedTime()));

    // 3d Plot
    QGridLayout *grid = new QGridLayout(ui->frame);
    plot = new Qwt3D::GridPlot(ui->frame);
    grid->addWidget( plot, 0, 0 );

    worker->trainingP = ui->horizontalSlider->value(); // Training size in percentage

    // Tree graph
    QGraphicsScene *scene = new QGraphicsScene(ui->treeGraph);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 1000, 2000);
    ui->treeGraph->setScene(scene);
    ui->treeGraph->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->treeGraph->setRenderHint(QPainter::Antialiasing);
    ui->treeGraph->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->treeGraph->scale(qreal(0.5), qreal(0.5));
    ui->treeGraph->setMinimumSize(300, 300);

    // Preselect +,-,/,* as function set
    ui->listFunctions->item(0)->setSelected(true);
    ui->listFunctions->item(1)->setSelected(true);
    ui->listFunctions->item(2)->setSelected(true);
    ui->listFunctions->item(3)->setSelected(true);

    // Preselct fitness function
    ui->listFitFunctions->item(0)->setSelected(true);

    // Default GP parameters
    worker->ngen = 100;
    worker->popsize = 100;
    worker->tournamentsize = 10;
    worker->maxdepth = 17;
    worker->mininitdepth = 2;
    worker->maxinitdepth = 5;
    worker->crossoverp = 0.9;
    worker->crossoverdp = 0.9;
    worker->mutationp = 0.05;
    worker->mutationmaxr = 5;
    worker->randomseed = 0;

    setupPlots();
    initializePlots();
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
    // To avoid having two threads running simultaneously, the previous thread is aborted.
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    worker->requestWork();
    GPthreadstarted = true;
    ui->labelElapsedTime->setText("0");
    showStartedTime();
    showStartedDate();
    startedDateTime = QDateTime::currentDateTime();
    timerGP->start(1000);
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
      maxFitness = 1;
      ui->treeGraph->scene()->clear();
      runGP();
    }
}

void MainWindow::on_actionE_xit_triggered()
{
    qApp->exit();
}

void MainWindow::initializePlots()
{
  ui->outputPlot->xAxis->setRange(1, worker->ngen);
  ui->outputPlot->graph(0)->clearData();
  ui->outputPlot->graph(1)->clearData();
  //ui->outputPlot->yAxis->setRange(0, 1);
  ui->outputPlot->replot();
  ui->sizePlot->xAxis->setRange(1, worker->ngen);
  ui->sizePlot->graph(0)->clearData();
  ui->sizePlot->graph(1)->clearData();
  ui->sizePlot->graph(2)->clearData();
  ui->sizePlot->replot();

  // Setup 3D plot
  plot->setPlotStyle(Qwt3D::FILLED);
  plot->setTitle("Fitness landscape");
  QFont font;
  plot->setTitleFont(font.family(), font.pointSize(), font.weight(), font.italic());
  plot->coordinates()->setLabelFont(font);
  plot->coordinates()->setNumberFont(font);
  plot3D_width1 = worker->ngen;
  plot3D_width2 = worker->popsize;

  double *dataplot[plot3D_width1];
  // fill initial data
  for (int i = 0; i < plot3D_width1; i++)
  {
    dataplot[i] = new double[plot3D_width2];
    for (int j = 0; j < plot3D_width2; j++) dataplot[i][j] = 0;
  }
  plot->createDataset(dataplot, plot3D_width1, plot3D_width2, 0,plot3D_width1, 0, plot3D_width2);
  plot->setRotation(30,0,15);
  plot->setScale(1,1,1);
  plot->setShift(0.15,0,0);
  plot->setZoom(0.6);
  for (unsigned i=0; i!=plot->coordinates()->axes.size(); ++i)
  {
    plot->coordinates()->axes[i].setMajors(4);
    plot->coordinates()->axes[i].setMinors(2);
  }

  plot->setCoordinateStyle(Qwt3D::FRAME);
  plot->coordinates()->setAutoScale(false);
}


void MainWindow::plot3DUpdateData(Worker::fitnessdata data)
{
  plot3D_width1 = worker->ngen;
  plot3D_width2 = worker->popsize;
  double *dataplot[plot3D_width1];
  // fill initial data
  for (int i = 0; i < plot3D_width1; i++)
  {
    dataplot[i] = new double[plot3D_width2];
    for (int j = 0; j < plot3D_width2; j++) {
      dataplot[i][j] = data.data[i][j];
    }
  }
  plot->createDataset(dataplot, plot3D_width1, plot3D_width2, 0,plot3D_width1, 0, plot3D_width2);
  plot->coordinates()->axes[Qwt3D::X1].setLabelString("Generations");
  plot->coordinates()->axes[Qwt3D::X2].setLabelString("Generations");
  plot->coordinates()->axes[Qwt3D::X3].setLabelString("Generations");
  plot->coordinates()->axes[Qwt3D::X4].setLabelString("Generations");
  plot->coordinates()->axes[Qwt3D::Y1].setLabelString("Population");
  plot->coordinates()->axes[Qwt3D::Y2].setLabelString("Population");
  plot->coordinates()->axes[Qwt3D::Y3].setLabelString("Population");
  plot->coordinates()->axes[Qwt3D::Y4].setLabelString("Population");
  plot->setScale(1,1,50);
  plot->updateGL();
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

void MainWindow::received_tree(Worker::TreeStruct data)
{
  selectedTree = data;
  nLeaves = 0;
  float spanx = 50;
  float startx;
  float spany = 80;
  float starty = 100;
  int maxDepth = 0;
  for(unsigned int i=0;i<selectedTree.mName.size();i++) {
    nLeaves = countLeaves(i,nLeaves);
  }
  spanx = spanx * nLeaves;
  startx = -(spanx/2) + 500;

  positionLeaves(0,0);
  positionParents(0,0);
  // Draw nodes
  for(unsigned int i=0;i<selectedTree.mName.size();i++) {
    Node *node = new Node(ui->treeGraph);
    node->nameNode = selectedTree.mName[i];
    ui->treeGraph->scene()->addItem(node);
    node->setPos((spanx*selectedTree.posX[i])+startx,(spany*selectedTree.posY[i])+starty);
    if(selectedTree.posY[i]>maxDepth) maxDepth = selectedTree.posY[i];
  }
  // Draw connections
  int counter,index;
  QList<QGraphicsItem *> listnodes = ui->treeGraph->scene()->items();
  index = 0;
  for(unsigned int depth=0;depth<maxDepth;depth++) {
    // Search all nodes with the same depth
    do
    {
      if(selectedTree.posY[index] == depth) {
        counter = 0;
        Node *nodeParent = qgraphicsitem_cast<Node *>( listnodes.at( index ) );
        for(unsigned int k=0;k<selectedTree.mNumberArguments[index];k++) {
          do // Search for childrens
          {
            if(selectedTree.posY[index + counter] == (depth+1)) {
              counter += 1;
              break;
            }
            counter += 1;
          }while((index + counter)<selectedTree.mName.size());
          // Found children
          Node *nodeChildren = qgraphicsitem_cast<Node *>( listnodes.at( (index+counter-1) ) );
          ui->treeGraph->scene()->addItem(new Edge(nodeParent,nodeChildren));
        }
      }
      index += 1;
    }while(index<selectedTree.mName.size());
    index = 0;
  }
}

int MainWindow::countLeaves(int index, int count)
{
  if(selectedTree.mSubTreeSize[index] == 1) {
    selectedTree.index[index] = count;
    count += 1;
  }
  return count;
}

void MainWindow::positionLeaves(int index, int depth)
{
  if(selectedTree.mSubTreeSize[index] == 1) {
    selectedTree.posX[index] = (float)selectedTree.index[index] / (nLeaves - 1);
    selectedTree.posY[index] = depth;
  }
  unsigned int j = index + 1;
  for(unsigned int i = 0;i<selectedTree.mNumberArguments[index];i++) {
    positionLeaves(j,depth+1);
    j += selectedTree.mSubTreeSize[j];
  }
}

void MainWindow::positionParents(int index,int depth)
{
  unsigned int j = index + 1;
  for(unsigned int i = 0;i<selectedTree.mNumberArguments[index];i++) {
    positionParents(j,depth+1);
    j += selectedTree.mSubTreeSize[j];
  }
  if(selectedTree.mSubTreeSize[index]>1) {
    float x = 0;
    int counter = 0;
    for(unsigned int k=0;k<selectedTree.mNumberArguments[index];k++) {
      do // Search for childrens
      {
        if(selectedTree.posY[index + counter] == (depth+1)) {
          x += selectedTree.posX[index + counter];
          counter += 1;
          break;
        }
        counter += 1;
      }while((index + counter)<selectedTree.mName.size());
    }
    selectedTree.posX[index] = x/selectedTree.mNumberArguments[index];
    selectedTree.posY[index] = depth;
  }
}

void MainWindow::received_GPstarted(QString value)
{
  if(QString::compare(value, "Stop", Qt::CaseInsensitive) == 0) {
    ui->actionRun->setIconText(value);
    ui->ButtonStop->setEnabled(true);
    ui->ButtonStart->setEnabled(false);
  }
  else
  {
    ui->ButtonStop->setEnabled(false);
    ui->ButtonStart->setEnabled(true);
    timerGP->stop();
  }
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
    ui->ButtonStart->setEnabled(true);
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

void MainWindow::on_ButtonStart_clicked()
{
  if(!GPthreadstarted) {
    ui->textEdit->clear();
    ui->outputPlot->graph(0)->clearData();
    ui->outputPlot->graph(1)->clearData();
    ui->sizePlot->graph(0)->clearData();
    ui->sizePlot->graph(1)->clearData();
    ui->sizePlot->graph(2)->clearData();
    maxSize = 0;
    maxFitness = 1;
    ui->treeGraph->scene()->clear();
    runGP();
  }
}

void MainWindow::on_ButtonStop_clicked()
{
  if(GPthreadstarted) {
    worker->abort();
    thread->wait(); // If the thread is not running, this will immediately return.
    ui->ButtonStart->setEnabled(true);
    ui->ButtonStop->setEnabled(false);
    GPthreadstarted = false;
  }
}

void MainWindow::on_listFunctions_itemSelectionChanged()
{
  std::vector<bool> funSelection;
  for(unsigned int i=0;i<ui->listFunctions->count();i++) {
    if(ui->listFunctions->item(i)->isSelected()) funSelection.push_back(true); else funSelection.push_back(false);
  }
  worker->functionselection = funSelection;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    worker->ngen = arg1;
}


void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    worker->popsize = arg1.toInt();
}

void MainWindow::on_lineEdit_9_textChanged(const QString &arg1)
{
    worker->tournamentsize = arg1.toInt();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    worker->maxdepth = arg1.toInt();
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    worker->mininitdepth = arg1.toInt();
}

void MainWindow::on_lineEdit_8_textChanged(const QString &arg1)
{
    worker->maxinitdepth = arg1.toInt();
}

void MainWindow::on_lineEdit_10_textChanged(const QString &arg1)
{
    worker->crossoverp = arg1.toFloat();
}

void MainWindow::on_lineEdit_7_textChanged(const QString &arg1)
{
    worker->crossoverdp = arg1.toFloat();
}

void MainWindow::on_lineEdit_11_textChanged(const QString &arg1)
{
    worker->mutationp = arg1.toFloat();
}

void MainWindow::on_lineEdit_12_textChanged(const QString &arg1)
{
    worker->mutationmaxr = arg1.toInt();
}

void MainWindow::on_lineEdit_13_textChanged(const QString &arg1)
{
    worker->randomseed = arg1.toInt();
}

void MainWindow::receivedEvalFunc(unsigned long value)
{
  ui->labelEvalFunc->setText(QString::number(value));
}

QString MainWindow::seconds_to_DHMS(qint64 duration)
{
  QString res;
  int seconds = (int) (duration % 60);
  duration /= 60;
  int minutes = (int) (duration % 60);
  duration /= 60;
  int hours = (int) (duration % 24);
  int days = (int) (duration / 24);
  if((hours == 0)&&(days == 0)&&(minutes == 0))
    return res.sprintf("%02d secs", seconds);
  if((hours == 0)&&(days == 0))
    return res.sprintf("%02d mins %02d secs", minutes, seconds);
  if (days == 0)
    return res.sprintf("%02d hrs %02d mins %02d secs", hours, minutes, seconds);
  return res.sprintf("%dd days %02d hrs %02d mins %02d secs", days, hours, minutes, seconds);
}

void MainWindow::showElapsedTime()
{
  QDateTime currentDateTime = QDateTime::currentDateTime();

  qint64 seconds = startedDateTime.secsTo(currentDateTime);

  ui->labelElapsedTime->setText(seconds_to_DHMS(seconds));
  ui->labelElapsedTime->update();
}

void MainWindow::showStartedTime()
{
  QTime time = QTime::currentTime();
  QString text = time.toString("hh:mm");
  ui->labelStartedTime->setText(text);
}

void MainWindow::showStartedDate()
{
  QDate date = QDate::currentDate();
  QString text = date.toString("ddd MMM d yyyy");
  ui->labelStartedDate->setText(text);
}

void MainWindow::received_tree_string(const QString data)
{
  ui->textEditTree->setText(data);
}
