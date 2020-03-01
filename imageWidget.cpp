#include "imageWidget.h"
#include "ui_widget.h"
#include "PicItem.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QWheelEvent>
#include <QGraphicsSceneWheelEvent>
ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent) {
    m_pPicItem = nullptr;
    m_pGraphicsScene = new QGraphicsScene(this);
    m_pGraphicsView = new QGraphicsView(this);
    m_pGraphicsView->setObjectName("GraphicsView");
    m_pGraphicsView->setScene(m_pGraphicsScene);
    m_pGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pGraphicsView->setFrameShape(QFrame::NoFrame);

    m_pGraphicsScene->installEventFilter(this);
    m_pGraphicsView->installEventFilter(this);
    auto *loyout = new QGridLayout;
    loyout->setMargin(0);
    loyout->addWidget(m_pGraphicsView);
    setLayout(loyout);
    setObjectName("imageWidget");
    setStyleSheet("background:yellow");
}

ImageWidget::~ImageWidget() {
}

bool ImageWidget::ShowImage(const QString &picture, bool isFirst) {
    if (nullptr != m_pPicItem) {
        m_pGraphicsScene->removeItem(m_pPicItem);
        delete m_pPicItem;
    }
    m_pPicItem = new PicItem(m_scaleVal);
    m_pGraphicsScene->addItem(m_pPicItem);

    m_strPicPath = picture;
    m_pixmap = QPixmap(picture);
    if (m_pixmap.isNull()) {
        QMessageBox::information(nullptr, tr("提示"), tr("加载图片失败"));
    }
    double factor = 1.0;
    if (m_pPicItem) {
        double maxHeight = 0, maxWidth = 0;
        double picWidth = m_pixmap.width();
        double picHeight = m_pixmap.height();
        QRect deskRect;
        if (isFirst) {
            QDesktopWidget *deskTop = QApplication::desktop();
            int curMonitor = 0;
            deskRect = deskTop->screenGeometry(curMonitor);
            maxWidth = deskRect.width() * 0.85;
            maxHeight = deskRect.height() * 0.85;
        } else {
            maxWidth = m_pGraphicsView->width();
            maxHeight = m_pGraphicsView->height();
        }

        double factor1 = maxWidth / picWidth;
        double factor2 = maxHeight / picHeight;
        if (factor1 < 1.0 || factor2 < 1.0) {
            factor = qMin(factor1, factor2);
        }

        picWidth = factor * picWidth;
        picHeight = factor * picHeight;
        m_pGraphicsScene->setSceneRect(-picWidth / 2, -picHeight / 2, picWidth, picHeight);
        if (isFirst) {
            parentWidget()->resize(static_cast<int>(picWidth + 34), static_cast<int>(picHeight + 86));
            parentWidget()->move((deskRect.width() - width()) / 2 + deskRect.x(),
                                 (deskRect.height() - height()) / 2 + deskRect.y());

        }
    }
    m_scaleVal = 0;
    m_angle = 0;
    m_pPicItem->setPixmap(m_pixmap, picture, factor);
    return true;
}

void ImageWidget::zoomIn() {
    m_pPicItem->zoomIn();
}

void ImageWidget::zoomOut() {
    m_pPicItem->zoomOut();
}

bool ImageWidget::eventFilter(QObject *o, QEvent *e) {
    if (e->type() == QEvent::GraphicsSceneMousePress) {
        m_startPos = QCursor::pos();
        m_pressed = true;
        e->accept();
    } else if (e->type() == QEvent::GraphicsSceneMouseRelease) {
        m_pressed = false;
        e->accept();
    }
    //else if (e->type() == QEvent::GraphicsSceneWheel) {
    //    //wheelEvent((QGraphicsSceneWheelEvent *)e);
    //    e->accept();
    //}
    else if (e->type() == QEvent::GraphicsSceneMouseMove) {
        //移动
        if (m_pressed) {
            QPoint p = QCursor::pos();
            m_pPicItem->moveBy((p.x() - m_startPos.x()), (p.y() - m_startPos.y()));
            m_startPos = p;
            e->accept();
        }
    } else if (e->type() == QEvent::Resize) {
        if (m_pPicItem)
            m_pPicItem->setPos(0, 0);
    } else {
        return QObject::eventFilter(o, e);
    }
    return false;
}

void ImageWidget::wheelEvent(QWheelEvent *e) {
    return QWidget::wheelEvent(e);
}

//void ImageWidget::wheelEvent(QGraphicsSceneWheelEvent *e) {
//    if (e->delta() > 0) {
//        m_pPicItem->zoomIn();
//    } else {
//        m_pPicItem->zoomOut();
//    }
//}
