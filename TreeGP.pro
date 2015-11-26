TEMPLATE = app
CONFIG      += qt warn_on thread
QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

unix:!macx { LIBS += -L../../lib -lGLU -L/home/emigdio/git_repositories/openblas/lib/ -lopenblas -lpthread}

macx: LIBS += -L../../lib -framework OpenGL

linux-g++:QMAKE_CXXFLAGS += -fno-exceptions

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1

INCLUDEPATH    += ./qwtplot3d/include ./klfbackend/ ./levmar /home/emigdio/git_repositories/openblas/include/

# KLF backend versions
KLF_BACKEND_VERSION = 3.2.8

DEFINES +=KLF_VERSION_STRING=\\\"$$KLF_BACKEND_VERSION\\\" \
        KLF_SRC_BUILD
        #HAVE_LAPACK \

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Primitive.cpp \
    Puppy.cpp \
    Tree.cpp \
    SymbRegMain.cpp \
    SymbRegPrimits.cpp \
    worker.cpp \
    qcustomplot.cpp \
    infix.cpp \
    edge.cpp \
    graphwidget.cpp \
    node.cpp \
    qwtplot3d/qwt3d_appearance.cpp \
    qwtplot3d/qwt3d_autoscaler.cpp \
    qwtplot3d/qwt3d_axis.cpp \
    qwtplot3d/qwt3d_color_std.cpp \
    qwtplot3d/qwt3d_colorlegend.cpp \
    qwtplot3d/qwt3d_coordsys.cpp \
    qwtplot3d/qwt3d_data.cpp \
    qwtplot3d/qwt3d_drawable.cpp \
    qwtplot3d/qwt3d_enrichment_std.cpp \
    qwtplot3d/qwt3d_extglwidget.cpp \
    qwtplot3d/qwt3d_function.cpp \
    qwtplot3d/qwt3d_graphplot.cpp \
    qwtplot3d/qwt3d_gridmapping.cpp \
    qwtplot3d/qwt3d_gridplot.cpp \
    qwtplot3d/qwt3d_io.cpp \
    qwtplot3d/qwt3d_io_reader.cpp \
    qwtplot3d/qwt3d_label.cpp \
    qwtplot3d/qwt3d_lighting.cpp \
    qwtplot3d/qwt3d_meshplot.cpp \
    qwtplot3d/qwt3d_parametricsurface.cpp \
    qwtplot3d/qwt3d_plot3d.cpp \
    qwtplot3d/qwt3d_scale.cpp \
    qwtplot3d/qwt3d_surfaceplot.cpp \
    qwtplot3d/qwt3d_types.cpp \
    qwtplot3d/qwt3d_volumeplot.cpp \
    benchmark.cpp \
    klfbackend/klfbackend.cpp \
    klfbackend/klfblockprocess.cpp \
    klfbackend/klfdebug.cpp \
    klfbackend/klfdefs.cpp \
    klfbackend/klfpreviewbuilderthread.cpp \
    aboutwindow.cpp \
    levmar/Axb.c \
    levmar/Axb_core.c \
    levmar/lm.c \
    levmar/lm_core.c \
    levmar/lmbc.c \
    levmar/lmbc_core.c \
    levmar/lmblec.c \
    levmar/lmblec_core.c \
    levmar/lmbleic.c \
    levmar/lmbleic_core.c \
    levmar/lmlec.c \
    levmar/lmlec_core.c \
    levmar/misc.c \
    levmar/misc_core.c

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
    qcustomplot.h \
    matrix.h \
    infix.h \
    edge.h \
    graphwidget.h \
    node.h \
    qwtplot3d/include/qwt3d_appearance.h \
    qwtplot3d/include/qwt3d_autoscaler.h \
    qwtplot3d/include/qwt3d_axis.h \
    qwtplot3d/include/qwt3d_color.h \
    qwtplot3d/include/qwt3d_color_std.h \
    qwtplot3d/include/qwt3d_colorlegend.h \
    qwtplot3d/include/qwt3d_coordsys.h \
    qwtplot3d/include/qwt3d_data.h \
    qwtplot3d/include/qwt3d_drawable.h \
    qwtplot3d/include/qwt3d_enrichment.h \
    qwtplot3d/include/qwt3d_enrichment_std.h \
    qwtplot3d/include/qwt3d_extglwidget.h \
    qwtplot3d/include/qwt3d_function.h \
    qwtplot3d/include/qwt3d_global.h \
    qwtplot3d/include/qwt3d_graphplot.h \
    qwtplot3d/include/qwt3d_gridmapping.h \
    qwtplot3d/include/qwt3d_gridplot.h \
    qwtplot3d/include/qwt3d_helper.h \
    qwtplot3d/include/qwt3d_io.h \
    qwtplot3d/include/qwt3d_io_reader.h \
    qwtplot3d/include/qwt3d_label.h \
    qwtplot3d/include/qwt3d_mapping.h \
    qwtplot3d/include/qwt3d_meshplot.h \
    qwtplot3d/include/qwt3d_openglhelper.h \
    qwtplot3d/include/qwt3d_parametricsurface.h \
    qwtplot3d/include/qwt3d_plot3d.h \
    qwtplot3d/include/qwt3d_portability.h \
    qwtplot3d/include/qwt3d_scale.h \
    qwtplot3d/include/qwt3d_surfaceplot.h \
    qwtplot3d/include/qwt3d_types.h \
    qwtplot3d/include/qwt3d_valueptr.h \
    qwtplot3d/include/qwt3d_volumeplot.h \
    klfbackend/klfbackend.h \
    klfbackend/klfblockprocess.h \
    klfbackend/klfdebug.h \
    klfbackend/klfdefs.h \
    klfbackend/klfpreviewbuilderthread.h \
    klfbackend/klfqt34common.h \
    aboutwindow.h \
    levmar/compiler.h \
    levmar/levmar.h \
    levmar/lm.h \
    levmar/misc.h

FORMS += \
    mainwindow.ui \
    aboutwindow.ui

RESOURCES += \
    images.qrc
