#include "CalculatorController.h"
#include "views/BasicCalculatorView.h"
#include "views/ScientificCalculatorView.h"
#include <QLocale>
#include <cmath>

CalculatorController::CalculatorController(CalculatorModel* model,
                                           BasicCalculatorView* basicView,
                                           ScientificCalculatorView* sciView,
                                           QObject* parent)
    : QObject(parent),
      m_model(model),
      m_basicView(basicView),
      m_sciView(sciView),
      m_accumulator(0.0),
      m_mode(InputMode::Idle)
{
    connect(basicView, &BasicCalculatorView::buttonClicked,
            this, &CalculatorController::handleButtonClick);
    connect(sciView, &ScientificCalculatorView::buttonClicked,
            this, &CalculatorController::handleButtonClick);

    connect(this, &CalculatorController::displayChanged, basicView, &BasicCalculatorView::setDisplay);
    connect(this, &CalculatorController::displayChanged, sciView, &ScientificCalculatorView::setDisplay);
    connect(this, &CalculatorController::statusMessage, basicView, &BasicCalculatorView::showStatus);
    connect(this, &CalculatorController::statusMessage, sciView, &ScientificCalculatorView::showStatus);
    connect(this, &CalculatorController::memoryActive, basicView, &BasicCalculatorView::setMemoryIndicator);
    connect(this, &CalculatorController::memoryActive, sciView, &ScientificCalculatorView::setMemoryIndicator);

    setDisplayFromState();
}

std::optional<CalculatorModel::BinaryOp> CalculatorController::parseBinary(const QString& t) const {
    if (t == "+") return CalculatorModel::BinaryOp::Add;
    if (t == "-") return CalculatorModel::BinaryOp::Sub;
    if (t == "×" || t == "*") return CalculatorModel::BinaryOp::Mul;
    if (t == "÷" || t == "/") return CalculatorModel::BinaryOp::Div;
    if (t == "x^y" || t == "^") return CalculatorModel::BinaryOp::Pow;
    return std::nullopt;
}

std::optional<CalculatorModel::UnaryOp> CalculatorController::parseUnary(const QString& t) const {
    if (t == "sin") return CalculatorModel::UnaryOp::Sin;
    if (t == "cos") return CalculatorModel::UnaryOp::Cos;
    if (t == "tan") return CalculatorModel::UnaryOp::Tan;
    if (t == "√")   return CalculatorModel::UnaryOp::Sqrt;
    if (t == "log") return CalculatorModel::UnaryOp::Log10;
    if (t == "ln")  return CalculatorModel::UnaryOp::Ln;
    if (t == "x^2" || t == "x²") return CalculatorModel::UnaryOp::Square;
    if (t == "%") return CalculatorModel::UnaryOp::Percent;
    return std::nullopt;
}

QString CalculatorController::formatNumber(double v) const {
    QLocale loc;
    return loc.toString(v, 'g', 12);
}

double CalculatorController::currentValue() const {
    if (!m_currentInput.isEmpty()) {
        QLocale loc; bool ok=false;
        double v = loc.toDouble(m_currentInput, &ok);
        if (ok) return v;
    }
    return m_accumulator;
}

void CalculatorController::setDisplayFromState() {
    emit displayChanged(formatNumber(currentValue()));
    emit memoryActive(std::abs(m_model->memoryRecall()) > 1e-15);
}

void CalculatorController::applyPendingIfNeeded() {
    if (m_pendingOp && !m_currentInput.isEmpty()) {
        QLocale loc; bool ok=false;
        double rhs = loc.toDouble(m_currentInput, &ok);
        if (!ok) { emit statusMessage("Entrada inválida"); return; }
        auto res = m_model->applyBinary(*m_pendingOp, m_accumulator, rhs);
        if (!res.ok) { emit statusMessage("Erro: " + res.error); clearAll(); return; }
        m_accumulator = res.value;
        m_currentInput.clear();
        m_pendingOp.reset();
        emit displayChanged(formatNumber(m_accumulator));
    }
}

void CalculatorController::clearAll() {
    m_currentInput.clear();
    m_accumulator = 0.0;
    m_pendingOp.reset();
    m_mode = InputMode::Idle;
    setDisplayFromState();
}

void CalculatorController::handleButtonClick(const QString& t) {
    if (t == "C") { clearAll(); return; }

    if (t == "±") {
        if (!m_currentInput.isEmpty()) {
            if (m_currentInput.startsWith("-")) m_currentInput.remove(0,1);
            else m_currentInput.prepend("-");
        } else {
            m_accumulator = -m_accumulator;
        }
        setDisplayFromState(); return;
    }

    if (t == "MR") { m_currentInput = formatNumber(m_model->memoryRecall()); setDisplayFromState(); return; }
    if (t == "MC") { m_model->memoryClear(); emit memoryActive(false); return; }
    if (t == "M+") { m_model->memoryAdd(currentValue()); emit memoryActive(true); emit statusMessage("Memória adicionada"); return; }

    if (t == "=") { applyPendingIfNeeded(); return; }

    if (t == ".") {
        if (!m_currentInput.contains(".")) {
            if (m_currentInput.isEmpty()) m_currentInput = "0.";
            else m_currentInput.append(".");
            setDisplayFromState();
        }
        return;
    }

    // constants
    if (t == "π") { m_currentInput = formatNumber(M_PI); setDisplayFromState(); return; }
    if (t == "e") { m_currentInput = formatNumber(M_E); setDisplayFromState(); return; }

    // digits
    if (t.size()==1 && t[0].isDigit()) {
        if (m_currentInput == "0") m_currentInput.clear();
        m_currentInput.append(t);
        m_mode = InputMode::Typing;
        setDisplayFromState(); return;
    }
    if (t == "00") {
        if (m_currentInput.isEmpty()) m_currentInput = "0";
        m_currentInput.append("00");
        setDisplayFromState(); return;
    }

    // unary
    if (auto u = parseUnary(t)) {
        double x = currentValue();
        auto res = m_model->applyUnary(*u, x);
        if (!res.ok) { emit statusMessage("Erro: " + res.error); clearAll(); return; }
        m_accumulator = res.value;
        m_currentInput.clear();
        emit displayChanged(formatNumber(m_accumulator));
        return;
    }

    // binary
    if (auto b = parseBinary(t)) {
        if (!m_currentInput.isEmpty() && !m_pendingOp) {
            QLocale loc; bool ok=false;
            double v = loc.toDouble(m_currentInput, &ok);
            if(!ok){ emit statusMessage("Entrada inválida"); return; }
            m_accumulator = v;
            m_currentInput.clear();
        } else {
            applyPendingIfNeeded();
        }
        m_pendingOp = *b;
        return;
    }

    emit statusMessage("Botão não reconhecido: " + t);
}

void CalculatorController::switchToBasic(){ emit requestViewIndex(0); }
void CalculatorController::switchToScientific(){ emit requestViewIndex(1); }
