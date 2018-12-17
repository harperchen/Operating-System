#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QIcon>
#include <QFont>
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QScrollBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QTimer *timer;
    Ui::MainWindow *ui;

    void setCpuContent();
    void setFileContent();
    void setSystemContent();
    void setProcessContent();
    void setModulesContent();
    void setResourceContent();
    double getCpuRate(pid_t pid);
    void computeCpuRate(QStringList Content, int &cpuTotal, int &idle);

private slots:
    void timer_update();
    void on_tabWidget_currentChanged(int index);
};

#endif // MAINWINDOW_H
