#include "head.h"

int right(int argc, char *argv[]){
    int i = 1;
    long sum = 0;
    QApplication app(argc, argv);
    QLabel *pLabel = new QLabel;
    QTimer *timer = new QTimer;
    QWidget *right_window = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    timer->start(500);
    right_window->setWindowTitle("Sum");
    right_window->move(736, 100);
    right_window->setFixedSize(330, 250);
    pLabel->setStyleSheet("color:black");

    QObject::connect(timer, &QTimer::timeout, [&] () {
        if(i <= 1000){
            sum += i;
            pLabel->setText(QString("Sum from 1 to ") + QString::number(i) + QString(" is ") + QString::number(sum));
            i++;
        }
    });

    layout->addWidget(pLabel);
    right_window->setLayout(layout);
    right_window->show();

    return app.exec();
}
