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

  QString               INPUT_PATH;
  QString               OUTPUT_PATH = "data.csv";
};
#endif // MAINWINDOW_H
