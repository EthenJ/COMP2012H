#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "City.h"

#include <QMainWindow>

namespace Ui { class MenuWindow; }

class MenuWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    void start_game(City *city);

    Ui::MenuWindow *ui;

    // Store the grid size in this variable
    int selected_grid_size;
};

#endif // MENUWINDOW_H
