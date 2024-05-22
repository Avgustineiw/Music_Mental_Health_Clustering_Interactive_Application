#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QGraphicsScene>

#include "modelview.h"
#include "proxymodel.h"
#include "rightaligneddelegate.h"

#include "Core/clusteringAlgorithm.h"
#include "Core/k-means.h"
#include "Core/k-medoids.h"
#include "Core/point.h"
//#include "Core/.h"

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

  void on_pushButton_9_clicked();

private:
  std::vector<Point>    convertModelDataToPoints(const QVector<QVector<QVariant>>& data);

private:
  Ui::MainWindow*       ui;
  ModelView*            pModel_;
  ProxyModel*           pProxy_;
  RightAlignedDelegate* pDelegate_;

  QGraphicsScene*       pScene_;

  QRadioButton*         selectedRb_;

  ClusteringAlgorithm*  pClusterType_;
  ClusteringResult      clusterData_;

  std::vector<Point>    dataPoints_;

  QString               INPUT_PATH;
  QString               OUTPUT_PATH_CSV = "points.csv";
  QString               OUTPUT_PATH_TXT = "data.txt";
};
#endif // MAINWINDOW_H
