#include "UI/headers/imagewidget.h"

#include <QVBoxLayout>
#include <QPixmap>

ImageWidget::ImageWidget(QWidget* parent, const QString& currentImage) :
    QWidget(parent)
{
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    imageLabel->setFixedSize(400, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    setLayout(layout);

    setImage(currentImage);
}

void ImageWidget::setImage(const QString& imagePath)
{
    QPixmap image(imagePath);
    if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("Immagine non trovata");
    }
}
