#pragma once
#include <QMainWindow>
#include <QTableView>
#include "transactionmodel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private:
    QTableView* m_tableView;
    TransactionModel* m_model;
};
