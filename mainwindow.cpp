#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "printwindowlog.h"
#include <string>
#include <map>
using namespace std;
typedef map<string, string> Couples;
Couples Matchmaking();


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_pressed()
{
    ui->label->setText("Starting matchmaking...");
   Matchmaking();
   PrintWIndowlog output;
   output.setModal(true);
   output.exec();

}

