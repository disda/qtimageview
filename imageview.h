#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class ImageWidget;
class imageview : public QWidget {
public:
    imageview(QWidget *parent = nullptr);
    void ShowImage(const QString &string);
    void wheelEvent(QWheelEvent *event);
private:
    ImageWidget *m_imageWidget;
    QWidget *m_toolWidget;
private:
    std::vector<std::pair<std::string, std::string> > _images; // <local, link>
    std::string _curLink;
    int _curIndex;

    bool _hasBefore;
    bool _hasNext;
    QPushButton *preBtn = nullptr;
    QPushButton *nextBtn = nullptr;
    QPushButton *saveasBtn = nullptr;
    QPushButton *turnrightBtn = nullptr;
    QHBoxLayout *toolLayout = nullptr;
};

#endif // IMAGEVIEW_H
