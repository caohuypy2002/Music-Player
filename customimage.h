#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H
#include <QPixmap>
#include <QPainter>
#include <QPixmapCache>
#include <QQuickPaintedItem>
class CustomImage: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged)
public:
    CustomImage(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
    QPixmap pixmap() const { return m_pixmap; }
    void setPixmap(const QPixmap &pix) {
        if (m_pixmap.cacheKey() != pix.cacheKey()) {
            m_pixmap = pix;
            update();
            emit pixmapChanged();
        }
    }
signals:
    void pixmapChanged();
private:
    QPixmap m_pixmap;
};

#endif // CUSTOMIMAGE_H
