#pragma once

#include <string>
#include <algorithm>

class Path {

public:
Path(const std::string& path) : path_(path) {
        normalize();
    }

    // 标准化路径（转换斜杠和反斜杠）
    void normalize() {
        #ifdef _WIN32
            std::replace(m_path.begin(), m_path.end(), '/', '\\');
        #else
            std::replace(path_.begin(), path_.end(), '\\', '/');
        #endif
    }

    // 合并两个路径
    static Path combine(const Path& path1, const Path& path2) {
        std::string combined = path1.path_;
        #ifdef _WIN32
            combined += "\\" + path2.m_path;
        #else
            combined += "/" + path2.path_;
        #endif
        return Path(combined);
    }

    // 获取路径的字符串表示
    std::string toString() const {
        return path_;
    }

    const char* c_str() const {
        return path_.c_str();
    }

    // 其他路径相关操作...


    private:
    std::string path_;
};