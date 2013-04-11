#ifndef COLOREDCIRCLEWIDGET_H
#define COLOREDCIRCLEWIDGET_H

#include <QWidget>

namespace Ui {
class ColoredCircleWidget;
}

/**
 * @brief The ColoredCircleWidget class displays a colored circle
 */
class ColoredCircleWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColoredCircleWidget(QWidget *parent = 0);
    ~ColoredCircleWidget();
    
    void paintEvent(QPaintEvent *);
    
    /**
     * @brief setCircleColor Set the color to be displayed
     * @param newCircleColor the color
     */
    void setCircleColor(QColor newCircleColor);
    
private:
    Ui::ColoredCircleWidget *ui;
    
    /**
     * @brief circleColor The color that should be displayed
     */
    QColor circleColor;
};

#endif // COLOREDCIRCLEWIDGET_H
