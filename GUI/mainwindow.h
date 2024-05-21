#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QGraphicsScene>

#include "modelview.h"
#include "proxymodel.h"
#include "rightaligneddelegate.h"

#include "Core/point.h"
#include "Core/clusteringResult.h"

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
  Ui::MainWindow*       ui;
  ModelView*            pModel_;
  ProxyModel*           pProxy_;
  RightAlignedDelegate* pDelegate_;

  QString               INPUT_PATH;
  QString               OUTPUT_PATH = "data.csv";

  QGraphicsScene*       pScene_;

  QRadioButton*                selectedRb_;
  vector<Point>                dataPoints_; //put this into clustering algorithm as an input
  ClusteringResult             clusterData_; //draw this on form #2
};
#endif // MAINWINDOW_H
