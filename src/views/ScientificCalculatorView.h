#ifndef SCIENTIFICCALCULATORVIEW_H
#define SCIENTIFICCALCULATORVIEW_H

#include <QWidget>
class QLineEdit;
class QLabel;
class QPushButton;

class ScientificCalculatorView : public QWidget {
    Q_OBJECT
public:
    explicit ScientificCalculatorView(QWidget* parent=nullptr);

signals:
    void buttonClicked(const QString& token);

public slots:
    void setDisplay(const QString& text);
    void showStatus(const QString& text);
    void setMemoryIndicator(bool on);

private:
    QPushButton* makeBtn(const QString& text, int row, int col);
    void buildUi();
    void styleButton(QPushButton* btn, const QString& text);

    QLineEdit* m_display;
    QLabel*    m_status;
    QLabel*    m_mem;
};

#endif // SCIENTIFICCALCULATORVIEW_H
