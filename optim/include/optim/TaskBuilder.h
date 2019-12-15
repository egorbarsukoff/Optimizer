//
// Created by eb on 09.10.2019.
//

#ifndef OPTIMIZER_OPTIM_INCLUDE_OPTIM_TASKBUILDER_H
#define OPTIMIZER_OPTIM_INCLUDE_OPTIM_TASKBUILDER_H

#include <optional>
#include <memory>
#include "Function.h"
#include "Optimizer.h"

//! @brief Построение задачи оптимизации
class TaskBuilder {
    std::optional<std::unique_ptr<AbstractFunction>> f = std::nullopt;
    std::optional<Eigen::VectorXd> start = Eigen::VectorXd::Zero(0);
    std::vector<std::unique_ptr<Criterion>> crits = {};
public:

    //! Установить фунцию
    //! @tparam T - Класс оптимизируемой функции
    //! @param args - Аргументы конструкора фунции
    template<typename T, typename ...Args>
    TaskBuilder &set_f(Args &&... args) {
        static_assert(std::is_base_of_v<AbstractFunction, T>, "T must derive from AbstractFunction");
        f = std::make_unique<T>(std::forward<Args>(args)...);
    }

    //! Добавить критерии остновки
    //! @tparam T - Класс критрия
    //! @param args - Аругменты конструктора критрерия
    template<typename T, typename ...Args>
    TaskBuilder &add_crit(Args &&... args) {
        static_assert(std::is_base_of_v<Criterion, T>, "T must derive from Criterion");
        crits.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    //! Установить начальную точку
    //! @param coords - координаты
    template<typename ...Args>
    TaskBuilder &set_start(Args... coords) {
        assert(f && (*f)->getDomain().dim() == sizeof...(Args));
        Eigen::VectorXd v(sizeof...(Args));
        std::vector<double> t{static_cast<double>(coords)...};
        for (long i = 0; i < v.size(); ++i) {
            v[i] = t[i];
        }
        start = v;
    }

    //! Статус задачи
    [[nodiscard]] bool configured() const {
        return f && start && start && !crits.empty();
    }

    //! Начать оптимизацию
    //! @tparam Method - Класс метода оптимизации
    //! @param args - аругменты оптимизатора
    template<typename Method, typename ... Args>
    std::pair<Eigen::VectorXd, double> start_and_reset(Args &&... args) {
        static_assert(std::is_base_of_v<Optimizer, Method>, "Method must derive from Optimizer");
        auto crit = std::make_unique<CriterionPack>(std::move(crits));
        Method optimizer = Method(std::move(*f), std::move(crit), std::forward<Args>(args)...);
        auto ans = optimizer.optimize(*start).back();
        start = std::nullopt;
        return std::make_pair(ans.x, ans.y);
    }
};

#endif //OPTIMIZER_OPTIM_INCLUDE_OPTIM_TASKBUILDER_H
