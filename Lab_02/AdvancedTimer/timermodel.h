#ifndef TIMERMODEL_H
#define TIMERMODEL_H

#include <QObject>
#include <QTimer>
#include <QTime>


class TimerModel : public QObject
{
    Q_OBJECT

public:
    enum TimerType{
    ALARM,
    STOPWATCH,
    TIMER,
    };
//enum використовується для зв'язки та можливості передачі \ тип даних, коли кожна змінна є ососбливою
    // Оголошення функції
    //за допомогою еміт ми можемо передавати посилання у вікно

    explicit TimerModel(QObject *parent = nullptr);//конструктор в класі

    QString getType() const;
    QString getActionTime() const;
//методи класу, які повертають тип таймера та час його дій у вигляді рядка, який ьуде пізніше викоритсовуватись
signals:
     void timerTick(int id);
    public:

    QTimer* timer;
    QString name;
    TimerType type; //    ALARM,    STOPWATCH, TIMER
    QTime actionTime;
    QTime currentTime;
    int id;
    //змінні класу, які використовуються для характеристики кожного таймеру
    void startTimer();

    void stopTimer();
    long int seconds = 0;
//запуск, зупинка таймера та змінна для збереження к=істі секунд
private slots:
    void onTimerProccesing();

//приватиний слот,я який потім буде визначати вид таймеру і в залежності від цього віднімати або додавати секунди
    //тобто оброблювати його

};

#endif // TIMERMODEL_H
