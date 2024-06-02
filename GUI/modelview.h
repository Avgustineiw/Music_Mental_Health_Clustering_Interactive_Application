#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QStringList>

#include "Core/point.h"

class ModelView : public QAbstractTableModel
{
  Q_OBJECT;
public:
  explicit ModelView(QObject* parent = nullptr);
  ModelView(const QString& fileName, QObject* parent = nullptr);
  ModelView(const vector<Point>& points, QObject* parent = nullptr);
  ~ModelView() {};

  int rowCount   (const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data      (const QModelIndex& index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  void     setHeader (const QStringList& headers);

  void addRow   (const QVector<QVariant>& rowData);
  void deleteRow(const qsizetype& idxRow);
  void editRow  (const qsizetype& idxRow);

  QVector<QVariant> getRow(const qsizetype& idxRow) const;
  void              setRow(const qsizetype& idxRow, const QVector<QVariant>& rowData);

  const QVector<QVector<QVariant>>& getData() const;

private:
  QVector<QVector<QVariant>> data_;
  QStringList                header_;
  QString                    fileName_;
};


#endif // MODELVIEW_H
