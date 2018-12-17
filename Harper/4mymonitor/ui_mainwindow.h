/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *process;
    QGridLayout *gridLayout_2;
    QTableWidget *process_table;
    QWidget *source;
    QGridLayout *gridLayout_5;
    QWidget *cpu_widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *memory_layout;
    QLabel *label_2;
    QProgressBar *memory_Bar;
    QHBoxLayout *horizontalLayout_4;
    QLabel *memory_data;
    QHBoxLayout *swap_layout;
    QLabel *label_3;
    QProgressBar *swap_Bar;
    QHBoxLayout *horizontalLayout_5;
    QLabel *swap_data;
    QHBoxLayout *net_layout;
    QLabel *recv_label;
    QLabel *recv_data;
    QLabel *send_label;
    QLabel *send_data;
    QWidget *layoutWidget;
    QVBoxLayout *cpu_layout;
    QHBoxLayout *cpu_layout_1;
    QLabel *text_label_1;
    QLabel *color_label_1;
    QHBoxLayout *cpu_layout_2;
    QLabel *text_label_2;
    QLabel *color_label_2;
    QHBoxLayout *cpu_layout_3;
    QLabel *text_label_3;
    QLabel *color_label_3;
    QHBoxLayout *cpu_layout_4;
    QLabel *text_label_4;
    QLabel *color_label_4;
    QWidget *filesystem;
    QGridLayout *gridLayout_4;
    QTableWidget *file_table;
    QWidget *module;
    QGridLayout *gridLayout_3;
    QTableWidget *module_table;
    QWidget *system;
    QGridLayout *gridLayout;
    QGridLayout *SystemLayout;
    QLabel *ubuntu;
    QLabel *handware;
    QLabel *cpuinfo_label;
    QLabel *ubuntu_label;
    QLabel *memory_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(634, 383);
        QIcon icon;
        icon.addFile(QStringLiteral("icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        process = new QWidget();
        process->setObjectName(QStringLiteral("process"));
        gridLayout_2 = new QGridLayout(process);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        process_table = new QTableWidget(process);
        process_table->setObjectName(QStringLiteral("process_table"));
        process_table->setFrameShape(QFrame::Panel);
        process_table->setFrameShadow(QFrame::Raised);
        process_table->setLineWidth(1);

        gridLayout_2->addWidget(process_table, 0, 0, 1, 1);

        tabWidget->addTab(process, QString());
        source = new QWidget();
        source->setObjectName(QStringLiteral("source"));
        gridLayout_5 = new QGridLayout(source);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        cpu_widget = new QWidget(source);
        cpu_widget->setObjectName(QStringLiteral("cpu_widget"));
        verticalLayoutWidget = new QWidget(cpu_widget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(170, 30, 411, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        memory_layout = new QHBoxLayout();
        memory_layout->setSpacing(6);
        memory_layout->setObjectName(QStringLiteral("memory_layout"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        memory_layout->addWidget(label_2);

        memory_Bar = new QProgressBar(verticalLayoutWidget);
        memory_Bar->setObjectName(QStringLiteral("memory_Bar"));
        memory_Bar->setValue(0);

        memory_layout->addWidget(memory_Bar);


        verticalLayout->addLayout(memory_layout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        memory_data = new QLabel(verticalLayoutWidget);
        memory_data->setObjectName(QStringLiteral("memory_data"));
        memory_data->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(memory_data);


        verticalLayout->addLayout(horizontalLayout_4);

        swap_layout = new QHBoxLayout();
        swap_layout->setSpacing(6);
        swap_layout->setObjectName(QStringLiteral("swap_layout"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        swap_layout->addWidget(label_3);

        swap_Bar = new QProgressBar(verticalLayoutWidget);
        swap_Bar->setObjectName(QStringLiteral("swap_Bar"));
        swap_Bar->setValue(0);

        swap_layout->addWidget(swap_Bar);


        verticalLayout->addLayout(swap_layout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        swap_data = new QLabel(verticalLayoutWidget);
        swap_data->setObjectName(QStringLiteral("swap_data"));
        swap_data->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(swap_data);


        verticalLayout->addLayout(horizontalLayout_5);

        net_layout = new QHBoxLayout();
        net_layout->setSpacing(6);
        net_layout->setObjectName(QStringLiteral("net_layout"));
        recv_label = new QLabel(verticalLayoutWidget);
        recv_label->setObjectName(QStringLiteral("recv_label"));
        recv_label->setAlignment(Qt::AlignCenter);
        recv_label->setWordWrap(true);

        net_layout->addWidget(recv_label);

        recv_data = new QLabel(verticalLayoutWidget);
        recv_data->setObjectName(QStringLiteral("recv_data"));
        recv_data->setAlignment(Qt::AlignCenter);

        net_layout->addWidget(recv_data);

        send_label = new QLabel(verticalLayoutWidget);
        send_label->setObjectName(QStringLiteral("send_label"));
        send_label->setAlignment(Qt::AlignCenter);

        net_layout->addWidget(send_label);

        send_data = new QLabel(verticalLayoutWidget);
        send_data->setObjectName(QStringLiteral("send_data"));
        send_data->setAlignment(Qt::AlignCenter);

        net_layout->addWidget(send_data);


        verticalLayout->addLayout(net_layout);

        layoutWidget = new QWidget(cpu_widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 9, 141, 301));
        cpu_layout = new QVBoxLayout(layoutWidget);
        cpu_layout->setSpacing(6);
        cpu_layout->setContentsMargins(11, 11, 11, 11);
        cpu_layout->setObjectName(QStringLiteral("cpu_layout"));
        cpu_layout->setSizeConstraint(QLayout::SetNoConstraint);
        cpu_layout->setContentsMargins(0, 0, 0, 0);
        cpu_layout_1 = new QHBoxLayout();
        cpu_layout_1->setSpacing(6);
        cpu_layout_1->setObjectName(QStringLiteral("cpu_layout_1"));
        text_label_1 = new QLabel(layoutWidget);
        text_label_1->setObjectName(QStringLiteral("text_label_1"));
        text_label_1->setAlignment(Qt::AlignCenter);

        cpu_layout_1->addWidget(text_label_1);

        color_label_1 = new QLabel(layoutWidget);
        color_label_1->setObjectName(QStringLiteral("color_label_1"));
        color_label_1->setAlignment(Qt::AlignCenter);

        cpu_layout_1->addWidget(color_label_1);


        cpu_layout->addLayout(cpu_layout_1);

        cpu_layout_2 = new QHBoxLayout();
        cpu_layout_2->setSpacing(6);
        cpu_layout_2->setObjectName(QStringLiteral("cpu_layout_2"));
        text_label_2 = new QLabel(layoutWidget);
        text_label_2->setObjectName(QStringLiteral("text_label_2"));
        text_label_2->setAlignment(Qt::AlignCenter);

        cpu_layout_2->addWidget(text_label_2);

        color_label_2 = new QLabel(layoutWidget);
        color_label_2->setObjectName(QStringLiteral("color_label_2"));
        color_label_2->setAlignment(Qt::AlignCenter);

        cpu_layout_2->addWidget(color_label_2);


        cpu_layout->addLayout(cpu_layout_2);

        cpu_layout_3 = new QHBoxLayout();
        cpu_layout_3->setSpacing(6);
        cpu_layout_3->setObjectName(QStringLiteral("cpu_layout_3"));
        text_label_3 = new QLabel(layoutWidget);
        text_label_3->setObjectName(QStringLiteral("text_label_3"));
        text_label_3->setAlignment(Qt::AlignCenter);

        cpu_layout_3->addWidget(text_label_3);

        color_label_3 = new QLabel(layoutWidget);
        color_label_3->setObjectName(QStringLiteral("color_label_3"));
        color_label_3->setAlignment(Qt::AlignCenter);

        cpu_layout_3->addWidget(color_label_3);


        cpu_layout->addLayout(cpu_layout_3);

        cpu_layout_4 = new QHBoxLayout();
        cpu_layout_4->setSpacing(6);
        cpu_layout_4->setObjectName(QStringLiteral("cpu_layout_4"));
        text_label_4 = new QLabel(layoutWidget);
        text_label_4->setObjectName(QStringLiteral("text_label_4"));
        text_label_4->setAlignment(Qt::AlignCenter);

        cpu_layout_4->addWidget(text_label_4);

        color_label_4 = new QLabel(layoutWidget);
        color_label_4->setObjectName(QStringLiteral("color_label_4"));
        color_label_4->setAlignment(Qt::AlignCenter);

        cpu_layout_4->addWidget(color_label_4);


        cpu_layout->addLayout(cpu_layout_4);


        gridLayout_5->addWidget(cpu_widget, 0, 0, 1, 1);

        tabWidget->addTab(source, QString());
        filesystem = new QWidget();
        filesystem->setObjectName(QStringLiteral("filesystem"));
        gridLayout_4 = new QGridLayout(filesystem);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        file_table = new QTableWidget(filesystem);
        file_table->setObjectName(QStringLiteral("file_table"));

        gridLayout_4->addWidget(file_table, 0, 0, 1, 1);

        tabWidget->addTab(filesystem, QString());
        module = new QWidget();
        module->setObjectName(QStringLiteral("module"));
        gridLayout_3 = new QGridLayout(module);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        module_table = new QTableWidget(module);
        module_table->setObjectName(QStringLiteral("module_table"));

        gridLayout_3->addWidget(module_table, 0, 0, 1, 1);

        tabWidget->addTab(module, QString());
        system = new QWidget();
        system->setObjectName(QStringLiteral("system"));
        gridLayout = new QGridLayout(system);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        SystemLayout = new QGridLayout();
        SystemLayout->setSpacing(6);
        SystemLayout->setObjectName(QStringLiteral("SystemLayout"));
        SystemLayout->setSizeConstraint(QLayout::SetFixedSize);
        ubuntu = new QLabel(system);
        ubuntu->setObjectName(QStringLiteral("ubuntu"));

        SystemLayout->addWidget(ubuntu, 0, 0, 1, 1);

        handware = new QLabel(system);
        handware->setObjectName(QStringLiteral("handware"));

        SystemLayout->addWidget(handware, 2, 0, 1, 1);

        cpuinfo_label = new QLabel(system);
        cpuinfo_label->setObjectName(QStringLiteral("cpuinfo_label"));

        SystemLayout->addWidget(cpuinfo_label, 3, 0, 1, 1);

        ubuntu_label = new QLabel(system);
        ubuntu_label->setObjectName(QStringLiteral("ubuntu_label"));
        ubuntu_label->setTextFormat(Qt::PlainText);

        SystemLayout->addWidget(ubuntu_label, 1, 0, 1, 1);

        memory_label = new QLabel(system);
        memory_label->setObjectName(QStringLiteral("memory_label"));

        SystemLayout->addWidget(memory_label, 4, 0, 1, 1);


        gridLayout->addLayout(SystemLayout, 0, 0, 1, 1);

        tabWidget->addTab(system, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Monitor", 0));
        tabWidget->setTabText(tabWidget->indexOf(process), QApplication::translate("MainWindow", "Process", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\206\205\345\255\230", 0));
        memory_data->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\344\272\244\346\215\242", 0));
        swap_data->setText(QString());
        recv_label->setText(QString());
        recv_data->setText(QString());
        send_label->setText(QString());
        send_data->setText(QString());
        text_label_1->setText(QString());
        color_label_1->setText(QString());
        text_label_2->setText(QString());
        color_label_2->setText(QString());
        text_label_3->setText(QString());
        color_label_3->setText(QString());
        text_label_4->setText(QString());
        color_label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(source), QApplication::translate("MainWindow", "Source", 0));
        tabWidget->setTabText(tabWidget->indexOf(filesystem), QApplication::translate("MainWindow", "FileSystem", 0));
        tabWidget->setTabText(tabWidget->indexOf(module), QApplication::translate("MainWindow", "Module", 0));
        ubuntu->setText(QApplication::translate("MainWindow", "Ubuntu", 0));
        handware->setText(QApplication::translate("MainWindow", "Hardware", 0));
        cpuinfo_label->setText(QString());
        ubuntu_label->setText(QString());
        memory_label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(system), QApplication::translate("MainWindow", "System", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
