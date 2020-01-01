/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#ifndef IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOB_H
#define IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOB_H

#include "abstractimapsettingscheckjob.h"
#include "libsieveeditor_private_export.h"
class LIBSIEVEEDITOR_TESTS_EXPORT ImportImapSettingsThunderbirdCheckJob : public AbstractImapSettingsCheckJob
{
    Q_OBJECT
public:
    explicit ImportImapSettingsThunderbirdCheckJob(QObject *parent = nullptr);
    ~ImportImapSettingsThunderbirdCheckJob() override;

    void start() override;
    Q_REQUIRED_RESULT bool settingsCanBeImported() const override;
    Q_REQUIRED_RESULT QString name() const override;
private:
    Q_REQUIRED_RESULT bool importSettings(const QString &directory, const QString &defaultProfile);
    Q_REQUIRED_RESULT QMap<QString, QString> listProfile(QString &currentProfile, const QString &defaultSettingPath);
    Q_REQUIRED_RESULT QString defaultPath() const;
    void insertIntoMap(const QString &line);
    void addAuth(SieveEditorUtil::SieveServerConfig &config, const QString &accountName);
    void encryption(SieveEditorUtil::SieveServerConfig &config, const QString &accountName);

    QHash<QString, QVariant> mHashConfig;
};

#endif // IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOB_H
