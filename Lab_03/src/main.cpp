#include "ApplicationService/SceneApplicationService.h"
#include "Dependencies/FacadeDependencies.h"
#include "facade/SceneFacade.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FacadeDependencies facadeDep{};
    SceneFacade facade{facadeDep.getSceneManager(),
                       facadeDep.getLoadService(),
                       facadeDep.getTransformService(),
                       facadeDep.getRenderService()};
    SceneApplicationService appService(facade);

    MainWindow w(appService);
    w.show();
    return a.exec();
}
