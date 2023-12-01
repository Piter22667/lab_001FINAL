#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


// Конструктор класу MainWindow, який ініціалізує головне вікно
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);// Ініціалізація користувацького інтерфейсу
    ui->lineEditA->setText("0");
    ui->lineEditB->setText("0");

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::onSliderChanged);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, &MainWindow::onSliderChanged);

    // Створення об'єкта QCustomPlot та призначення його центральним віджетом головного вікна
    customPlot = new QCustomPlot(this);
    //setCentralWidget(customPlot);
    QVBoxLayout* graphLayout = new QVBoxLayout;
    graphLayout->addWidget(customPlot);
    customPlot->setParent(ui->widget);
    ui->widget->setLayout(graphLayout);



    // Встановлення міток осей
    customPlot->xAxis->setLabel("X"); // Мітка для осі X
    customPlot->yAxis->setLabel("Y"); // Мітка для осі Y

    // Встановлення розміру графіка
    //customPlot->setMinimumSize(400, 300);

    // Перевірка меж для осі X та осі Y
    customPlot->xAxis->setRange(minX, maxX); // Встановлення меж для осі X від 0 до 100
    customPlot->yAxis->setRange(minY, maxY); // Встановлення меж для осі Y, приблизно визначена верхня межа

    graphplot();
}

// Деструктор класу MainWindow
MainWindow::~MainWindow()
{
    // Видалення об'єкта ui для очищення ресурсів
    delete ui;
}

void MainWindow::graphplot()
{
    // Створення графіка, який буде містити дані
    QVector<double> x, y;
    for (int i = minX; i < maxX; ++i) {
        x.push_back(i); // Додавання значень x до вектора
        y.push_back(calculateY(i)); // визначаємо, як сильно буде зростати функція
    }
    //i - це і є, як далеко буде показуватись функція

    // Додавання графіка до QCustomPlot
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    // Перемальовка графіка для відображення змін
    customPlot->replot();
}

double MainWindow::calculateY(double x)
{
    int a = ui->lineEditA->text().toInt();
    int b = ui->lineEditB->text().toInt();
    switch(functionType)
    {
    case 0:
        if(b ==0){
            return minY - 1;
        }
        return qPow(a, x/b);

    }
    return minY - 1;
}

void MainWindow::onSliderChanged()
{
    ui->lineEditA->setText(QString::number(ui->horizontalSlider->value()));
    ui->lineEditB->setText(QString::number(ui->horizontalSlider_2->value()));
    graphplot();
}

