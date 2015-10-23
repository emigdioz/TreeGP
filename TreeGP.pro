TEMPLATE = app

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Primitive.cpp \
    Puppy.cpp \
    Tree.cpp \
    SymbRegMain.cpp \
    SymbRegPrimits.cpp \
    worker.cpp \
    optionsdialog.cpp \
    qcustomplot.cpp \
    infix.cpp \
    edge.cpp \
    graphwidget.cpp \
    node.cpp

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainwindow.h \
    Context.hpp \
    Primitive.hpp \
    PrimitiveHandle.hpp \
    PrimitiveInline.hpp \
    Puppy.hpp \
    Randomizer.hpp \
    TokenT.hpp \
    Tree.hpp \
    SymbRegPrimits.hpp \
    worker.h \
    optionsdialog.h \
    qcustomplot.h \
    matrix.h \
    infix.h \
    edge.h \
    graphwidget.h \
    node.h

FORMS += \
    mainwindow.ui \
    optionsdialog.ui
