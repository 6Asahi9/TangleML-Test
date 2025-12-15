#ifndef GRAPHICSVIEWCANVAS_H
#define GRAPHICSVIEWCANVAS_H

#pragma once
#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QResizeEvent>
#include "NodeList.h"

class GraphicsViewCanvas : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsViewCanvas(QWidget *parent = nullptr);
    void zoom(double factor, const QPointF& center);

    NodeList nodes; // linked list of nodes

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QString extractTreeWidgetText(const QMimeData* mimeData);
};

#endif // GRAPHICSVIEWCANVAS_H
