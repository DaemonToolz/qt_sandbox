#include "filereader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <QJsonDocument>
#include <QJsonObject>

FileReader::FileReader(QObject *parent): QObject{parent}
{
    source = "D:/temp/source.json";
    m_data = read();
}


QJsonObject FileReader::data(){
    return m_data;
}

QJsonObject FileReader::read(){
    try {
      std::string buffer;
      std::ifstream file(source.toStdString(), std::ifstream::binary);

      file.seekg(0, std::ios::end);
      buffer.resize(file.tellg());
      file.seekg(0);
      file.read(buffer.data(), buffer.size());

      return QJsonDocument::fromJson(QString::fromStdString(buffer).toUtf8()).object();
    } catch (std::exception& ex) {
        return QJsonObject();
    }
}
