#pragma once

#include <QtWidgets/QWidget>
#include "ui_OpenGLTest.h"

class OpenGLTest : public QWidget
{
    Q_OBJECT

public:
    OpenGLTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::OpenGLTestClass ui;
};
