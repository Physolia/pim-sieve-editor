/*
  Copyright (c) 2014 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "sieveeditorcentralwidget.h"
#include "sieveeditormainwidget.h"
#include "sieveeditorconfigureserverpage.h"

SieveEditorCentralWidget::SieveEditorCentralWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    mConfigureWidget = new SieveEditorConfigureServerPage;
    connect(mConfigureWidget, SIGNAL(configureClicked()), SIGNAL(configureClicked()));
    addWidget(mConfigureWidget);
    mSieveEditorMainWidget = new SieveEditorMainWidget;
    connect(mSieveEditorMainWidget, &SieveEditorMainWidget::serverSieveFound, this, &SieveEditorCentralWidget::slotServerSieveFound);
    addWidget(mSieveEditorMainWidget);
    setCurrentWidget(mConfigureWidget);
}

SieveEditorCentralWidget::~SieveEditorCentralWidget()
{

}

void SieveEditorCentralWidget::slotServerSieveFound(bool hasServer)
{
    if (hasServer)
        setCurrentWidget(mSieveEditorMainWidget);
    else
        setCurrentWidget(mConfigureWidget);
}

SieveEditorMainWidget *SieveEditorCentralWidget::sieveEditorMainWidget() const
{
    return mSieveEditorMainWidget;
}
