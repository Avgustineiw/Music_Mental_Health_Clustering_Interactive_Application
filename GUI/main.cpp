#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  // QMessageBox msgb;
  // msgb.setWindowTitle("Tip");
  // msgb.setText("In order to see the table,\nchoose convenient file.");
  // //msgb.setGeometry(400, 350, 400, 200);
  // msgb.exec();

  return a.exec();
}
