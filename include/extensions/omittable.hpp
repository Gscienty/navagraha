#ifndef _NAVAGRAHA_EXTENSION_OMITTABLE_H
#define _NAVAGRAHA_EXTENSION_OMITTABLE_H

namespace navagraha {
namespace extensions {

template <typename T>
class omittable {
private:
    T _obj;
    bool _omit;

public:
    omittable() : _omit(false) { }
    omittable(T && obj) : _obj(obj), _omit(true) { }

    operator T & ()
    {
        this->_omit = true;
        return this->_obj;
    }

    T & operator= (T & obj)
    {
        this->_omit = true;
        this->_obj = obj;
    }

    bool omit() const
    {
        return this->_omit;
    }

    T & get()
    {
        this->_omit = true;
        return this->_obj;
    }
};

}
}

#endif
