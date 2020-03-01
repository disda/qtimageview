#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class PicItem;

class ImageWidget : public QWidget {
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();
    bool ShowImage(const QString &picture, bool isFirst);
    void zoomIn();
    void zoomOut();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *e);
    void wheelEvent(QWheelEvent *e);
private:
    QGraphicsScene *m_pGraphicsScene;       //图形场景
    QGraphicsView *m_pGraphicsView;          //图形窗口
    PicItem *m_pPicItem;
    QPixmap m_pixmap;
private:
    int m_scaleVal;
    int m_angle;
    QString m_strPicPath;

private:
    QPointF m_startPos;
    bool m_pressed;
};

#endif // WIDGET_H
