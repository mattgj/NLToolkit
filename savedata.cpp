#include "savedata.h"

SaveData *SaveData::m_saveData = NULL;

SaveData * SaveData::getInstance()
{

    if(!m_saveData) {
        m_saveData = new SaveData();
    }

    return SaveData::m_saveData;
}

SaveData::SaveData()
{

}

SaveData::~SaveData()
{

}

bool SaveData::open(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    m_path = path;

    if(file.isReadable()) {

        m_dataByteArray = file.readAll();
        m_data = (uchar*) m_dataByteArray.data();
        m_error = 0;
        file.close();

        return true;

    } else {
        m_error = 1;
    }

    return false;
}

int SaveData::getError()
{
    return m_error;
}

QString SaveData::readString(uint offset, int len)
{
    return QString::fromUtf16((const ushort*)&m_data[offset], len);
}

void SaveData::writeString(uint offset, QString str)
{
    const ushort * strPtr = str.utf16();
    ushort * dataPtr = (ushort *)&m_data[offset];

    for(int i = 0; i < str.length(); i++) {
        dataPtr[i] = strPtr[i];
    }
}


quint8 SaveData::readInt8(uint offset) {
    return m_data[offset];
}

void SaveData::writeInt8(uint offset, quint8 value) {
    m_data[offset] = value;
}

quint16 SaveData::readInt16(uint offset) {
    return *((quint16 *)&m_data[offset]);
}

void SaveData::writeInt16(uint offset, quint16 value) {
    *((quint16 *)&m_data[offset]) = value;
}


quint32 SaveData::readInt32(uint offset) {
    return *((quint32 *)&m_data[offset]);
}

void SaveData::writeInt32(uint offset, quint32 value) {
    *((quint32 *)&m_data[offset]) = value;
}

bool SaveData::save() {

    QFile file(m_path);
    file.open(QIODevice::ReadWrite);

    if(file.isWritable()) {

        file.write((const char*)m_data, m_dataByteArray.size());
        file.close();

        return true;
    }

    return false;
}
