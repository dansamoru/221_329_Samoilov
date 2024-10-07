#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_tableView(new QTableView(this)), m_model(new TransactionModel(this)) {

    setWindowTitle("Транзакции");
    setMinimumSize(400, 300);
    setCentralWidget(m_tableView);
    m_tableView->setModel(m_model);

    // Добавление тестовых транзакций
    m_model->addTransaction(12345.67, "");
    m_model->addTransaction(890.12, "");
    m_model->addTransaction(19.25, "");
    m_model->addTransaction(1166.01, "");
    m_model->addTransaction(1028.10, "");
}
