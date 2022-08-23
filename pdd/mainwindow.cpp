#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(short i=1;i<=40;i++) ui->comboBox->addItem(QString::number(i));
    hideButtonsTest();
    hideButtonsResult();
    ui->goToMenu->hide();
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    pixmap_item = new QGraphicsPixmapItem();
    scene->addItem(pixmap_item);
    error((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/wall.jpg");
    pixmap_item->setPixmap((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/wall.jpg");
    QPainter painter1;
    painter1.setPen(QPen(Qt::red));
    painter1.drawPolygon(QPolygon()<<QPoint(5, 20)<<QPoint(35, 40)<<QPoint(40, 100));
    painter1.drawRect(50,50,40,40);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    hide();
    creatTest(QString::number(qrand()%40+1));
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    creatTest(ui->comboBox->currentText());
}

void MainWindow::hide()
{
    ui->comboBox->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
}

void MainWindow::showMenu()
{
    ui->comboBox->show();
    ui->pushButton->show();
    ui->pushButton_2->show();
}

//http://www.prog.org.ru/topic_11416_0.html
void MainWindow::showOption()
{
    showButtonsTest(ticket->numberOfOptions[numberOfOption]);
    pixmap_item->setPixmap(ticket->pictures[numberOfOption]);
    ui->graphicsView->fitInView(pixmap_item, Qt::KeepAspectRatio);
    numberOfOption++;
    ui->radioButton->setChecked(1);
}

void MainWindow::showResult()
{
    ui->youranswer->show();
    ui->label->show();
    ui->label_2->show();
    ui->back->show();
    ui->next_2->show();
    ui->label->clear();
    int rez=0;
    for (int i=0; i<20; i++)
    {
        if(ticket->answer[i]==ticket->correctAnswer[i])rez++;
    }
    ui->label->setText("Результат:"+QString::number(rez)+"/20");
    numberOfOption=0;
    showCorrectAnswer(numberOfOption);
}

void MainWindow::showCorrectAnswer(int a)
{
    ui->youranswer->setText("Ваш ответ: "+QString::number(ticket->answer[a])+
                            "\nПравильный ответ: "+QString::number(ticket->correctAnswer[a]));
    pixmap_item->setPixmap(ticket->pictures[a]);
    ui->graphicsView->fitInView(pixmap_item, Qt::KeepAspectRatio);
    if(ticket->answer[a]==ticket->correctAnswer[a]){
        error((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/ok.png");
        QPixmap pixmap((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/ok.png");
        ui->label_2->setPixmap(pixmap);
    }
    else{
        error((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/error.png");
        QPixmap pixmap((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/error.png");
        ui->label_2->setPixmap(pixmap);
    }
}

void MainWindow::hideButtonsTest()
{
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->radioButton_4->hide();
    ui->next->hide();
}

void MainWindow::hideButtonsResult()
{
    ui->youranswer->hide();
    ui->label_2->hide();
    ui->label->hide();
    ui->back->hide();
    ui->next_2->hide();
}

void MainWindow::showButtonsTest(int a)
{
    ui->next->show();
    if(a>=1) ui->radioButton->show();
    if(a>=2) ui->radioButton_2->show();
    if(a>=3) ui->radioButton_3->show();
    if(a>=4) ui->radioButton_4->show();
}

void MainWindow::showItem()
{
    ui->centralwidget->show();
    ui->pushButton->show();
    ui->pushButton_2->show();

}

void MainWindow::creatTest(QString str)
{
    ticket = new tickets();
    QString doc=(QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/"+str +"/";
    error(doc+"0.txt");
    QFile text(doc+"0.txt");
    text.open(QIODevice::ReadOnly);
    if(!text.isOpen()) on_goToMenu_clicked();
    QVector<QString> buf;
    buf.push_back(text.readLine());
    buf.push_back(text.readLine());
    for(int i=0;i<40;i+=2){
        ticket->numberOfOptions[i/2]=buf[0].mid(i,1).toInt();
        ticket->correctAnswer[i/2]=buf[1].mid(i,1).toInt();
        error(doc+QString::number((i+2)/2)+".jpg");
        ticket->pictures[i/2]=doc+QString::number((i+2)/2)+".jpg";
    }
    text.close();
    numberOfOption=0;
    ui->goToMenu->show();
    showOption();
}


void MainWindow::on_next_clicked()
{
    if(ui->radioButton->isChecked())ticket->answer[numberOfOption-1]=1;
    if(ui->radioButton_2->isChecked())ticket->answer[numberOfOption-1]=2;
    if(ui->radioButton_3->isChecked())ticket->answer[numberOfOption-1]=3;
    if(ui->radioButton_4->isChecked())ticket->answer[numberOfOption-1]=4;
    hideButtonsTest();
    if(numberOfOption==20) showResult();
    else showOption();
}


void MainWindow::on_goToMenu_clicked()
{
    delete ticket;
    hideButtonsResult();
    hideButtonsTest();
    ui->goToMenu->hide();
    showMenu();
    error((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/wall.jpg");
    pixmap_item->setPixmap((QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation))[0]+"/pdd/resources/wall.jpg");
    ui->graphicsView->fitInView(pixmap_item, Qt::KeepAspectRatio);
}


void MainWindow::on_next_2_clicked()
{
    if(numberOfOption!=19)showCorrectAnswer(++numberOfOption);
}


void MainWindow::on_back_clicked()
{
    if(numberOfOption!=0)showCorrectAnswer(--numberOfOption);
}

void MainWindow::error(QString str)
{
    if(!QFileInfo::exists(str)){
        QMessageBox messageBox;
        messageBox.critical(0,"Ошибка","Не найден файл:\n"+str);
        messageBox.setFixedSize(500,200);
        exit(0);
    }
}
