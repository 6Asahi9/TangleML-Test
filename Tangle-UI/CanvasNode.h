#ifndef CANVASNODE_H
#define CANVASNODE_H

#include <QGraphicsItem>
#include <QString>

class CanvasNode : public QGraphicsItem
{
public:
    CanvasNode(const QString& text);

    // Required overrides
    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

private:
    QString m_text;

    // visual sizes
    const qreal m_width  = 120;
    const qreal m_height = 60;

    // hook radius
    const qreal m_hookRadius = 6;
};

#endif // CANVASNODE_H
