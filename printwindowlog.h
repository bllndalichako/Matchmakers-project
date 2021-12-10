#ifndef PRINTWINDOWLOG_H
#define PRINTWINDOWLOG_H

#include <QDialog>

namespace Ui {
class PrintWIndowlog;
}

class PrintWIndowlog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintWIndowlog(QWidget *parent = nullptr);
    ~PrintWIndowlog();

private:
    Ui::PrintWIndowlog *ui;
};

#endif // PRINTWINDOWLOG_H
