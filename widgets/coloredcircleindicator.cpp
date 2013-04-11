#include "coloredcircleindicator.h"
#include "ui_coloredcircleindicator.h"

ColoredCircleIndicator::ColoredCircleIndicator(QWidget *parent) :
    ColoredCircleWidget(parent),
    ui(new Ui::ColoredCircleIndicator)
{
    ui->setupUi(this);
}

ColoredCircleIndicator::~ColoredCircleIndicator()
{
    delete ui;
}
