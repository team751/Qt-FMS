#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QMainWindow>

#include "../src/fms.h"

namespace Ui {
class StatusWindow;
}

class StatusWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StatusWindow(QWidget *parent = 0);
    ~StatusWindow();
    
private slots:
    void on_startMatchButton_clicked();
    
    void on_abortMatchButton_clicked();
    
    void updateTiming(qint64 millisecondsElapsed);
    
private:
    Ui::StatusWindow *ui;
    
    FMS fms;
};

#endif // STATUSWINDOW_H
