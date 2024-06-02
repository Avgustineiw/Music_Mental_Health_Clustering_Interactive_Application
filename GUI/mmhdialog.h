#ifndef MMHDIALOG_H
#define MMHDIALOG_H

#include <QDialog>
#include <QVector>
#include <QVariant>

namespace Ui
{
class MmhDialog;
}

class MmhDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MmhDialog (QWidget *parent = nullptr);
  ~MmhDialog ();

  bool isValid() const;
  const QVector<QVariant>& getData();
  void setData(const QVector<QVariant>& data);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::MmhDialog *ui;

  QVector<QVariant> data_;
};

#endif // MMHDIALOG_H
