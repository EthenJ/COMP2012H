#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "City.h"

#include <QPixmap>
#include <QFileDialog>

MenuWindow::MenuWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MenuWindow),
        selected_grid_size(20)
{
    ui->setupUi(this);

    // Scale label logo pixmap
    QPixmap p = ui->label_logo->pixmap(Qt::ReturnByValue);
    const int SCALE = 4;
    ui->label_logo->setPixmap(p.scaled(p.width() * SCALE, p.height() * SCALE));

    // Set pixmap for increase and decrease size buttons
    QPixmap increase {":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::start_game(City *city) {
    MainWindow *m = new MainWindow{city, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
}
