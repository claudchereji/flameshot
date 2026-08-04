// SPDX-License-Identifier: GPL-3.0-or-later

#include "autoresizetool.h"
#include <QPainter>

AutoResizeTool::AutoResizeTool(QObject* parent)
  : AbstractActionTool(parent)
{}

bool AutoResizeTool::closeOnButtonPressed() const
{
    return false;
}

bool AutoResizeTool::isSelectable() const
{
    return true;
}

QIcon AutoResizeTool::icon(const QColor& background, bool inEditor) const
{
    Q_UNUSED(inEditor)
    return QIcon(iconPath(background) + "mail-spark.svg");
}

QString AutoResizeTool::name() const
{
    return tr("Auto Resize");
}

CaptureTool::Type AutoResizeTool::type() const
{
    return CaptureTool::TYPE_AUTORESIZE;
}

QString AutoResizeTool::description() const
{
    return tr("Auto resize screenshot to 920px width on export");
}

CaptureTool* AutoResizeTool::copy(QObject* parent)
{
    return new AutoResizeTool(parent);
}

void AutoResizeTool::pressed(CaptureContext& context)
{
    Q_UNUSED(context)
    emit requestAction(REQ_TOGGLE_AUTORESIZE);
}
