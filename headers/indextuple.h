#ifndef SEM_ESTRUCTURAS_II_INDEXTUPLE_H
#define SEM_ESTRUCTURAS_II_INDEXTUPLE_H
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

template <class T = string >
class IndexTuple{
private:
    long long index;
    T data;
public:
    IndexTuple():index(0),data(T()){};
    IndexTuple(const IndexTuple& it){
        this->data = it.data;
        this->index = it.index;
    }
    IndexTuple(const long long& num,const T& data){
        this->data = data;
        this->index = num;
    }

    [[nodiscard]] int getIndex() const{
        return this->index;
    }
    T getData() const{
        return this->data;
    }
    void setIndex(const int& i){
        this->index = i;
    }
    void setData(const T& t){
        this->data = t;
    }

    friend ostream &operator << (ostream &ofs,IndexTuple &it){
        ofs << it.index << '*' << it.data;
        return ofs;
    }
    friend istream &operator >> (istream &ifs, IndexTuple &it){
        ifs >> it.index;
        ifs.ignore(1,'*');
        getline(ifs,it.data,'\n');
        return ifs;
    }
    IndexTuple& operator = (const IndexTuple&) = default;

    bool operator == (const IndexTuple& it) const{
        return this->data == it.data;
    }
    bool operator <= (const IndexTuple& it) const{
        return this->data <= it.data;
    }
    bool operator >= (const IndexTuple& it) const{
        return this->data >= it.data;
    }
    bool operator < (const IndexTuple& it) const{
        return this->data < it.data;
    }
    bool operator > (const IndexTuple& it) const{
        return this->data > it.data;
    }
    bool operator != (const IndexTuple& it) const{
        return this->data != it.data;
    }


};
#endif //SEM_ESTRUCTURAS_II_INDEXTUPLE_H
