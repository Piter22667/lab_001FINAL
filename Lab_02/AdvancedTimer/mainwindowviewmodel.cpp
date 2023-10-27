#include "mainwindowviewmodel.h"
#include <QSoundEffect>



MainWindowViewModel::MainWindowViewModel(QObject *parent)
    : QObject{parent}
{
    timerId = 0;
}

void MainWindowViewModel::addTimer(TimerModel *timer)
{
    connect(timer, &TimerModel::timerTick, this, &MainWindowViewModel::onTimerTicked);
    timer->id = timerId++;
    qDebug() << "timerId " << timerId << "timerid " << timer->id;


    this->timers.append(timer);
    emit timerAdded();
}

int MainWindowViewModel::getTimersCount()
{
    return timers.count();
}

 TimerModel *MainWindowViewModel::getLastTimer()
{
    return timers.last();
}

TimerModel *MainWindowViewModel::getTimer(int index)
{
    return timers[index];
}


QString MainWindowViewModel::getButtonTitle(TimerModel::TimerType type)
{
    switch(type){
    case TimerModel::TimerType:: ALARM:
        return "On/Off";
    case TimerModel::TimerType::STOPWATCH:
        return "Start/Stop";
    case TimerModel::TimerType::TIMER:
        return "Start/Stop";
    }
}
//повертає назву кнопки для вказаного типу таймера.
int MainWindowViewModel::getTimerIndex(int id)
{
    for(int i=0; i<timers.count(); i++){
        if(timers[i]->id == id ){
            return i;
        }
    }
    return -1;
}
//повертає індекс таймера за його унікальним ідентифікатором.
QString MainWindowViewModel::getTimeString(int index)
{
    TimerModel* timer = timers[index];
    if(timer->type == TimerModel::TimerType::ALARM){
        if(QDateTime::currentDateTime().time() >= timer->actionTime){
            timer->stopTimer();

//            QSoundEffect effect;
//            effect.setSource(QUrl::fromLocalFile("sounds/alarms.wav"));
//            effect.play();
//            return "ALARM";  спроба реалізувати відворення звуку по завершенню будильника

        }
        else{
            return timer->actionTime.toString();
        }
    }

    return timer->currentTime.toString();
}
//для будильника - якщо час сплив, будильник зупиняється
void MainWindowViewModel::deleteTimer(int row, QSet<TimerModel::TimerType> filter, QString text)
{
    int j = 0;
    for (int i = 0; i < getTimersCount(); ++i) {
        TimerModel* timer = getTimer(i);

        if(j==row){
            timers.removeAt(i);
        }


        if(((filter.count() == 0) || filter.contains(timer->type))  && timer->name.contains(text)) {
            j++;
        }

    }
}

void MainWindowViewModel::onTimerTicked(int id)
{
    int index = getTimerIndex(id);
    if(index>=0){
        qDebug() << "timerTicked " << index;
        emit timerTicked(index);
    }
}
//Для кожного таймера випускає сигнал timerticked з індексом кожного таймера, тож відлік часу йшов незалежно,

