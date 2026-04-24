/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QGroupBox *loadGroupBox;
    QPushButton *fileSelectButton;
    QLabel *label;
    QPushButton *loadPushButton;
    QGroupBox *fileGroupBox;
    QRadioButton *txtRadioButton;
    QRadioButton *csvRadioButton;
    QGroupBox *cameraGroupBox;
    QDoubleSpinBox *cameraXSpin;
    QDoubleSpinBox *cameraZSpin;
    QDoubleSpinBox *cameraYSpin;
    QPushButton *cameraAddPushbutton;
    QListWidget *cameraListWidget;
    QPushButton *cameraSetPushbutton;
    QPushButton *cameraDeletePushbutton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *objectGroupBox;
    QListWidget *objectListWidget;
    QDoubleSpinBox *obkectMoveXSpin;
    QDoubleSpinBox *objectScaleXSpin;
    QDoubleSpinBox *objectRotateXSpin;
    QDoubleSpinBox *objectMoveYSpin;
    QDoubleSpinBox *objectRotateYSpin;
    QDoubleSpinBox *objectScaleYSpin;
    QDoubleSpinBox *objectMoveZSpin;
    QDoubleSpinBox *objectRotateZSpin;
    QDoubleSpinBox *objectScaleZSpin;
    QPushButton *objectDeletePushbutton;
    QPushButton *objectCompositePushbutton;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *objectMovePushbutton;
    QPushButton *objectRotatePushbutton;
    QPushButton *objectScalePushbutton;
    QPushButton *toggleFaceCullingPushbutton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1527, 835);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, 0, 931, 821));
        loadGroupBox = new QGroupBox(centralwidget);
        loadGroupBox->setObjectName("loadGroupBox");
        loadGroupBox->setGeometry(QRect(940, 10, 571, 201));
        fileSelectButton = new QPushButton(loadGroupBox);
        fileSelectButton->setObjectName("fileSelectButton");
        fileSelectButton->setGeometry(QRect(10, 50, 551, 27));
        label = new QLabel(loadGroupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 321, 19));
        loadPushButton = new QPushButton(loadGroupBox);
        loadPushButton->setObjectName("loadPushButton");
        loadPushButton->setGeometry(QRect(190, 170, 131, 27));
        fileGroupBox = new QGroupBox(loadGroupBox);
        fileGroupBox->setObjectName("fileGroupBox");
        fileGroupBox->setGeometry(QRect(10, 90, 551, 71));
        txtRadioButton = new QRadioButton(fileGroupBox);
        txtRadioButton->setObjectName("txtRadioButton");
        txtRadioButton->setGeometry(QRect(100, 30, 81, 25));
        txtRadioButton->setChecked(true);
        csvRadioButton = new QRadioButton(fileGroupBox);
        csvRadioButton->setObjectName("csvRadioButton");
        csvRadioButton->setGeometry(QRect(360, 30, 101, 25));
        csvRadioButton->setChecked(false);
        cameraGroupBox = new QGroupBox(centralwidget);
        cameraGroupBox->setObjectName("cameraGroupBox");
        cameraGroupBox->setGeometry(QRect(940, 210, 571, 201));
        cameraXSpin = new QDoubleSpinBox(cameraGroupBox);
        cameraXSpin->setObjectName("cameraXSpin");
        cameraXSpin->setGeometry(QRect(10, 50, 151, 28));
        cameraXSpin->setMinimum(-5000.000000000000000);
        cameraXSpin->setMaximum(5000.000000000000000);
        cameraZSpin = new QDoubleSpinBox(cameraGroupBox);
        cameraZSpin->setObjectName("cameraZSpin");
        cameraZSpin->setGeometry(QRect(340, 50, 151, 28));
        cameraZSpin->setMinimum(-5000.000000000000000);
        cameraZSpin->setMaximum(5000.000000000000000);
        cameraYSpin = new QDoubleSpinBox(cameraGroupBox);
        cameraYSpin->setObjectName("cameraYSpin");
        cameraYSpin->setGeometry(QRect(170, 50, 161, 28));
        cameraYSpin->setMinimum(-5000.000000000000000);
        cameraYSpin->setMaximum(5000.000000000000000);
        cameraAddPushbutton = new QPushButton(cameraGroupBox);
        cameraAddPushbutton->setObjectName("cameraAddPushbutton");
        cameraAddPushbutton->setGeometry(QRect(300, 90, 91, 27));
        cameraListWidget = new QListWidget(cameraGroupBox);
        cameraListWidget->setObjectName("cameraListWidget");
        cameraListWidget->setGeometry(QRect(10, 90, 281, 101));
        cameraSetPushbutton = new QPushButton(cameraGroupBox);
        cameraSetPushbutton->setObjectName("cameraSetPushbutton");
        cameraSetPushbutton->setGeometry(QRect(400, 90, 91, 27));
        cameraDeletePushbutton = new QPushButton(cameraGroupBox);
        cameraDeletePushbutton->setObjectName("cameraDeletePushbutton");
        cameraDeletePushbutton->setGeometry(QRect(300, 120, 91, 27));
        label_2 = new QLabel(cameraGroupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 30, 151, 20));
        label_3 = new QLabel(cameraGroupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(175, 30, 151, 20));
        label_4 = new QLabel(cameraGroupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(345, 30, 141, 20));
        objectGroupBox = new QGroupBox(centralwidget);
        objectGroupBox->setObjectName("objectGroupBox");
        objectGroupBox->setGeometry(QRect(940, 410, 571, 411));
        objectListWidget = new QListWidget(objectGroupBox);
        objectListWidget->setObjectName("objectListWidget");
        objectListWidget->setGeometry(QRect(10, 40, 281, 181));
        objectListWidget->setSelectionMode(QAbstractItemView::NoSelection);
        obkectMoveXSpin = new QDoubleSpinBox(objectGroupBox);
        obkectMoveXSpin->setObjectName("obkectMoveXSpin");
        obkectMoveXSpin->setGeometry(QRect(10, 250, 101, 28));
        obkectMoveXSpin->setMinimum(-500.000000000000000);
        obkectMoveXSpin->setMaximum(500.000000000000000);
        objectScaleXSpin = new QDoubleSpinBox(objectGroupBox);
        objectScaleXSpin->setObjectName("objectScaleXSpin");
        objectScaleXSpin->setGeometry(QRect(10, 370, 101, 28));
        objectScaleXSpin->setMinimum(-100.000000000000000);
        objectScaleXSpin->setMaximum(100.000000000000000);
        objectScaleXSpin->setValue(1.000000000000000);
        objectRotateXSpin = new QDoubleSpinBox(objectGroupBox);
        objectRotateXSpin->setObjectName("objectRotateXSpin");
        objectRotateXSpin->setGeometry(QRect(10, 310, 101, 28));
        objectRotateXSpin->setMinimum(-360.000000000000000);
        objectRotateXSpin->setMaximum(360.000000000000000);
        objectMoveYSpin = new QDoubleSpinBox(objectGroupBox);
        objectMoveYSpin->setObjectName("objectMoveYSpin");
        objectMoveYSpin->setGeometry(QRect(120, 250, 101, 28));
        objectMoveYSpin->setMinimum(-490.000000000000000);
        objectMoveYSpin->setMaximum(500.000000000000000);
        objectRotateYSpin = new QDoubleSpinBox(objectGroupBox);
        objectRotateYSpin->setObjectName("objectRotateYSpin");
        objectRotateYSpin->setGeometry(QRect(120, 310, 101, 28));
        objectRotateYSpin->setMinimum(-360.000000000000000);
        objectRotateYSpin->setMaximum(360.000000000000000);
        objectScaleYSpin = new QDoubleSpinBox(objectGroupBox);
        objectScaleYSpin->setObjectName("objectScaleYSpin");
        objectScaleYSpin->setGeometry(QRect(120, 370, 101, 28));
        objectScaleYSpin->setMinimum(-100.000000000000000);
        objectScaleYSpin->setMaximum(100.000000000000000);
        objectScaleYSpin->setValue(1.000000000000000);
        objectMoveZSpin = new QDoubleSpinBox(objectGroupBox);
        objectMoveZSpin->setObjectName("objectMoveZSpin");
        objectMoveZSpin->setGeometry(QRect(230, 250, 101, 28));
        objectMoveZSpin->setMinimum(-490.000000000000000);
        objectMoveZSpin->setMaximum(500.000000000000000);
        objectRotateZSpin = new QDoubleSpinBox(objectGroupBox);
        objectRotateZSpin->setObjectName("objectRotateZSpin");
        objectRotateZSpin->setGeometry(QRect(230, 310, 101, 28));
        objectRotateZSpin->setMinimum(-360.000000000000000);
        objectRotateZSpin->setMaximum(360.000000000000000);
        objectScaleZSpin = new QDoubleSpinBox(objectGroupBox);
        objectScaleZSpin->setObjectName("objectScaleZSpin");
        objectScaleZSpin->setGeometry(QRect(230, 370, 101, 28));
        objectScaleZSpin->setMinimum(-100.000000000000000);
        objectScaleZSpin->setMaximum(100.000000000000000);
        objectScaleZSpin->setValue(1.000000000000000);
        objectDeletePushbutton = new QPushButton(objectGroupBox);
        objectDeletePushbutton->setObjectName("objectDeletePushbutton");
        objectDeletePushbutton->setGeometry(QRect(360, 80, 191, 27));
        objectCompositePushbutton = new QPushButton(objectGroupBox);
        objectCompositePushbutton->setObjectName("objectCompositePushbutton");
        objectCompositePushbutton->setGeometry(QRect(360, 40, 191, 27));
        label_5 = new QLabel(objectGroupBox);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 230, 101, 19));
        label_6 = new QLabel(objectGroupBox);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 290, 101, 19));
        label_7 = new QLabel(objectGroupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 350, 101, 19));
        label_8 = new QLabel(objectGroupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(120, 230, 101, 19));
        label_9 = new QLabel(objectGroupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(120, 350, 101, 19));
        label_10 = new QLabel(objectGroupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(120, 290, 101, 19));
        label_11 = new QLabel(objectGroupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(230, 290, 101, 19));
        label_12 = new QLabel(objectGroupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(230, 230, 101, 19));
        label_13 = new QLabel(objectGroupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(230, 350, 101, 19));
        objectMovePushbutton = new QPushButton(objectGroupBox);
        objectMovePushbutton->setObjectName("objectMovePushbutton");
        objectMovePushbutton->setGeometry(QRect(340, 250, 151, 27));
        objectRotatePushbutton = new QPushButton(objectGroupBox);
        objectRotatePushbutton->setObjectName("objectRotatePushbutton");
        objectRotatePushbutton->setGeometry(QRect(340, 310, 151, 27));
        objectScalePushbutton = new QPushButton(objectGroupBox);
        objectScalePushbutton->setObjectName("objectScalePushbutton");
        objectScalePushbutton->setGeometry(QRect(340, 370, 151, 27));
        toggleFaceCullingPushbutton = new QPushButton(objectGroupBox);
        toggleFaceCullingPushbutton->setObjectName("toggleFaceCullingPushbutton");
        toggleFaceCullingPushbutton->setGeometry(QRect(360, 120, 191, 27));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        loadGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260", nullptr));
        fileSelectButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273...", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        loadPushButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        fileGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264 \320\244\320\260\320\271\320\273\320\260", nullptr));
        txtRadioButton->setText(QCoreApplication::translate("MainWindow", "Txt", nullptr));
        csvRadioButton->setText(QCoreApplication::translate("MainWindow", "csv", nullptr));
        cameraGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\321\213", nullptr));
        cameraAddPushbutton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        cameraSetPushbutton->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        cameraDeletePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        objectGroupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213", nullptr));
        objectDeletePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\265", nullptr));
        objectCompositePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\212\320\265\320\264\320\270\320\275\320\270\321\202\321\214 \320\262 \320\272\320\276\320\274\320\277\320\276\320\267\320\270\321\202", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "dx", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "ax", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "kx", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "dy", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "ky", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "ay", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "az", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "dz", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "kz", nullptr));
        objectMovePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214", nullptr));
        objectRotatePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        objectScalePushbutton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        toggleFaceCullingPushbutton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \321\201\320\276\320\272\321\200\321\213\321\202\320\270\320\265 \320\263\321\200\320\260\320\275\320\265\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
