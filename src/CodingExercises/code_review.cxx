#include <cstdlib>
#include <string>
#include <map>

// Junior's code
class Store {
public:
    Store() {}

    Store(Store& other) {
        for (auto& pair : other.values) {
            values[pair.first] = new std::string(*pair.second);
        }
    }

    void Set(std::string key, std::string value) {
        values[key] = new std::string(value);
    }

    std::string* Load(std::string key) {
        return values[key];
    }

    void Remove(std::string key) {
        values[key] = nullptr;
    }

    bool Exist(std::string key) {
        if (values[key] == nullptr) {
            return true;
        }
        return false;
    }

    void Clear() {
        values.clear();
    }

private:
    std::map<std::string, std::string*> values;
};

// My output
class Store {
public:
    Store() {}

    ~Store() {
        for (auto& pair : values) {
            delete pair.second;
        }

        values.clear();
    }

    Store(Store& other) {
        for (auto& pair : other.values) {
            values[pair.first] = new std::string(*pair.second);
        }
    }

    void Set(std::string key, std::string value) {
        values.at(key) = new std::string(value);
    }

    std::string* Load(std::string key) {
        try {
            return values.at(key);
        } catch () {
            return nullptr;
        }
    }

    void Remove(std::string key) {
        values.at(key) = nullptr;
    }

    bool Exist(std::string key) {
        if (values.at(key) == nullptr) {
            return true;
        }
        return false;
    }

    void Clear() {
        values.clear();
    }

private:
    std::map<std::string, std::string*> values;
};

// Correct handling
class Store {
public:
    Store() {}

    ~Store() {
        for (auto& pair : values) {
            delete pair.second;
        }

        values.clear();
    }

    Store(Store& other) {
        for (auto& pair : other.values) {
            values[pair.first] = new std::string(*pair.second);
        }
    }

    void Set(std::string key, std::string value) {
        if (values.find(key) != values.end()) {
            delete values.at(key);
        }
        values[key] = new std::string(value);
    }

    std::string* Load(std::string key) {
        try {
            return values.at(key);
        } catch (std::out_of_range&) {
            return nullptr;
        }
    }

    void Remove(std::string key) {
        if (values.find(key) != values.end()) {
            delete values.at(key);
            values.at(key) = nullptr;
            values.erase(key);
        }
    }

    bool Exist(std::string key) {
        if (values.find(key) != values.end() && values.at(key) != nullptr) {
            return true;
        }
        return false;
    }

    void Clear() {
        for (auto& pair : values) {
            delete pair.second;
        }

        values.clear();
    }

private:
    std::map<std::string, std::string*> values;
};

int main() {
    return EXIT_SUCCESS;
} 