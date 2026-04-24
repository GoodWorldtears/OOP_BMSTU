#include "load/BoneModelReader.h"
#include <QFileInfo>

QString BoneModelReader::baseNameFromPath(const std::string &path)
{
    return QFileInfo(QString::fromStdString(path)).baseName();
}
