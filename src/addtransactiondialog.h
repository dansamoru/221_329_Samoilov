#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "transactionmodel.h"

class AddTransactionDialog : public QDialog {
    Q_OBJECT

public:
    AddTransactionDialog(TransactionModel* model, QWidget* parent = nullptr);

    private slots:
        void onAddTransaction();
    void onInputChanged();

private:
    QLineEdit* m_amountEdit;
    QLineEdit* m_walletEdit;
    QLineEdit* m_dateEdit;
    QPushButton* m_saveButton;
    TransactionModel* m_model;

    bool validateInput();
};
