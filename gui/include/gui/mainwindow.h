#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include "gui/DialogForm.h"
#include "Plot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    DialogForm *dialog_form;
    Plot *plot;
    QLabel *coord_label;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void optimize_from(double x, double y);
    void set_coord_label(double x, double y);
    void change_f();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
