#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onBackspaceClicked();
    void onDecimalClicked();

private:
    Ui::MainWindow *ui;

    double m_firstOperand;       // 第一个操作数 / 累计结果
    QString m_pendingOperator;   // 待执行的运算符: + - * / 或空
    bool m_waitingForOperand;    // true=等待输入下一个操作数
    bool m_error;                // true=处于错误状态(如除零)

    void handleDigit(const QString &digit);
    void handleOperator(const QString &op);
    void handleEquals();
    void handleClear();
    void handleBackspace();
    void handleDecimal();

    double displayValue() const;
    void setDisplay(double value);
    void setDisplay(const QString &text);
    void clearAll();
    void performCalculation();
    void updateHistory(const QString &first, const QString &op, const QString &second = QString());
    QString formatNumber(double value) const;
    QString opToSymbol(const QString &op) const;
    void connectButtons();
    void applyStyleSheet();
};

#endif // MAINWINDOW_H
