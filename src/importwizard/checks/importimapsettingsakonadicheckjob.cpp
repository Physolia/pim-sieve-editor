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

#include "importimapsettingsakonadicheckjob.h"
#include <KLocalizedString>
#include <QStandardPaths>
#include <QDir>

ImportImapSettingsAkonadiCheckJob::ImportImapSettingsAkonadiCheckJob(QObject *parent)
    : AbstractImapSettingsCheckJob(parent)
{

}

ImportImapSettingsAkonadiCheckJob::~ImportImapSettingsAkonadiCheckJob()
{

}

void ImportImapSettingsAkonadiCheckJob::start()
{
    //TODO
}

bool ImportImapSettingsAkonadiCheckJob::settingsCanBeImported() const
{
    const QStringList dirs = QStandardPaths::locateAll(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory);
    for (const QString &dir : dirs) {
        const QStringList fileNames = QDir(dir).entryList(QStringList() << QStringLiteral("*.rc"));
        for (const QString &file : fileNames) {
            if (file.startsWith(QStringLiteral("akonadi_kolab_resource")) ||
                    file.startsWith(QStringLiteral("akonadi_imap_resource"))) {
                return true;
            }
        }
    }

    return false;
}

QString ImportImapSettingsAkonadiCheckJob::name() const
{
    return i18n("Akonadi IMAP Settings");
}
