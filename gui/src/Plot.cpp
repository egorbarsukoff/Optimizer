//
// Created by egor on 12/23/19.
//

#include "include/gui/Plot.h"

Plot::Plot(QWidget *parent, QSize size) : QLabel(parent), heatmap{size, QImage::Format::Format_RGB32} {
    setFixedSize(size);
    setMouseTracking(true);
    coord_label = new QLabel(this);
    coord_label->setFixedSize(200, 20);
    connect(this, SIGNAL(mouseAt(double, double, double)), parent, SLOT(set_coord_label(double, double, double)));
}

void Plot::set_coord_label(double x, double y) {
    coord_label->setText("(" + QString::number(x, 'f', 5) + ", " + QString::number(y, 'f', 5) + ")");
}

std::pair<int, int> Plot::d2i(double x, double y) const {
    assert(domain.dim() == 2);
    return {(x - domain[0][0]) / (domain[0][1] - domain[0][0]) * height(),
            (y - domain[1][0]) / (domain[1][1] - domain[1][0]) * width()};
}

std::pair<double, double> Plot::i2d(int x, int y) const {
    assert(domain.dim() == 2);
    return {x * (domain[0][1] - domain[0][0]) / width() + domain[0][0],
            y * (domain[1][1] - domain[1][0]) / height() + domain[1][0]};
}

QColor Plot::heat_color(double min, double max, double val) {
    QColor res;
    res.setHsvF(0.65 - std::clamp((val - min) / (max - min) * 0.65, 0., 0.65), 1, 1);
    return res;
}

void Plot::plot_function(std::unique_ptr<AbstractFunction> f) {
    domain = f->getDomain();

    Eigen::MatrixXd vals(width(), height());
    Eigen::VectorXd v(2);
    for (size_t i = 0; (int)i < width(); ++i) {
        for (size_t j = 0; (int)j < height(); ++j) {
            std::tie(v[0], v[1]) = i2d(i, j);
            vals(i, j) = (*f)(v);
        }
    }
    double max_v = vals.maxCoeff();
    double min_v = vals.minCoeff();

    for (size_t i = 0; (int)i < width(); ++i) {
        for (size_t j = 0; (int)j < height(); ++j) {
            heatmap.setPixelColor(i, j, heat_color(min_v, max_v, vals(i, j)));
        }
    }

    setPixmap(QPixmap::fromImage(heatmap));
}

std::pair<int, int> Plot::coord_transform(int x, int y) {
    return {x, height() - y};
}

void Plot::mouseMoveEvent(QMouseEvent *ev) {
    QLabel::mouseMoveEvent(ev);
    auto[x, y] = i2d(ev->x(), ev->y());
    emit mouseAt(x, y, 0);
}

void Plot::plot_path(const Track &track) {

}

Plot::~Plot() {

}
void Plot::mouseReleaseEvent(QMouseEvent *ev) {
    QLabel::mouseReleaseEvent(ev);
    auto[x, y] = i2d(ev->x(), ev->y());
    emit clicked(x, y);
}
