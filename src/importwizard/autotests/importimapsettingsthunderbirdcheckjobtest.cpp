/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importimapsettingsthunderbirdcheckjobtest.h"
#include "importwizard/checks/importimapsettingsthunderbirdcheckjob.h"
#include "libsieveeditor_export.h"
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>

Q_DECLARE_METATYPE(SieveEditorUtil::SieveServerConfig)
extern LIBSIEVEEDITOR_EXPORT QString sieveeditor_thunderbird_default_toplevel_path;
ImportImapSettingsThunderbirdCheckJobTest::ImportImapSettingsThunderbirdCheckJobTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<SieveEditorUtil::SieveServerConfig>();
    QStandardPaths::setTestModeEnabled(true);
    sieveeditor_thunderbird_default_toplevel_path = QString();
}

ImportImapSettingsThunderbirdCheckJobTest::~ImportImapSettingsThunderbirdCheckJobTest() = default;

void ImportImapSettingsThunderbirdCheckJobTest::shouldHaveDefaultValue()
{
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/empty2"));
    ImportImapSettingsThunderbirdCheckJob check;
    QVERIFY(!check.settingsCanBeImported());
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldHaveDefaultValueWithEmptyDirectory()
{
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/empty"));
    ImportImapSettingsThunderbirdCheckJob check;
    QVERIFY(check.settingsCanBeImported());
    check.start();
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldBeAbleToImportSettings()
{
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/thunderbird1"));
    ImportImapSettingsThunderbirdCheckJob check;
    QVERIFY(check.settingsCanBeImported());
    check.start();
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldBeAbleToImportSettings2()
{
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + QStringLiteral("/thunderbird2"));
    ImportImapSettingsThunderbirdCheckJob check;
    QVERIFY(check.settingsCanBeImported());
    check.start();
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldHaveImportSettings_data()
{
    QTest::addColumn<QString>("directory");
    QTest::addColumn<int>("nbsignals");
    QTest::addColumn<int>("nbSignalsNoSettingsFound");
    QTest::newRow("thunderbird1-withoutsieve") << QStringLiteral("/thunderbird1") << 0 << 1;
    QTest::newRow("empty") << QStringLiteral("/empty") << 0 << 1;
    QTest::newRow("thunderbird2-withoutsieve") << QStringLiteral("/thunderbird2") << 0 << 1;
    QTest::newRow("thunderbirdencryptionnone") << QStringLiteral("/thunderbirdencryptionnone") << 2 << 0;
    QTest::newRow("thunderbirdencryptionssl") << QStringLiteral("/thunderbirdencryptionssl") << 2 << 0;
    QTest::newRow("thunderbirdencryptionstarttls") << QStringLiteral("/thunderbirdencryptionstarttls") << 2 << 0;

    QTest::newRow("thunderbirdencryptionnoneoneaccount") << QStringLiteral("/thunderbirdencryptionnoneoneaccount") << 1 << 0;
    QTest::newRow("thunderbirdencryptionssloneaccount") << QStringLiteral("/thunderbirdencryptionssloneaccount") << 1 << 0;
    QTest::newRow("thunderbirdencryptionstarttlsoneaccount") << QStringLiteral("/thunderbirdencryptionstarttlsoneaccount") << 1 << 0;
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldHaveImportSettings()
{
    QFETCH(QString, directory);
    QFETCH(int, nbsignals);
    QFETCH(int, nbSignalsNoSettingsFound);
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + directory);
    ImportImapSettingsThunderbirdCheckJob job;
    QVERIFY(job.settingsCanBeImported());
    QSignalSpy spy(&job, &ImportImapSettingsThunderbirdCheckJob::importSetting);
    QSignalSpy spy2(&job, &ImportImapSettingsThunderbirdCheckJob::noSettingsImported);

    job.start();
    QCOMPARE(spy.count(), nbsignals);
    QCOMPARE(spy2.count(), nbSignalsNoSettingsFound);
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldImportSieveSettings_data()
{
    QTest::addColumn<QString>("directory");
    QTest::addColumn<QString>("name");
    QTest::addColumn<SieveEditorUtil::SieveServerConfig>("settings");

    {
        SieveEditorUtil::SieveServerConfig settings;
        settings.sieveImapAccountSettings.setUserName(QStringLiteral("bla@kde.org"));
        settings.sieveImapAccountSettings.setServerName(QStringLiteral("sever.foo.org"));
        settings.sieveImapAccountSettings.setPort(993);
        settings.sieveImapAccountSettings.setAuthenticationType(KSieveCore::SieveImapAccountSettings::NTLM);
        settings.sieveSettings.userName = QStringLiteral("bla@kde.org");
        settings.sieveSettings.serverName = QStringLiteral("sever.foo.org");
        settings.sieveSettings.port = 4190;

        QTest::newRow("thunderbirdencryptionnoneoneaccount")
            << QStringLiteral("/thunderbirdencryptionnoneoneaccount") << QStringLiteral("bla@kde.org") << settings;
    }
    {
        SieveEditorUtil::SieveServerConfig settings;
        settings.sieveImapAccountSettings.setUserName(QStringLiteral("bla@kde.org"));
        settings.sieveImapAccountSettings.setServerName(QStringLiteral("sever.foo.org"));
        settings.sieveImapAccountSettings.setEncryptionMode(KSieveCore::SieveImapAccountSettings::EncryptionMode::SSLorTLS);
        settings.sieveImapAccountSettings.setAuthenticationType(KSieveCore::SieveImapAccountSettings::Plain);
        settings.sieveImapAccountSettings.setPort(993);
        settings.sieveSettings.userName = QStringLiteral("bla@kde.org");
        settings.sieveSettings.serverName = QStringLiteral("sever.foo.org");
        settings.sieveSettings.port = 4190;

        QTest::newRow("thunderbirdencryptionssloneaccount")
            << QStringLiteral("/thunderbirdencryptionssloneaccount") << QStringLiteral("bla@kde.org") << settings;
    }

    {
        SieveEditorUtil::SieveServerConfig settings;
        settings.sieveImapAccountSettings.setUserName(QStringLiteral("bla@kde.org"));
        settings.sieveImapAccountSettings.setServerName(QStringLiteral("sever.foo.org"));
        settings.sieveImapAccountSettings.setEncryptionMode(KSieveCore::SieveImapAccountSettings::EncryptionMode::STARTTLS);
        settings.sieveImapAccountSettings.setAuthenticationType(KSieveCore::SieveImapAccountSettings::GSSAPI);
        settings.sieveImapAccountSettings.setPort(993);
        settings.sieveSettings.userName = QStringLiteral("bla@kde.org");
        settings.sieveSettings.serverName = QStringLiteral("sever.foo.org");
        settings.sieveSettings.port = 4190;

        QTest::newRow("thunderbirdencryptionstarttlsoneaccount")
            << QStringLiteral("/thunderbirdencryptionstarttlsoneaccount") << QStringLiteral("bla@kde.org") << settings;
    }
}

void ImportImapSettingsThunderbirdCheckJobTest::shouldImportSieveSettings()
{
    QFETCH(QString, directory);
    QFETCH(QString, name);
    QFETCH(SieveEditorUtil::SieveServerConfig, settings);
    sieveeditor_thunderbird_default_toplevel_path = QString(QLatin1StringView(IMPORTWIZARD_DATA_DIR) + directory);
    ImportImapSettingsThunderbirdCheckJob job;
    QVERIFY(job.settingsCanBeImported());
    QSignalSpy spy(&job, &ImportImapSettingsThunderbirdCheckJob::importSetting);
    job.start();
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), name);
    auto importSettings = spy.at(0).at(1).value<SieveEditorUtil::SieveServerConfig>();
    QCOMPARE(importSettings, settings);
}

QTEST_MAIN(ImportImapSettingsThunderbirdCheckJobTest)

#include "moc_importimapsettingsthunderbirdcheckjobtest.cpp"
