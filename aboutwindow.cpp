#include "aboutwindow.h"
#include "ui_aboutwindow.h"

aboutwindow::aboutwindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::aboutwindow)
{
  ui->setupUi(this);
}

aboutwindow::~aboutwindow()
{
  delete ui;
}
