#include "coloredcirclewidget.h"
#include "ui_coloredcirclewidget.h"

#include <QPainter>

ColoredCircleWidget::ColoredCircleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColoredCircleWidget),
    circleColor(Qt::gray)
{
    ui->setupUi(this);
}

void ColoredCircleWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    //Enable antialiasing
    painter.setRenderHint(QPainter::Antialiasing, true);
    
    QPainterPath circle;
    circle.addEllipse(rect());
    
    painter.fillPath(circle, circleColor);
}

void ColoredCircleWidget::setCircleColor(QColor newCircleColor) {
    if(circleColor != newCircleColor) {
        circleColor = newCircleColor;
        update();
    }
}

ColoredCircleWidget::~ColoredCircleWidget()
{
    delete ui;
}
