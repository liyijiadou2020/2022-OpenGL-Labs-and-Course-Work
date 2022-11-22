#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_act_DrawCube_triggered();
    void on_act_DrawBall_triggered();
    void on_act_DrawCone_triggered();

    void on_act_MoveCube_triggered();
    void on_act_MoveBall_triggered();
    void on_act_MoveCone_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
