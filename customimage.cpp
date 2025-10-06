#include "customimage.h"
#include <QPainter>
#include <QPainterPath>

CustomImage::CustomImage(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{}

void CustomImage::paint(QPainter *painter)
{
    if (m_pixmap.isNull())
        return;

    // Tạo path bo cong 4 góc
    QPainterPath path;
    qreal radius = 20; // bán kính bo góc
    path.addRoundedRect(boundingRect(), radius, radius);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setClipPath(path);

    painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}
