#include "addtimerdialog.h"
#include "ui_addtimerdialog.h"

AddTimerDialog::AddTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTimerDialog)
{
    ui->setupUi(this);
}//

AddTimerDialog::~AddTimerDialog()
{
    delete ui;
}
// створюємо конструктор та деструктор
void AddTimerDialog::on_buttonBox_accepted()
{
    TimerModel* timer = new TimerModel;
    timer->name = ui->lineEdit->text();
    timer->type = checkedTimerType;
    timer->actionTime = ui->timeEdit->time();

    emit createTimer(timer);
}


void AddTimerDialog::on_stopWatchRadioButton_clicked()
{
    checkedTimerType = TimerModel::TimerType::STOPWATCH;
}


void AddTimerDialog::on_timerRadioButton_clicked()
{
     checkedTimerType = TimerModel::TimerType::TIMER;
}


void AddTimerDialog::on_alarmRadioButton_clicked()
{
     checkedTimerType = TimerModel::TimerType::ALARM;
}

