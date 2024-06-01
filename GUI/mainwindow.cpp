#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Core/point.h"
#include "Core/header.h"
#include "Core/clusteringAlgorithm.h"
#include "Core/k-means.h"
#include "Core/k-medoids.h"
#include "Core/header.h"
#include "Core/silhouette.h"
#include "Core/getCurrentTime.h"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QPen>
#include <QApplication>

#include <QGraphicsEllipseItem>
#include "clusterpoint.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  //if (SYSTEM == "Mac") {
      //INPUT_PATH = QDir::currentPath() + "/Source/music_health_data.csv"; //Mac
  // }
  // else if (SYSTEM == "Windows") {
      //INPUT_PATH = QCoreApplication::applicationDirPath() + "/Source/music_health_data.csv"; //Windows;
  // }

  INPUT_PATH = ":/dataset/Source/music_health_data.csv";

  ui->setupUi(this);

  ui->tabWidget->setCurrentIndex(0);

  //set up model view
  //pModel_        = new ModelView(INPUT_PATH);
  pModel_        = new ModelView(INPUT_PATH);

  pModel_->setHeader({"Age", "HPD", "Musician", "Frequency", "Anxiety", "Depression", "Insomnia", "OCD", "Effect"});

  pProxy_        = new ProxyModel;
  pDelegate_     = new RightAlignedDelegate;

  pModelCluster_ = new ModelView;

  pModelCluster_->setHeader({"X coordinate", "Y coordinate", "Cluster"});

  pProxyCluster_ = new ProxyModel;

  pProxy_->setSourceModel(pModel_);
  pProxyCluster_->setSourceModel(pModelCluster_);

  //tableView
  ui->tableView->setItemDelegate(pDelegate_);
  ui->tableView->setModel(pProxy_);
  ui->tableView->setSortingEnabled(true);
  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //tableView_clusterize
  ui->tableView_clusterize->reset();
  ui->tableView_clusterize->setModel(pProxyCluster_);
  ui->tableView_clusterize->setSortingEnabled(true);
  ui->tableView_clusterize->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  //set up graphics view
  pScene_ = new ClusterScene(this);
  pScene_->setSceneRect(0, 0, 850, 700);
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
  ui->le_numClusters->setText("2");
  ui->le_numIterations->setText("5");
  scaleX_ = 1;
  scaleY_ = 1;

  ui->pb_removeRow->setEnabled(false);
  ui->pb_editCell->setEnabled(false);
  ui->pb_clearData->setEnabled(false);
  ui->pb_clusterize->setEnabled(false);

  ui->pb_saveGraph->setEnabled(false);
  ui->pb_saveResults->setEnabled(false);

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

// void MainWindow::on_actionOpen_triggered()
// {
//   INPUT_PATH = QFileDialog::getOpenFileName(this, "Open dataset", "", "CSV file (*.csv)");


//   try {
//     ModelView* newModel = new ModelView(INPUT_PATH);

//     if (pModel_ != nullptr) {
//       delete pModel_;
//     }
//     newModel->setHeader({"Age", "HPD", "Musician", "Frequency", "Anxiety", "Depression", "Insomnia", "OCD", "Effect"});
//     pModel_ = newModel;

//     if (pModel_) {
// //delete pProxy_;
// //pProxy_ = new ProxyModel;

//       //tableView
//       ui->tableView->reset();
//       pProxy_->setSourceModel(pModel_);
//       ui->tableView->setModel(pProxy_);
//       ui->tableView->setSortingEnabled(true);
//       ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//       ui->pb_removeRow->setEnabled(true);
//       ui->pb_editCell->setEnabled(true);
//       ui->pb_clearData->setEnabled(true);
//     }

//   }
//   catch (const std::invalid_argument& e) {
//     QString e_msg = e.what();

//     QMessageBox msgb;
//     msgb.setText(e_msg + ": " + INPUT_PATH);
//     msgb.exec();
//   }
//   catch (...) {
//     // "Global" exception
//   }
// }


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
  //unsigned int idx = ui->tableView->selectionModel()->currentIndex().row();
  for (int i = 0; i < row; ++i)
    {

    }
}

void MainWindow::clearData()
{

}

void MainWindow::clusterize()
{
  try {
    dataPoints_ = InitializeProgram(INPUT_PATH.toStdString());
  }
  catch(const std::exception& e) {
    QMessageBox msgb;
    msgb.setText(QString::fromStdString(e.what()));
    msgb.exec();
    return;
  }

  if (!selectedRb_) {
    return;
  }
  QString type = selectedRb_->text();
  bool flag1 = false;
  bool flag2 = false;

  int32_t clusters   = ui->le_numClusters->text().toUInt(&flag1);
  int32_t iterations = ui->le_numIterations->text().toUInt(&flag2);
  if (!flag1 || clusters > pModel_->rowCount() ||
      !flag2 || iterations > 1000) {
        QMessageBox msgb;
        msgb.setText("Invalid values");
        msgb.exec();
      return;
  }

  minX = INT_MAX;
  minY = INT_MAX;
  maxX = INT_MIN;
  maxY = INT_MIN;

  for (uint32_t i = 0; i < dataPoints_.size(); ++i)
  {
    int32_t currX = dataPoints_[i].GetX();
    int32_t currY = dataPoints_[i].GetY();
    if (currX < minX) {
      minX = currX;
    }
    if (currY < minY) {
      minY = currY;
    }
    if (currX > maxX) {
      maxX = currX;
    }
    if (currY > maxY) {
      maxY = currY;
    }
  }

  clusterBBox_.setRect(0, 0, maxX - minX, maxY - minY);
  uint32_t sceneX = pScene_->sceneRect().width();
  uint32_t sceneY = pScene_->sceneRect().height();

  scaleX_ = sceneX / static_cast<double>(clusterBBox_.width());
  scaleY_ = sceneY / static_cast<double>(clusterBBox_.height());

  if (type == "Sort by Hierarchy") {
    //pClusterType_ = new AAA(clusters, iterations);
    Last_Algorithm_Used = "Hierarchy";
  }
  else if (type == "Sort by Medoids") {
    pClusterType_ = new KMedoids(clusters, iterations);
    Last_Algorithm_Used = "K-Medoids";
  }
  else {
    pClusterType_ = new KMeans(clusters, iterations);
    Last_Algorithm_Used = "K-Means";
  }

  clusterData_ = pClusterType_->Run(dataPoints_);

  if (clusterData_.GetClustersSize() == 0) {
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

  ModelView* newModel2 = new ModelView(clusterData_.GetPoints());

  if (pModelCluster_ != nullptr) {
    delete pModelCluster_;
  }
  newModel2->setHeader({"X coordinate", "Y coordinate", "Cluster"});
  pModelCluster_ = newModel2;
  //newModel2->setHeader({"ID", "X coordinate", "Y coordinate", "Cluster"});

  if (pModelCluster_)
  {
    //tableView_clusterize
    ui->tableView_clusterize->reset();
    pProxyCluster_->setSourceModel(pModelCluster_);
    ui->tableView_clusterize->setModel(pProxyCluster_);
    ui->tableView_clusterize->setSortingEnabled(true);
    ui->tableView_clusterize->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }
  ui->pb_saveGraph->setEnabled(true);
  ui->pb_saveResults->setEnabled(true);
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
  const uint32_t offsetLine = 6;
  const uint32_t offset = 10;
  pScene_->clear();

  unsigned int height = pScene_->height();
  unsigned int width  = pScene_->width();

  QPen line_color = QColor(255, 255, 255, 50);


  for (qsizetype i = 1; i < 8; i++) {
    pScene_->addLine(0, height/7*i - offsetLine,
                     width, height/7*i - offsetLine,
                     line_color);
  }


  for (qsizetype i = 1; i < 5; i++) {
    pScene_->addLine(offsetLine + width/5*i, 0,
                     offsetLine + width/5*i, height,
                     line_color);
  }
  pScene_->addLine(offsetLine, 0,
                   offsetLine, height,
                   line_color);

  QGraphicsTextItem* text0 = pScene_->addText("0");
  text0->setPos(offsetLine, height - 28);
  QGraphicsTextItem* text1x = pScene_->addText(QString::number(maxX/5));
  QGraphicsTextItem* text2x = pScene_->addText(QString::number(maxX/5*2));
  QGraphicsTextItem* text3x = pScene_->addText(QString::number(maxX/5*3));
  QGraphicsTextItem* text4x = pScene_->addText(QString::number(maxX/5*4));
  QGraphicsTextItem* text5x = pScene_->addText(QString::number(maxX));
  text1x->setPos(width/5   - text1x->boundingRect().width() + 5, height - 28);
  text2x->setPos(width/5*2 - text2x->boundingRect().width() + 5, height - 28);
  text3x->setPos(width/5*3 - text3x->boundingRect().width() + 5, height - 28);
  text4x->setPos(width/5*4 - text4x->boundingRect().width() + 5, height - 28);
  text5x->setPos(width     - text5x->boundingRect().width()    , height - 28);

  QGraphicsTextItem* text1y = pScene_->addText(QString::number(maxY/7*6));
  QGraphicsTextItem* text2y = pScene_->addText(QString::number(maxY/7*5));
  QGraphicsTextItem* text3y = pScene_->addText(QString::number(maxY/7*4));
  QGraphicsTextItem* text4y = pScene_->addText(QString::number(maxY/7*3));
  QGraphicsTextItem* text5y = pScene_->addText(QString::number(maxY/7*2));
  QGraphicsTextItem* text6y = pScene_->addText(QString::number(maxY/7));
  QGraphicsTextItem* text7y = pScene_->addText(QString::number(maxY));
  text1y->setPos(offsetLine, height/7   + offsetLine - 10);
  text2y->setPos(offsetLine, height/7*2 + offsetLine - 10);
  text3y->setPos(offsetLine, height/7*3 + offsetLine - 10);
  text4y->setPos(offsetLine, height/7*4 + offsetLine - 10);
  text5y->setPos(offsetLine, height/7*5 + offsetLine - 10);
  text6y->setPos(offsetLine, height/7*6 + offsetLine - 10);
  text7y->setPos(offsetLine,              offsetLine - 5);

  for (qsizetype i = 0 ; i < clusterData_.GetClustersSize(); ++i)
  {
    int red   = rand() % 255;
    int blue  = rand() % 255;
    int green = rand() % 255;
    QPen pen = QPen(QColor(red, blue, green));

    for (qsizetype j = 0; j < clusterData_.GetCluster(i).GetClusterSize(); ++j) {
        CLusterPoint* point = new CLusterPoint(0, 0, 5, 5, clusterData_.GetCluster(i).GetPoint(j).GetPointId());
        point->setBrush(pen.brush());
        int x = clusterData_.GetCluster(i).GetPoint(j).GetX() * scaleX_;
        int y = clusterData_.GetCluster(i).GetPoint(j).GetY() * scaleY_;
        point->setPos(x + offset, height - y - offset);
        pScene_->addItem(point);
    }

    QGraphicsEllipseItem* cluster_point = new QGraphicsEllipseItem(0, 0, 15, 15);
    cluster_point->setBrush(pen.brush());
    int x = clusterData_.GetCluster(i).GetCentroidX() * scaleX_;
    int y = clusterData_.GetCluster(i).GetCentroidY() * scaleY_;
    cluster_point->setPos(x + offset, height - y - offset);
    pScene_->addItem(cluster_point);
  }
  return;
}

void MainWindow::on_pb_saveResults_clicked()
{
  if (SYSTEM == "Mac") {
    OUTPUT_PATH_TXT = QDir::currentPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "data.txt"; //Mac
    OUTPUT_PATH_CSV = QDir::currentPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "points.csv"; //Mac
  }
  else if (SYSTEM == "Windows") {
    OUTPUT_PATH_TXT = QCoreApplication::applicationDirPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "data.txt"; //Windows
    OUTPUT_PATH_CSV = QCoreApplication::applicationDirPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "points.csv"; //Windows
  }

  std::ofstream csv(OUTPUT_PATH_CSV);

  csv << "id, x, y, cluster" << '\n';

  for (qsizetype i = 0; i < clusterData_.GetPointsSize(); i++) {
        csv << clusterData_.GetPoint(i).GetPointId() << ",";
        csv << clusterData_.GetPoint(i).GetX() << ",";
        csv << clusterData_.GetPoint(i).GetY() << ",";
        csv << clusterData_.GetPoint(i).GetClusterId() << '\n';
  }

  csv.close();

  std::ofstream txt(OUTPUT_PATH_TXT);

  txt << "Quality of algorithm: " << Silhouette(clusterData_.GetClusters(), clusterData_.GetPoints()) << '\n';

  for (qsizetype i = 0; i < clusterData_.GetClustersSize(); i++) {
    txt << "Cluster: " << clusterData_.GetCluster(i).GetClusterId() << '\n';
    txt << "Size: " << clusterData_.GetCluster(i).GetClusterSize() << '\n';
    txt << "Centroid X: " << clusterData_.GetCluster(i).GetCentroidX() << '\n';
    txt << "Centroid Y: " << clusterData_.GetCluster(i).GetCentroidY() << "\n\n";
  }
}

void MainWindow::on_pb_saveGraph_clicked()
{
  if (SYSTEM == "Mac") {
    OUTPUT_PATH_PNG = QDir::currentPath() + "/Source/" + QString::fromStdString(currentDateTime())
                              + "_" + QString::fromStdString(Last_Algorithm_Used) + "_result.png"; //Mac
  }
  else if (SYSTEM == "Windows") {
    OUTPUT_PATH_PNG = QCoreApplication::applicationDirPath() + "/Source/" + QString::fromStdString(currentDateTime())
                              + "_" + QString::fromStdString(Last_Algorithm_Used) + "_result.png"; //Windows
  }
  QPixmap pixmap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
  pixmap.save(OUTPUT_PATH_PNG, "PNG", -1);
}

void MainWindow::on_pb_compare_clicked()
{
  //TODO: Handle errors
  QString name_1, name_2, name_3, best_alg;
  std::string val_1, val_2, val_3;

  for (qsizetype i = 0; i < 3; i++) {
    std::string line;
    QString INPUT_PATH_DATA = QFileDialog::getOpenFileName(this, "Open first data", "", "TXT file (*.txt)");
    std::ifstream data(INPUT_PATH_DATA.toStdString());

    getline(data, line);
    stringstream ss(line);

    switch (i) {
      case 0:
        name_1 = INPUT_PATH_DATA.mid(INPUT_PATH_DATA.lastIndexOf("/") + 1);
        for (qsizetype j = 0; j < 4; j++) {
          ss >> val_1;
        }
        break;
      case 1:
        name_2 = INPUT_PATH_DATA.mid(INPUT_PATH_DATA.lastIndexOf("/") + 1);
        for (qsizetype j = 0; j < 4; j++) {
          ss >> val_2;
        }
        break;
      case 2:
        name_3 = INPUT_PATH_DATA.mid(INPUT_PATH_DATA.lastIndexOf("/") + 1);
        for (qsizetype j = 0; j < 4; j++) {
          ss >> val_3;
        }
        break;
      }
  }

  double dval_1 = stod(val_1);
  double dval_2 = stod(val_2);
  double dval_3 = stod(val_3);

  if (max(max(dval_1, dval_2), dval_3) == dval_1) {
    best_alg = "first";
  }
  else if (max(max(dval_1, dval_2), dval_3) == dval_2) {
    best_alg = "second";
  }
  else if (max(max(dval_1, dval_2), dval_3) == dval_3) {
    best_alg = "third";
  }

  QMessageBox msgb;
  msgb.setText(name_1 + ": " + QString::fromStdString(val_1) + "\n\n" +
               name_2 + ": " + QString::fromStdString(val_2) + "\n\n" +
               name_3 + ": " + QString::fromStdString(val_3) + "\n\n");
  msgb.setInformativeText("The " + best_alg + " is the best, as it is closer to 1");
  //TODO: rescale the box
  msgb.exec();
}

void MainWindow::on_actionExit_triggered()
{
  QCoreApplication::quit();
}

