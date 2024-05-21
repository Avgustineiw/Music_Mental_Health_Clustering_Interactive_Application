#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Core/respondent.h"
#include "Core/readFromCSV.h"
#include "Core/point.h"
#include "Core/header.h"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QPen>
#include <QGraphicsEllipseItem>

#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->tabWidget->setCurrentIndex(0);

  //set up model view
  pModel_    = new ModelView;
  pProxy_    = new ProxyModel;
  pDelegate_ = new RightAlignedDelegate;

  pProxy_->setSourceModel(pModel_);

  ui->tableView->setItemDelegate(pDelegate_);
  ui->tableView->setModel(pProxy_);
  ui->tableView->setSortingEnabled(true);
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //set up graphics view
  pScene_ = new QGraphicsScene(this);
  pScene_->setSceneRect(0, 0, 950, 700);
  // цвет сцены 30, 30, 30
  ui->graphicsView->setScene(pScene_);
  ui->graphicsView->setFixedSize(pScene_->sceneRect().size().toSize());



  //set up menu
  //ui->menubar->actions().at(1)->menu();
  QMenu* menuFile = ui->menubar->findChild<QMenu*>("menuFile");//("actionSave");

  if (menuFile) {
    QAction* save = menuFile->actions().at(1);
    save->setEnabled(false);
    //TODO
  }
  //set up buttons
  selectedRb_ = nullptr;

  ui->pb_removeRow->setEnabled(false);
  ui->pb_editCell->setEnabled(false);
  ui->pb_clearData->setEnabled(false);
  ui->pb_clusterize->setEnabled(false);

  //signals and slots
  connect(ui->pb_addRow,     &QPushButton::clicked, this, &MainWindow::addRow);
  connect(ui->pb_removeRow,  &QPushButton::clicked, this, &MainWindow::removeRow);
  connect(ui->pb_editCell,   &QPushButton::clicked, this, &MainWindow::editCell);
  connect(ui->pb_clearData,  &QPushButton::clicked, this, &MainWindow::clearData);
  connect(ui->pb_clusterize, &QPushButton::clicked, this, &MainWindow::clusterize);

  connect(ui->rb_hierarchy, &QRadioButton::clicked, this, &MainWindow::setClusterization);
  connect(ui->rb_means,     &QRadioButton::clicked, this, &MainWindow::setClusterization);
  connect(ui->rb_medoids,   &QRadioButton::clicked, this, &MainWindow::setClusterization);

  connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::editClicked);
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::on_actionOpen_triggered()
{
  INPUT_PATH = QFileDialog::getOpenFileName(this, "Open dataset", "", "CSV file (*.csv)");

  if (INPUT_PATH.isEmpty()) {
    return;
  }

  try {
    ModelView* newModel = new ModelView(INPUT_PATH);

    if (pModel_ != nullptr) {
      delete pModel_;
    }
    pModel_ = newModel;

    if (pModel_) {
//delete pProxy_;
//pProxy_ = new ProxyModel;

      ui->tableView->reset();
      pProxy_->setSourceModel(pModel_);
      ui->tableView->setModel(pProxy_);
      ui->tableView->setSortingEnabled(true);

      ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
      for (int i = 0; i < pModel_->rowCount(); ++i)
      {
        //ui->tableView->item
        //pModel_->index(i, 1)
      }

      ui->pb_removeRow->setEnabled(true);
      ui->pb_editCell->setEnabled(true);
      ui->pb_clearData->setEnabled(true);
    }

    InitializeProgram(INPUT_PATH);

    }
  catch (const std::invalid_argument& e) {
    QString e_msg = e.what();

    QMessageBox msgb;
    msgb.setText(e_msg + ": " + INPUT_PATH);
    msgb.exec();
  }
  catch (...) {
    // "Global" exception
  }
}


void MainWindow::addRow()
{

}

void MainWindow::removeRow()
{

}

void MainWindow::editCell()
{

}

void MainWindow::editClicked(const QModelIndex& ind)
{
  int row = pProxy_->mapToSource(ind).row();
  //pModel_->set
  size_t idx = ui->tableView->selectionModel()->currentIndex().row();
  for (int i = 0; i < row; ++i)
    {

    }
}

void MainWindow::clearData()
{

}

void MainWindow::clusterize()
{
  if (!selectedRb_) {
    return;
  }
  QString type = selectedRb_->text();

  if (type == "Sort by Hierarchy") {

  }
  else if (type == "Sort by Medoids") {

  }
  else {
    //pClusterType_ = new kMeans(pModel_->getData());
    clusterData_.reserve(100);
    int maxRange = 200;
    for (size_t i = 0; i < 100; ++i)
    {
      int signX = (rand() % 2 == 0) ? 1 : -1;
      int signY = (rand() % 2 == 0) ? 1 : -1;

      clusterData_.push_back({(rand() % maxRange) * signX, (rand() % maxRange) * signY, (i + 1) % 5, i});

    }
  }
  //TODO
  //pClusterType_->Run();
  if (clusterData_.isEmpty()) {
      //message box - > error because data is empty
  }
  else {
    displayClusterData();
    ui->tabWidget->setCurrentIndex(1);
  }

  selectedRb_->setAutoExclusive(false);
  selectedRb_->setChecked(false);
  selectedRb_ = nullptr;
  ui->pb_clusterize->setEnabled(false);
}


void MainWindow::setClusterization()
{
  QRadioButton* rb = dynamic_cast<QRadioButton*>(sender());

  if (!rb) {
    return;
  }
  if (selectedRb_) {
    selectedRb_->setChecked(false);
  }
  selectedRb_ = rb;

  ui->pb_clusterize->setEnabled(true);
}

void MainWindow::displayClusterData()
{
  pScene_->clear();

  size_t height = pScene_->height();
  size_t width  = pScene_->width();

  for (size_t i = 0 ; i < clusterData_.size(); ++i)
  {
    QGraphicsEllipseItem* point = new QGraphicsEllipseItem(0, 0, 10, 10);
    QPen pen = QPen(QColor(152, 69, 191));
    if (clusterData_[i][2] == 0)
    {
      pen = QPen(QColor(71, 69, 191));
    }
    else if  (clusterData_[i][2] == 1)
    {
      pen = QPen(QColor(69, 191, 132));
    }
    else if (clusterData_[i][2] == 2)
    {
      pen = QPen(QColor(191, 187, 69));
    }
    point->setPen(pen);
    point->setPos(width / 2  + clusterData_[i][0].toInt(),
                  height / 2 + clusterData_[i][1].toInt());
    pScene_->addItem(point);
  }
}



