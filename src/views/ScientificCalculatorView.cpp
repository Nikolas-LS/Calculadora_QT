#include "ScientificCalculatorView.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QSizePolicy>

static bool isOperatorSci(const QString& t){
    static const QStringList ops = {"+","-","*","/","=","x^y","sin","cos","tan","√","log","ln","π","e"};
    return ops.contains(t);
}

ScientificCalculatorView::ScientificCalculatorView(QWidget* parent)
    : QWidget(parent) {
    buildUi();
}

QPushButton* ScientificCalculatorView::makeBtn(const QString& text, int row, int col) {
    auto* btn = new QPushButton(text);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setMinimumSize(56, 48);
    connect(btn, &QPushButton::clicked, this, [this, text](){ emit buttonClicked(text); });
    styleButton(btn, text);
    auto* layout = qobject_cast<QGridLayout*>(this->layout());
    layout->addWidget(btn, row, col, 1, 1);
    return btn;
}

void ScientificCalculatorView::styleButton(QPushButton* btn, const QString& text){
    if (text == "C") { btn->setProperty("role","danger"); return; }
    if (text == "MC" || text == "MR" || text == "M+") { btn->setProperty("role","soft"); return; }
    if (isOperatorSci(text)) { btn->setProperty("role","op"); return; }
    btn->setProperty("role","num");
}

void ScientificCalculatorView::buildUi() {
    auto* grid = new QGridLayout(this);
    grid->setContentsMargins(12,12,12,12);
    grid->setHorizontalSpacing(8);
    grid->setVerticalSpacing(8);

    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    QFont f = m_display->font(); f.setPointSize(18); m_display->setFont(f);
    m_display->setMinimumHeight(56);
    grid->addWidget(m_display, 0, 0, 1, 5); // full width

    m_status = new QLabel;
    m_mem    = new QLabel; m_mem->setText(" ");
    auto* top = new QWidget;
    auto* topH = new QHBoxLayout(top);
    topH->addWidget(m_mem, 0, Qt::AlignLeft);
    topH->addWidget(m_status, 1, Qt::AlignRight);
    grid->addWidget(top, 1, 0, 1, 5);

    // Row 2
    makeBtn("MC", 2, 0);
    makeBtn("MR", 2, 1);
    makeBtn("M+", 2, 2);
    makeBtn("±",  2, 3);
    makeBtn("C",  2, 4);

    // Row 3
    makeBtn("sin", 3, 0);
    makeBtn("cos", 3, 1);
    makeBtn("tan", 3, 2);
    makeBtn("√",   3, 3);
    makeBtn("log", 3, 4);

    // Row 4
    makeBtn("7", 4, 0);
    makeBtn("8", 4, 1);
    makeBtn("9", 4, 2);
    makeBtn("/", 4, 3);
    makeBtn("ln", 4, 4);

    // Row 5
    makeBtn("4", 5, 0);
    makeBtn("5", 5, 1);
    makeBtn("6", 5, 2);
    makeBtn("*", 5, 3);
    makeBtn("x^y", 5, 4);

    // Row 6
    makeBtn("1", 6, 0);
    makeBtn("2", 6, 1);
    makeBtn("3", 6, 2);
    makeBtn("-", 6, 3);
    makeBtn("π", 6, 4);

    // Row 7
    makeBtn("0", 7, 0);
    makeBtn(".", 7, 1);
    makeBtn("=", 7, 2);
    makeBtn("+", 7, 3);
    makeBtn("e", 7, 4);
}

void ScientificCalculatorView::setDisplay(const QString& text){ m_display->setText(text); }
void ScientificCalculatorView::showStatus(const QString& text){ m_status->setText(text); }
void ScientificCalculatorView::setMemoryIndicator(bool on){ m_mem->setText(on ? "M" : " "); }
