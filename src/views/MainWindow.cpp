#include "MainWindow.h"
#include <QStackedWidget>
#include <QToolBar>
#include <QAction>
#include <QApplication>
#include <QStyle>
#include "views/BasicCalculatorView.h"
#include "views/ScientificCalculatorView.h"
#include "models/CalculatorModel.h"
#include "controllers/CalculatorController.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_stack(nullptr),
      m_basicView(nullptr),
      m_sciView(nullptr),
      m_model(nullptr),
      m_controller(nullptr)
{
    buildUi();
    applyTheme();
}

MainWindow::~MainWindow(){}

void MainWindow::buildUi(){
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    m_basicView = new BasicCalculatorView;
    m_sciView   = new ScientificCalculatorView;
    m_stack->addWidget(m_basicView);
    m_stack->addWidget(m_sciView);

    m_model = new CalculatorModel;
    m_controller = new CalculatorController(m_model, m_basicView, m_sciView, this);
    connect(m_controller, &CalculatorController::requestViewIndex, this, &MainWindow::setViewIndex);

    auto* tb = addToolBar("Modo");
    auto* actBasic = tb->addAction("Básica");
    auto* actSci   = tb->addAction("Científica");
    connect(actBasic, &QAction::triggered, m_controller, &CalculatorController::switchToBasic);
    connect(actSci,   &QAction::triggered, m_controller, &CalculatorController::switchToScientific);

    setWindowTitle("Calculadora Qt MVC (Básica + Científica)");
    resize(460, 560);
}

void MainWindow::applyTheme(){
    // Dark theme + button roles similar to the screenshots
    QString qss = R"(
        QWidget { background: #2b2b2b; color: #e6e6e6; }
        QLineEdit {
            background: #141414; color: #e6e6e6;
            border: 1px solid #3a3a3a; border-radius: 12px;
            padding: 10px;
        }
        QPushButton {
            background: #3a3a3a; color: #e6e6e6;
            border: 1px solid #444; border-radius: 14px;
            padding: 8px; font-weight: 500;
        }
        QPushButton[role="num"] { background: #3a3a3a; }
        QPushButton[role="soft"] { background: #3a3a3a; }
        QPushButton[role="op"] { background: #1e88e5; }
        QPushButton[role="danger"] { background: #e53935; }
        QPushButton:hover { filter: brightness(1.05); }
        QPushButton:pressed { transform: scale(0.98); }
        QToolBar { background: #202020; border: 0px; }
        QToolButton { color: #e6e6e6; }
        QStatusBar { background:#202020; color:#aaaaaa; }
    )";
    qApp->setStyleSheet(qss);
}

void MainWindow::setViewIndex(int index){
    if(index>=0 && index<m_stack->count()) m_stack->setCurrentIndex(index);
}
