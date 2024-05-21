/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_19;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QTableView *tableView;
    QSplitter *splitter;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QPushButton *pb_addRow;
    QPushButton *pb_removeRow;
    QPushButton *pb_editCell;
    QPushButton *pb_clearData;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_18;
    QGridLayout *gridLayout_17;
    QSpacerItem *verticalSpacer_6;
    QGridLayout *gridLayout_16;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_11;
    QSpacerItem *spacer;
    QGridLayout *gridLayout_6;
    QRadioButton *rb_hierarchy;
    QRadioButton *rb_medoids;
    QRadioButton *rb_means;
    QSpacerItem *horizontalSpacer_8;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_13;
    QSpacerItem *horizontalSpacer_5;
    QGridLayout *gridLayout_12;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pb_clusterize;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_2;
    QGridLayout *gridLayout_10;
    QSplitter *splitter_2;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_10;
    QSpacerItem *verticalSpacer_2;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuDocumentation;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1179, 774);
        QFont font;
        font.setFamilies({QString::fromUtf8("Calibri")});
        font.setPointSize(10);
        font.setBold(false);
        font.setStrikeOut(false);
        font.setKerning(true);
        MainWindow->setFont(font);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Calibri")});
        actionOpen->setFont(font1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName("actionSave_as");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_19 = new QGridLayout(tab);
        gridLayout_19->setObjectName("gridLayout_19");
        splitter_4 = new QSplitter(tab);
        splitter_4->setObjectName("splitter_4");
        splitter_4->setOrientation(Qt::Horizontal);
        splitter_4->setHandleWidth(2);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setHandleWidth(2);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName("layoutWidget");
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Calibri")});
        font2.setPointSize(15);
        font2.setWeight(QFont::Medium);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        label->setFont(font2);

        gridLayout_5->addWidget(label, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        splitter_3->addWidget(layoutWidget);
        tableView = new QTableView(splitter_3);
        tableView->setObjectName("tableView");
        tableView->setMinimumSize(QSize(900, 600));
        splitter_3->addWidget(tableView);
        splitter_4->addWidget(splitter_3);
        splitter = new QSplitter(splitter_4);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(2);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        pb_addRow = new QPushButton(layoutWidget1);
        pb_addRow->setObjectName("pb_addRow");
        pb_addRow->setMinimumSize(QSize(128, 32));
        pb_addRow->setMaximumSize(QSize(128, 32));

        gridLayout_2->addWidget(pb_addRow, 0, 0, 1, 1);

        pb_removeRow = new QPushButton(layoutWidget1);
        pb_removeRow->setObjectName("pb_removeRow");
        pb_removeRow->setMinimumSize(QSize(128, 32));
        pb_removeRow->setMaximumSize(QSize(128, 32));

        gridLayout_2->addWidget(pb_removeRow, 1, 0, 1, 1);

        pb_editCell = new QPushButton(layoutWidget1);
        pb_editCell->setObjectName("pb_editCell");
        pb_editCell->setMinimumSize(QSize(128, 32));
        pb_editCell->setMaximumSize(QSize(128, 32));

        gridLayout_2->addWidget(pb_editCell, 2, 0, 1, 1);

        pb_clearData = new QPushButton(layoutWidget1);
        pb_clearData->setObjectName("pb_clearData");
        pb_clearData->setMinimumSize(QSize(128, 32));
        pb_clearData->setMaximumSize(QSize(128, 32));

        gridLayout_2->addWidget(pb_clearData, 3, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        splitter->addWidget(layoutWidget1);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName("layoutWidget2");
        gridLayout_18 = new QGridLayout(layoutWidget2);
        gridLayout_18->setObjectName("gridLayout_18");
        gridLayout_18->setContentsMargins(0, 0, 0, 0);
        gridLayout_17 = new QGridLayout();
        gridLayout_17->setObjectName("gridLayout_17");
        verticalSpacer_6 = new QSpacerItem(20, 28, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_17->addItem(verticalSpacer_6, 0, 0, 1, 1);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName("gridLayout_16");
        horizontalSpacer = new QSpacerItem(13, 17, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_16->addItem(horizontalSpacer, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName("label_2");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Calibri")});
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setStrikeOut(false);
        font3.setKerning(true);
        label_2->setFont(font3);

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(184, 13, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 1, 0, 1, 1);


        gridLayout_16->addLayout(gridLayout_4, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(13, 17, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout_17->addLayout(gridLayout_16, 1, 0, 1, 1);


        gridLayout_18->addLayout(gridLayout_17, 0, 0, 1, 1);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName("gridLayout_15");
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName("gridLayout_11");
        spacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_11->addItem(spacer, 0, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        rb_hierarchy = new QRadioButton(layoutWidget2);
        rb_hierarchy->setObjectName("rb_hierarchy");

        gridLayout_6->addWidget(rb_hierarchy, 0, 0, 1, 1);

        rb_medoids = new QRadioButton(layoutWidget2);
        rb_medoids->setObjectName("rb_medoids");

        gridLayout_6->addWidget(rb_medoids, 1, 0, 1, 1);

        rb_means = new QRadioButton(layoutWidget2);
        rb_means->setObjectName("rb_means");

        gridLayout_6->addWidget(rb_means, 2, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_6, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_8, 0, 2, 1, 1);


        gridLayout_15->addLayout(gridLayout_11, 0, 0, 1, 1);

        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName("gridLayout_14");
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName("gridLayout_13");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName("gridLayout_12");
        verticalSpacer_4 = new QSpacerItem(18, 21, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_12->addItem(verticalSpacer_4, 0, 0, 1, 1);

        pb_clusterize = new QPushButton(layoutWidget2);
        pb_clusterize->setObjectName("pb_clusterize");
        pb_clusterize->setMinimumSize(QSize(128, 32));
        pb_clusterize->setMaximumSize(QSize(128, 32));

        gridLayout_12->addWidget(pb_clusterize, 1, 0, 1, 1);


        gridLayout_13->addLayout(gridLayout_12, 0, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_6, 0, 2, 1, 1);


        gridLayout_14->addLayout(gridLayout_13, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 18, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_14->addItem(verticalSpacer_5, 1, 0, 1, 1);


        gridLayout_15->addLayout(gridLayout_14, 1, 0, 1, 1);


        gridLayout_18->addLayout(gridLayout_15, 1, 0, 1, 1);

        splitter->addWidget(layoutWidget2);
        splitter_4->addWidget(splitter);

        gridLayout_19->addWidget(splitter_4, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        gridLayout_10 = new QGridLayout(tab_2);
        gridLayout_10->setObjectName("gridLayout_10");
        splitter_2 = new QSplitter(tab_2);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Horizontal);
        layoutWidget3 = new QWidget(splitter_2);
        layoutWidget3->setObjectName("layoutWidget3");
        gridLayout_9 = new QGridLayout(layoutWidget3);
        gridLayout_9->setObjectName("gridLayout_9");
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName("gridLayout_7");
        pushButton_8 = new QPushButton(layoutWidget3);
        pushButton_8->setObjectName("pushButton_8");

        gridLayout_7->addWidget(pushButton_8, 0, 0, 1, 1);

        pushButton_9 = new QPushButton(layoutWidget3);
        pushButton_9->setObjectName("pushButton_9");

        gridLayout_7->addWidget(pushButton_9, 1, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_7, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_8->addItem(verticalSpacer, 1, 0, 1, 1);

        pushButton_10 = new QPushButton(layoutWidget3);
        pushButton_10->setObjectName("pushButton_10");

        gridLayout_8->addWidget(pushButton_10, 2, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_8, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_9->addItem(verticalSpacer_2, 1, 0, 1, 1);

        splitter_2->addWidget(layoutWidget3);
        graphicsView = new QGraphicsView(splitter_2);
        graphicsView->setObjectName("graphicsView");
        splitter_2->addWidget(graphicsView);

        gridLayout_10->addWidget(splitter_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1179, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuDocumentation = new QMenu(menubar);
        menuDocumentation->setObjectName("menuDocumentation");
        menuDocumentation->setFont(font);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuDocumentation->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("MainWindow", "Save as ...", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Music & Mental health ", nullptr));
        pb_addRow->setText(QCoreApplication::translate("MainWindow", " Add row", nullptr));
        pb_removeRow->setText(QCoreApplication::translate("MainWindow", "Remove row", nullptr));
        pb_editCell->setText(QCoreApplication::translate("MainWindow", "Edit cell", nullptr));
        pb_clearData->setText(QCoreApplication::translate("MainWindow", "Clear data", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select clusterization method", nullptr));
        rb_hierarchy->setText(QCoreApplication::translate("MainWindow", "Sort by Hierarchy", nullptr));
        rb_medoids->setText(QCoreApplication::translate("MainWindow", "Sort by Medoids", nullptr));
        rb_means->setText(QCoreApplication::translate("MainWindow", "Sort by Means", nullptr));
        pb_clusterize->setText(QCoreApplication::translate("MainWindow", "Clusterize", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", " Save graph as .jpg file", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Save results as .txt file", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Compare methods", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuDocumentation->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
