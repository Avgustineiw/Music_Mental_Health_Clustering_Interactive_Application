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

  if (!itemsList.isEmpty()) {
    QGraphicsItem* item = itemsList.first();

    if (auto clusterPoint = qgraphicsitem_cast<CLusterPoint*>(item)) {
      //TODO
      QMessageBox pointInfo;
      pointInfo.setText("fhdahshhs");
      pointInfo.setInformativeText(QString::number(clusterPoint->getId()));
      pointInfo.exec();
    }

  }
  QGraphicsScene::mousePressEvent(event);
}

