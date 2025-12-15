#include "CanvasNode.h"
#include <QPainter>

CanvasNode::CanvasNode(const QString& text)
    : m_text(text)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges); // optional, but good for future connections
}

// Expand bounding rect to include hooks fully
QRectF CanvasNode::boundingRect() const
{
    // include hook radius as padding on left and right
    return QRectF(-m_hookRadius, 0, m_width + 2*m_hookRadius, m_height);
}

void CanvasNode::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*)
{
    // Node body
    painter->setBrush(QColor(60, 60, 60));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(0, 0, m_width, m_height, 6, 6);

    // Text
    painter->setPen(Qt::white);
    painter->drawText(0, 0, m_width, m_height, Qt::AlignCenter, m_text);

    // Left hook
    QPointF leftHook(0, m_height / 2);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(leftHook, m_hookRadius, m_hookRadius);

    // Right hook
    QPointF rightHook(m_width, m_height / 2);
    painter->drawEllipse(rightHook, m_hookRadius, m_hookRadius);
}
