#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tickets.h"
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFileInfo>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_next_clicked();

    void on_goToMenu_clicked();

    void on_next_2_clicked();

    void on_back_clicked();

private:
    Ui::MainWindow *ui;
    void error(QString);
    void hide();
    void showMenu();
    void showOption();
    void showResult();
    void showCorrectAnswer(int);
    void hideButtonsTest();
    void hideButtonsResult();
    void showButtonsTest(int);
    void showItem();
    tickets *ticket;
    void creatTest(QString);
    int numberOfOption;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmap_item;
};
#endif // MAINWINDOW_H
