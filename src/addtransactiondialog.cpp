#include "addtransactiondialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QRegularExpressionValidator>

AddTransactionDialog::AddTransactionDialog(TransactionModel *model, QWidget *parent)
    : QDialog(parent), m_model(model) {
    setWindowTitle("Добавить транзакцию");
    setMinimumSize(300, 300);

    m_amountEdit = new QLineEdit(this);
    m_walletEdit = new QLineEdit(this);
    m_dateEdit = new QLineEdit(this);
    m_saveButton = new QPushButton("Сохранить", this);
    m_saveButton->setEnabled(false); // Изначально кнопка отключена

    // Установка валидаторов для полей ввода
    m_amountEdit->setPlaceholderText("Сумма (0000000)");
    m_walletEdit->setPlaceholderText("Номер кошелька (6 цифр)");
    m_dateEdit->setPlaceholderText("Дата (YYYY.MM.DD_HH:MM:SS)");

    // Валидатор для суммы (7 цифр)
    QRegularExpressionValidator *amountValidator = new QRegularExpressionValidator(QRegularExpression("\\d{7}"), this);
    m_amountEdit->setValidator(amountValidator);

    // Валидатор для номера кошелька (6 цифр)
    QRegularExpressionValidator *walletValidator = new QRegularExpressionValidator(QRegularExpression("\\d{6}"), this);
    m_walletEdit->setValidator(walletValidator);

    // Валидатор для даты (YYYY.MM.DD_HH:MM:SS)
    QRegularExpressionValidator *dateValidator = new QRegularExpressionValidator(
        QRegularExpression("\\d{4}\\.\\d{2}\\.\\d{2}_\\d{2}:\\d{2}:\\d{2}"), this);
    m_dateEdit->setValidator(dateValidator);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Сумма:"));
    layout->addWidget(m_amountEdit);
    layout->addWidget(new QLabel("Номер кошелька:"));
    layout->addWidget(m_walletEdit);
    layout->addWidget(new QLabel("Дата:"));
    layout->addWidget(m_dateEdit);
    layout->addWidget(m_saveButton);

    connect(m_amountEdit, &QLineEdit::textChanged, this, &AddTransactionDialog::onInputChanged);
    connect(m_walletEdit, &QLineEdit::textChanged, this, &AddTransactionDialog::onInputChanged);
    connect(m_dateEdit, &QLineEdit::textChanged, this, &AddTransactionDialog::onInputChanged);
    connect(m_saveButton, &QPushButton::clicked, this, &AddTransactionDialog::onAddTransaction);
}

void AddTransactionDialog::onInputChanged() {
    m_saveButton->setEnabled(validateInput());
}

bool AddTransactionDialog::validateInput() {
    return !m_amountEdit->text().isEmpty() &&
           !m_walletEdit->text().isEmpty() &&
           !m_dateEdit->text().isEmpty() &&
           m_amountEdit->hasAcceptableInput() &&
           m_walletEdit->hasAcceptableInput() &&
           m_dateEdit->hasAcceptableInput();
}

void AddTransactionDialog::onAddTransaction() {
    QString amount = m_amountEdit->text();
    QString wallet = m_walletEdit->text();
    QString date = m_dateEdit->text();

    // Предполагается, что предыдущий хеш передается как пустая строка, если это первая транзакция
    QString prevHash = m_model->rowCount() > 0
                           ? m_model->data(m_model->index(m_model->rowCount() - 1, 3), Qt::DisplayRole).toString()
                           : "";

    // Добавление транзакции в модель
    m_model->addTransaction(amount.toDouble(), prevHash);

    accept(); // Закрыть диалог
}
