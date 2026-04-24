#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "scene/Camera.h"
#include <QGraphicsScene>
#include <QInputDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include "render/QtRenderSurface.h"

MainWindow::MainWindow(SceneApplicationService &appService, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _appService(appService)
{
    ui->setupUi(this);

    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(-450, -400, 900, 800);
    scene->setBackgroundBrush(Qt::white);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(1.0, 1.0);

    ui->objectListWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->cameraListWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    try
    {
        _appService.AddCamera(0.0, 0.0, -400.0);
        refreshCameraList();
        redrawScene();
    }
    catch (...) {}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redrawScene()
{
    QtRenderSurface surface(ui->graphicsView->scene());
    _appService.Draw(surface);
}

void MainWindow::refreshObjectList()
{
    ui->objectListWidget->clear();
    const auto &objects = _appService.scene().objects();
    for (int i = 0; i < static_cast<int>(objects.size()); ++i)
    {
        if (std::dynamic_pointer_cast<Camera>(objects[i]))
            continue;
        auto *item = new QListWidgetItem(QString("%1").arg(objects[i]->name()));
        item->setData(Qt::UserRole, i);
        ui->objectListWidget->addItem(item);
    }
}

void MainWindow::refreshCameraList()
{
    ui->cameraListWidget->clear();
    const auto cameras = _appService.scene().cameras();
    for (int i = 0; i < static_cast<int>(cameras.size()); ++i)
    {
        auto *item = new QListWidgetItem(cameras[i]->name());
        item->setData(Qt::UserRole, i);
        if (i == _appService.scene().activeCameraIndex())
            item->setText(item->text() + " [active]");
        ui->cameraListWidget->addItem(item);
    }
}

std::vector<int> MainWindow::selectedObjectIndices() const
{
    std::vector<int> result;
    for (QListWidgetItem *item : ui->objectListWidget->selectedItems())
        result.push_back(item->data(Qt::UserRole).toInt());
    return result;
}

void MainWindow::on_loadPushButton_clicked()
{
    try
    {
        _appService.LoadModel(_selectedFilePath, ui->txtRadioButton->isChecked());
        refreshObjectList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_fileSelectButton_clicked()
{
    QString filter;
    if (ui->txtRadioButton->isChecked())
        filter = "Text files (*.txt)";
    else if (ui->csvRadioButton->isChecked())
        filter = "CSV files (*.csv)";
    else
    {
        QMessageBox::warning(this, "Ошибка", "Выберите формат файла (TXT или CSV)");
        return;
    }

    const QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл модели", QString(), filter);
    if (!filePath.isEmpty())
        _selectedFilePath = filePath;
}

void MainWindow::on_cameraAddPushbutton_clicked()
{
    try
    {
        _appService.AddCamera(ui->cameraXSpin->value(), ui->cameraYSpin->value(), ui->cameraZSpin->value());
        refreshCameraList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_cameraSetPushbutton_clicked()
{
    auto *item = ui->cameraListWidget->currentItem();
    if (!item)
        return;

    try
    {
        _appService.SetCamera(item->data(Qt::UserRole).toInt());
        refreshCameraList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_cameraDeletePushbutton_clicked()
{
    auto *item = ui->cameraListWidget->currentItem();
    if (!item)
        return;

    try
    {
        _appService.RemoveCamera(item->data(Qt::UserRole).toInt());
        refreshCameraList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_objectMovePushbutton_clicked()
{
    try
    {
        _appService.MoveSelectedModels(selectedObjectIndices(), ui->obkectMoveXSpin->value(), ui->objectMoveYSpin->value(), ui->objectMoveZSpin->value());
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_objectRotatePushbutton_clicked()
{
    try
    {
        _appService.RotateSelectedModels(selectedObjectIndices(), ui->objectRotateXSpin->value(), ui->objectRotateYSpin->value(), ui->objectRotateZSpin->value());
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_objectScalePushbutton_clicked()
{
    try
    {
        _appService.ScaleSelectedModels(selectedObjectIndices(), ui->objectScaleXSpin->value(), ui->objectScaleYSpin->value(), ui->objectScaleZSpin->value());
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_objectDeletePushbutton_clicked()
{
    try
    {
        _appService.RemoveSelectedModels(selectedObjectIndices());
        refreshObjectList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_objectCompositePushbutton_clicked()
{
    const auto indices = selectedObjectIndices();
    if (indices.size() < 2)
    {
        QMessageBox::warning(this, "Ошибка", "Для композита нужно выбрать минимум 2 объекта");
        return;
    }

    bool ok = false;
    const QString name = QInputDialog::getText(this, "Имя композита", "Введите имя композита", QLineEdit::Normal, "Composite", &ok);
    if (!ok || name.trimmed().isEmpty())
        return;

    try
    {
        _appService.CompositeSelectedModels(indices, name.trimmed());
        refreshObjectList();
        redrawScene();
    }
    catch (const std::exception &error)
    {
        QMessageBox::critical(this, "Ошибка", error.what());
    }
}

void MainWindow::on_toggleFaceCullingPushbutton_clicked()
{
}
