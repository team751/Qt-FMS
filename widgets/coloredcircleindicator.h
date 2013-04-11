#ifndef COLOREDCIRCLEINDICATOR_H
#define COLOREDCIRCLEINDICATOR_H

#include "coloredcirclewidget.h"

namespace Ui {
class ColoredCircleIndicator;
}

/**
 * @brief The ColoredCircleIndicator class is a type of ColoredCircleWidget
 * that provides methods that map statuses to colors.
 */
class ColoredCircleIndicator : public ColoredCircleWidget
{
    Q_OBJECT
    
public:
    explicit ColoredCircleIndicator(QWidget *parent = 0);
    ~ColoredCircleIndicator();
    
    /**
     * @brief indicateError Display an error status
     */
    void indicateError() {
        //display red
        ColoredCircleWidget::setCircleColor(Qt::red);
    }
    
    void indicateOK() {
        //display green
        ColoredCircleWidget::setCircleColor(Qt::green);
    }
    
    void indicateWarning() {
        //display yellow
        ColoredCircleWidget::setCircleColor(Qt::yellow);
    }
    
    void indicateOff() {
        //display gray
        ColoredCircleWidget::setCircleColor(Qt::gray);
    }
    
private:
    Ui::ColoredCircleIndicator *ui;
};

#endif // COLOREDCIRCLEINDICATOR_H
