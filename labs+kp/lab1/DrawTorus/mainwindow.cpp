#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);  // 将 OpenGL 控件充满整个窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_act_1_triggered()
{
    ui->openGLWidget->is_change_scale = true;
}

void MainWindow::on_act_2_triggered()
{
    ui->openGLWidget->is_change_scale = false;
}
