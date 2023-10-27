#ifndef ADDTIMERDIALOG_H
#define ADDTIMERDIALOG_H

#include <QDialog>
#include "timermodel.h"
namespace Ui {
class AddTimerDialog;
}

class AddTimerDialog : public QDialog// успадковує від QDialog
{
    Q_OBJECT //макрос

public:
    explicit AddTimerDialog(QWidget *parent = nullptr);
    ~AddTimerDialog();
signals:
    void createTimer(TimerModel* model);// сигнали. які породжує цей клас

private slots:

    void on_buttonBox_accepted();

    void on_stopWatchRadioButton_clicked();

    void on_timerRadioButton_clicked();

    void on_alarmRadioButton_clicked(); // приватні події, які для яких потім буде створено реалізацію

private:
    Ui::AddTimerDialog *ui;
    TimerModel::TimerType checkedTimerType = TimerModel::TimerType::STOPWATCH;
//інтерфейс вікна
};

#endif // ADDTIMERDIALOG_H
