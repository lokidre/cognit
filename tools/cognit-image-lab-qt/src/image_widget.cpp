/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include "image_widget.h"

#include "image_graphics_view.h"
#include "image_toolkit.h"

#include "main_window.h"


APEAL_QT_HEADERS_BEGIN
#include <QBitmap>

#include <QGraphicsAnchorLayout>
#include <QGraphicsTextItem>

#include <QBoxLayout>
#include <QResizeEvent>
APEAL_QT_HEADERS_END


namespace image_lab {


ImageWidget::ImageWidget(MainWindow* mainWindow)
    : mainWindow_{mainWindow}
{
    //setBackgroundRole(QPalette::Dark);

    //auto layout = new QVBoxLayout;
    //setLayout(layout);

    //auto layout = new QGraphicsAnchorLayout();

    /*
    imageLabel_ = new QLabel();

    imageLabel_->setBackgroundRole(QPalette::Base);
    imageLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel_->setScaledContents(true);


    setWidget(imageLabel_);
    */

    imageScene_ = new ImageScene();
    //imageScene_->setBackgroundBrush(QPixmap(":/images/background3.png"));
    //imageScene_->setSceneRect(0, 0, 200, 200);
    imageScene_->setSceneRect(0, 0, 10, 10);

    //setScene(imageScene_);


    graphicsView_ = new ImageGraphicsView(imageScene_, this);
    graphicsView_->setCacheMode(QGraphicsView::CacheBackground);
    graphicsView_->setOptimizationFlags(
        QGraphicsView::DontAdjustForAntialiasing | QGraphicsView::DontSavePainterState);
    graphicsView_->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    graphicsView_->setBackgroundBrush(QPixmap(":/images/background3.png"));

    graphicsView_->move(0, 0);

    pixmapItem_ = imageScene_->addPixmap(pixmap_);
    pixmapItem_->setPos(0, 0);


    imageScene_->update();
    //graphicsView_->update();

    //setVisible(false);

    //scrollArea_ = new QScrollArea();

    //scrollArea_->setBackgroundRole(QPalette::Dark);
    //scrollArea_->setWidget(imageLabel_);
    //scrollArea_->setVisible(false);
    //setCentralWidget(scrollArea_);
}

void ImageWidget::processResize(int width, int height)
{
    //graphicsView_->move(0, 0);
    graphicsView_->resize(width, height);

    if (imageInfo_) {
        auto w = int(imageInfo_->width) * zoom_;
        auto h = int(imageInfo_->height) * zoom_;
        imageScene_->setSceneRect(0, 0, w, h);

        pixmapItem_->setPos(0, 0);
    }
}


void ImageWidget::setImageContainer(const apl::ImageContainer* image)
{
    imageContainer_ = image;
    setCurrentImageIndex(0);
}

void ImageWidget::setCurrentImageIndex(Index idx)
{
    imageIndex_ = idx;

    auto toolkit = ImageToolkit::instance();
    imageInfo_ = toolkit->selectImage(imageIndex_);
    auto& ii = *imageInfo_;

    updateImageData();

    auto iiPanel = mainWindow_->imageInfoPanel;
    iiPanel->imageSize->setText(QString::asprintf("%d, %d", ii.width, ii.height));
    iiPanel->imageColorModel->setText(
        apl::toQt(imageContainer_->images[imageIndex_].colorModelTag()));


    //auto pixPanel = mainWindow_->pixelInfoPanel;
    //pixPanel->selAlpha->clear();
    //pixPanel->selAlpha->setEnabled(ii.haveAlpha);


    processResize(widgetWidth_, widgetHeight_);
}

void ImageWidget::updateImageData()
{
    auto& ii = *imageInfo_;
    auto imgData = zoom_ == 1 ? ii.argbData.get() : zoomedImageData_.get();
    auto w = int(ii.width) * zoom_;
    auto h = int(ii.height) * zoom_;

    QImage qimage{imgData, w, h, QImage::Format_ARGB32};  //Format_RGBA8888

    pixmap_.convertFromImage(qimage, Qt::NoOpaqueDetection);
    pixmapItem_->setPixmap(pixmap_);
}


void ImageWidget::setZoom(int zoom)
{
    if (zoom_ == zoom)
        return;

    zoom_ = zoom;

    if (zoom_ != 1) {
        auto& ii = *imageInfo_;
        auto w = ii.width * zoom_;
        auto h = ii.height * zoom_;

        zoomedImageData_.alloc(w * h * 4);

        //auto srow = reinterpret_cast<const uint32_t *>(ii.argbData.get());
        auto zbpr = w * 4;
        auto srow = ii.argbData.get();
        auto drow = zoomedImageData_.get();

        for (Index y = 0; y < ii.height; ++y) {
            auto spix = reinterpret_cast<const uint32_t*>(srow);
            auto dpix = reinterpret_cast<uint32_t*>(drow);

            for (Index x = 0; x < ii.width; ++x) {

                for (int z = 0; z < zoom_; ++z) {
                    *dpix++ = *spix;
                }

                ++spix;
            }

            for (int z = 1; z < zoom_; ++z) {
                std::memcpy(drow + zbpr, drow, zbpr);
                drow += zbpr;
            }

            srow += ii.bpr;
            drow += zbpr;
        }
    }

    updateImageData();

    processResize(widgetWidth_, widgetHeight_);
}



//void ImageWidget::setImageData(uint8_t * data, int width, int height)
//{
//    pixmap_->loadFromData(data, width * height * 4,
//}

static inline QString formatRgb(const PixelInfo& p, bool haveAlpha, uint8_t alpha)
{
    auto& rgb = p.rgb;
    if (!haveAlpha)
        return QString::asprintf("%02x%02x%02x", rgb.r, rgb.g, rgb.b);

    return QString::asprintf("%02x%02x%02x%02x", rgb.r, rgb.g, rgb.b, alpha);

    /*
    auto fc = QChar('0');
    auto srgb = QString("%1%2%3").arg((uint)pixi.r, 2, 16, fc)
        .arg((uint)pixi.g, 2, 16, fc)
        .arg((uint)pixi.b, 2, 16, fc);
        */

    //auto srgb = tr("#%1%2%3%4").arg((uint)pixi.r, 2, 16, fc)
    //    .arg((uint)pixi.g, 2, 16, fc)
    //    .arg((uint)pixi.b, 2, 16, fc)
    //    .arg((uint)pixi.alpha, 2, 16, fc);

    //return srgb;
}

void ImageWidget::clearMouseHover()
{
    if (mouseMoveCleared_)
        return;

    auto pixPanel = mainWindow_->pixelInfoPanel;

    pixPanel->hoverPos->clear();
    pixPanel->hoverRgb->clear();

    mouseMoveCleared_ = true;
}

void ImageWidget::onMouseMove(int x, int y)
{
    auto pixPanel = mainWindow_->pixelInfoPanel;

    if (!imageInfo_)
        return;

    auto& ii = *imageInfo_;

    x /= zoom_;
    y /= zoom_;

    if (x < 0 || x >= ii.width || y < 0 || y >= ii.height) {
        return clearMouseHover();
    }

    auto& pixi = ii.pixels[y * ii.width + x];


    //QString::asprintf("%d, %d", x, y);

    //pixPanel->hoverPos->setText(tr("%1, %2").arg(x).arg(y));
    pixPanel->hoverPos->setText(QString::asprintf("%d, %d", x, y));
    pixPanel->hoverRgb->setText(formatRgb(pixi, ii.haveAlpha, pixi.alpha));
}

void ImageWidget::onMouseClick(int x, int y)
{
    if (!imageInfo_)
        return;

    auto pixPanel = mainWindow_->pixelInfoPanel;
    auto& ii = *imageInfo_;

    x /= zoom_;
    y /= zoom_;


    if (x < 0 || x >= ii.width || y < 0 || y >= ii.height) {
        pixPanel->selPos->clear();
        pixPanel->selRgb->clear();
        return;
    }

    auto& pixi = ii.pixels[y * ii.width + x];

    QString text;

    pixPanel->selPos->setText(QString::asprintf("%d, %d", x, y));
    pixPanel->selRgb->setText(formatRgb(pixi, ii.haveAlpha, pixi.alpha));

    {
        auto& p = pixi.rgbn;
        if (ii.haveAlpha) {
            text = QString::asprintf("%.2f, %.2f, %.2f, %.2f", p.r, p.g, p.b, pixi.alphan);
        } else {
            text = QString::asprintf("%.2f, %.2f, %.2f", p.r, p.g, p.b);
        }
        pixPanel->selRgbNorm->setText(text);
    }


    //if (ii.haveAlpha) {
    //    auto alphaText = tr("%1 (%2)").arg(pixi.alpha, 2, 16, QChar('0')).arg(float(pixi.alpha) / 255);
    //    pixPanel->selAlpha->setText(alphaText);
    //}

    if (ii.haveYCC) {
        auto& ycc = pixi.ycc;
        text = QString::asprintf("%02x %02x %02x", ycc.y, ycc.cb, ycc.cr);
        pixPanel->selYcc->setText(text);

        //text = QString::asprintf("%d %d %d", ycc.y, ycc.cb, ycc.cr);
        //pixPanel->selYccDec->setText(text);

        auto& yccn = pixi.yccn;
        text = QString::asprintf("%.2f, %.2f, %.2f", yccn.y, yccn.cb, yccn.cr);
        pixPanel->selYccNorm->setText(text);
    }

    {
        auto& p = pixi.hsv;
        text = QString::asprintf("%d %d %d", p.hue, p.sat, p.val);
        pixPanel->selHsv->setText(text);
    }


    {
        auto& p = pixi.hsvn;
        text = QString::asprintf("%.2f, %.2f, %.2f", p.hue, p.sat, p.val);
        pixPanel->selHsvNorm->setText(text);
    }

    {
        auto& p = pixi.lab;
        text = QString::asprintf("%.2f, %.2f, %.2f", p.l, p.a, p.b);
        pixPanel->selLab->setText(text);
    }
}



}  // namespace image_lab
