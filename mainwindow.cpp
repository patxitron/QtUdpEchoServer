#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
		:QMainWindow(parent)
		,ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->pushStop->setDisabled(true);
	ui->plainTextEdit->setReadOnly(true);
	connect(ui->pushBegin, &QPushButton::clicked, [this]() {
		int from = ui->spinFrom->value();
		int to = ui->spinTo->value();
		if(from < to) {
			ui->plainTextEdit->clear();
			ui->pushStop->setDisabled(false);
			ui->pushBegin->setDisabled(true);
			ui->spinFrom->setDisabled(true);
			ui->spinTo->setDisabled(true);
			for(int i = from; i <= to; ++i) {
				std::unique_ptr p(new UdpListener(i));
				connect(p.get(), &UdpListener::received, [this](QString const& data) {
					ui->plainTextEdit->appendPlainText(data + "\r\n");
					ui->plainTextEdit->moveCursor(QTextCursor::End);
				});
				sockets_.push_back(std::move(p));
			}
		}
	});
	connect(ui->pushStop, &QPushButton::clicked, [this]() {
		ui->pushStop->setDisabled(true);
		ui->pushBegin->setDisabled(false);
		ui->spinFrom->setDisabled(false);
		ui->spinTo->setDisabled(false);
		sockets_.clear();
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}
