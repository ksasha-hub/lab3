#ifndef SERIALIZATIONUTILS_H
#define SERIALIZATIONUTILS_H

#include <fstream>
#include <string>

class SerializationUtils {
public:
    // Сохранение в текстовый файл
    template<typename T>
    static bool saveToTextFile(const T& obj, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        obj.serializeText(file);
        file.close();
        return true;
    }
    
    // Загрузка из текстового файла
    template<typename T>
    static bool loadFromTextFile(T& obj, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        obj.deserializeText(file);
        file.close();
        return true;
    }
    
    // Сохранение в бинарный файл
    template<typename T>
    static bool saveToBinaryFile(const T& obj, const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        obj.serialize(file);
        file.close();
        return true;
    }
    
    // Загрузка из бинарного файла
    template<typename T>
    static bool loadFromBinaryFile(T& obj, const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }
        obj.deserialize(file);
        file.close();
        return true;
    }
};

#endif