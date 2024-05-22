#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Core/point.h"
#include "Core/header.h"
#include "Core/clusteringAlgorithm.h"
#include "Core/k-means.h"
#include "Core/header.h"
#include "Core/silhouette.h"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <QPen>
#include <QGraphicsEllipseItem>

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
  pModel_        = new ModelView;

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
  pScene_ = new QGraphicsScene(this);
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
  INPUT_PATH = QFileDialog::getOpenFileName(this, "Open dataset", "", "CSV file (*.csv)");

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

    dataPoints_ = InitializeProgram(INPUT_PATH.toStdString()); //Load it here to prepare points for clusterization
    //Otherwise you'd do it every time you clusterize data which is inefficient
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
  //TODO: get number of clusters and iterations
  int clusters   = 3;
  int iterations = 10;

  if (type == "Sort by Hierarchy") {
    //pClusterType_ = new AAA(clusters, iterations);
  }
  else if (type == "Sort by Medoids") {
    pClusterType_ = new KMedoids(clusters, iterations);
  }
  else {
    pClusterType_ = new KMeans(clusters, iterations);
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

  size_t height = pScene_->height();
  size_t width  = pScene_->width();

  for (qsizetype i = 0 ; i < clusterData_.GetClustersSize(); ++i)
  {
    int red = rand() % 255;
    int blue = rand() % 255;
    int green = rand() % 255;
    QPen pen = QPen(QColor(red, blue, green));

    for (qsizetype j = 0; j < clusterData_.GetPointsSize(); j++) {
      if (clusterData_.GetPoint(j).GetClusterId() == i+1) {
        QGraphicsEllipseItem* point = new QGraphicsEllipseItem(0, 0, 5, 5);
        point->setBrush(pen.brush());
        int x = clusterData_.GetPoint(j).GetX()*2;
        int y = clusterData_.GetPoint(j).GetY()*2;
        point->setPos(width / 3  + x,
                      height / 4 + y);
        pScene_->addItem(point);
      }
    }

    QGraphicsEllipseItem* cluster_point = new QGraphicsEllipseItem(0, 0, 15, 15);
    cluster_point->setBrush(pen.brush());
    int x = clusterData_.GetCluster(i).GetCentroidX()*2;
    int y = clusterData_.GetCluster(i).GetCentroidY()*2;
    cluster_point->setPos(width / 3 + x,
                          height / 4 + y);
    pScene_->addItem(cluster_point);
  }
  return;
}
/* Obsolete function which didn't do anything for clusterization (you were converting respondents to clusters
 * without actual clusterization)
std::vector<Point> MainWindow::convertModelDataToPoints(const QVector<QVector<QVariant>>& data)
{
  std::vector<Point> convertedData(data.size());

  for (qsizetype i = 0; i < data.size(); ++i)
  {
    Respondent rsp;
    rsp.SetAge(data[i][0].toInt());
    rsp.SetHpd(data[i][1].toDouble());
    rsp.SetMusician(data[i][2].toInt());
    rsp.SetFrequency(data[i][3].toInt());
    rsp.SetAnxiety(data[i][4].toInt());
    rsp.SetDepression(data[i][5].toInt());
    rsp.SetInsomnia(data[i][6].toInt());
    rsp.SetOcd(data[i][7].toInt());
    rsp.SetEffect(data[i][8].toInt());

    convertedData[i] = respondentToPoint(rsp, i);
  }

  return convertedData;
}
*/

void MainWindow::on_pb_saveResults_clicked()
{
  std::ofstream csv(OUTPUT_PATH_CSV.toStdString());

  csv << "id, x, y, cluster" << '\n';

  for (qsizetype i = 0; i < clusterData_.GetPointsSize(); i++) {
    csv << clusterData_.GetPoint(i).GetPointId() << ",";
    csv << clusterData_.GetPoint(i).GetX() << ",";
    csv << clusterData_.GetPoint(i).GetY() << ",";
    csv << clusterData_.GetPoint(i).GetClusterId() << '\n';
  }

  csv.close();

  std::ofstream txt(OUTPUT_PATH_TXT.toStdString());

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
  QPixmap pixmap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
  pixmap.save("clustering_result.png", "PNG", -1);
}
