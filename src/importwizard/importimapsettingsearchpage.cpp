/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "importimapsettingsearchpage.h"

#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include <KLocalizedString>

ImportImapSettingSearchPage::ImportImapSettingSearchPage(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel(i18n("Please select the program from which you like to import IMAP settings:"), this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    mFoundProgramList = new QListWidget(this);
    mFoundProgramList->setObjectName(QStringLiteral("foundprogramlist"));
    mainLayout->addWidget(mFoundProgramList);
    connect(mFoundProgramList, &QListWidget::itemChanged, this, &ImportImapSettingSearchPage::slotItemChanged);
}

ImportImapSettingSearchPage::~ImportImapSettingSearchPage()
{
}

void ImportImapSettingSearchPage::setProgramList(const QStringList &lst)
{
    for (const QString &prog : lst) {
        QListWidgetItem *item = new QListWidgetItem(prog, mFoundProgramList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }
}

QStringList ImportImapSettingSearchPage::selectedPrograms() const
{
    QStringList checkedItems;
    const int nbProgram = {mFoundProgramList->count()};
    for (int i = 0; i < nbProgram; ++i) {
        QListWidgetItem *item = mFoundProgramList->item(i);
        if (item->checkState() == Qt::Checked) {
            checkedItems << item->text();
        }
    }
    return checkedItems;
}

void ImportImapSettingSearchPage::slotItemChanged()
{
    bool hasSelectedItem = false;
    const int nbProgram = {mFoundProgramList->count()};
    for (int i = 0; i < nbProgram; ++i) {
        QListWidgetItem *item = mFoundProgramList->item(i);
        if (item->checkState() == Qt::Checked) {
            hasSelectedItem = true;
            break;
        }
    }
    Q_EMIT needToImportSettings(hasSelectedItem);
}
