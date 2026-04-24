#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>

#include "ApplicationService/SceneApplicationService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SceneApplicationService &appService, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadPushButton_clicked();
    void on_fileSelectButton_clicked();
    void on_cameraAddPushbutton_clicked();
    void on_cameraSetPushbutton_clicked();
    void on_cameraDeletePushbutton_clicked();
    void on_objectMovePushbutton_clicked();
    void on_objectRotatePushbutton_clicked();
    void on_objectScalePushbutton_clicked();
    void on_objectDeletePushbutton_clicked();
    void on_objectCompositePushbutton_clicked();
    void on_toggleFaceCullingPushbutton_clicked();

private:
    void redrawScene();
    void refreshObjectList();
    void refreshCameraList();
    std::vector<int> selectedObjectIndices() const;

    Ui::MainWindow *ui;
    SceneApplicationService &_appService;
    QString _selectedFilePath;
};

#endif
