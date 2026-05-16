#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <memory>

#include "../elevator/elevator.h"
#include "../defines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update_floor_button_style(int floor, direction_t direction, bool is_active);
    void update_cabin_button_style(int floor, cabin_id_t cabin_id, bool is_active);
    void update_cabin_position(cabin_id_t cabin_id, int floor);

private:
    QPushButton *find_cabin_button(cabin_id_t cabin_id, int floor) const;
    void apply_cabin_button_style(cabin_id_t cabin_id, int floor);

    Ui::MainWindow *ui;
    std::unique_ptr<QVBoxLayout> layout_;
    LiftSystem lift_system_;

    int current_cabin_floors_[CABINS_COUNT] = {0, 0};
    bool active_cabin_buttons_[CABINS_COUNT][FLOOR_COUNT] = {};
};

#endif
