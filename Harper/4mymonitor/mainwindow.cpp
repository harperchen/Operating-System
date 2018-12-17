#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    setWindowIcon(QIcon(":/new/prefix1/icon.png"));
    QWidget::connect(timer, SIGNAL(timeout()), this, SLOT(timer_update()));
    QWidget::connect(ui->tabWidget, SIGNAL(currentChanged()), this, SLOT(on_tabWidget_currentChanged()));
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_update(){
    int index = ui->tabWidget->currentIndex();
    if(index == 0){
        setProcessContent();
    }
    else if(index == 1){
        setCpuContent();
        setResourceContent();
    }
    else if(index == 2){
        setFileContent();
    }
    else if(index == 3){
        setModulesContent();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0){
        setProcessContent();
    }
    else if(index == 1){
        setCpuContent();
        setResourceContent();
    }
    else if(index == 2){
        setFileContent();
    }
    else if(index == 3){
        setModulesContent();
    }
    else{
        setSystemContent();
    }
}

void MainWindow::setResourceContent(){
    bool ok;
    double memtotal;
    double memfree;
    double swaptotal;
    double swapfree;
    QString tmpStr;
    QFile procFile;
    QStringList Content;
    procFile.setFileName("/proc/meminfo");
    if(!procFile.open(QIODevice::ReadOnly)){
        qDebug() << "Fail to open the /proc/meminfo file";
        qDebug() << errno;
    }
    while(1){
        int pos;
        tmpStr = procFile.readLine();
        if((pos = tmpStr.indexOf("MemTotal:")) == 0){
            pos += QString("MemTotal:\t").length();
            QString tmp;
            int kb = tmpStr.indexOf("kB");
            tmp = tmpStr.mid(pos, kb - pos);
            memtotal = tmp.toInt(&ok, 10);
            memtotal = memtotal * 1000.0 / (1024 * 1024 * 1024);
        }
        else if((pos = tmpStr.indexOf("MemAvailable:")) == 0){
            pos += QString("MemAvailable:\t").length();
            QString tmp;
            int kb = tmpStr.indexOf("kB");
            tmp = tmpStr.mid(pos, kb - pos);
            memfree = tmp.toInt(&ok, 10);
            memfree = memfree * 1000.0 / (1024 * 1024 * 1024);
        }
        else if((pos = tmpStr.indexOf("SwapTotal:")) == 0){
            pos += QString("SwapTotal:\t").length();
            QString tmp;
            int kb = tmpStr.indexOf("kB");
            tmp = tmpStr.mid(pos, kb - pos);
            swaptotal = tmp.toInt(&ok, 10);
            swaptotal = swaptotal * 1000.0 / (1024 * 1024 * 1024);
        }
        else if((pos = tmpStr.indexOf("SwapFree:")) == 0){
            pos += QString("SwapFree:\t").length();
            QString tmp;
            int kb = tmpStr.indexOf("kB");
            tmp = tmpStr.mid(pos, kb - pos);
            swapfree = tmp.toInt(&ok, 10);
            swapfree = swapfree * 1000.0 / (1024 * 1024 * 1024);
            break;
        }
    }
    procFile.close();
    int memory_rate = (memtotal - memfree) * 100 / memtotal;
    ui->memory_Bar->setRange(0, 100);
    ui->memory_Bar->setValue(memory_rate);
    ui->memory_data->setText("Total: " + QString::number(memtotal, 'f', 1) + "GiB\t\t\t\t\t" + "Free: " + QString::number(memfree, 'f', 1) + "GiB\t");
    int swap_rate;
    if(swaptotal){
        swap_rate = (swaptotal - swapfree) * 100 / swaptotal;
    }
    else{
        swap_rate = 0;
    }
    ui->swap_Bar->setRange(0, 100);
    ui->swap_Bar->setValue(swap_rate);
    ui->swap_data->setText("Total: " + QString::number(swaptotal, 'f', 1) + "GiB\t\t\t\t\t" + "Free: " + QString::number(swapfree, 'f', 1) + "GiB\t");

    procFile.setFileName("/proc/net/dev");
    if(!procFile.open(QIODevice::ReadOnly)){
        qDebug() << "Fail to open the /proc/meminfo file";
    }
    int i = 0;
    int upload;
    int download;
    while(1){
        tmpStr = procFile.readLine();
        if(i == 2){
            Content = QString(tmpStr).split(" ");
            foreach(QString item, Content){
                int j = Content.indexOf(item);
                if(item.compare("") == 0){
                    Content.removeAt(j);
                }
                if(item.contains('\n')){
                    int i = item.indexOf('\n');
                    item.remove(i, 1);
                    Content.replace(j, item);
                }
            }
            download = QString(Content.at(1)).toInt(&ok, 10) / 1000.0;
            upload = QString(Content.at(9)).toInt(&ok, 10) / 1000.0;
            break;
        }
        i++;
    }
    ui->recv_label->setText(QString("网络\n总计已接受"));
    ui->recv_data->setText(QString::number(download, 'f', 1) + "KB");
    ui->send_label->setText(QString("网络\n总计已发送"));
    ui->send_data->setText(QString::number(upload, 'f', 1) + "KB");
    procFile.close();
}

void MainWindow::setCpuContent(){
    QFile cpuFile;
    QStringList Content;
    int idle[5][2], cpuTotal[5][2];
    for(int i = 0; i < 2; i++){
        cpuFile.setFileName("/proc/stat");
        if(!cpuFile.open(QIODevice::ReadOnly)){
            qDebug() << "Fail to open the /proc/stat file";
        }
        cpuFile.readLine();
        for(int j = 1; j <= 4; j++){
            Content = QString(cpuFile.readLine()).split(" ");
            cpuTotal[j][i] = 0;
            computeCpuRate(Content, cpuTotal[j][i], idle[j][i]);
        }
        cpuFile.close();
        usleep(500000);
    }
    double rate[5];
    for(int i = 1; i <= 4; i++){
        int cpuTotal_diff = qAbs(cpuTotal[i][1] - cpuTotal[i][0]);
        int idle_diff = qAbs(idle[i][1] - idle[i][0]);
        rate[i] = (cpuTotal_diff - idle_diff) * 100.0 / cpuTotal_diff;
    }
    QPalette palette;

    ui->color_label_1->setFixedSize(40, 20);
    palette.setColor(QPalette::Background, QColor(255, 127, 0));
    ui->color_label_1->setAutoFillBackground(true);
    ui->color_label_1->setPalette(palette);
    ui->text_label_1->setText("CPU1: " + QString::number(rate[1], 'f', 2) + "%");

    ui->color_label_2->setFixedSize(40, 20);
    palette.setColor(QPalette::Background, QColor(205, 0, 0));
    ui->color_label_2->setAutoFillBackground(true);
    ui->color_label_2->setPalette(palette);
    ui->text_label_2->setText("CPU2: " + QString::number(rate[2], 'f', 2) + "%");

    ui->color_label_3->setFixedSize(40, 20);
    palette.setColor(QPalette::Background, QColor(69, 139, 0));
    ui->color_label_3->setAutoFillBackground(true);
    ui->color_label_3->setPalette(palette);
    ui->text_label_3->setText("CPU3: " + QString::number(rate[3], 'f', 2) + "%");

    ui->color_label_4->setFixedSize(40, 20);
    palette.setColor(QPalette::Background, QColor(16, 78, 139));
    ui->color_label_4->setAutoFillBackground(true);
    ui->color_label_4->setPalette(palette);
    ui->text_label_4->setText("CPU4: " + QString::number(rate[4], 'f', 2) + "%");

}

void MainWindow::computeCpuRate(QStringList Content, int &cpuTotal, int &idle){
    bool ok;
    for(int i = 1; i < Content.length(); i++){
        int num = Content.at(i).toInt(&ok, 10);
        if(i == 4){
            idle = num;
        }
        cpuTotal += num;
    }
}


void MainWindow::setModulesContent(){
    ui->module_table->setRowCount(0);
    ui->module_table->clearContents();

    bool ok;
    int memory;
    int totalNum = 0;

    QString name;
    QString instance;
    QString dependences;
    QString state;

    QFile procFile;
    QStringList Content;
    QStringList Header;

    ui->module_table->setColumnCount(5);
    Header << QString("模块名") << QString("状态") << QString("加载次数") << QString("内存") << QString("依赖模块");
    ui->module_table->setHorizontalHeaderLabels(Header);
    ui->module_table->horizontalHeader()->setHighlightSections(false);
    ui->module_table->verticalHeader()->setVisible(false);
    ui->module_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->module_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->module_table->setShowGrid(false);
    ui->module_table->horizontalHeader()->setStretchLastSection(true);
    ui->module_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->module_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->module_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);


    procFile.setFileName("/proc/modules");
    if(!procFile.open(QIODevice::ReadOnly)){
        qDebug() << "Fail to open /proc/modules file";
    }
    QByteArray tmp;
    while((tmp = procFile.readLine()).count()){
        Content = QString(tmp).split(" ");
        name = Content.at(0);
        memory = Content.at(1).toInt(&ok, 10);
        memory = memory / 1000.0;
        instance = Content.at(2);
        dependences = Content.at(3);
        dependences.replace(",", "  ");
        state = Content.at(4);

        int row = ui->module_table->rowCount();
        ui->module_table->insertRow(row);
        ui->module_table->setItem(totalNum, 0, new QTableWidgetItem(name));
        ui->module_table->setItem(totalNum, 1, new QTableWidgetItem(state));
        ui->module_table->setItem(totalNum, 2, new QTableWidgetItem(instance));
        ui->module_table->setItem(totalNum, 3, new QTableWidgetItem(QString::number(memory, 'f', 1) + "KB"));
        ui->module_table->setItem(totalNum, 4, new QTableWidgetItem(dependences));
        ui->module_table->item(totalNum, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->module_table->item(totalNum, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->module_table->item(totalNum, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->module_table->item(totalNum, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->module_table->item(totalNum, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        totalNum++;
    }
    procFile.close();
}



void MainWindow::setFileContent(){
    ui->file_table->setRowCount(0);
    ui->file_table->clearContents();
    int i = 0;
    QString tmp;
    QFile procFile;
    QStringList Content;
    system("df -h > /tmp/filesystem");
    procFile.setFileName("/tmp/filesystem");
    if(!procFile.open(QIODevice::ReadWrite)){
        qDebug() << "Fail to open file";
    }
    ui->file_table->horizontalHeader()->setHighlightSections(false);
    ui->file_table->verticalHeader()->setVisible(false);
    ui->file_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->file_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->file_table->setShowGrid(false);
    ui->file_table->horizontalHeader()->setStretchLastSection(true);
    ui->file_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->file_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->file_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    while((tmp = procFile.readLine()).count()){
        Content = QString(tmp).split(" ");
        foreach(QString item, Content){
                int j = Content.indexOf(item);
                if(item.compare("") == 0){
                    Content.removeAt(j);
                }
                if(item.contains('\n')){
                    int i = item.indexOf('\n');
                    item.remove(i, 1);
                    Content.replace(j, item);
                }
            }
        if(!i){
            ui->file_table->setColumnCount(Content.count());
            ui->file_table->setHorizontalHeaderLabels(Content);
            i++;
            continue;
        }
        int row = ui->file_table->rowCount();
        ui->file_table->insertRow(row);
        for(int j = 0; j < Content.count();j++){
            QTableWidgetItem *item = new QTableWidgetItem(Content.at(j));
            ui->file_table->setItem(i - 1, j, item);
            ui->file_table->item(i - 1, j)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        }
        i++;
    }
    procFile.close();
}

void MainWindow::setProcessContent(){
    ui->process_table->setRowCount(0);
    ui->process_table->clearContents();
    int pid;
    int totalNum = 0;

    QString name;
    QString user;
    QString state;
    QString tmpStr;
    QString memory;
    QString priority;

    QFile procFile;
    QStringList Content;
    QStringList Header;
    ui->process_table->setColumnCount(6);
    Header << QString("进程名") << QString("状态") << QString("用户") << QString("ID") << QString("内存") << QString("优先级");
    ui->process_table->setHorizontalHeaderLabels(Header);
    ui->process_table->horizontalHeader()->setHighlightSections(false);
    ui->process_table->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->process_table->verticalHeader()->setVisible(false);
    ui->process_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->process_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->process_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->process_table->setShowGrid(false);
    ui->process_table->horizontalHeader()->setStretchLastSection(true);
    ui->process_table->setSelectionBehavior ( QAbstractItemView::SelectRows);
    ui->process_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->process_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    QDir proc("/proc");
    QStringList proc_list = proc.entryList();
    foreach(QString process, proc_list){
        bool ok = false;
        pid = process.toInt(&ok, 10);
        if(!ok){
            continue;
        }
        procFile.setFileName("/proc/" + process + "/stat");
        if(!procFile.open(QIODevice::ReadOnly)){
            qDebug() << "Fail to open the stat file of process" << QString(pid);
            continue;
        }
        Content = QString(procFile.readLine()).split(" ");
        priority = Content.at(17);
        procFile.close();
        procFile.setFileName("/proc/" + process + "/status");
        if(!procFile.open(QIODevice::ReadOnly)){
            qDebug() << "Fail to open the status file of process" << QString(pid);
            continue;
        }
        while((tmpStr = procFile.readLine()).count()){
            int pos;
            if((pos = tmpStr.indexOf("Name:\t")) == 0){
                pos += QString("Name:\t").length();
                name = tmpStr.mid(pos);
                name.remove(name.length() - 1, 1);
            }
            else if((pos = tmpStr.indexOf("State:\t")) == 0){
                pos += QString("State:\t").length();
                state = tmpStr.mid(pos);
                state.remove(state.length() - 1, 1);
            }
            else if((pos = tmpStr.indexOf("Uid:\t")) == 0){
                pos += QString("Uid:\t").length();
                user = tmpStr.mid(pos);
                int end_pos = user.indexOf("\t");
                user = user.mid(0, end_pos);
                if(user.compare("0") == 0){
                    break;
                }
                user = QString(QLatin1String(getpwuid(user.toInt(&ok, 10))->pw_name));
            }
            else if((pos = tmpStr.indexOf("RssAnon:\t")) == 0){
                pos += QString("RssAnon:\t").length();
                memory = tmpStr.mid(pos);
                memory.remove(memory.length() - 1, 1);
                break;
            }
        }
        if(user.compare("harperchen") != 0){
            continue;
        }
        int row = ui->process_table->rowCount();
        ui->process_table->insertRow(row);
        ui->process_table->setItem(totalNum, 0, new QTableWidgetItem(name));
        ui->process_table->setItem(totalNum, 1, new QTableWidgetItem(state));
        ui->process_table->setItem(totalNum, 2, new QTableWidgetItem(user));
        ui->process_table->setItem(totalNum, 3, new QTableWidgetItem(QString::number(pid)));
        ui->process_table->setItem(totalNum, 4, new QTableWidgetItem(memory));
        ui->process_table->setItem(totalNum, 5, new QTableWidgetItem(priority));
        ui->process_table->item(totalNum, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->process_table->item(totalNum, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->process_table->item(totalNum, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->process_table->item(totalNum, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->process_table->item(totalNum, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->process_table->item(totalNum, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        totalNum++;
        procFile.close();
    }
}

void MainWindow::setSystemContent(){
    char logname[32];
    QString ubuntu_text;
    struct utsname kernel_info;

    uname(&kernel_info);
    memcpy(logname, getenv("LOGNAME"), 32);

    QFont small_font("Microsoft YaHei", 11);
    QFont big_font("Microsoft YaHei", 12, 75);
    ui->ubuntu->setFont(big_font);
    ui->handware->setFont(big_font);
    ui->ubuntu_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->ubuntu_label->setWordWrap(true);
    ui->ubuntu_label->setFont(small_font);
    ubuntu_text.append(tr("\t用户:")).append(QString(logname)).append("\n")
            .append(tr("\t版本:")).append(QString(kernel_info.version)).append("\n")
            .append(tr("\t内核:")).append(QString(kernel_info.sysname)).append(" ").append(QString(kernel_info.release));
    ui->ubuntu_label->setText(ubuntu_text);

    QFile cpuFile;
    cpuFile.setFileName("/proc/cpuinfo");
    if(cpuFile.open(QIODevice::ReadOnly)){
        qDebug() << "Fail to open the /proc/cpuinfo file";
    }
    QString cpu_mhz;
    QString tmpStr;
    QString hardware_text;
    QString model_name;
    QString vendor_id;
    QString cache_size;
    while(1){
        int pos;
        tmpStr = cpuFile.readLine();
        if((pos = tmpStr.indexOf("model name\t:")) == 0){
            pos += QString("model name\t:").length();
            model_name = tmpStr.mid(pos);
            model_name.remove(model_name.length() - 1, 1);
        }
        else if((pos = tmpStr.indexOf("vendor_id\t:")) == 0){
            pos += QString("vendor_id\t:").length();
            vendor_id = tmpStr.mid(pos);
            vendor_id.remove(vendor_id.length() - 1, 1);
        }
        else if((pos = tmpStr.indexOf("cpu MHz\t\t:")) == 0){
            pos += QString("cpu MHz\t\t:").length();
            cpu_mhz = tmpStr.mid(pos);
            cpu_mhz.remove(cpu_mhz.length() - 1, 1);
        }
        else if((pos = tmpStr.indexOf("cache size\t:")) == 0){
            pos += QString("cache size\t:").length();
            cache_size = tmpStr.mid(pos);
            cache_size.remove(cache_size.length() - 1, 1);
            break;
        }
    }
    ui->cpuinfo_label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->cpuinfo_label->setWordWrap(true);
    ui->cpuinfo_label->setFont(small_font);
    hardware_text.append(tr("\t处理器:")).append(model_name).append("\n")
            .append(tr("\tCPU类型:")).append(vendor_id).append("\n")
            .append(tr("\tCPU频率:")).append(cpu_mhz).append("\n")
            .append(tr("\tCache大小:")).append(cache_size);
    ui->cpuinfo_label->setText(hardware_text);
    cpuFile.close();
}
