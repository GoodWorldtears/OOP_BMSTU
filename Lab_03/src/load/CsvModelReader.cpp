#include "load/CsvModelReader.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>

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
    return line.split(',', Qt::SkipEmptyParts);
}

std::size_t parsePositiveIndex(const QString &value)
{
    bool ok = false;
    const uint parsed = value.trimmed().toUInt(&ok);
    if (!ok || parsed == 0)
        throw std::runtime_error("Номер точки в ребре должен быть положительным");

    return static_cast<std::size_t>(parsed - 1);
}
}

ModelData CsvModelReader::read(const std::string &path) const
{
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Не удалось открыть csv-файл");

    ModelData data;
    data.name = baseNameFromPath(path);

    QTextStream input(&file);

    const QString pointsCountLine = readNextMeaningfulLine(input);
    if (pointsCountLine.isEmpty())
        throw std::runtime_error("В csv-файле отсутствует количество точек");

    bool ok = false;
    const int pointsCount = pointsCountLine.trimmed().toInt(&ok);
    if (!ok || pointsCount <= 0)
        throw std::runtime_error("Некорректное количество точек в csv-файле");

    for (int i = 0; i < pointsCount; ++i)
    {
        const QString line = readNextMeaningfulLine(input);
        if (line.isEmpty())
            throw std::runtime_error("Недостаточно строк с координатами точек в csv-файле");

        const QStringList parts = splitLine(line);
        if (parts.size() != 3)
            throw std::runtime_error("Каждая точка в csv-файле должна задаваться тремя координатами");

        data.points.emplace_back(parts.at(0).trimmed().toDouble(),
                                 parts.at(1).trimmed().toDouble(),
                                 parts.at(2).trimmed().toDouble());
    }

    const QString edgesCountLine = readNextMeaningfulLine(input);
    if (edgesCountLine.isEmpty())
        throw std::runtime_error("В csv-файле отсутствует количество ребер");

    const int edgesCount = edgesCountLine.trimmed().toInt(&ok);
    if (!ok || edgesCount <= 0)
        throw std::runtime_error("Некорректное количество ребер в csv-файле");

    for (int i = 0; i < edgesCount; ++i)
    {
        const QString line = readNextMeaningfulLine(input);
        if (line.isEmpty())
            throw std::runtime_error("Недостаточно строк с ребрами в csv-файле");

        const QStringList parts = splitLine(line);
        if (parts.size() != 2)
            throw std::runtime_error("Каждое ребро в csv-файле должно задаваться двумя номерами точек");

        const std::size_t firstIndex = parsePositiveIndex(parts.at(0));
        const std::size_t secondIndex = parsePositiveIndex(parts.at(1));
        if (firstIndex >= data.points.size() || secondIndex >= data.points.size())
            throw std::runtime_error("Ребро в csv-файле ссылается на несуществующую точку");

        data.edges.emplace_back(firstIndex, secondIndex);
    }

    return data;
}
