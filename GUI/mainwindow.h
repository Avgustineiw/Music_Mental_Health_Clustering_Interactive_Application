#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QDir>
#include <QCoreApplication>

#include "modelview.h"
#include "proxymodel.h"
#include "rightaligneddelegate.h"

#include "clusterscene.h"
#include "clusterpoint.h"

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
  //void on_actionOpen_triggered();

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

  void on_pb_compare_clicked();

  private:
  std::vector<Point>    convertModelDataToPoints(const QVector<QVector<QVariant>>& data);

private:
  Ui::MainWindow*       ui;
  ModelView*            pModel_;
  ModelView*            pModelCluster_;
  ProxyModel*           pProxy_;
  ProxyModel*           pProxyCluster_;
  RightAlignedDelegate* pDelegate_;

  ClusterScene*         pScene_;

  QRect                 clusterBBox_;
  double                scaleX_;
  double                scaleY_;

  QRadioButton*         selectedRb_;

  ClusteringAlgorithm*  pClusterType_;
  ClusteringResult      clusterData_;

  std::vector<Point>    dataPoints_;

  std::string           Last_Algorithm_Used = "NONE";

  QString               INPUT_PATH;
  QString               OUTPUT_PATH_PNG;
  std::string           OUTPUT_PATH_TXT;
  std::string           OUTPUT_PATH_CSV;

  int32_t               minX = INT_MAX;
  int32_t               minY = INT_MAX;
  int32_t               maxX = INT_MIN;
  int32_t               maxY = INT_MIN;

  QString               SYSTEM = "Mac"; //Only takes strings "Mac" and "Windows"
};
#endif // MAINWINDOW_H
