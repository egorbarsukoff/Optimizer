
#include <QHBoxLayout>
#include <QtWidgets/QMessageBox>

#include "gui/mainwindow.h"
#include "./ui_mainwindow.h"

#include "optim/Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    setFixedSize(1000, 700);
    setWindowTitle("Optimizer");
    ui->setupUi(this);

    auto mainWidget = new QWidget(this);
    auto mainlayout = new QHBoxLayout(mainWidget);

    plot = new Plot{this, QSize(650, 650)};
    dialog_form = new DialogForm(this);
    mainlayout->addWidget(plot);
    mainlayout->addWidget(dialog_form);

    setCentralWidget(mainWidget);

    coord_label = new QLabel(this);
    statusBar()->addWidget(coord_label);
    set_coord_label(0, 0, 0);

    plot->plot_function(dialog_form->get_f());
    plot->show();

    connect(dialog_form, SIGNAL(change_function()), this, SLOT(change_f()));
    connect(plot, SIGNAL(clicked(double, double)), this, SLOT(optimize_from(double, double)));
    connect(this, SIGNAL(optim_finished(
                             const Track&)), dialog_form, SLOT(print_result(
                                                                   const Track&)));
    connect(this, SIGNAL(optim_finished(
                             const Track&)), plot, SLOT(print_track(
                                                            const Track&)));
}

void MainWindow::set_coord_label(double x, double y, double f) {
    coord_label->setText("x: " + QString::number(x, 'f', 5) + " " + "y: " + QString::number(y, 'f', 5) +
        " f(x, y) = " + QString::number(f, 'f', 5));
}

void MainWindow::optimize_from(double x, double y) {
    try {
        auto opt = dialog_form->get_optimizer();
        Eigen::VectorXd v(2);
        v << x, y;
        auto track = opt->optimize(v);
        emit optim_finished(track);
    } catch (std::exception &e) {
        QMessageBox::critical(this, "Ошибка", e.what());
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::change_f() {
    plot->plot_function(dialog_form->get_f());
}

