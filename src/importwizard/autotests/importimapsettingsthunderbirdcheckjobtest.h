/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOBTEST_H
#define IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOBTEST_H

#include <QObject>

class ImportImapSettingsThunderbirdCheckJobTest : public QObject
{
    Q_OBJECT
public:
    explicit ImportImapSettingsThunderbirdCheckJobTest(QObject *parent = nullptr);
    ~ImportImapSettingsThunderbirdCheckJobTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldBeAbleToImportSettings();
    void shouldHaveDefaultValueWithEmptyDirectory();
    void shouldBeAbleToImportSettings2();

    void shouldHaveImportSettings();
    void shouldHaveImportSettings_data();
    void shouldImportSieveSettings_data();
    void shouldImportSieveSettings();
};

#endif // IMPORTIMAPSETTINGSTHUNDERBIRDCHECKJOBTEST_H
