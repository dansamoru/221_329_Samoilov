#pragma once
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QTextStream>

struct Transaction {
    QString amount;  // сумма с ведущими нулями
    QString wallet;  // номер криптокошелька
    QString date;    // дата в формате YYYY.mm.dd_HH:MM:SS
    QString hash;    // значение хеш-функции SHA-256
};

class TransactionModel : public QAbstractTableModel {
    Q_OBJECT
public:
    TransactionModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addTransaction(double amount, const QString& prevHash);

    void loadTransactionsFromFile(const QString &filePath);

    void saveTransactionsToFile(const QString &filePath) const;

private:
    QList<Transaction> m_transactions;
    QString generateWalletNumber() const;
    QString calculateHash(const Transaction& transaction, const QString& prevHash) const;
    QString formatAmount(double amount) const;
};
