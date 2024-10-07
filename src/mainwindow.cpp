#include "mainwindow.h"
#include "addtransactiondialog.h"
#include <QToolBar>
#include <QAction>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_tableView(new QTableView(this)), m_model(new TransactionModel(this)) {
    setWindowTitle("Транзакции");
    setMinimumSize(400, 300);
    setCentralWidget(m_tableView);
    m_tableView->setModel(m_model);

    // Добавляем панель инструментов
    QToolBar *toolbar = addToolBar("Toolbar");
    QAction *addAction = toolbar->addAction("Добавить транзакцию");
    connect(addAction, &QAction::triggered, this, [this]() {
        AddTransactionDialog dialog(m_model, this);
        dialog.exec();
    });
    QAction*saveAction = toolbar->addAction("Сохранить транзакции");
    connect(saveAction, &QAction::triggered, this, [this]() {
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Transactions File"), "", tr("Text Files (*.txt)"));
        m_model->saveTransactionsToFile(filePath);
    });

    // Загрузка транзакций из файла
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Transactions File"), "", tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        m_model->loadTransactionsFromFile(filePath);
    }
}
