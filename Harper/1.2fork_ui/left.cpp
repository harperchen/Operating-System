#include "head.h"

int left(int argc, char *argv[]){
    QApplication app(argc, argv);
    QLabel *pLabel = new QLabel;
    QTimer *timer = new QTimer;
    QWidget *left_window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    timer->start(1000);
    left_window->setWindowTitle("Time");
    left_window->move(300, 100);
    left_window->setFixedSize(330, 250);
    pLabel->setStyleSheet("color:black");

    QObject::connect(timer, &QTimer::timeout, [=] () {
        QDateTime CurrentTime = QDateTime::currentDateTime();
        QString Timestr = CurrentTime.toString("  yyyy年-MM月-dd日  hh:mm:ss  ");
        pLabel->setText(Timestr);
    });

    layout->addWidget(pLabel);
    left_window->setLayout(layout);
    left_window->show();
    return app.exec();
}
