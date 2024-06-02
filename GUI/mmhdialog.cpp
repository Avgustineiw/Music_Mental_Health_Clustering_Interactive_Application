#include "mmhdialog.h"
#include "ui_mmhdialog.h"

#include <QMessageBox>

MmhDialog::MmhDialog (QWidget *parent)
    : QDialog (parent), ui (new Ui::MmhDialog)
{
  ui->setupUi (this);

  ui->le_Age->       setPlaceholderText("23");
  ui->le_HPD->       setPlaceholderText("2");
  ui->le_Musician->  setPlaceholderText("true");
  ui->le_Frequency-> setPlaceholderText("5");
  ui->le_Anxiety->   setPlaceholderText("3");
  ui->le_Depression->setPlaceholderText("3");
  ui->le_Insomnia->  setPlaceholderText("2");
  ui->le_OCD->       setPlaceholderText("3");
  ui->le_Effect->    setPlaceholderText("1");

  connect(ui->pb_OK,     &QPushButton::clicked, this, &MmhDialog::handleAccepted);
  connect(ui->pb_Cancel, &QPushButton::clicked, this, &QDialog::reject);
}

MmhDialog::~MmhDialog () { delete ui; }



bool MmhDialog::isValid() const
{
  if (ui->le_Age->text().isEmpty() || ui->le_Age->text().toInt() < 0) {
    return false;
  }
  if (ui->le_HPD->text().isEmpty() || ui->le_HPD->text().toInt() < 0 || ui->le_HPD->text().toInt() > 24) {
    return false;
  }
  //
  if (ui->le_Frequency->text().isEmpty() || ui->le_Frequency->text().toInt() < 0 || ui->le_Frequency->text().toInt() > 24) {
    return false;
  }
  if (ui->le_Anxiety->text().isEmpty() || ui->le_Anxiety->text().toInt() < 0 || ui->le_Anxiety->text().toInt() > 24) {
    return false;
  }
  if (ui->le_Depression->text().isEmpty() || ui->le_Depression->text().toInt() < 0 || ui->le_Depression->text().toInt() > 24) {
    return false;
  }
  if (ui->le_Insomnia->text().isEmpty() || ui->le_Insomnia->text().toInt() < 0 || ui->le_Insomnia->text().toInt() > 24) {
    return false;
  }
  if (ui->le_OCD->text().isEmpty() || ui->le_OCD->text().toInt() < 0 || ui->le_OCD->text().toInt() > 24) {
    return false;
  }
  // if (!ui->le_Effect->text().isEmpty() || ui->le_Effect->text().toInt() < 0 || ui->le_HPD->text().toInt() > 24) {
  //     return false;
  // }

  return true;
}

const QVector<QVariant>& MmhDialog::getData()
{
  if (data_.size() != 9) {
    data_ = QVector<QVariant>(9);
  }
  data_[0] = QVariant(ui->le_Age->text());
  data_[1] = QVariant(ui->le_HPD->text());
  data_[2] = QVariant(ui->le_Musician->text());
  data_[3] = QVariant(ui->le_Frequency->text());
  data_[4] = QVariant(ui->le_Anxiety->text());
  data_[5] = QVariant(ui->le_Depression->text());
  data_[6] = QVariant(ui->le_Insomnia->text());
  data_[7] = QVariant(ui->le_OCD->text());
  data_[8] = QVariant(ui->le_Effect->text());
  return data_;
}

void MmhDialog::setData(const QVector<QVariant>& data)
{
  if (data.size() != 9) {
    return;
  }
  data_ = data;

  ui->le_Age->       setText(data[0].toString());
  ui->le_HPD->       setText(data[1].toString());
  ui->le_Musician->  setText(data[2].toString());
  ui->le_Frequency-> setText(data[3].toString());
  ui->le_Anxiety->   setText(data[4].toString());
  ui->le_Depression->setText(data[5].toString());
  ui->le_Insomnia->  setText(data[6].toString());
  ui->le_OCD->       setText(data[7].toString());
  ui->le_Effect->    setText(data[8].toString());

}

void MmhDialog::on_buttonBox_accepted()
{
  bool status = this->isValid();
  if (!status) {
    QMessageBox msgb;
    msgb.setText("Invalid arguments");
    msgb.exec();
  }
  else {
    QDialog::accept();
  }
}

void MmhDialog::handleAccepted()
{
  bool status = this->isValid();

  if (!status) {
    QMessageBox msgb;
    msgb.setText("Invalid arguments");
    msgb.exec();
  }
  else {
    this->QDialog::accept();
  }
}

void MmhDialog::handleRejected()
{
  QDialog::reject();
}

