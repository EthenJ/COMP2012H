#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "City.h"

#include <QPixmap>
#include <QFileDialog>

#include <Qdir>

MenuWindow::MenuWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MenuWindow),
                                          selected_grid_size(20)
{
    ui->setupUi(this);

    // Scale label logo pixmap
    const QPixmap *p = ui->label_logo->pixmap();
    const int SCALE = 4;
    ui->label_logo->setPixmap(p->scaled(p->width() * SCALE, p->height() * SCALE));

    // Set pixmap for increase and decrease size buttons
    QPixmap increase{":/resources/images/next.png"};
    QPixmap decrease = increase.transformed(QTransform().rotate(180));
    ui->btn_increase_size->setIcon(increase);
    ui->btn_decrease_size->setIcon(decrease);

    ui->pages->setCurrentIndex(0);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::start_game(City *city)
{
    MainWindow *m = new MainWindow{city, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();

    close();
}

/*When the "Load Game" button is clicked, open a dialog to prompt the player to choose a save file to load.
 *If no file is chosen, for example, "Cancel" is clicked, or the dialog is closed, do nothing.
 *If a file is chosen, then load the city from the file and start the game.
 *The menu window is closed and the main window is started.
 *Similar to PA3, you can assume the format of the save file is correct.*/
void MenuWindow::on_btn_load_clicked()
{
    std::string map_file = (QFileDialog::getOpenFileName(this, QString(), QDir::currentPath())).toStdString();
    if (map_file == std::string())
    {
        return;
    }
    else
    {
        City *city = new City(map_file);
        start_game(city);
    }
}

/*When the "New Game" button is clicked, the UI is changed to prompt the player for the desired size of the city.*/
void MenuWindow::on_btn_new_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MenuWindow::on_btn_increase_size_clicked()
{
    int grid_size = (ui->label_grid_size->text()).toInt();
    if (grid_size >= 30)
    {
        return;
    }
    else
    {
        grid_size += 2;
        ui->label_grid_size->setText(QString::number(grid_size));
    }
}

void MenuWindow::on_btn_decrease_size_clicked()
{
    int grid_size = (ui->label_grid_size->text()).toInt();
    if (grid_size <= 10)
    {
        return;
    }
    else
    {
        grid_size -= 2;
        ui->label_grid_size->setText(QString::number(grid_size));
    }
}

void MenuWindow::on_btn_start_game_clicked()
{
    int grid_size = (ui->label_grid_size->text()).toInt();
    City *city = new City(grid_size);
    start_game(city);
}
