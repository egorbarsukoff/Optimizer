//
// Created by egor on 12/23/19.
//

#ifndef OPTIMIZER_GUI_QT_PLOT_H
#define OPTIMIZER_GUI_QT_PLOT_H

#include "optim/Function.h"
#include "optim/Track.h"
#include <QLabel>
#include <QMouseEvent>

class Plot : public QLabel {
Q_OBJECT

    QImage heatmap;
    QLabel *coord_label;
    BoxDomain domain = BoxDomain{{{-1, 1}, {-1, 1}}};
    [[nodiscard]] std::pair<int, int> d2i(double x, double y) const;
    [[nodiscard]] std::pair<double, double> i2d(int x, int y) const;
    [[nodiscard]] static QColor heat_color(double min, double max, double val);
    std::pair<int, int> coord_transform(int x, int y);

private slots:
    void set_coord_label(double x, double y);
public:
protected:
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
public:
    explicit Plot(QWidget *parent, QSize size);
    void plot_function(std::unique_ptr<AbstractFunction> f);
    void plot_path(const Track &track);
    ~Plot();
signals:
    void mouseAt(double, double, double);
    void clicked(double, double);
};

#endif //OPTIMIZER_GUI_QT_PLOT_H
