#ifndef MAINWINDOWVIEWMODEL_H
#define MAINWINDOWVIEWMODEL_H

#include <QObject> //базовий клас для всіх об'єктів
#include <QVector>//вектор таймерів, зберігає елементи в послідовності
#include "timermodel.h"//



class MainWindowViewModel : public QObject//успадковує властивості класу QObject
{
    Q_OBJECT
public:
    explicit MainWindowViewModel(QObject *parent = nullptr);

    void addTimer(TimerModel* timer);
    int getTimersCount();
    TimerModel* getLastTimer();
     TimerModel* getTimer(int index);
    QString getButtonTitle(TimerModel::TimerType type);
    int getTimerIndex(int id);
    QString getTimeString(int index);
    void deleteTimer(int row, QSet<TimerModel::TimerType> filter, QString text);
// публічні методи класу, які використовуються для управління таймерами (додавання, отримання, видалення
signals:
    void timerAdded();
    void timerTicked(int index);
    //сигнали, які можуть надходити з класу. Вони і будуть сповіщувати про певні події
private:
    QVector<TimerModel*> timers; // створення моделі таймерів
    int timerId;//ідентифікатор ос таймера

private slots:
    void onTimerTicked(int id);//обробка таймера для секунд

};

#endif // MAINWINDOWVIEWMODEL_H
