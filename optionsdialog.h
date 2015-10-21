#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "worker.h"
#include <iostream>
#include <vector>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();
    void read_values(QString &output, int choice);
    typedef struct
    {
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
      unsigned long randomseed;
      std::vector<bool> functionselection;
    } Options;


private:
    Ui::OptionsDialog *ui;
    QStandardItemModel *model;
    QList<QStandardItem*> standardItemList;

public slots:
    void write_gen(int value);
    void accept();

signals:
    void send_data(OptionsDialog::Options data);
};

#endif // OPTIONSDIALOG_H

