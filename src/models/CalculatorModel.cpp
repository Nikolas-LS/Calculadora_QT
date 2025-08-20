#include "CalculatorModel.h"
#include <cmath>
#include <limits>

static bool valid(double x){ return std::isfinite(x); }

CalculatorModel::CalculatorModel() : m_memory(0.0) {}

void CalculatorModel::memoryClear(){ m_memory = 0.0; }
void CalculatorModel::memoryAdd(double v){ m_memory += v; }
double CalculatorModel::memoryRecall() const { return m_memory; }

CalculatorModel::Result CalculatorModel::applyUnary(UnaryOp op, double x) const {
    Result r{0.0,false,QString()};
    if(!valid(x)){ r.error = "Valor inválido"; return r; }
    double out = 0.0;
    switch(op){
        case UnaryOp::Sin: out = std::sin(x); break;
        case UnaryOp::Cos: out = std::cos(x); break;
        case UnaryOp::Tan: out = std::tan(x); break;
        case UnaryOp::Sqrt:
            if(x < 0){ r.error = "Raiz de número negativo"; return r; }
            out = std::sqrt(x); break;
        case UnaryOp::Log10:
            if(x <= 0){ r.error = "log10(x) com x<=0"; return r; }
            out = std::log10(x); break;
        case UnaryOp::Ln:
            if(x <= 0){ r.error = "ln(x) com x<=0"; return r; }
            out = std::log(x); break;
        case UnaryOp::Square:
            out = x * x; break;
        case UnaryOp::Percent:
            out = x / 100.0; break;
    }
    if(!valid(out)){ r.error = "Resultado inválido"; return r; }
    r.value = out; r.ok = true; return r;
}

CalculatorModel::Result CalculatorModel::applyBinary(BinaryOp op, double a, double b) const {
    Result r{0.0,false,QString()};
    if(!valid(a) || !valid(b)){ r.error = "Valor inválido"; return r; }
    double out = 0.0;
    switch(op){
        case BinaryOp::Add: out = a + b; break;
        case BinaryOp::Sub: out = a - b; break;
        case BinaryOp::Mul: out = a * b; break;
        case BinaryOp::Div:
            if(b == 0.0){ r.error = "Divisão por zero"; return r; }
            out = a / b; break;
        case BinaryOp::Pow: out = std::pow(a, b); break;
    }
    if(!valid(out)){ r.error = "Resultado inválido"; return r; }
    r.value = out; r.ok = true; return r;
}
