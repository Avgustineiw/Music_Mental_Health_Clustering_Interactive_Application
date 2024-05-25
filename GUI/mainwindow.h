#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QGraphicsScene>
#include <QDir>
#include <QCoreApplication>

#include "modelview.h"
#include "proxymodel.h"
#include "rightaligneddelegate.h"

#include "Core/clusteringAlgorithm.h"
#include "Core/point.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionOpen_triggered();

  void addRow();
  void removeRow();
  void editCell();
  void clearData();
  void clusterize();
  void editClicked(const QModelIndex& ind);

  void setClusterization();
  void displayClusterData();

  void on_pb_saveResults_clicked();

  void on_pb_saveGraph_clicked();

private:
  std::vector<Point>    convertModelDataToPoints(const QVector<QVector<QVariant>>& data);

private:
  Ui::MainWindow*       ui;
  ModelView*            pModel_;
  ModelView*            pModelCluster_;
  ProxyModel*           pProxy_;
  ProxyModel*           pProxyCluster_;
  RightAlignedDelegate* pDelegate_;

  QGraphicsScene*       pScene_;

  QRadioButton*         selectedRb_;

  ClusteringAlgorithm*  pClusterType_;
  ClusteringResult      clusterData_;

  std::vector<Point>    dataPoints_;

  QString               INPUT_PATH;
  QString               SETTINGS_PATH = QCoreApplication::applicationDirPath() + "/Source/settings.txt";
  std::string           Last_Algorithm_Used = "NONE";
};
#endif // MAINWINDOW_H
