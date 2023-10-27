#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindowviewmodel.h"
#include "addtimerdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow //наслідування
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); //конструктор
    ~MainWindow(); //деструктор

private slots:
    void on_addTimerPushButton_clicked();
    void onCreateTimer(TimerModel* model);
    void onTimerAdded();
    void onTimerTicked(int index);

    void on_applyPushButton_clicked();


    void on_deletTimerPushButton_clicked();

    void on_timersTableWidget_cellClicked(int row, int column);
// так само оголошення слотів, які потім будуть оброблювати певні дії користувача та давати якусь реакцію
private:
    Ui::MainWindow *ui;
    MainWindowViewModel *viewModel;
    AddTimerDialog *addTimerDialog;

    void updateTimersTable();
    void updateTimersTableWithFilter();
    QVector<QPushButton*> buttons;
    void onTimerButtonClicked(TimerModel* timer);
    QSet<TimerModel::TimerType> filter;//filter типи таймерів

    int timerRow= 0;
};
#endif // MAINWINDOW_H
