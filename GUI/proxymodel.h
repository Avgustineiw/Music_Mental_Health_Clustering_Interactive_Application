#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>


class ProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT;
public:
  ProxyModel(QObject* parent = nullptr);
  virtual ~ProxyModel() {}

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  bool     filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
};

#endif // PROXYMODEL_H
