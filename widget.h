#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

class PicItem;

namespace Ui {
class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool loadImage(const QString &picture, bool isFirst);
private:
    Ui::Widget *ui;
    QGraphicsScene *_pGraphicsScene;
    QGraphicsView *_pGraphicsView;
    PicItem *_pPicItem;

    QPixmap _pixmap;

private:
    int _scaleVal;
    int _angle;
    QString _strPicPath;

private:
    QPointF _startPos;
    bool _pressed;
};

#endif // WIDGET_H
