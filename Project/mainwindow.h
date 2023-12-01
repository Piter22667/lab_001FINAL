#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot/qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    const int maxX = 100;
    const int minX = 0;
    const int maxY = 50;
    const int minY = 0;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCustomPlot* plot;
    QPointer<QCPGraph> graph;
    QCustomPlot *customPlot;
    int functionType = 0;

    void graphplot();
    double calculateY(double x);

private slots:
    void onSliderChanged();

};
#endif // MAINWINDOW_H
