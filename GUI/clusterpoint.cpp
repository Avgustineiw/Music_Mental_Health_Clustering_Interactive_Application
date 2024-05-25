#include "clusterpoint.h"

CLusterPoint::CLusterPoint(qreal x, qreal y, qreal w, qreal h, uint32_t id, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x, y, w, h, parent)
    , id_(id)
{}

uint32_t CLusterPoint::getId() const
{
  return id_;
}
