#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QString>

class CalculatorModel {
public:
    enum class UnaryOp { Sin, Cos, Tan, Sqrt, Log10, Ln, Square, Percent };
    enum class BinaryOp { Add, Sub, Mul, Div, Pow };

    struct Result {
        double value;
        bool ok;
        QString error;
    };

    CalculatorModel();

    void memoryClear();
    void memoryAdd(double v);
    double memoryRecall() const;

    Result applyUnary(UnaryOp op, double x) const;
    Result applyBinary(BinaryOp op, double a, double b) const;

private:
    double m_memory;
};

#endif // CALCULATORMODEL_H
