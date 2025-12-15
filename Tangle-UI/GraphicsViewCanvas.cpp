#include "GraphicsViewCanvas.h"
#include <QMimeData>
#include <QGraphicsScene>
#include <QDataStream>
#include "CanvasNode.h"
#include <QScrollBar>

// GraphicsViewCanvas::GraphicsViewCanvas(QWidget *parent)
//     : QGraphicsView(parent)
// {
//     setAcceptDrops(true);
//     viewport()->setAcceptDrops(true);

//     QGraphicsScene* sc = new QGraphicsScene(this);
//     setScene(sc);
//     sc->setSceneRect(viewport()->rect());

//     setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//     setDragMode(QGraphicsView::RubberBandDrag);

//     setTransformationAnchor(QGraphicsView::AnchorViewCenter);
//     setResizeAnchor(QGraphicsView::AnchorViewCenter);

// }
GraphicsViewCanvas::GraphicsViewCanvas(QWidget *parent)
    : QGraphicsView(parent)
{
    setAcceptDrops(true);
    viewport()->setAcceptDrops(true);

    setScene(new QGraphicsScene(this));
    scene()->setSceneRect(-5000, -5000, 10000, 10000);

    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setDragMode(QGraphicsView::RubberBandDrag);

    // Default: keyboard zoom stays centered
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

// Accept drag enter
void GraphicsViewCanvas::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText() ||
        event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

// Accept drag move
void GraphicsViewCanvas::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasText() ||
        event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

// Handle drop
void GraphicsViewCanvas::dropEvent(QDropEvent *event)
{
    QString text = extractTreeWidgetText(event->mimeData());
    if (text.isEmpty()) {
        event->ignore();
        return;
    }

#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    QPointF scenePos = mapToScene(event->position().toPoint());
#else
    QPointF scenePos = mapToScene(event->pos());
#endif

    CanvasNode* node = new CanvasNode(text);
    node->setPos(scenePos);

    scene()->addItem(node);
    event->accept();
}

// Update scene rect on resize
void GraphicsViewCanvas::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    // if (scene())
    //     scene()->setSceneRect(viewport()->rect());
}

void GraphicsViewCanvas::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // Zoom factor
        const double zoomFactor = 1.15;

        // Map mouse position to scene coordinates BEFORE scaling
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        QPointF scenePos = mapToScene(event->position().toPoint());
#else
        QPointF scenePos = mapToScene(event->pos());
#endif

        // Apply scale
        if (event->angleDelta().y() > 0)
            scale(zoomFactor, zoomFactor);
        else
            scale(1.0 / zoomFactor, 1.0 / zoomFactor);

        // Map mouse position to scene coordinates AFTER scaling
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        QPointF newScenePos = mapToScene(event->position().toPoint());
#else
        QPointF newScenePos = mapToScene(event->pos());
#endif

        // Adjust scrollbars so the point under the mouse stays fixed
        QPointF delta = newScenePos - scenePos;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());

        event->accept();
        return;
    }

    // Normal scroll
    QGraphicsView::wheelEvent(event);
}



// Extract text from TreeWidget MIME
QString GraphicsViewCanvas::extractTreeWidgetText(const QMimeData* mimeData)
{
    // First try plain text
    if (mimeData->hasText())
        return mimeData->text();

    // Then try TreeWidget format
    if (!mimeData->hasFormat("application/x-qabstractitemmodeldatalist"))
        return QString();

    QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    while (!stream.atEnd())
    {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;
        if (roleDataMap.contains(Qt::DisplayRole))
            return roleDataMap[Qt::DisplayRole].toString();
    }

    return QString();
}

void GraphicsViewCanvas::zoom(double factor, const QPointF& center)
{
    // Map the scene point before scaling
    QPointF oldPos = mapToScene(center.toPoint());

    // Apply scale
    scale(factor, factor);

    // Map after scaling
    QPointF newPos = mapToScene(center.toPoint());

    // Adjust scrollbars to keep 'center' fixed
    QPointF delta = newPos - oldPos;
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() + delta.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() + delta.y());
}
