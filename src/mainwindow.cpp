#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_tableView(new QTableView(this)), m_model(new TransactionModel(this)) {

    setWindowTitle("Транзакции");
    setMinimumSize(400, 300);
    setCentralWidget(m_tableView);
    m_tableView->setModel(m_model);

    // Загрузка транзакций из файла
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Transactions File"), "", tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        m_model->loadTransactionsFromFile(filePath);
    }
}
