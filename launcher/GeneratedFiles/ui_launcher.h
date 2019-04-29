/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_launcherClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *launcherClass)
    {
        if (launcherClass->objectName().isEmpty())
            launcherClass->setObjectName(QStringLiteral("launcherClass"));
        launcherClass->resize(600, 400);
        menuBar = new QMenuBar(launcherClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        launcherClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(launcherClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        launcherClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(launcherClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        launcherClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(launcherClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        launcherClass->setStatusBar(statusBar);

        retranslateUi(launcherClass);

        QMetaObject::connectSlotsByName(launcherClass);
    } // setupUi

    void retranslateUi(QMainWindow *launcherClass)
    {
        launcherClass->setWindowTitle(QApplication::translate("launcherClass", "launcher", 0));
    } // retranslateUi

};

namespace Ui {
    class launcherClass: public Ui_launcherClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
