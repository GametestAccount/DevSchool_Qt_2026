#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTimer *m_update_timer = nullptr;
    QTimer *m_spawn_timer = nullptr;
};

#endif // MAINWINDOW_H