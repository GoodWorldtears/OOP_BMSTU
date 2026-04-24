#include "load/TxtModelReader.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include <QRegularExpression>

namespace
{
QString readNextMeaningfulLine(QTextStream &input)
{
    while (!input.atEnd())
    {
        const QString line = input.readLine().trimmed();
        if (!line.isEmpty() && !line.startsWith('#'))
            return line;
    }

    return {};
}

QStringList splitLine(const QString &line)
{
    return line.split(QRegularExpression(R"(\s+)"), Qt::SkipEmptyParts);
}

std::size_t parsePositiveIndex(const QString &value)
{
    bool ok = false;
    const uint parsed = value.toUInt(&ok);
    if (!ok || parsed == 0)
        throw std::runtime_error("Номер точки в ребре должен быть положительным");

    return static_cast<std::size_t>(parsed - 1);
}
}

ModelData TxtModelReader::read(const std::string &path) const
{
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Не удалось открыть txt-файл");

    ModelData data;
    data.name = baseNameFromPath(path);

    QTextStream input(&file);

    const QString pointsCountLine = readNextMeaningfulLine(input);
    if (pointsCountLine.isEmpty())
        throw std::runtime_error("В txt-файле отсутствует количество точек");

    bool ok = false;
    const int pointsCount = pointsCountLine.toInt(&ok);
    if (!ok || pointsCount <= 0)
        throw std::runtime_error("Некорректное количество точек в txt-файле");

    for (int i = 0; i < pointsCount; ++i)
    {
        const QString line = readNextMeaningfulLine(input);
        if (line.isEmpty())
            throw std::runtime_error("Недостаточно строк с координатами точек в txt-файле");

        const QStringList parts = splitLine(line);
        if (parts.size() != 3)
            throw std::runtime_error("Каждая точка в txt-файле должна задаваться тремя координатами");

        data.points.emplace_back(parts.at(0).toDouble(), parts.at(1).toDouble(), parts.at(2).toDouble());
    }

    const QString edgesCountLine = readNextMeaningfulLine(input);
    if (edgesCountLine.isEmpty())
        throw std::runtime_error("В txt-файле отсутствует количество ребер");

    const int edgesCount = edgesCountLine.toInt(&ok);
    if (!ok || edgesCount <= 0)
        throw std::runtime_error("Некорректное количество ребер в txt-файле");

    for (int i = 0; i < edgesCount; ++i)
    {
        const QString line = readNextMeaningfulLine(input);
        if (line.isEmpty())
            throw std::runtime_error("Недостаточно строк с ребрами в txt-файле");

        const QStringList parts = splitLine(line);
        if (parts.size() != 2)
            throw std::runtime_error("Каждое ребро в txt-файле должно задаваться двумя номерами точек");

        const std::size_t firstIndex = parsePositiveIndex(parts.at(0));
        const std::size_t secondIndex = parsePositiveIndex(parts.at(1));
        if (firstIndex >= data.points.size() || secondIndex >= data.points.size())
            throw std::runtime_error("Ребро в txt-файле ссылается на несуществующую точку");

        data.edges.emplace_back(firstIndex, secondIndex);
    }

    return data;
}
