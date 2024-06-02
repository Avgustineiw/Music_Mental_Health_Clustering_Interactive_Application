#include "clusterscene.h"
#include "clusterpoint.h"

#include <QMessageBox>
#include <QList>

ClusterScene::ClusterScene (QObject* parent)
{}

void ClusterScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  QRectF rect = QRectF(event->scenePos(), QSizeF(1, 1));
  QList<QGraphicsItem*> itemsList = items(rect, Qt::IntersectsItemShape, Qt::DescendingOrder);
}

