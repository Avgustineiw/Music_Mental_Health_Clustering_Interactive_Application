#ifndef CLUSTERSCENE_H
#define CLUSTERSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class ClusterScene : public QGraphicsScene
{
public:
  ClusterScene (QObject* parent = nullptr);

  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // CLUSTERSCENE_H
