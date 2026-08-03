// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2017-2019 Alejandro Sirgo Rica & Contributors

#include "blurtool.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>

BlurTool::BlurTool(QObject* parent)
  : AbstractTwoPointTool(parent)
{}

QIcon BlurTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "blur.svg");
}

QString BlurTool::name() const
{
    return tr("Blur");
}

CaptureTool::Type BlurTool::type() const
{
    return CaptureTool::TYPE_BLUR;
}

QString BlurTool::description() const
{
    return tr("Set Blur as the paint tool");
}

QRect BlurTool::boundingRect() const
{
    return QRect(points().first, points().second).normalized();
}

CaptureTool* BlurTool::copy(QObject* parent)
{
    auto* tool = new BlurTool(parent);
    copyParams(this, tool);
    return tool;
}

void BlurTool::process(QPainter& painter, const QPixmap& pixmap)
{
    QRect selection = boundingRect().intersected(pixmap.rect());
    auto pixelRatio = pixmap.devicePixelRatio();
    QRect selectionScaled = QRect(selection.topLeft() * pixelRatio,
                                  selection.bottomRight() * pixelRatio);

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(10);
    auto* item = new QGraphicsPixmapItem(pixmap.copy(selectionScaled));
    item->setGraphicsEffect(blur);

    QGraphicsScene scene;
    scene.addItem(item);

    scene.render(&painter, selection, QRectF());
    blur->setBlurRadius(12);
    // multiple repeat for make blur effect stronger
    scene.render(&painter, selection, QRectF());
}

void BlurTool::drawSearchArea(QPainter& painter, const QPixmap& pixmap)
{
    Q_UNUSED(pixmap)
    painter.fillRect(boundingRect(), QBrush(Qt::black));
}

void BlurTool::paintMousePreview(QPainter& painter,
                                 const CaptureContext& context)
{
    Q_UNUSED(context)
    Q_UNUSED(painter)
}

void BlurTool::pressed(CaptureContext& context)
{
    Q_UNUSED(context)
}
