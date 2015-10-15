#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);

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
    emit send_data(GPparam);
    hide();
}
