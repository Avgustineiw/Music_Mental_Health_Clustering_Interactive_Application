#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QFileDialog>

#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  pModel_ = new ModelView;
  pProxy_ = new ProxyModel;

  pProxy_->setSourceModel(pModel_);
  ui->tableView->setModel(pProxy_);
  //ui->tableView->setModel(pModel_);
  ui->tableView->setSortingEnabled(true);

  //ui->menubar->actions().at(1)->menu();
  QMenu* menuFile = ui->menubar->findChild<QMenu*>("menuFile");//("actionSave");

  if (menuFile) {
    QAction* save = menuFile->actions().at(1);
    save->setEnabled(false);
    //TODO
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_10_clicked()
{
  QMessageBox msgb;
  msgb.setText("test");
  msgb.exec();
}


void MainWindow::on_actionOpen_triggered()
{
  QString path = QFileDialog::getOpenFileName(this, "Open dataset", "", "CSV file (*.csv)");

  if (path.isEmpty()) {
    return;
  }

  try {
    ModelView* newModel = new ModelView(path);

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
    }

  }
  catch (const std::invalid_argument& e) {
    QString e_msg = e.what();

    QMessageBox msgb;
    msgb.setText(e_msg + ": " + path);
    msgb.exec();
  }
  catch (...) {
    // "Global" exception
  }
}

