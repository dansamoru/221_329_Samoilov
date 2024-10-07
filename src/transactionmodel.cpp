#include "transactionmodel.h"
#include <QDateTime>
#include <QRandomGenerator>

TransactionModel::TransactionModel(QObject* parent)
    : QAbstractTableModel(parent) {}

int TransactionModel::rowCount(const QModelIndex& /*parent*/) const {
    return m_transactions.size();
}

int TransactionModel::columnCount(const QModelIndex& /*parent*/) const {
    return 4; // amount, wallet, date, hash
}

QVariant TransactionModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Transaction& transaction = m_transactions[index.row()];

    switch (index.column()) {
        case 0: return transaction.amount;
        case 1: return transaction.wallet;
        case 2: return transaction.date;
        case 3: return transaction.hash;
        default: return QVariant();
    }
}

QVariant TransactionModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return QString("Amount");
            case 1: return QString("Wallet");
            case 2: return QString("Date");
            case 3: return QString("Hash");
            default: return QVariant();
        }
    }
    return QVariant();
}

void TransactionModel::addTransaction(double amount, const QString& prevHash) {
    Transaction transaction;
    transaction.amount = formatAmount(amount);
    transaction.wallet = generateWalletNumber();
    transaction.date = QDateTime::currentDateTime().toString("yyyy.MM.dd_hh:mm:ss");
    transaction.hash = calculateHash(transaction, prevHash);

    beginInsertRows(QModelIndex(), m_transactions.size(), m_transactions.size());
    m_transactions.append(transaction);
    endInsertRows();
}

QString TransactionModel::generateWalletNumber() const {
    QString wallet;
    for (int i = 0; i < 6; ++i) {
        wallet.append(QString::number(QRandomGenerator::global()->bounded(0, 10)));
    }
    return wallet;
}

QString TransactionModel::calculateHash(const Transaction& transaction, const QString& prevHash) const {
    QString data = transaction.amount + transaction.wallet + transaction.date + prevHash;
    QByteArray hashData = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashData.toHex());
}

QString TransactionModel::formatAmount(double amount) const {
    return QString("%1").arg(QString::number(amount, 'f', 2), 7, '0');
}
