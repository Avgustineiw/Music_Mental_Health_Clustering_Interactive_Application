#include "proxymodel.h"

ProxyModel::ProxyModel(QObject* parent)
  : QSortFilterProxyModel(parent)
{};


QVariant ProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  return sourceModel()->headerData(section, orientation, role);
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
  return true;
}
