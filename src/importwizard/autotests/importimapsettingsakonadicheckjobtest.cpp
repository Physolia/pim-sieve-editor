/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#include "importimapsettingsakonadicheckjobtest.h"
#include "../checks/importimapsettingsakonadicheckjob.h"

#include <QTest>
#include <QStandardPaths>
#include <QDebug>

ImportImapSettingsAkonadiCheckJobTest::ImportImapSettingsAkonadiCheckJobTest(QObject *parent)
    : QObject(parent)
{
}

ImportImapSettingsAkonadiCheckJobTest::~ImportImapSettingsAkonadiCheckJobTest()
{

}

void ImportImapSettingsAkonadiCheckJobTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}


void ImportImapSettingsAkonadiCheckJobTest::shouldHaveSettingsFiles()
{
    qputenv("XDG_CONFIG_DIRS", QString(QLatin1String(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/config/config1")).toLatin1().constData());
    ImportImapSettingsAkonadiCheckJob job;
    QVERIFY(job.settingsCanBeImported());
}

void ImportImapSettingsAkonadiCheckJobTest::shouldHaveNotSettingsFiles()
{
    qputenv("XDG_CONFIG_DIRS", QString(QLatin1String(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/config/noconfig")).toLatin1().constData());
    ImportImapSettingsAkonadiCheckJob job;
    QVERIFY(!job.settingsCanBeImported());
}

void ImportImapSettingsAkonadiCheckJobTest::shouldHaveSettingsFilesImap()
{
    qputenv("XDG_CONFIG_DIRS", QString(QLatin1String(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/config/config2")).toLatin1().constData());
    ImportImapSettingsAkonadiCheckJob job;
    QVERIFY(job.settingsCanBeImported());
}

void ImportImapSettingsAkonadiCheckJobTest::shouldHaveSettingsFilesMbox()
{
    qputenv("XDG_CONFIG_DIRS", QString(QLatin1String(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/config/config3")).toLatin1().constData());
    ImportImapSettingsAkonadiCheckJob job;
    QVERIFY(!job.settingsCanBeImported());
}

QTEST_MAIN(ImportImapSettingsAkonadiCheckJobTest)
