//
// Created by egor on 12/23/19.
//

#include <QHBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>

#include "include/gui/DialogForm.h"
#include <optim/TaskBuilder.h>
#include <optim/NewtonOptimizer.h>
#include <optim/RandomSearch.h>
#include <optim/Criterion.h>
#include <optim/Functions.h>

DialogForm::DialogForm(QWidget *parent) : QWidget(parent) {
    auto formlayout = new QFormLayout(this);

    auto formrow1 = new QHBoxLayout();
    auto label1 = new QLabel("Функция");
    auto function_list = new QComboBox();
    function_list->addItem("Розенброк");
    function_list->addItem("абц}");
    function = function_list;

    auto border_box = new QGroupBox("Границы", this);
    auto border_box_layout = new QGridLayout(border_box);
    auto double_validator = new QDoubleValidator(border_box);
    x0 = new QLineEdit("-1", border_box);
    x0->setValidator(double_validator);
    x1 = new QLineEdit("1", border_box);
    x1->setValidator(double_validator);
    y0 = new QLineEdit("-1", border_box);
    y0->setValidator(double_validator);
    y1 = new QLineEdit("1", border_box);
    y1->setValidator(double_validator);
    border_box_layout->addWidget(new QLabel("x0:"), 0, 0);
    border_box_layout->addWidget(x0, 0, 1);
    border_box_layout->addWidget(new QLabel("x1:"), 0, 2);
    border_box_layout->addWidget(x1, 0, 3);
    border_box_layout->addWidget(new QLabel("y0:"), 1, 0);
    border_box_layout->addWidget(y0, 1, 1);
    border_box_layout->addWidget(new QLabel("y0:"), 1, 2);
    border_box_layout->addWidget(y1, 1, 3);

    connect(function_list,
            static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,
            [this](const auto &s) {
                emit change_function();
            });

    connect(x0,
            &QLineEdit::editingFinished,
            this,
            [this]() {
                emit change_function();
            });

    connect(x1,
            &QLineEdit::editingFinished,
            this,
            [this]() {
                emit change_function();
            });

    connect(y0,
            &QLineEdit::editingFinished,
            this,
            [this]() {
                emit change_function();
            });

    connect(y1,
            &QLineEdit::editingFinished,
            this,
            [this]() {
                emit change_function();
            });

    formrow1->addWidget(label1);
    formrow1->addWidget(function_list);
    formlayout->addRow(formrow1);
    formlayout->addWidget(border_box);

    auto formrow2 = new QHBoxLayout();
    auto label2 = new QLabel("Метод");
    auto method_list = new QComboBox();
    method_list->addItem("Метод Ньютона");
    method_list->addItem("Случайный поиск");
    method = method_list;

    formrow2->addWidget(label2);
    formrow2->addWidget(method_list);
    formlayout->addRow(formrow2);

    auto rs_params_group = new QGroupBox("Параметры случайного поиска", this);
    rs_params_group->setDisabled(true);
    auto rs_box_layout = new QHBoxLayout(rs_params_group);
    auto rs_params_validator = new QDoubleValidator(0, 1, 5, rs_params_group);
    p_rs = new QLineEdit(rs_params_group);
    p_rs->setValidator(rs_params_validator);
    p_rs->setText("0.5");
    h_rs = new QLineEdit(rs_params_group);
    h_rs->setValidator(rs_params_validator);
    h_rs->setText("0.1");

    auto p_label = new QLabel(rs_params_group);
    p_label->setText("p:");
    auto h_label = new QLabel(rs_params_group);
    h_label->setText("h:");
    rs_box_layout->addWidget(p_label);
    rs_box_layout->addWidget(p_rs);
    rs_box_layout->addWidget(h_label);
    rs_box_layout->addWidget(h_rs);

    formlayout->addWidget(rs_params_group);

    connect(method_list, &QComboBox::currentTextChanged, rs_params_group, [rs_params_group](const auto &s) {
        rs_params_group->setDisabled(s == "Метод Ньютона");
    });

    crit_box = new QGroupBox("Критерии остановки", this);
    formlayout->addWidget(crit_box);
    new QFormLayout(crit_box);

    add_crit_int_param("Количество итераций");
    add_crit_int_param("Количество итераций \nбез обновления");
    add_crit_float_param("Изменение функции");

    auto test_button = new QPushButton(this);
    formlayout->addWidget(test_button);
    connect(test_button, &QPushButton::clicked, this, [this](auto s) {
        auto opt = get_optimizer();;
        std::cerr << "!";
    });
}

void DialogForm::add_crit_float_param(std::string_view name) {
    auto double_validator = new QDoubleValidator(0, 100, 5, crit_box);
    add_crit(name, double_validator);
}

void DialogForm::add_crit_int_param(std::string_view name) {
    auto int_validator = new QIntValidator(0, 1000000000, crit_box);
    add_crit(name, int_validator);
}

void DialogForm::add_crit(std::string_view name, QValidator *validator) {
    auto critrow1 = new QHBoxLayout();
    auto checkbox1 = new QCheckBox(name.data(), crit_box);
    auto param1 = new QLineEdit(crit_box);
    param1->setValidator(validator);
    param1->setPlaceholderText("Параметр");
    param1->setFixedSize(70, 30);
    param1->setDisabled(true);
    connect(checkbox1, &QCheckBox::stateChanged, param1, [param1](int state) { param1->setDisabled(!state); });

    critrow1->addWidget(checkbox1);
    critrow1->addWidget(param1);
    static_cast<QFormLayout *>(crit_box->layout())->addRow(critrow1);

    crits.emplace_back(checkbox1, param1);

}

std::unique_ptr<AbstractFunction> DialogForm::get_f() const {
    std::optional<BoxDomain> domain;
    bool ok1 = false, ok2 = false, ok3 = false, ok4 = false;
    try {
        domain = BoxDomain{{{x0->text().toDouble(&ok1), x1->text().toDouble(&ok2)},
                            {y0->text().toDouble(&ok3), y1->text().toDouble(&ok4)}}};
    } catch (std::exception &e) {
        if (strcmp(e.what(), "Bad bounds") == 0) {
            throw std::runtime_error("Некоректно введенные границы");
        }
    }
    if (!ok1 || !ok2 || !ok3 || !ok4) {
        throw std::runtime_error("Некоректно введенные границы");
    }

    if (function->currentText() == "Розенброк") {
        return std::make_unique<Rosenbrock>(*domain);
    }
    assert(false);
}

std::unique_ptr<Criterion> DialogForm::get_crit() const {
    std::vector<std::unique_ptr<Criterion>> crits_vec;
    std::transform(crits.cbegin(),
                   crits.cend(),
                   std::back_inserter(crits_vec),
                   [](const std::pair<QCheckBox *, QLineEdit *> &pair) -> std::unique_ptr<Criterion> {
                       if (pair.first->isChecked()) {
                           bool ok = false;
                           double param = pair.second->text().toDouble(&ok);
                           if (!ok) {
                               throw std::runtime_error(
                                   "Ошибка парсинга праметров критерия " + pair.first->text().toStdString());
                           }
                           if (pair.first->text() == "Количество итераций") {
                               return std::make_unique<MaxN>((size_t)param);
                           } else if (pair.first->text() == "Количество итераций \nбез обновления") {
                               return std::make_unique<NWithoutUpdates>((size_t)param);
                           } else if (pair.first->text() == "Изменение функции") {
                               return std::make_unique<FunctionChange>(param);
                           }
                       }
                       return nullptr;
                   });
    crits_vec.erase(std::remove_if(crits_vec.begin(), crits_vec.end(), [](auto &el) {
        return !bool(el);
    }), crits_vec.end());
    if (crits_vec.empty()) {
        throw std::runtime_error("Нужно отметить хотя бы 1 критерий");
    }
    return std::make_unique<CriterionPack>(std::move(crits_vec));
}

std::unique_ptr<Optimizer> DialogForm::get_optimizer() const {
    if (method->currentText() == "Случайный поиск") {
        bool ok1 = false, ok2 = false;
        double p = p_rs->text().toDouble(&ok1);
        double h = h_rs->text().toDouble(&ok2);
        if (!ok1 || !ok2) {
            throw std::runtime_error("Ошибка парсинга параметров случайного поиска");
        }
        return std::make_unique<RandomSearch>(get_f(), get_crit(), h, p);
    } else {
        return std::make_unique<NewtonOptimizer>(get_f(), get_crit());
    }
}
