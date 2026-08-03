// SPDX-License-Identifier: GPL-3.0-or-later

#include "bordertool.h"
#include <QPainter>

BorderTool::BorderTool(QObject* parent)
  : AbstractActionTool(parent)
{}

bool BorderTool::closeOnButtonPressed() const
{
    return false;
}

bool BorderTool::isSelectable() const
{
    return true;
}

QIcon BorderTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "border-outer.svg");
}

QString BorderTool::name() const
{
    return tr("Border");
}

CaptureTool::Type BorderTool::type() const
{
    return CaptureTool::TYPE_BORDER;
}

QString BorderTool::description() const
{
    return tr("Add a border to the screenshot");
}

CaptureTool* BorderTool::copy(QObject* parent)
{
    return new BorderTool(parent);
}

void BorderTool::pressed(CaptureContext& context)
{
    Q_UNUSED(context)
    emit requestAction(REQ_TOGGLE_BORDER);
}
