#include "widget.h"
#include "ui_widget.h"
#include "PicItem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent) {
    _pPicItem = nullptr;
    _pGraphicsScene = new QGraphicsScene(this);
    _pGraphicsView = new QGraphicsView(this);
    _pGraphicsView->setObjectName("GraphicsView");
    _pGraphicsView->setScene(_pGraphicsScene);
    _pGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _pGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _pGraphicsView->setFrameShape(QFrame::NoFrame);

    _pGraphicsScene->installEventFilter(this);
    _pGraphicsView->installEventFilter(this);

    auto *loyout = new QGridLayout;
    loyout->setMargin(0);
    loyout->addWidget(_pGraphicsView);
    setLayout(loyout);
}

Widget::~Widget() {
}

bool Widget::loadImage(const QString &picture, bool isFirst) {
    if (nullptr != _pPicItem) {
        _pGraphicsScene->removeItem(_pPicItem);
        delete _pPicItem;
    }
    _pPicItem = new PicItem(_scaleVal);
    _pGraphicsScene->addItem(_pPicItem);

    _strPicPath = picture;
    _pixmap = QPixmap(picture);
    if (_pixmap.isNull()) {
        //QtMessageBox::information(nullptr, tr("提示"), tr("加载图片失败"));
        return false;
    }
    double factor = 1.0;
    if (true) {

        double maxHeight = 0, maxWidth = 0;
        double picWidth = _pixmap.width();
        double picHeight = _pixmap.height();
        QRect deskRect;
        if (isFirst) {
            QDesktopWidget *deskTop = QApplication::desktop();
            int curMonitor = 0;
            deskRect = deskTop->screenGeometry(curMonitor);
            maxWidth = deskRect.width() * 0.85;
            maxHeight = deskRect.height() * 0.85;
        } else {
            maxWidth = _pGraphicsView->width();
            maxHeight = _pGraphicsView->height();
        }


        double factor1 = maxWidth / picWidth;
        double factor2 = maxHeight / picHeight;
        if (factor1 < 1.0 || factor2 < 1.0) {
            factor = qMin(factor1, factor2);
        }

        picWidth = factor * picWidth;
        picHeight = factor * picHeight;

        _pGraphicsScene->setSceneRect(-picWidth / 2, -picHeight / 2, picWidth, picHeight);
        if (isFirst) {
            resize(static_cast<int>(picWidth + 34), static_cast<int>(picHeight + 86));
            move((deskRect.width() - width()) / 2 + deskRect.x(),
                 (deskRect.height() - height()) / 2 + deskRect.y());

        }
    }
    _scaleVal = 0;
    _angle = 0;
    _pPicItem->setPixmap(_pixmap, picture, factor);
    return true;
}
