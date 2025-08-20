#include "BasicCalculatorView.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QSizePolicy>

static bool isOperator(const QString& t){
    static const QStringList ops = {"+","-","*","/","=","x^2","%"};
    return ops.contains(t);
}

BasicCalculatorView::BasicCalculatorView(QWidget* parent)
    : QWidget(parent) {
    buildUi();
}

QPushButton* BasicCalculatorView::makeBtn(const QString& text, int row, int col) {
    auto* btn = new QPushButton(text);
    btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn->setMinimumSize(56, 48);
    connect(btn, &QPushButton::clicked, this, [this, text](){ emit buttonClicked(text); });
    styleButton(btn, text);
    auto* layout = qobject_cast<QGridLayout*>(this->layout());
    layout->addWidget(btn, row, col, 1, 1);
    return btn;
}

void BasicCalculatorView::styleButton(QPushButton* btn, const QString& text){
    if (text == "C") { btn->setProperty("role","danger"); return; }
    if (text == "MC" || text == "MR" || text == "M+") { btn->setProperty("role","soft"); return; }
    if (isOperator(text)) { btn->setProperty("role","op"); return; }
    btn->setProperty("role","num");
}

void BasicCalculatorView::buildUi() {
    auto* grid = new QGridLayout(this);
    grid->setContentsMargins(12,12,12,12);
    grid->setHorizontalSpacing(8);
    grid->setVerticalSpacing(8);

    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    QFont f = m_display->font(); f.setPointSize(18); m_display->setFont(f);
    m_display->setMinimumHeight(56);
    grid->addWidget(m_display, 0, 0, 1, 5); // full width (5 columns)

    // Status + Memory indicator row
    m_status = new QLabel;
    m_mem    = new QLabel; m_mem->setText(" ");
    auto* top = new QWidget;
    auto* topH = new QHBoxLayout(top);
    topH->addWidget(m_mem, 0, Qt::AlignLeft);
    topH->addWidget(m_status, 1, Qt::AlignRight);
    grid->addWidget(top, 1, 0, 1, 5);

    // Row 2: MC MR M+ ± C
    makeBtn("MC", 2, 0);
    makeBtn("MR", 2, 1);
    makeBtn("M+", 2, 2);
    makeBtn("±",  2, 3);
    makeBtn("C",  2, 4);

    // Fill ALL cells (5 columns) uniformly — no dummies:
    // Row 3
    makeBtn("7", 3, 0);
    makeBtn("8", 3, 1);
    makeBtn("9", 3, 2);
    makeBtn("x^2", 3, 3);
    makeBtn("/", 3, 4);

    // Row 4
    makeBtn("4", 4, 0);
    makeBtn("5", 4, 1);
    makeBtn("6", 4, 2);
    makeBtn("%", 4, 3);
    makeBtn("*", 4, 4);

    // Row 5
    makeBtn("1", 5, 0);
    makeBtn("2", 5, 1);
    makeBtn("3", 5, 2);
    makeBtn("=", 5, 3);
    makeBtn("-", 5, 4);

    // Row 6
    makeBtn("0", 6, 0);
    makeBtn("00", 6, 1);
    makeBtn(".", 6, 2);
    makeBtn("=", 6, 3);
    makeBtn("+", 6, 4);
}

void BasicCalculatorView::setDisplay(const QString& text){ m_display->setText(text); }
void BasicCalculatorView::showStatus(const QString& text){ m_status->setText(text); }
void BasicCalculatorView::setMemoryIndicator(bool on){ m_mem->setText(on ? "M" : " "); }
