#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QPushButton>

// ==================== 构造与析构 ====================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_firstOperand(0)
    , m_pendingOperator("")
    , m_waitingForOperand(false)
    , m_error(false)
{
    ui->setupUi(this);
    applyStyleSheet();
    connectButtons();
    ui->displayLineEdit->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== 信号槽连接 ====================

void MainWindow::connectButtons()
{
    // 数字按钮 0-9 —— 统一连接到 onDigitClicked
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::onDigitClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::onDigitClicked);

    // 运算符按钮 —— 统一连接到 onOperatorClicked
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnSubtract, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &MainWindow::onOperatorClicked);

    // 功能按钮
    connect(ui->btnEquals, &QPushButton::clicked, this, &MainWindow::onEqualsClicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearClicked);
    connect(ui->btnBackspace, &QPushButton::clicked, this, &MainWindow::onBackspaceClicked);
    connect(ui->btnDecimal, &QPushButton::clicked, this, &MainWindow::onDecimalClicked);
}

// ==================== 深色主题样式表 ====================

void MainWindow::applyStyleSheet()
{
    setStyleSheet(
        "QMainWindow {"
        "   background-color: #1e1e2e;"
        "}"
        "QLabel#historyLabel {"
        "   color: #a6adc8;"
        "   font-size: 16px;"
        "   padding: 4px 8px;"
        "   background: transparent;"
        "}"
        "QLineEdit#displayLineEdit {"
        "   font-size: 36px;"
        "   font-weight: bold;"
        "   color: #cdd6f4;"
        "   background-color: #181825;"
        "   border: none;"
        "   border-radius: 12px;"
        "   padding: 16px 20px;"
        "}"
        "QPushButton {"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "   border-radius: 24px;"
        "   min-height: 52px;"
        "   min-width: 52px;"
        "   color: #cdd6f4;"
        "   background-color: #313244;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45475a;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #585b70;"
        "}"
        "QPushButton#btnAdd, QPushButton#btnSubtract,"
        "QPushButton#btnMultiply, QPushButton#btnDivide {"
        "   background-color: #f38ba8;"
        "   color: #1e1e2e;"
        "}"
        "QPushButton#btnAdd:hover, QPushButton#btnSubtract:hover,"
        "QPushButton#btnMultiply:hover, QPushButton#btnDivide:hover {"
        "   background-color: #eba0c0;"
        "}"
        "QPushButton#btnEquals {"
        "   background-color: #89b4fa;"
        "   color: #1e1e2e;"
        "}"
        "QPushButton#btnEquals:hover {"
        "   background-color: #a5c4fb;"
        "}"
        "QPushButton#btnClear, QPushButton#btnBackspace {"
        "   background-color: #f9e2af;"
        "   color: #1e1e2e;"
        "}"
        "QPushButton#btnClear:hover, QPushButton#btnBackspace:hover {"
        "   background-color: #fcefba;"
        "}"
    );
}

// ==================== 按钮点击槽函数 ====================
// 以下槽函数仅做路由，核心逻辑在 handle* 方法中，
// 键盘事件也调用同一套 handle* 方法，实现逻辑复用。

void MainWindow::onDigitClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    handleDigit(btn->text());
}

void MainWindow::onOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    // 通过 objectName 映射为内部运算符，避免编码问题
    QString name = btn->objectName();
    if (name == "btnAdd")      handleOperator("+");
    else if (name == "btnSubtract")  handleOperator("-");
    else if (name == "btnMultiply") handleOperator("*");
    else if (name == "btnDivide")    handleOperator("/");
}

void MainWindow::onEqualsClicked()    { handleEquals();    }
void MainWindow::onClearClicked()     { handleClear();     }
void MainWindow::onBackspaceClicked() { handleBackspace(); }
void MainWindow::onDecimalClicked()   { handleDecimal();   }

// ==================== 统一输入处理（鼠标+键盘共用） ====================

void MainWindow::handleDigit(const QString &digit)
{
    // 错误状态下按数字键 → 清除错误并重新开始
    if (m_error) {
        clearAll();
    }

    if (m_waitingForOperand) {
        // 刚按下运算符或等号后，开始输入新操作数
        ui->displayLineEdit->setText(digit);
        m_waitingForOperand = false;
    } else {
        QString current = ui->displayLineEdit->text();
        // 显示为 "0" 时用数字替换（避免前导零，如 "05"）
        if (current == "0") {
            ui->displayLineEdit->setText(digit);
        } else {
            ui->displayLineEdit->setText(current + digit);
        }
    }
}

void MainWindow::handleDecimal()
{
    if (m_error) {
        clearAll();
    }

    if (m_waitingForOperand) {
        // 运算符后输入小数点，从 "0." 开始
        ui->displayLineEdit->setText("0.");
        m_waitingForOperand = false;
        return;
    }

    // 防止同一操作数重复输入小数点（如 "3.1.4" → 忽略第二个点）
    QString current = ui->displayLineEdit->text();
    if (!current.contains('.')) {
        ui->displayLineEdit->setText(current + ".");
    }
}

void MainWindow::handleOperator(const QString &op)
{
    if (m_error) {
        clearAll();
    }

    // 连续运算：有待执行运算符且已输入第二操作数时，先完成上一步
    // 例如 5 + 3 - → 先算 5+3=8，再用8作为下一步的第一操作数
    if (!m_pendingOperator.isEmpty() && !m_waitingForOperand) {
        performCalculation();
        if (m_error) return;
    }

    // 保存当前显示值为第一操作数
    m_firstOperand = displayValue();
    m_pendingOperator = op;
    m_waitingForOperand = true;

    // 更新历史显示：如 "5 +" 或 "8 ×"
    updateHistory(formatNumber(m_firstOperand), opToSymbol(op));
}

void MainWindow::handleEquals()
{
    if (m_error) return;

    // 无待执行运算符时等号无效
    if (m_pendingOperator.isEmpty()) {
        return;
    }

    double secondOperand;
    if (m_waitingForOperand) {
        // 未输入第二操作数，复用第一操作数（如 5+= → 5+5=10）
        secondOperand = m_firstOperand;
    } else {
        secondOperand = displayValue();
    }

    // === 除零检测 ===
    if (m_pendingOperator == "/" && secondOperand == 0) {
        setDisplay("Error: \303\267 0");
        ui->historyLabel->setText(formatNumber(m_firstOperand) + " \303\267 0 =");
        m_error = true;
        m_pendingOperator.clear();
        m_waitingForOperand = true;
        return;
    }

    // === 执行四则运算 ===
    double result = 0;
    if      (m_pendingOperator == "+") result = m_firstOperand + secondOperand;
    else if (m_pendingOperator == "-") result = m_firstOperand - secondOperand;
    else if (m_pendingOperator == "*") result = m_firstOperand * secondOperand;
    else if (m_pendingOperator == "/") result = m_firstOperand / secondOperand;

    // 更新历史显示：如 "5 + 3 ="
    updateHistory(formatNumber(m_firstOperand), opToSymbol(m_pendingOperator),
                  formatNumber(secondOperand) + " =");

    setDisplay(result);

    // 保存结果，准备后续连续操作（如 5+3=8 后按 - → 8-...）
    m_firstOperand = result;
    m_pendingOperator.clear();
    m_waitingForOperand = true;
}

void MainWindow::handleClear()
{
    clearAll();
}

void MainWindow::handleBackspace()
{
    if (m_error) {
        clearAll();
        return;
    }

    // 等待操作数状态下退格无效（运算符/等号后不能退格）
    if (m_waitingForOperand) {
        return;
    }

    QString current = ui->displayLineEdit->text();
    // 只剩一位（或负号+一位）时退格回到 "0"
    if (current.length() <= 1 || (current.length() == 2 && current.startsWith('-'))) {
        ui->displayLineEdit->setText("0");
    } else {
        current.chop(1);
        ui->displayLineEdit->setText(current);
    }
}

// ==================== 辅助方法 ====================

double MainWindow::displayValue() const
{
    return ui->displayLineEdit->text().toDouble();
}

void MainWindow::setDisplay(double value)
{
    setDisplay(formatNumber(value));
}

void MainWindow::setDisplay(const QString &text)
{
    ui->displayLineEdit->setText(text);
}

void MainWindow::clearAll()
{
    m_firstOperand = 0;
    m_pendingOperator.clear();
    m_waitingForOperand = false;
    m_error = false;
    ui->displayLineEdit->setText("0");
    ui->historyLabel->clear();
}

void MainWindow::performCalculation()
{
    double secondOperand = displayValue();

    // 除零检测（连续运算场景，如 5/0*3）
    if (m_pendingOperator == "/" && secondOperand == 0) {
        setDisplay("Error: \303\267 0");
        ui->historyLabel->setText(formatNumber(m_firstOperand) + " \303\267 0");
        m_error = true;
        m_pendingOperator.clear();
        m_waitingForOperand = true;
        return;
    }

    double result = 0;
    if      (m_pendingOperator == "+") result = m_firstOperand + secondOperand;
    else if (m_pendingOperator == "-") result = m_firstOperand - secondOperand;
    else if (m_pendingOperator == "*") result = m_firstOperand * secondOperand;
    else if (m_pendingOperator == "/") result = m_firstOperand / secondOperand;

    m_firstOperand = result;
    setDisplay(result);
}

void MainWindow::updateHistory(const QString &first, const QString &op, const QString &second)
{
    if (second.isEmpty()) {
        ui->historyLabel->setText(first + " " + op);
    } else {
        ui->historyLabel->setText(first + " " + op + " " + second);
    }
}

QString MainWindow::formatNumber(double value) const
{
    // 整数直接显示（去掉 .0 后缀），在 qint64 范围内
    if (value >= -9.2e18 && value <= 9.2e18 && value == static_cast<qint64>(value)) {
        return QString::number(static_cast<qint64>(value));
    }
    // 小数最多15位有效数字，自动去除末尾多余零
    return QString::number(value, 'g', 15);
}

QString MainWindow::opToSymbol(const QString &op) const
{
    if (op == "+") return "+";
    if (op == "-") return "\342\210\222";  // − (U+2212 MINUS SIGN)
    if (op == "*") return "\303\227";      // × (U+00D7 MULTIPLICATION SIGN)
    if (op == "/") return "\303\267";      // ÷ (U+00F7 DIVISION SIGN)
    return op;
}

// ==================== 键盘事件处理 ====================
// 键盘按键映射到与鼠标按钮相同的 handle* 方法，
// 保证鼠标与键盘输入逻辑完全一致。

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QString text = event->text();

    // 数字键 0-9（主键盘和小键盘均可）
    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        handleDigit(QString(QChar('0' + (key - Qt::Key_0))));
        return;
    }

    // 小数点（句号或逗号）
    if (key == Qt::Key_Period || key == Qt::Key_Comma) {
        handleDecimal();
        return;
    }

    // 运算符（同时检测 keyCode 和 text 以覆盖 Shift 组合键和小键盘）
    if (key == Qt::Key_Plus || text == "+") {
        handleOperator("+");
        return;
    }
    if (key == Qt::Key_Minus || text == "-") {
        handleOperator("-");
        return;
    }
    if (key == Qt::Key_Asterisk || text == "*") {
        handleOperator("*");
        return;
    }
    if (key == Qt::Key_Slash || text == "/") {
        handleOperator("/");
        return;
    }

    // 等号 / 回车（主键盘 Enter 和小键盘 Enter）
    if (key == Qt::Key_Enter || key == Qt::Key_Return || key == Qt::Key_Equal) {
        handleEquals();
        return;
    }

    // 退格键
    if (key == Qt::Key_Backspace) {
        handleBackspace();
        return;
    }

    // 清除（Esc 或 Delete）
    if (key == Qt::Key_Escape || key == Qt::Key_Delete) {
        handleClear();
        return;
    }

    // 其他按键交给基类处理
    QMainWindow::keyPressEvent(event);
}
