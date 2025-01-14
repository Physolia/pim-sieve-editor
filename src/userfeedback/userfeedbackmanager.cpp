/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "userfeedbackmanager.h"
#include <KUserFeedbackQt6/ApplicationVersionSource>
#include <KUserFeedbackQt6/LocaleInfoSource>
#include <KUserFeedbackQt6/PlatformInfoSource>
#include <KUserFeedbackQt6/Provider>
#include <KUserFeedbackQt6/QtVersionSource>
#include <KUserFeedbackQt6/ScreenInfoSource>
#include <KUserFeedbackQt6/StartCountSource>
#include <KUserFeedbackQt6/UsageTimeSource>

UserFeedBackManager::UserFeedBackManager(QObject *parent)
    : QObject(parent)
    , mUserFeedbackProvider(new KUserFeedback::Provider(this))
{
    mUserFeedbackProvider->setProductIdentifier(QStringLiteral("org.kde.pim-sieve-editor"));
    mUserFeedbackProvider->setFeedbackServer(QUrl(QStringLiteral("https://telemetry.kde.org/")));
    mUserFeedbackProvider->setSubmissionInterval(7);
    mUserFeedbackProvider->setApplicationStartsUntilEncouragement(5);
    mUserFeedbackProvider->setEncouragementDelay(30);

    mUserFeedbackProvider->addDataSource(new KUserFeedback::ApplicationVersionSource);
    mUserFeedbackProvider->addDataSource(new KUserFeedback::PlatformInfoSource);
    mUserFeedbackProvider->addDataSource(new KUserFeedback::ScreenInfoSource);
    mUserFeedbackProvider->addDataSource(new KUserFeedback::QtVersionSource);

    mUserFeedbackProvider->addDataSource(new KUserFeedback::StartCountSource);
    mUserFeedbackProvider->addDataSource(new KUserFeedback::UsageTimeSource);

    mUserFeedbackProvider->addDataSource(new KUserFeedback::LocaleInfoSource);
}

UserFeedBackManager *UserFeedBackManager::self()
{
    static UserFeedBackManager s_self;
    return &s_self;
}

KUserFeedback::Provider *UserFeedBackManager::userFeedbackProvider() const
{
    return mUserFeedbackProvider;
}

#include "moc_userfeedbackmanager.cpp"
