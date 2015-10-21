#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->functionsView->setModel(model);

    QStringList list;
    QStandardItem *newItem = 0;
    list.append("Enabled");
    list.append("Description");
    model->setHorizontalHeaderLabels(list);

    newItem = new QStandardItem("+");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Add");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("-");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Substract");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("*");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Multiply");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("/");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Divide");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("Sin");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Sine");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("Cos");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Cosine");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("Log");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Logarithm");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

    newItem = new QStandardItem("Exp");
    newItem->setCheckable(true);
    newItem->setCheckState(Qt::Checked);
    standardItemList.append(newItem);
    newItem = new QStandardItem("Exponential");
    standardItemList.append(newItem);
    model->appendRow(standardItemList);
    standardItemList.clear();

}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::write_gen(int value)
{
    ui->spinBox->setValue(value);
}


//void OptionsDialog::send_data(QString &output,int choice)
//{
//    switch(choice){
//        case 1: // Number of generations
//            output = QString::number(ui->spinBox->value());
//            break;
//    }
//}

void OptionsDialog::read_values(QString &output,int choice)
{
    switch(choice){
            case 1: // Number of generations
                output = QString::number(ui->spinBox->value());
                break;
        }
}

void OptionsDialog::accept()
{
    Options GPparam;

    GPparam.ngen = ui->spinBox->value();
    GPparam.popsize = ui->lineEdit->text().toInt();
    GPparam.tournamentsize = ui->lineEdit_2->text().toInt();
    GPparam.maxdepth = ui->lineEdit_3->text().toInt();
    GPparam.mininitdepth = ui->lineEdit_4->text().toInt();
    GPparam.maxinitdepth = ui->lineEdit_5->text().toInt();
    GPparam.crossoverp = ui->lineEdit_6->text().toFloat();
    GPparam.crossoverdp = ui->lineEdit_7->text().toFloat();
    GPparam.mutationp = ui->lineEdit_8->text().toFloat();
    GPparam.mutationmaxr = ui->lineEdit_9->text().toInt();
    GPparam.randomseed = ui->lineEdit_10->text().toLong();
    QModelIndex index;
    for(int i=0;i<8;i++) {
      index = ui->functionsView->model()->index(i,0, QModelIndex());
      if(index.data(Qt::CheckStateRole) == Qt::Checked) GPparam.functionselection.push_back(true); else GPparam.functionselection.push_back(false);
    }
    emit send_data(GPparam);
    hide();
}
