#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class BasicCalculatorView;
class ScientificCalculatorView;
class CalculatorModel;
class CalculatorController;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow();

private slots:
    void setViewIndex(int index);

private:
    void buildUi();
    void applyTheme();

    QStackedWidget* m_stack;
    BasicCalculatorView* m_basicView;
    ScientificCalculatorView* m_sciView;
    CalculatorModel* m_model;
    CalculatorController* m_controller;
};

#endif // MAINWINDOW_H
