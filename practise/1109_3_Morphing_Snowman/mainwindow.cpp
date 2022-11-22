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


void MainWindow::on_actionDice_triggered()
{
     ui->openGLWidget->is_move_dice = ui->actionDice->isChecked();
}

void MainWindow::on_actionBall_triggered()
{
    ui->openGLWidget->is_move_ball = ui->actionBall->isChecked();
}

void MainWindow::on_actionCone_triggered()
{
    ui->openGLWidget->is_move_cone = ui->actionCone->isChecked();
}

void MainWindow::on_actionChange_Color_of_Light_triggered()
{
    ui->openGLWidget->is_change_color = ui->actionCone->isChecked();
}

void MainWindow::on_action_2_triggered()
{

}

void MainWindow::on_action_3_triggered()
{

}
