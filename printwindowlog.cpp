#include "printwindowlog.h"
#include "ui_printwindowlog.h"
#include <QString>
#include <string>
#include <queue>
#include <map>
#include <iostream>
using namespace std;
typedef map<string, string> Couples;
Couples Matchmaking();
Couples Matchmaking2();

PrintWIndowlog::PrintWIndowlog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintWIndowlog)
{
    //beatrice's list
     ui->setupUi(this);
   Couples temp = Matchmaking();
   int count = 0;
   QString name = "worked";
   queue <QLabel*> qlabels;
   qlabels.push(ui->label_7);
   qlabels.push(ui->label_8);
   qlabels.push(ui->label_11);
   qlabels.push(ui->label_12);
   qlabels.push(ui->label_15);
   qlabels.push(ui->label_16);
   qlabels.push(ui->label_19);
   qlabels.push(ui->label_20);
   qlabels.push(ui->label_23);
   qlabels.push(ui->label_24);
   qlabels.push(ui->label_27);
   qlabels.push(ui->label_28);
   qlabels.push(ui->label_31);
   qlabels.push(ui->label_32);
   qlabels.push(ui->label_35);
   qlabels.push(ui->label_36);
   qlabels.push(ui->label_39);
   qlabels.push(ui->label_40);
   qlabels.push(ui->label_43);
   qlabels.push(ui->label_44);

   for (Couples::const_iterator it = temp.begin(); count < 10; ++it)
   {
       QLabel* front = qlabels.front();
       qlabels.pop();
       name = QString::fromStdString(it->first);
       front->setText(name);
       front = qlabels.front();
       qlabels.pop();
       name = QString::fromStdString(it->second);
       front->setText(name);
        count++;
   }

//alex's matrix
   Couples temp2 = Matchmaking2();
   int count2 = 0;
   QString name2 = "worked";
   queue <QLabel*> qlabels2;
   qlabels2.push(ui->label_9);
   qlabels2.push(ui->label_10);
   qlabels2.push(ui->label_13);
   qlabels2.push(ui->label_14);
   qlabels2.push(ui->label_17);
   qlabels2.push(ui->label_18);
   qlabels2.push(ui->label_21);
   qlabels2.push(ui->label_22);
   qlabels2.push(ui->label_25);
   qlabels2.push(ui->label_26);
   qlabels2.push(ui->label_29);
   qlabels2.push(ui->label_30);
   qlabels2.push(ui->label_33);
   qlabels2.push(ui->label_34);
   qlabels2.push(ui->label_37);
   qlabels2.push(ui->label_38);
   qlabels2.push(ui->label_41);
   qlabels2.push(ui->label_42);
   qlabels2.push(ui->label_45);
   qlabels2.push(ui->label_46);

   for (Couples::const_iterator it = temp2.begin(); count2 < 10; ++it)
   {
       QLabel* front = qlabels2.front();
       qlabels2.pop();
       name2 = QString::fromStdString(it->first);
       front->setText(name2);
       front = qlabels2.front();
       qlabels2.pop();
       name2 = QString::fromStdString(it->second);
       front->setText(name2);
        count2++;
   }


}

PrintWIndowlog::~PrintWIndowlog()
{
    delete ui;
}
