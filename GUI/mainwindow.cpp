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
#include "Core/getSetting.h"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QPen>

#include <QGraphicsEllipseItem>
#include "clusterpoint.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->tabWidget->setCurrentIndex(0);

  //set up model view
  pModel_        = new ModelView(QString("D:\\Project_cpp\\GUI\build\\Desktop_Qt_6_7_0_MinGW_64_bit-Debug\\debug\\Source\\music_health_data.csv"));

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
  ui->le_numClusters->setText("4");
  ui->le_numIterations->setText("4");
  scale_ = 1;

  ui->pb_removeRow->setEnabled(false);
  ui->pb_editCell->setEnabled(false);
  ui->pb_clearData->setEnabled(false);
  ui->pb_clusterize->setEnabled(false);

  ui->pb_saveGraph->setEnabled(false);
  ui->pb_saveResults->setEnabled(false);
  ui->pb_compare->setEnabled(false);

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
  // INPUT_PATH = QFileDialog::getOpenFileName(this, "Open dataset", "", "CSV file (*.csv)");
  INPUT_PATH = QString::fromStdString(GetSetting(SETTINGS_PATH.toStdString(), 0));

  if (INPUT_PATH.isEmpty()) {
    return;
  }

  try {
    ModelView* newModel = new ModelView(INPUT_PATH);

    if (pModel_ != nullptr) {
      delete pModel_;
    }
    newModel->setHeader({"Age", "HPD", "Musician", "Frequency", "Anxiety", "Depression", "Insomnia", "OCD", "Effect"});
    pModel_ = newModel;

    if (pModel_) {
//delete pProxy_;
//pProxy_ = new ProxyModel;

      //tableView
      ui->tableView->reset();
      pProxy_->setSourceModel(pModel_);
      ui->tableView->setModel(pProxy_);
      ui->tableView->setSortingEnabled(true);
      ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

      ui->pb_removeRow->setEnabled(true);
      ui->pb_editCell->setEnabled(true);
      ui->pb_clearData->setEnabled(true);
    }

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
  unsigned int idx = ui->tableView->selectionModel()->currentIndex().row();
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
  bool flag1 = false;
  bool flag2 = false;

  uint32_t clusters   = ui->le_numClusters->text().toUInt(&flag1);
  uint32_t iterations = ui->le_numClusters->text().toUInt(&flag2);
  if (!flag1 || clusters > pModel_->rowCount() ||
      !flag2 || iterations > 1000) {
      return;
  }
  dataPoints_ = InitializeProgram(INPUT_PATH.toStdString());
  int32_t minX = INT_MAX;
  int32_t minY = INT_MAX;
  int32_t maxX = INT_MIN;
  int32_t maxY = INT_MIN;

  for (qsizetype i = 0; i < dataPoints_.size(); ++i)
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
    if (currY > maxX) {
      maxY = currY;
    }
  }

  clusterBBox_.setRect(0, 0, maxX - minX, maxY - minY);
  uint32_t sceneX = pScene_->sceneRect().height();

  if (clusterBBox_.height() > clusterBBox_.width()) {
    scale_ = sceneX / static_cast<double>(clusterBBox_.width());
  }
  else {
    scale_ = sceneX / static_cast<double>(clusterBBox_.height());
  }
  scale_ /= 2.0;

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
  //std::vector<Point> dataPoints_ = convertModelDataToPoints(pModel_->getData());

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
  ui->pb_compare->setEnabled(true);
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

  unsigned int height = pScene_->height();
  unsigned int width  = pScene_->width();
  uint32_t offSetX = 00;
  uint32_t offSetY = 35;
  pScene_->addLine(offSetX, offSetY,
                   offSetX, height - offSetY,
                   QPen(Qt::white));
  pScene_->addLine(offSetX, height - offSetY,
                   width - offSetX, height - offSetY,
                   QPen(Qt::white));

  for (qsizetype i = 0 ; i < clusterData_.GetClustersSize(); ++i)
  {
    int red = rand() % 255;
    int blue = rand() % 255;
    int green = rand() % 255;
    QPen pen = QPen(QColor(red, blue, green));

    for (qsizetype j = 0; j < clusterData_.GetPointsSize(); ++j) {
      if (clusterData_.GetPoint(j).GetClusterId() == i + 1) {
        //TODO
        CLusterPoint* point = new CLusterPoint(0, 0, 5, 5, clusterData_.GetPoint(j).GetPointId());
        point->setBrush(pen.brush());
        int x = clusterData_.GetPoint(j).GetX() * scale_;
        int y = clusterData_.GetPoint(j).GetY() * scale_;
        point->setPos(width / 3  + x,
                      height / 4 + y);
        pScene_->addItem(point);
      }
    }

    QGraphicsEllipseItem* cluster_point = new QGraphicsEllipseItem(0, 0, 15, 15);
    cluster_point->setBrush(pen.brush());
    int x = clusterData_.GetCluster(i).GetCentroidX() * scale_;
    int y = clusterData_.GetCluster(i).GetCentroidY() * scale_;
    cluster_point->setPos(width / 3  + x,
                          height / 4 + y);
    pScene_->addItem(cluster_point);
  }
  return;
}

void MainWindow::on_pb_saveResults_clicked()
{
  std::string OUTPUT_PATH_CSV = QCoreApplication::applicationDirPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "points"; //Windows
  //std::string OUTPUT_PATH_TXT = QDir::currentPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "data"; //Mac

  std::ofstream csv(OUTPUT_PATH_CSV);

  csv << "id, x, y, cluster" << '\n';

  for (qsizetype i = 0; i < clusterData_.GetPointsSize(); i++) {
      csv << clusterData_.GetPoint(i).GetPointId() << ",";
      csv << clusterData_.GetPoint(i).GetX() << ",";
      csv << clusterData_.GetPoint(i).GetY() << ",";
      csv << clusterData_.GetPoint(i).GetClusterId() << '\n';
    }

  csv.close();

  std::string OUTPUT_PATH_TXT = QCoreApplication::applicationDirPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "data"; //Windows
  //std::string OUTPUT_PATH_TXT = QDir::currentPath().toStdString() + "/Source/" + currentDateTime() + "_" + Last_Algorithm_Used + "_" + "data"; //Mac
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
  QString OUTPUT_PATH = QCoreApplication::applicationDirPath() + "/Source/" + QString::fromStdString(currentDateTime())
                        + "_" + QString::fromStdString(Last_Algorithm_Used) + "_result.png";
  QPixmap pixmap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
  pixmap.save(OUTPUT_PATH, "PNG", -1);
}


