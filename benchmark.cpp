#include <mainwindow.h>
#include "ui_mainwindow.h"

void MainWindow::gen_benchmark(int selection)
{
  int i,j,nrows,ncols;
  model = new QStandardItemModel(this);
  ui->tableView->setModel(model);
  switch(selection) {
    case 0:  // Koza-1
        worker->dataset_cols = ncols = 2;
        worker->dataset_rows = nrows = 20;
        worker->dataset = new double[nrows*ncols];
        // Inputs
        for(j = 0;j < ncols-1;j++) {
            for(i = 0;i < nrows;i++) {
                worker->dataset[(j*nrows)+i] = rollUniform(-1,1);
              }
          }
        // Output
        for(i = 0;i < nrows;i++) worker->dataset[((ncols-1)*nrows)+i] = pow(worker->dataset[i],4) + pow(worker->dataset[i],3) + pow(worker->dataset[i],2) + worker->dataset[i];
        break;
    case 1:  // Koza-2
        worker->dataset_cols = ncols = 2;
        worker->dataset_rows = nrows = 20;
        worker->dataset = new double[nrows*ncols];
        // Inputs
        for(j = 0;j < ncols-1;j++) {
            for(i = 0;i < nrows;i++) {
                worker->dataset[(j*nrows)+i] = rollUniform(-1,1);
              }
          }
        // Output
        for(i = 0;i < nrows;i++) worker->dataset[((ncols-1)*nrows)+i] = pow(worker->dataset[i],5) - 2*pow(worker->dataset[i],3) + worker->dataset[i];
      break;
    case 2:  // Koza-3
        worker->dataset_cols = ncols = 2;
        worker->dataset_rows = nrows = 20;
        worker->dataset = new double[nrows*ncols];
        // Inputs
        for(j = 0;j < ncols-1;j++) {
            for(i = 0;i < nrows;i++) {
                worker->dataset[(j*nrows)+i] = rollUniform(-1,1);
              }
          }
        // Output
        for(i = 0;i < nrows;i++) worker->dataset[((ncols-1)*nrows)+i] = pow(worker->dataset[i],6) - 2*pow(worker->dataset[i],4) + pow(worker->dataset[i],2);
      break;
    }
  // Populate grid
  for(i = 0;i < nrows;i++) {
      QList<QStandardItem*> rowitems;
      for(j = 0;j < ncols;j++) {
          QStandardItem *item = new QStandardItem(QString::number(worker->dataset[(j*nrows)+i]));
          rowitems.append(item);
        }
      model->appendRow(rowitems);
      rowitems.clear();
    }
}

double MainWindow::rollUniform(double inLow, double inUp)
{
  assert(inLow <= inUp);
  return inLow + ((inUp-inLow) * double(std::rand()) / double(RAND_MAX+1.0));
}
