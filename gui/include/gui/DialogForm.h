//
// Created by egor on 12/23/19.
//

#ifndef OPTIMIZER_GUI_INCLUDE_GUI_DIALOGFORM_H
#define OPTIMIZER_GUI_INCLUDE_GUI_DIALOGFORM_H

#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>

#include "optim/Track.h"
#include "optim/Function.h"
#include "optim/Criterion.h"
#include "optim/Optimizer.h"

class DialogForm : public QWidget {
Q_OBJECT

    QComboBox *function = nullptr;
    QComboBox *method = nullptr;
    QGroupBox *crit_box = nullptr;
    QLineEdit *x0, *x1, *y0, *y1, *h_rs, *p_rs;
    std::vector<std::pair<QCheckBox *, QLineEdit *>> crits;

    QLabel *results;

    void add_crit_float_param(std::string_view name);
    void add_crit_int_param(std::string_view name);
    void add_crit(std::string_view name, QValidator *validator);
public:
    explicit DialogForm(QWidget *parent);
    [[nodiscard]] std::unique_ptr<AbstractFunction> get_f() const;
    [[nodiscard]] std::unique_ptr<Criterion> get_crit() const;
    [[nodiscard]] std::unique_ptr<Optimizer> get_optimizer() const;

signals:
    void change_function();

public slots:
    void print_result(const Track &);
};

#endif //OPTIMIZER_GUI_INCLUDE_GUI_DIALOGFORM_H
