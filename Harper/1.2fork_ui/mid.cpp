#include "head.h"
#define LENGTH 100

int mid(int argc, char *argv[]){
    QApplication app(argc, argv);
    QFile *file = new QFile("/etc/fstab");
    QLabel *pLabel = new QLabel;
    QTimer *timer = new QTimer;
    QWidget *mid_window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    file->open(QIODevice::ReadOnly);
    timer->start(1000);
    mid_window->setWindowTitle("Content");
    mid_window->setFixedSize(766, 250);
    mid_window->move(300, 418);
    pLabel->setStyleSheet("color:black");
    pLabel->setWordWrap(true);
    QString content =QString(file->readAll().data());
    int len = LENGTH, size = file->size();

    QObject::connect(timer, &QTimer::timeout, [&,content] () {
        if(len <= size){
            pLabel->setText(content.mid(0, len));
            len += LENGTH;
        }
        else{
            pLabel->setText(content);
        }
    });

    layout->addWidget(pLabel);
    mid_window->setLayout(layout);
    mid_window->show();
    file->close();
    return app.exec();
}
