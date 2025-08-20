#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>
#include <QString>
#include <optional>
#include "models/CalculatorModel.h"

class BasicCalculatorView;
class ScientificCalculatorView;

class CalculatorController : public QObject {
    Q_OBJECT
public:
    explicit CalculatorController(CalculatorModel* model,
                                  BasicCalculatorView* basicView,
                                  ScientificCalculatorView* sciView,
                                  QObject* parent=nullptr);

public slots:
    void handleButtonClick(const QString& token);
    void switchToBasic();
    void switchToScientific();

signals:
    void displayChanged(const QString& text);
    void statusMessage(const QString& text);
    void memoryActive(bool active);
    void requestViewIndex(int index);

private:
    enum class InputMode { Idle, Typing };
    std::optional<CalculatorModel::BinaryOp> parseBinary(const QString& token) const;
    std::optional<CalculatorModel::UnaryOp> parseUnary(const QString& token) const;
    QString formatNumber(double v) const;
    double currentValue() const;
    void setDisplayFromState();
    void applyPendingIfNeeded();
    void clearAll();

    CalculatorModel* m_model;
    BasicCalculatorView* m_basicView;
    ScientificCalculatorView* m_sciView;
    QString m_currentInput;
    double  m_accumulator;
    std::optional<CalculatorModel::BinaryOp> m_pendingOp;
    InputMode m_mode;
};

#endif // CALCULATORCONTROLLER_H
