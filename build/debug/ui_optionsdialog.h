/********************************************************************************
** Form generated from reading UI file 'optionsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSDIALOG_H
#define UI_OPTIONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OptionsDialog
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QSpinBox *spinBox;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_2;
    QLabel *label_4;
    QLineEdit *lineEdit_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLabel *label_11;
    QLineEdit *lineEdit_10;
    QVBoxLayout *verticalLayout;
    QLabel *label_12;
    QTableView *functionsView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OptionsDialog)
    {
        if (OptionsDialog->objectName().isEmpty())
            OptionsDialog->setObjectName(QStringLiteral("OptionsDialog"));
        OptionsDialog->resize(556, 437);
        gridLayout_2 = new QGridLayout(OptionsDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(OptionsDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_3 = new QLineEdit(OptionsDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 3, 1, 1, 1);

        lineEdit_7 = new QLineEdit(OptionsDialog);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 7, 1, 1, 1);

        lineEdit = new QLineEdit(OptionsDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label = new QLabel(OptionsDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(OptionsDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_4 = new QLineEdit(OptionsDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 4, 1, 1, 1);

        lineEdit_5 = new QLineEdit(OptionsDialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 5, 1, 1, 1);

        label_3 = new QLabel(OptionsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(OptionsDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        spinBox = new QSpinBox(OptionsDialog);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(10000);
        spinBox->setValue(100);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);

        label_10 = new QLabel(OptionsDialog);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 9, 0, 1, 1);

        label_9 = new QLabel(OptionsDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        label_2 = new QLabel(OptionsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(OptionsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_6 = new QLineEdit(OptionsDialog);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 6, 1, 1, 1);

        label_7 = new QLabel(OptionsDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_8 = new QLabel(OptionsDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        lineEdit_8 = new QLineEdit(OptionsDialog);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout->addWidget(lineEdit_8, 8, 1, 1, 1);

        lineEdit_9 = new QLineEdit(OptionsDialog);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        gridLayout->addWidget(lineEdit_9, 9, 1, 1, 1);

        label_11 = new QLabel(OptionsDialog);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 10, 0, 1, 1);

        lineEdit_10 = new QLineEdit(OptionsDialog);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));

        gridLayout->addWidget(lineEdit_10, 10, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_12 = new QLabel(OptionsDialog);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout->addWidget(label_12);

        functionsView = new QTableView(OptionsDialog);
        functionsView->setObjectName(QStringLiteral("functionsView"));

        verticalLayout->addWidget(functionsView);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(OptionsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(OptionsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(OptionsDialog);
    } // setupUi

    void retranslateUi(QDialog *OptionsDialog)
    {
        OptionsDialog->setWindowTitle(QApplication::translate("OptionsDialog", "Options & parameters...", 0));
        label_6->setText(QApplication::translate("OptionsDialog", "Maximum tree initialization depth", 0));
        lineEdit_3->setText(QApplication::translate("OptionsDialog", "17", 0));
        lineEdit_7->setText(QApplication::translate("OptionsDialog", "0.9", 0));
        lineEdit->setText(QApplication::translate("OptionsDialog", "100", 0));
        label->setText(QApplication::translate("OptionsDialog", "Generations number", 0));
        label_5->setText(QApplication::translate("OptionsDialog", "Minimum tree initialization depth", 0));
        lineEdit_4->setText(QApplication::translate("OptionsDialog", "2", 0));
        lineEdit_5->setText(QApplication::translate("OptionsDialog", "5", 0));
        label_3->setText(QApplication::translate("OptionsDialog", "Tournament size", 0));
        lineEdit_2->setText(QApplication::translate("OptionsDialog", "10", 0));
        label_10->setText(QApplication::translate("OptionsDialog", "Mutation max regeneration depth", 0));
        label_9->setText(QApplication::translate("OptionsDialog", "Mutation probability", 0));
        label_2->setText(QApplication::translate("OptionsDialog", "Population size", 0));
        label_4->setText(QApplication::translate("OptionsDialog", "Maximum tree depth", 0));
        lineEdit_6->setText(QApplication::translate("OptionsDialog", "0.9", 0));
        label_7->setText(QApplication::translate("OptionsDialog", "Crossover probability", 0));
        label_8->setText(QApplication::translate("OptionsDialog", "Crossover distribution probability", 0));
        lineEdit_8->setText(QApplication::translate("OptionsDialog", "0.05", 0));
        lineEdit_9->setText(QApplication::translate("OptionsDialog", "5", 0));
        label_11->setText(QApplication::translate("OptionsDialog", "Random number generator seed value", 0));
        lineEdit_10->setText(QApplication::translate("OptionsDialog", "0", 0));
        label_12->setText(QApplication::translate("OptionsDialog", "Functions set", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsDialog: public Ui_OptionsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSDIALOG_H
