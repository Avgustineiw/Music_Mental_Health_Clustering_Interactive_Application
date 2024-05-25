#ifndef CLUSTERPOINT_H
#define CLUSTERPOINT_H

#include <QGraphicsEllipseItem>

class CLusterPoint : public QGraphicsEllipseItem
{
private:
  uint32_t id_;
public:
  CLusterPoint (qreal x, qreal y, qreal w, qreal h, uint32_t id, QGraphicsItem* parent = nullptr);

  uint32_t getId() const;

};

#endif // CLUSTERPOINT_H
