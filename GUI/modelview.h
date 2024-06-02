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
  using ContainerType = QVector<QVector<QVariant>>;
  using ContainerData = QVector<QVariant>;

public:
  explicit ModelView(QObject* parent = nullptr);
  ModelView(const QString& fileName, QObject* parent = nullptr);
  ModelView(const std::vector<Point>& points, QObject* parent = nullptr);
  ~ModelView() {};

  // inherited methods
  int                   rowCount(const QModelIndex& parent = QModelIndex())                              const override;
  int                   columnCount(const QModelIndex& parent = QModelIndex())                           const override;
  QVariant              data(const QModelIndex& index, int role = Qt::DisplayRole)                       const override;
  QVariant              headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  void                  setHeader(const QStringList& headers);
  // own methods
  void                  addRow(const QVector<QVariant>& rowData);
  void                  removeRow(const qsizetype& idxRow);
  void                  editRow(const qsizetype& idxRow, const ContainerData& rowData);
  const ContainerData&  getRow(const qsizetype& idxRow)                                  const;
  const ContainerType&  getData()                                                        const;
  void                  clearData();

private:
  ContainerType data_;
  QStringList   header_;
  QString       fileName_;
};

#endif // MODELVIEW_H
