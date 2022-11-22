/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <MyOpenGLWidget04.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMOVE;
    QAction *actionDice;
    QAction *actionBall;
    QAction *actionCone;
    QAction *actionChange_Color_of_Light;
    QAction *action_1;
    QAction *action_2;
    QAction *action_3;
    QAction *actionWireFrame;
    QWidget *centralwidget;
    MyOpenGLWidget04 *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuPress_0_Change_color_of_light;
    QMenu *menuPress_1_Reset_white_color;
    QStatusBar *statusbar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(768, 556);
        MainWindow->setStyleSheet(QLatin1String("QWidget {\n"
"	background-color:rgb(68, 68, 68);\n"
"	color:rgb(255, 255, 255);\n"
"	font: 12pt;\n"
"}\n"
"QMenuBar {\n"
"	background-color:rgb(200, 200, 200);\n"
"	color:rgb(60, 60, 60);\n"
"}\n"
"QWidget:checked {\n"
"	background-color:rgb(150, 150, 150);\n"
"}"));
        actionMOVE = new QAction(MainWindow);
        actionMOVE->setObjectName(QStringLiteral("actionMOVE"));
        actionDice = new QAction(MainWindow);
        actionDice->setObjectName(QStringLiteral("actionDice"));
        actionDice->setCheckable(true);
        actionBall = new QAction(MainWindow);
        actionBall->setObjectName(QStringLiteral("actionBall"));
        actionBall->setCheckable(true);
        actionCone = new QAction(MainWindow);
        actionCone->setObjectName(QStringLiteral("actionCone"));
        actionCone->setCheckable(true);
        actionChange_Color_of_Light = new QAction(MainWindow);
        actionChange_Color_of_Light->setObjectName(QStringLiteral("actionChange_Color_of_Light"));
        actionChange_Color_of_Light->setCheckable(true);
        action_1 = new QAction(MainWindow);
        action_1->setObjectName(QStringLiteral("action_1"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_2->setCheckable(true);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_3->setCheckable(true);
        actionWireFrame = new QAction(MainWindow);
        actionWireFrame->setObjectName(QStringLiteral("actionWireFrame"));
        actionWireFrame->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new MyOpenGLWidget04(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(120, 20, 551, 351));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 768, 27));
        menuPress_0_Change_color_of_light = new QMenu(menubar);
        menuPress_0_Change_color_of_light->setObjectName(QStringLiteral("menuPress_0_Change_color_of_light"));
        menuPress_1_Reset_white_color = new QMenu(menubar);
        menuPress_1_Reset_white_color->setObjectName(QStringLiteral("menuPress_1_Reset_white_color"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);

        menubar->addAction(menuPress_0_Change_color_of_light->menuAction());
        menubar->addAction(menuPress_1_Reset_white_color->menuAction());
        toolBar_2->addAction(actionWireFrame);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionMOVE->setText(QApplication::translate("MainWindow", "MOVE", Q_NULLPTR));
        actionDice->setText(QApplication::translate("MainWindow", "Dice", Q_NULLPTR));
        actionBall->setText(QApplication::translate("MainWindow", "Ball", Q_NULLPTR));
        actionCone->setText(QApplication::translate("MainWindow", "Cone", Q_NULLPTR));
        actionChange_Color_of_Light->setText(QApplication::translate("MainWindow", "Change Color of Light", Q_NULLPTR));
        action_1->setText(QApplication::translate("MainWindow", "\320\273\320\260\320\2611:", Q_NULLPTR));
        action_2->setText(QApplication::translate("MainWindow", "Torus", Q_NULLPTR));
        action_3->setText(QApplication::translate("MainWindow", "Cone, Sphere, Cube", Q_NULLPTR));
        actionWireFrame->setText(QApplication::translate("MainWindow", "WireFrame", Q_NULLPTR));
        menuPress_0_Change_color_of_light->setTitle(QApplication::translate("MainWindow", "Press 0: Change color of light.", Q_NULLPTR));
        menuPress_1_Reset_white_color->setTitle(QApplication::translate("MainWindow", "Press 1: Reset white color.", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
