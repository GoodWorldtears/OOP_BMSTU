#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../defines.h"

#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>

namespace
{
QString pageStyle()
{
    return "QMainWindow { background-color: #f0f0f0; }"
           "QWidget { font-family: Arial, sans-serif; font-size: 10pt; }";
}

QString groupStyle()
{
    return "QGroupBox {"
           "  border: 1px solid #b8b8b8;"
           "  border-radius: 3px;"
           "  margin-top: 10px;"
           "  padding: 8px;"
           "  background-color: #f7f7f7;"
           "}"
           "QGroupBox::title {"
           "  subcontrol-origin: margin;"
           "  left: 8px;"
           "  padding: 0 4px;"
           "  color: #202020;"
           "}";
}

QString floorLabelStyle()
{
    return "QLabel {"
           "  color: #202020;"
           "  padding: 4px 8px;"
           "}";
}

QString headerLabelStyle()
{
    return "QLabel { color: #202020; font-weight: bold; padding: 4px; }";
}

QString floorCallButtonStyle(bool active)
{
    const QString background = active ? "#d9edf7" : "#eeeeee";
    const QString border = active ? "#5bc0de" : "#9f9f9f";

    return QString(
        "QPushButton {"
        "  background-color: %1;"
        "  color: #000000;"
        "  border: 1px solid %2;"
        "  border-radius: 2px;"
        "  min-width: 38px; min-height: 30px;"
        "  max-width: 38px; max-height: 30px;"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover { background-color: #e0e0e0; }"
        "QPushButton:pressed { background-color: #cfcfcf; }")
        .arg(background, border);
}

QString cabinButtonStyle(cabin_id_t, bool active, bool current)
{
    QString background = "#eeeeee";
    QString border = "#9f9f9f";
    QString color = "#000000";

    if (active)
    {
        background = "#dff0d8";
        border = "#5cb85c";
    }

    if (current)
    {
        background = "#d9edf7";
        border = "#5bc0de";
    }

    if (active && current)
    {
        background = "#c4e3f3";
        border = "#31b0d5";
    }

    return QString(
        "QPushButton {"
        "  background-color: %1;"
        "  color: %2;"
        "  border: 1px solid %3;"
        "  border-radius: 2px;"
        "  min-width: 46px; min-height: 30px;"
        "  margin: 1px;"
        "}"
        "QPushButton:hover { background-color: #e0e0e0; }"
        "QPushButton:pressed { background-color: #cfcfcf; }")
        .arg(background, color, border);
}

QLabel *makeHeader(const QString& text)
{
    auto *label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet(headerLabelStyle());
    return label;
}
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      layout_(new QVBoxLayout())
{
    ui->setupUi(this);

    setWindowTitle("Лифты");
    setStyleSheet(pageStyle());
    resize(760, 620);

    ui->centralwidget->setLayout(layout_.get());
    layout_->setContentsMargins(10, 10, 10, 10);
    layout_->setSpacing(8);

    auto *mainWidget = new QWidget();
    auto *mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    auto *callSection = new QGroupBox("Вызов лифта");
    callSection->setStyleSheet(groupStyle());
    auto *callLayout = new QGridLayout(callSection);
    callLayout->setHorizontalSpacing(6);
    callLayout->setVerticalSpacing(4);

    callLayout->addWidget(makeHeader("Этаж"), 0, 0);
    callLayout->addWidget(makeHeader("Вверх"), 0, 1);
    callLayout->addWidget(makeHeader("Вниз"), 0, 2);

    for (int floor = FLOOR_COUNT; floor >= 1; --floor)
    {
        const int row = FLOOR_COUNT - floor + 1;

        auto *floorLabel = new QLabel(QString("%1 этаж").arg(floor));
        floorLabel->setAlignment(Qt::AlignCenter);
        floorLabel->setStyleSheet(floorLabelStyle());
        callLayout->addWidget(floorLabel, row, 0);

        if (floor != FLOOR_COUNT)
        {
            auto *upButton = new QPushButton("↑");
            upButton->setObjectName(QString("floor%1_up").arg(floor));
            upButton->setStyleSheet(floorCallButtonStyle(false));
            callLayout->addWidget(upButton, row, 1, Qt::AlignCenter);

            QObject::connect(upButton, &QPushButton::clicked, [this, floor]()
            {
                lift_system_.request_floor_call(floor, DIR_UP);
            });
        }

        if (floor > 1)
        {
            auto *downButton = new QPushButton("↓");
            downButton->setObjectName(QString("floor%1_down").arg(floor));
            downButton->setStyleSheet(floorCallButtonStyle(false));
            callLayout->addWidget(downButton, row, 2, Qt::AlignCenter);

            QObject::connect(downButton, &QPushButton::clicked, [this, floor]()
            {
                lift_system_.request_floor_call(floor, DIR_DOWN);
            });
        }
    }

    auto *liftsWidget = new QWidget();
    auto *liftsLayout = new QHBoxLayout(liftsWidget);
    liftsLayout->setSpacing(10);
    liftsLayout->setContentsMargins(0, 0, 0, 0);

    auto *lift1Section = new QGroupBox("Лифт 1");
    lift1Section->setStyleSheet(groupStyle());
    auto *lift1Layout = new QGridLayout(lift1Section);
    lift1Layout->setVerticalSpacing(6);

    auto *lift2Section = new QGroupBox("Лифт 2");
    lift2Section->setStyleSheet(groupStyle());
    auto *lift2Layout = new QGridLayout(lift2Section);
    lift2Layout->setVerticalSpacing(6);

    for (int floor = FLOOR_COUNT; floor >= 1; --floor)
    {
        const int row = FLOOR_COUNT - floor;

        auto *lift1Button = new QPushButton(QString::number(floor));
        lift1Button->setObjectName(QString("el1_floor%1").arg(floor));
        lift1Button->setStyleSheet(cabinButtonStyle(CID_FIRST, false, false));
        lift1Layout->addWidget(lift1Button, row, 0);
        QObject::connect(lift1Button, &QPushButton::clicked, [this, floor]()
        {
            lift_system_.request_cabin_call(floor, CID_FIRST);
        });

        auto *lift2Button = new QPushButton(QString::number(floor));
        lift2Button->setObjectName(QString("el2_floor%1").arg(floor));
        lift2Button->setStyleSheet(cabinButtonStyle(CID_SECOND, false, false));
        lift2Layout->addWidget(lift2Button, row, 0);
        QObject::connect(lift2Button, &QPushButton::clicked, [this, floor]()
        {
            lift_system_.request_cabin_call(floor, CID_SECOND);
        });
    }

    liftsLayout->addWidget(lift1Section);
    liftsLayout->addWidget(lift2Section);

    mainLayout->addWidget(callSection, 1);
    mainLayout->addWidget(liftsWidget, 1);
    layout_->addWidget(mainWidget);

    QObject::connect(&lift_system_, &LiftSystem::floor_button_style_changed,
                     this, &MainWindow::update_floor_button_style);
    QObject::connect(&lift_system_, &LiftSystem::cabin_button_style_changed,
                     this, &MainWindow::update_cabin_button_style);
    QObject::connect(&lift_system_, &LiftSystem::cabin_position_changed,
                     this, &MainWindow::update_cabin_position);

    for (int i = 0; i < CABINS_COUNT; ++i)
        update_cabin_position(static_cast<cabin_id_t>(i), START_FLOOR);
}

void MainWindow::update_floor_button_style(int floor, direction_t direction, bool is_active)
{
    const QString name = direction == DIR_UP
        ? QString("floor%1_up").arg(floor)
        : QString("floor%1_down").arg(floor);

    if (auto *button = findChild<QPushButton *>(name))
        button->setStyleSheet(floorCallButtonStyle(is_active));
}

void MainWindow::update_cabin_button_style(int floor, cabin_id_t cabin_id, bool is_active)
{
    if (floor < 1 || floor > FLOOR_COUNT)
        return;

    active_cabin_buttons_[cabin_id][floor - 1] = is_active;
    apply_cabin_button_style(cabin_id, floor);
}

void MainWindow::update_cabin_position(cabin_id_t cabin_id, int floor)
{
    if (cabin_id < 0 || cabin_id >= CABINS_COUNT)
        return;

    const int previous_floor = current_cabin_floors_[cabin_id];

    // Сначала обновляем модель состояния, и только потом перекрашиваем кнопки.
    // Иначе старая кнопка всё ещё считается текущей и остаётся голубой/синей.
    current_cabin_floors_[cabin_id] = floor;

    if (previous_floor >= 1 && previous_floor <= FLOOR_COUNT && previous_floor != floor)
        apply_cabin_button_style(cabin_id, previous_floor);

    if (floor >= 1 && floor <= FLOOR_COUNT)
        apply_cabin_button_style(cabin_id, floor);
}

QPushButton *MainWindow::find_cabin_button(cabin_id_t cabin_id, int floor) const
{
    const QString name = cabin_id == CID_FIRST
        ? QString("el1_floor%1").arg(floor)
        : QString("el2_floor%1").arg(floor);

    return findChild<QPushButton *>(name);
}

void MainWindow::apply_cabin_button_style(cabin_id_t cabin_id, int floor)
{
    if (auto *button = find_cabin_button(cabin_id, floor))
    {
        const bool active = active_cabin_buttons_[cabin_id][floor - 1];
        const bool current = current_cabin_floors_[cabin_id] == floor;
        button->setStyleSheet(cabinButtonStyle(cabin_id, active, current));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
