/*
   Copyright (C) 2013-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "sieveeditorscriptwidget.h"
#include <KSieveUi/SieveEditor>

#include <QHBoxLayout>

SieveEditorScriptWidget::SieveEditorScriptWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setMargin(0);
    mSieveEditor = new KSieveUi::SieveEditor;
}

SieveEditorScriptWidget::~SieveEditorScriptWidget()
{
}

void SieveEditorScriptWidget::setScript(const QString &script)
{
    mSieveEditor->setScript(script);
}

void SieveEditorScriptWidget::setScriptName(const QString &scriptName)
{
    mSieveEditor->setScriptName(scriptName);
}

void SieveEditorScriptWidget::setSieveCapabilities(const QStringList &capabilities)
{
    mSieveEditor->setSieveCapabilities(capabilities);
}
