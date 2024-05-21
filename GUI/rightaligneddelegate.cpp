#include "rightaligneddelegate.h"

void RightAlignedDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QStyleOptionViewItem newOption = option;
  newOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;
  QStyledItemDelegate::paint(painter, newOption, index);
}
