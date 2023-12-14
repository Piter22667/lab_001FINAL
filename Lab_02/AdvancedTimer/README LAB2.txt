---addtimerdialog.h
Цей заголовок описує клас AddTimerDialog, який є вікном діалогу для створення та редагування таймерів. 

Q_OBJECT - має підтримку сигналів та слотів у Qt.

explicit AddTimerDialog(QWidget *parent = nullptr);
    ~AddTimerDialog(); - - оголошення конструктора та деструктора


---- mainwindow.h
   Ui::MainWindow *ui - вказівник на головне вікно
    MainWindowViewModel *viewModel;
    AddTimerDialog *addTimerDialog - вказівник на вікно створення нового таймера, який використовується для взаємодії діалогового вікна з даними, отриманими від користувача
 вказівники на інтерфейси 


-----mainwindowviewmodel.h
клас, який створений для керування моделями таймерів

-----timermodel.h
модель таймера
Макрос Q_OBJECT використовується для підтримки сигналів та слотів та інших функцій Qt.

-----addtimerdialog.cpp
вікно саме для створення нового таймеру в програмі

void AddTimerDialog::on_buttonBox_accepted()
цей метод викликається, коли користувач натиснув Apply/.створює новий таймап, дає йому назву, час дії, а потім через еміт дає сигнал, передаючи новий таймер як параметр.

void AddTimerDialog::on_stopWatchRadioButton_clicked()

void AddTimerDialog::on_timerRadioButton_clicked()

void AddTimerDialog::on_alarmRadioButton_clicked()

встановлення типу таймерів за вибором коритсувача.

-------------mainwindow.cpp
void MainWindow::on_addTimerPushButton_clicked() 
викликається при натисканні на кнопку Add Timer. У ньому відбувається створення діалогового вікна AddTimerDialog і підключення сигналу createTimer цього діалогового вікна до слоту onCreateTimer.

void MainWindow::onTimerTicked(int index)
с будемо оновлювати таймер для відображення секунд для певного таймера в таблиці

void MainWindow::updateTimersTable()

функція, яка використовується для оновлення таблиці таймерів



void MainWindow::updateTimersTableWithFilter() - ф-я фільтрування таймерів 


void MainWindow::on_applyPushButton_clicked()
реалізація кнопки аплай для фільтру або сортування таймерів


------mainWindowViewmodel.cpp

void MainWindowViewModel::addTimer(TimerModel *timer)
Ця функція додає новий таймер до моделі. Вона підключає сигнал timerTick таймера до слота onTimerTicked цього класу, присвоює таймеру унікальний ідентифікатор, додає таймер до списку таймерів і випромінює сигнал timerAdded;


-------timermodel.cpp
TimerModel::TimerModel(QObject *parent)
    : QObject{parent}
конструктор класу. підключає сигна timeout для слота onTimerProccesing цього класу, та ініціалізує змінні seconds ,id для таймерів.

Використання методів та класів повинно задовільняти Ваші умови.

