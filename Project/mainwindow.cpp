#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
//#include <QtWidgets/QHeaderView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


// Конструктор класу MainWindow, який ініціалізує головне вікно
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);// Ініціалізація користувацького інтерфейсу

    initFunctions();

    setupCoefficientRanges();

    ui->lineEditA->setText("0");
    ui->lineEditB->setText("0");
    ui->diagramsComboBox->setHidden(true);
    ui->groupBox_3->setTitle("Graphics");
    ui->graphicsParametersGroupBox->setHidden(false);
    ui->diagramsParametersGroupBox->setHidden(true);

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::onSliderChanged);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, &MainWindow::onSliderChanged);

    // Створення об'єкта QCustomPlot та призначення його центральним віджетом головного вікна
    customPlot = new QCustomPlot(this);
    //setCentralWidget(customPlot);
    QVBoxLayout* graphLayout = new QVBoxLayout;
    graphLayout->addWidget(customPlot);
    customPlot->setParent(ui->widget);

    graphicsView = new QChartView;
    graphicsView->setHidden(true);
    graphLayout->addWidget(graphicsView);
    graphicsView->setParent(ui->widget);


    ui->widget->setLayout(graphLayout);

    for(const auto &item: functions){
        ui->comboBox->addItem(item.name);
    }



    // Встановлення міток осей
    customPlot->xAxis->setLabel("X"); // Мітка для осі X
    customPlot->yAxis->setLabel("Y"); // Мітка для осі Y

    setupAxis();
    setupTable();

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
    double i = minX;
    while ( i <= maxX) {
        x.push_back(i); // Додавання значень x до вектора
        y.push_back(calculateY(i)); // визначаємо, як сильно буде зростати функція
        i+= functions.at(functionType).stepX;
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
    double a = ui->lineEditA->text().toDouble();
    double b = ui->lineEditB->text().toDouble();
    switch(functionType)
    {
    case 0:
        if(b == 0){
            return minY - 1;
        }
        return qPow(a, x/b);
    case 1:
        return (a/10) * x * x + b;

    case 2:
    return a*qSin(b*x);
    }
    return minY - 1;
}

void MainWindow::initFunctions()
{
//QString name, double minA, double maxA, double stepA, double minB, double maxB, double stepB, int maxX = 50, int minX = -50, int maxY = 50, int minY = -50, double stepX = 1):
    functions.append(FuncParam("a^(x/b)", -10, 10, 0.01, 0, 10, 0.01));
    functions.append(FuncParam("(a/10)x^2+b",-50, 50, 0.01, 0, 10, 0.01, 50, -50, 100, -100, 0.1 ));
    functions.append(FuncParam("a*sin(b*x)",-10, 10, 0.01, 0, 10, 0.01));
}

void MainWindow::setupAxis()
{
    minX = functions.at(functionType).minX;
    maxX = functions.at(functionType).maxX;
    minY = functions.at(functionType).minY;
    maxY = functions.at(functionType).maxY;

    customPlot->xAxis->setRange(minX, maxX); // Встановлення меж для осі X від 0 до 100
    customPlot->yAxis->setRange(minY, maxY); // Встановлення меж для осі Y, приблизно визначена верхня межа
    ui->comboBox->setCurrentIndex(functionType);
}


void MainWindow::setupCoefficientRanges()
{
    ui->minADoubleSpinBox->setValue(functions.at(functionType).minA);
    ui->minBDoubleSpinBox->setValue(functions.at(functionType).minB);

    ui->maxADoubleSpinBox->setValue(functions.at(functionType).maxA);
    ui->maxBDoubleSpinBox->setValue(functions.at(functionType).maxB);
    ui->stepADoubleSpinBox->setValue(functions.at(functionType).stepA);
    ui->stepBDoubleSpinBox->setValue(functions.at(functionType).stepB);
    ui->horizontalSlider->setMinimum(functions.at(functionType).minA);
    ui->horizontalSlider->setMaximum(functions.at(functionType).maxA);

    ui->horizontalSlider_2->setMinimum(functions.at(functionType).minB);
    ui->horizontalSlider_2->setMaximum(functions.at(functionType).maxB);

}

void MainWindow::setupTable()
{
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(10);

    ui->tableWidget->horizontalHeader()->setHidden(true);
//    for(int i = 0; i<ui->tableWidget->columnCount(); i++){
//    ui->tableWidget->item(1, i)->setBackground(QColor (250,0,0)) ;
//    }
//ui->tableWidget->verticalHeaderItem(1)->setText("Columns title");
    QTableWidgetItem* item = new QTableWidgetItem("Columns title");
    ui->tableWidget->setVerticalHeaderItem(0, item);
    item->setBackground(QBrush(Qt::red));
    ui->tableWidget->setItem(1, 1, item);


}

void MainWindow::setupDiagram()
{
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // series 1




    QBarSet *set0 = new QBarSet("Jane");
    QBarSet *set1 = new QBarSet("John");
    QBarSet *set2 = new QBarSet("Axel");
    QBarSet *set3 = new QBarSet("Mary");
    QBarSet *set4 = new QBarSet("Samantha");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    //! [5]
    chart->addSeries(series);
    //! [6]
    QStringList categories;
    categories << "April" << "May" << "June" << "July" << "August" << "September";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //! [6]

    //! [7]
    graphicsView->setChart(chart);

    graphicsView->setRenderHint(QPainter::Antialiasing);
//    graphicsView->setMinimumSize(640, 480);
}

void MainWindow::onSliderChanged()
{
    ui->lineEditA->setText(QString::number(ui->horizontalSlider->value()));
    ui->lineEditB->setText(QString::number(ui->horizontalSlider_2->value()));
    graphplot();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    functionType = index;
    setupAxis();
    setupCoefficientRanges();
    graphplot();
}


void MainWindow::on_radioButton_2_clicked()
{

    ui->comboBox->setHidden(false);
    ui->diagramsComboBox->setHidden(true);
    customPlot->setHidden(false); //графіки
    graphicsView->setHidden(true);//діаграми
    ui->groupBox_3->setTitle("Graphics");

    ui->graphicsParametersGroupBox->setHidden(false);
    ui->diagramsParametersGroupBox->setHidden(true);

}


void MainWindow::on_radioButton_clicked() //Діаграми
{
    ui->comboBox->setHidden(true);
    ui->diagramsComboBox->setHidden(false);

    customPlot->setHidden(true);
    graphicsView->setHidden(false);
    ui->groupBox_3->setTitle("Diagrams");

    ui->graphicsParametersGroupBox->setHidden(true);
    ui->diagramsParametersGroupBox->setHidden(false);

    setupDiagram();
}

