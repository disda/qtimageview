#include <QVBoxLayout>
#include <QWheelEvent>
#include <QPushButton>

#include "imageview.h"
#include "imageWidget.h"
imageview::imageview(QWidget *parent): QWidget(parent) {
    this->setMinimumSize(480, 480);
    setContentsMargins(0, 0, 0, 0);
    // title
    m_toolWidget = new QWidget(this);
    m_toolWidget->setFixedHeight(60);
    m_toolWidget->setObjectName("toolWidget");
    m_toolWidget->setStyleSheet("#toolWidget {background:white}");

    toolLayout = new QHBoxLayout(m_toolWidget);
    toolLayout->setSpacing(0);
    toolLayout->setContentsMargins(11, 11, 11, 11);
    toolLayout->setObjectName(QStringLiteral("toolLayout"));
    toolLayout->setContentsMargins(0, 0, 0, 5);
    auto horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    toolLayout->addItem(horizontalSpacer);

    preBtn = new QPushButton(m_toolWidget);

    preBtn->setFixedSize(QSize(32, 32));
    preBtn->setObjectName(QStringLiteral("pre"));
    preBtn->setFocusPolicy(Qt::NoFocus);
    preBtn->setStyleSheet(QStringLiteral(""));
    preBtn->setIconSize(QSize(32, 32));
    preBtn->setFlat(true);

    toolLayout->addWidget(preBtn, 0, Qt::AlignHCenter);

    nextBtn = new QPushButton(m_toolWidget);
    nextBtn->setObjectName(QStringLiteral("next"));
    nextBtn->setFixedSize(QSize(32, 32));
    nextBtn->setFocusPolicy(Qt::NoFocus);
    nextBtn->setStyleSheet(QStringLiteral(""));
    nextBtn->setIconSize(QSize(32, 32));
    nextBtn->setFlat(true);

    toolLayout->addWidget(nextBtn);

    saveasBtn = new QPushButton(m_toolWidget);
    saveasBtn->setObjectName(QStringLiteral("saveas"));
    saveasBtn->setFixedSize(QSize(32, 32));
    saveasBtn->setFocusPolicy(Qt::NoFocus);
    saveasBtn->setFlat(true);

    toolLayout->addWidget(saveasBtn);

    turnrightBtn = new QPushButton(m_toolWidget);
    turnrightBtn->setObjectName(QStringLiteral("turnright"));
    turnrightBtn->setFixedSize(QSize(32, 32));
    turnrightBtn->setIconSize(QSize(32, 32));
    turnrightBtn->setFlat(true);

    toolLayout->addWidget(turnrightBtn);

    auto horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    toolLayout->addItem(horizontalSpacer_2);

    m_toolWidget->setLayout(toolLayout);

    m_imageWidget = new ImageWidget(this);
    m_imageWidget->setObjectName("bottomFrame");
    m_imageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    auto *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_imageWidget);
    layout->addWidget(m_toolWidget);
    setLayout(layout);
}

void imageview::ShowImage(const QString &string) {
    m_imageWidget->ShowImage(string, true);
}

void imageview::wheelEvent(QWheelEvent *e) {
    if (e->delta() > 0) {
        m_imageWidget->zoomIn();
    } else {
        m_imageWidget->zoomOut();
    }
}
