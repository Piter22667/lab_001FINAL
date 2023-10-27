#include "timermodel.h"
#include <QDebug>
TimerModel::TimerModel(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &TimerModel::onTimerProccesing);
    qDebug() << "New Timer Created";
    seconds = 0;
    id = -1;
}

QString TimerModel::getType() const
{
    switch(type){
    case TimerType:: ALARM:
        return "Alarm";
    case TimerType::STOPWATCH:
        return "Stop Watch";
    case TimerType::TIMER:
        return "Timer";
    }
}

QString TimerModel::getActionTime() const
{

    return actionTime.toString();
}

void TimerModel::startTimer()
{
        currentTime = actionTime;
        seconds=0;
        timer->start(1000);
}



void TimerModel::stopTimer()
{
    timer->stop();
}

void TimerModel::onTimerProccesing()
{
    seconds++;
    switch(type){
    case TimerType:: ALARM:
        break;
    case TimerType::STOPWATCH:
        currentTime = actionTime.addSecs(seconds);
        break;
    case TimerType::TIMER:
        currentTime = actionTime.addSecs(-seconds);
        break;
    }
emit timerTick(id);

    qDebug() << currentTime.toString() << id;
}
//ця функція викливається, коли таймер працює, в залежності від типу таймера тут ми оновлюємо час
//якщо таймер, то відлік в оберненій стороні. Ідея роботи кожного таймера.
