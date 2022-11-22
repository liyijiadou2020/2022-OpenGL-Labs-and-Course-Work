#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);  // 将 OpenGL 控件充满整个窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_act_DrawCube_triggered()
{

}

void MainWindow::on_act_DrawBall_triggered()
{

}

void MainWindow::on_act_DrawCone_triggered()
{

}

void MainWindow::on_act_MoveCube_triggered()
{

}

void MainWindow::on_act_MoveBall_triggered()
{

}

void MainWindow::on_act_MoveCone_triggered()
{

}
