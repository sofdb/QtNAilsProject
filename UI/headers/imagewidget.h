#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>

class ImageWidget : public QWidget {
    Q_OBJECT
private:
    QLabel* imageLabel;
    QString currentImage;
public:
    explicit ImageWidget(QWidget* parent = 0, const QString& currentImage = "");
    void setImage(const QString& imagePath);

};

#endif // IMAGEWIDGET_H
