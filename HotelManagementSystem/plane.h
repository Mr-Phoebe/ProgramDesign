#ifndef PLANE_H
#define PLANE_H

#include <QWidget>

namespace Ui {
class plane;
}

class plane : public QWidget
{
    Q_OBJECT
    
public:
    explicit plane(QWidget *parent = 0);
    ~plane();
    void updatePlanePage();
    void showPlanePage();

private:
    Ui::plane *ui;
};

#endif // PLANE_H
