QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    modelview.cpp \
    proxymodel.cpp \
    rightaligneddelegate.cpp

HEADERS += \
    Core/k-means.h \
    Core/header.h \
    Core/point.h \
    Core/silhouette.h \
    Core/logger.h \
    Core/point.h \
    Core/readFromCSV.h \
    Core/respondent.h \
    Core/respondentToPoint.h \
    Core/silhouette.h \
    Core/clusteringAlgorithm.h \
    Core/clusteringResult.h \
    Core/k-medoids.h \
    Core/getCurrentTime.h \\
    Core/getSetting.h \\
    mainwindow.h \\
    modelview.h \\
    proxymodel.h \\
    rightaligneddelegate.h
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
