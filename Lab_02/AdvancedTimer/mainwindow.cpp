 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "timermodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , viewModel(new MainWindowViewModel(this))
{
    ui->setupUi(this);//ініціалізує інтерфейс користувача
    connect(viewModel, &MainWindowViewModel :: timerAdded, this, &MainWindow::onTimerAdded); //сигнал викликає onTimerAdded, підключення сигналу таймераддед до слоту он таймераддед
    connect(viewModel, &MainWindowViewModel :: timerTicked, this, &MainWindow::onTimerTicked);
//аналогічно, тільки для сигналу таймертикед
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addTimerPushButton_clicked()
{
    qDebug() << "Add Timer Clicked";
    addTimerDialog = new AddTimerDialog(this);
    connect(addTimerDialog, &AddTimerDialog::createTimer, this, &MainWindow::onCreateTimer);
    addTimerDialog->exec();

}

void MainWindow::onCreateTimer(TimerModel *model)
{
    viewModel->addTimer(model);
}
//викликається при створення нового таймеру через діалогове вікно, також передає модель таймеру до viewModel
void MainWindow::onTimerAdded()
{
    updateTimersTable();

}//оновлюємо таблицю таймерів
void MainWindow::onTimerTicked(int index)
{
    QString time = viewModel->getTimeString(index);
    ui->timersTableWidget->setItem(index, 2, new QTableWidgetItem(time));
}

void MainWindow::onTimerButtonClicked(TimerModel* timer)
{
    qDebug() << "Button Clicked" << timer->name;
    if(timer->timer->isActive()){
        timer->stopTimer();

    }
    else{
        timer->startTimer();
    }
}
// викликається при натисканні на кнопку в таблиці. Або запускаємо, або зупиняємо таймер.
void MainWindow::updateTimersTable()
{
    qDebug() << "Кількість таймерів" << viewModel->getTimersCount();
    ui->timersTableWidget->setColumnCount(4);
    int rowCount = ui->timersTableWidget->rowCount();
    ui->timersTableWidget->insertRow(rowCount);//тут ми дізнаємось скільки рядків є і будемо додавати ще один для нового таймера
    TimerModel* timer = viewModel->getLastTimer();//
    QString buttonTitle =viewModel->getButtonTitle( timer->type);//отримуэмо даны про останный доданий таймер ы з його типу визначаэмо вид кнопки для цього таймеру
    buttons.append(new QPushButton(buttonTitle));//
    connect(buttons.last(), &QPushButton::clicked, this, [=](){onTimerButtonClicked(timer);});// лямбда ф-ція, підключаємо сигнал для кнопки і даємо інформацію про цю кнопку слоту onTimerButtonClicked
    ui->timersTableWidget->setItem(rowCount, 0, new QTableWidgetItem(timer->getType()) );
    ui->timersTableWidget->setItem(rowCount, 1, new QTableWidgetItem(timer->name) );
    ui->timersTableWidget->setItem(rowCount, 2, new QTableWidgetItem(timer->getActionTime()) );
    ui->timersTableWidget->setCellWidget(rowCount, 3, buttons.last());//цими рядками ми заповнюємо у рядок таблиці дані про таймер:тип, назва...
    qDebug() << "added Row";//

}

void MainWindow::updateTimersTableWithFilter()
{
    ui->timersTableWidget->clear();
    ui->timersTableWidget->setRowCount(0);
    buttons.clear();
    ui->timersTableWidget->setColumnCount(4);
    int j = 0;
    for (int i = 0; i < viewModel->getTimersCount(); ++i) {
        TimerModel* timer = viewModel->getTimer(i);
        if(((filter.count() == 0) || filter.contains(timer->type)) && timer->name.contains(ui->timerNameFilterLineEdit->text())) {
            ui->timersTableWidget->insertRow(j);
                        //цикл, який проходить через всі таймери і вставляє їх у нову таблицю, якщо він задовольняє умовам фільтру
            QString buttonTitle =viewModel->getButtonTitle( timer->type);
            buttons.append(new QPushButton(buttonTitle));
            connect(buttons[j], &QPushButton::clicked, this, [=](){onTimerButtonClicked(timer);});// лямбда ф-ція

            //так само створюємо нову кнопку і підключаємо її сигнал до слота onButtonClicked, щоб запуск продовжувався навіть після фільтрування

            ui->timersTableWidget->setItem(j, 0, new QTableWidgetItem(timer->getType()) );
            ui->timersTableWidget->setItem(j, 1, new QTableWidgetItem(timer->name) );
            ui->timersTableWidget->setItem(j, 2, new QTableWidgetItem(timer->getActionTime()) );
            ui->timersTableWidget->setCellWidget(j, 3, buttons[j]);
            j++;//заповнення таблиці даними про відсортовані таймери
        }
    }

}

void MainWindow::on_applyPushButton_clicked()
{
    filter.clear();
    if (ui->alarmCheckBox->isChecked()) {
        filter.insert(TimerModel::TimerType::ALARM);
    }
    if (ui->timerCheckBox->isChecked()) {
        filter.insert(TimerModel::TimerType::TIMER);
    }
    if (ui->stopwatchCheckBox->isChecked()) {
        filter.insert(TimerModel::TimerType::STOPWATCH);
    }//в залежності від того, який тип таймеру обраний, будемо додавати його до фільтра
    updateTimersTableWithFilter();
}

void MainWindow::on_deletTimerPushButton_clicked()
{
 viewModel->deleteTimer(timerRow, filter, ui->timerNameFilterLineEdit->text());
    updateTimersTableWithFilter();
}//видалення обраного таймеру


void MainWindow::on_timersTableWidget_cellClicked(int row, int column)
{
    timerRow = row;

}//тут інформація про обраний номер рядка.........

