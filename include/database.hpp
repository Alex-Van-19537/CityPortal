#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::remove_if;
using std::string;
using std::vector;

template<typename T>
class Database
{
public:
    Database() = default;
    Database(const string &);
    bool load(const string &);
    vector<T>& getData() { return data; }
    const vector<T>& getData() const { return data; }
    bool save() const;
    bool empty() const;
    void list() const;
    template<typename Predicate>
    const T* find(Predicate) const;
    template<typename Predicate>
    T* find(Predicate);
    bool add(const T &);
    bool remove(int);
    int getNextId() const;
    void reload();

private:
    int nextId = 1;
    vector<T> data;
    string currentFile;
};

template <typename T>
Database<T>::Database(const string &filename) { load(filename); }

template <typename T>
bool Database<T>::load(const string &fname)
{
    data.clear();
    ofstream tmpFile(fname, std::ios::app);
    if (!tmpFile)
        return false;
    tmpFile.close();

    ifstream file(fname);
    if (!file)
        return false;
    T temp;
    string nextIdStr;
    if (getline(file >> std::ws, nextIdStr))
        nextId = stoi(nextIdStr);
    else
        nextId = 1;
    while (temp.loadFromCSV(file))
        data.push_back(temp);
    file.close();
    currentFile = fname;
    return true;
}

template<typename T>
void Database<T>::reload() {
    T temp;
    string nextIdStr;
    data.clear();
    ifstream file(currentFile);
    file.clear();
    file.seekg(0, std::ios::beg);
    if (getline(file >> std::ws, nextIdStr))
        nextId = stoi(nextIdStr);
    else
        nextId = 1;
    while (temp.loadFromCSV(file))
        data.push_back(temp);
    file.close();
}

template <typename T>
bool Database<T>::save() const
{
    ofstream file(currentFile);
    if (!file)
        return false;
    file << nextId << '\n';
    for (const auto &d : data)
        d.writeToCSV(file);
    return true;
}

template <typename T>
bool Database<T>::empty() const
{
    return data.empty();
}

template <typename T>
void Database<T>::list() const
{
    if (data.empty())
        return;
    for (auto &d : data)
    {
        cout << d;
    }
}

template<typename T>
template<typename Predicate>
const T* Database<T>::find(Predicate pred) const{
    for(const auto& item:data){
        if(pred(item)) return &item;
    }
    return nullptr;
}

template<typename T>
template<typename Predicate>
T* Database<T>::find(Predicate pred) {
    for(auto& item:data){
        if(pred(item)) return &item;
    }
    return nullptr;
}

template <typename T>
bool Database<T>::add(const T &d)
{
    data.push_back(d);
    nextId++;
    if (!save())
        return false;
    return true;
}

template <typename T>
bool Database<T>::remove(int id)
{
    auto prevSize = data.size();
    data.erase(remove_if(data.begin(), data.end(), [id](const T &d)
                              { return id == d.getId(); }),
               data.end());

    if (prevSize <= data.size())
        return false;
    if (!save())
        return false;
    return true;
}

template <typename T>
int Database<T>::getNextId() const
{
    return nextId;
}

#endif