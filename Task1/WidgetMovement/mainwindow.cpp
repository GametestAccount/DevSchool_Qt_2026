#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    resize(300, 600);

    m_update_timer = new QTimer(this);
    m_update_timer->setInterval(100);
    connect(m_update_timer, &QTimer::timeout, this, [this]() {
        for (QObject *child : children()) {
            QPushButton *button = qobject_cast<QPushButton *>(child);
            if (!button) {
                continue;
            }

            int speed = button->property("speed").toInt();
            if (button->underMouse()) {
                speed *= 2;
            }
            button->move(button->x(), button->y() + speed);

            if ((button->y() + button->height()) >= height()) {
                button->deleteLater();
                setStyleSheet("QMainWindow { background-color: red; }");
                setWindowTitle("You LOOSE!");
            }
        }
    });

    m_spawn_timer = new QTimer(this);
    m_spawn_timer->setSingleShot(true);
    connect(m_spawn_timer, &QTimer::timeout, this, [this]() {
        QPushButton *button = new QPushButton("*", this);
        button->resize(25, 25);
        connect(button, &QPushButton::clicked, this, [this]() {
            QPushButton *button = qobject_cast<QPushButton *>(sender());
            button->deleteLater();
        });

        int x = QRandomGenerator::global()->bounded(0, (width() - button->width()) + 1);
        int speed = QRandomGenerator::global()->bounded(1, 4 + 1);
        button->move(x, 100);
        button->setProperty("speed", speed);
        button->show();

        int spawn_time = QRandomGenerator::global()->bounded(100, 1000 + 1);
        m_spawn_timer->start(spawn_time);
    });

    m_update_timer->start();
    m_spawn_timer->start(1000);
}

MainWindow::~MainWindow() = default;
