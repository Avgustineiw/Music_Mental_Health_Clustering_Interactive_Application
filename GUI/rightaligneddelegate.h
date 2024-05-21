#ifndef RIGHTALIGNEDDELEGATE_H
#define RIGHTALIGNEDDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>

class RightAlignedDelegate : public QStyledItemDelegate
{
public:
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // RIGHTALIGNEDDELEGATE_H
