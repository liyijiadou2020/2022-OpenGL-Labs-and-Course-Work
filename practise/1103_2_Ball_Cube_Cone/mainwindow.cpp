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
    ui->openGLWidget->is_draw_sphere = ui->act_DrawCube->isChecked();
    ui->openGLWidget->updateGL();
}

void MainWindow::on_act_DrawBall_triggered()
{
    ui->openGLWidget->is_draw_sphere = ui->act_DrawBall->isChecked();
    ui->openGLWidget->updateGL();
}

void MainWindow::on_act_DrawCone_triggered()
{
    ui->openGLWidget->is_draw_cone = ui->act_DrawCone->isChecked();
    ui->openGLWidget->updateGL();
}

void MainWindow::on_act_MoveCube_triggered()
{
    ui->openGLWidget->is_move_cube = ui->act_MoveCube->isChecked();
}

void MainWindow::on_act_MoveBall_triggered()
{
    ui->openGLWidget->is_move_sphere = ui->act_MoveBall->isChecked();
}

void MainWindow::on_act_MoveCone_triggered()
{
    ui->openGLWidget->is_move_cone = ui->act_MoveCone->isChecked();
}
