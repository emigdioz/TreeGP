/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "graphwidget.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionE_xit;
    QAction *actionRun;
    QAction *actionOptions;
    QAction *actionLoad_file;
    QAction *actionBenchmarks;
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QSplitter *splitter_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QProgressBar *progressBar;
    QSplitter *splitter;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_3;
    QCustomPlot *sizePlot;
    QCustomPlot *outputPlot;
    GraphWidget *treeGraph;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QTableView *tableView;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuDatasets;
    QMenu *menu_Tools;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(956, 783);
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QStringLiteral("actionE_xit"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionRun->setEnabled(false);
        actionOptions = new QAction(MainWindow);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionLoad_file = new QAction(MainWindow);
        actionLoad_file->setObjectName(QStringLiteral("actionLoad_file"));
        actionBenchmarks = new QAction(MainWindow);
        actionBenchmarks->setObjectName(QStringLiteral("actionBenchmarks"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        verticalLayoutWidget_2 = new QWidget(splitter_2);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(verticalLayoutWidget_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_2->addWidget(textEdit);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        progressBar = new QProgressBar(verticalLayoutWidget_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        splitter_2->addWidget(verticalLayoutWidget_2);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        gridLayoutWidget = new QWidget(splitter);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayout_3 = new QGridLayout(gridLayoutWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        sizePlot = new QCustomPlot(gridLayoutWidget);
        sizePlot->setObjectName(QStringLiteral("sizePlot"));
        sizePlot->setMinimumSize(QSize(350, 200));

        gridLayout_3->addWidget(sizePlot, 1, 1, 1, 1);

        outputPlot = new QCustomPlot(gridLayoutWidget);
        outputPlot->setObjectName(QStringLiteral("outputPlot"));
        outputPlot->setMinimumSize(QSize(350, 200));

        gridLayout_3->addWidget(outputPlot, 0, 1, 1, 1);

        treeGraph = new GraphWidget(gridLayoutWidget);
        treeGraph->setObjectName(QStringLiteral("treeGraph"));
        treeGraph->setMaximumSize(QSize(500, 16777215));

        gridLayout_3->addWidget(treeGraph, 0, 0, 1, 1);

        splitter->addWidget(gridLayoutWidget);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_2->addWidget(lineEdit_3, 3, 1, 1, 1);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 1, 1, 1, 1);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 2, 1, 1, 1);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(70);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        splitter->addWidget(verticalLayoutWidget);
        splitter_2->addWidget(splitter);

        gridLayout_4->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 956, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuDatasets = new QMenu(menu_File);
        menuDatasets->setObjectName(QStringLiteral("menuDatasets"));
        menu_Tools = new QMenu(menubar);
        menu_Tools->setObjectName(QStringLiteral("menu_Tools"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Tools->menuAction());
        menu_File->addAction(actionE_xit);
        menu_File->addAction(menuDatasets->menuAction());
        menuDatasets->addAction(actionLoad_file);
        menuDatasets->addSeparator();
        menuDatasets->addAction(actionBenchmarks);
        menu_Tools->addAction(actionOptions);
        toolBar->addAction(actionRun);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TreeGP", 0));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0));
        actionRun->setText(QApplication::translate("MainWindow", "Run...", 0));
        actionOptions->setText(QApplication::translate("MainWindow", "Options...", 0));
        actionLoad_file->setText(QApplication::translate("MainWindow", "Load file...", 0));
        actionBenchmarks->setText(QApplication::translate("MainWindow", "Benchmarks", 0));
        label_6->setText(QApplication::translate("MainWindow", "Progress", 0));
        label_3->setText(QApplication::translate("MainWindow", "Data", 0));
        label_4->setText(QApplication::translate("MainWindow", "Instances", 0));
        label_2->setText(QApplication::translate("MainWindow", "Output variable column", 0));
        label->setText(QApplication::translate("MainWindow", "Input variables columns", 0));
        label_5->setText(QApplication::translate("MainWindow", "Training/Testing (75/30)", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuDatasets->setTitle(QApplication::translate("MainWindow", "Datasets", 0));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
