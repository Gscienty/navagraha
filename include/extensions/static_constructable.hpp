#ifndef _NAVAGRAHA_EXTENSIONS_STATIC_CONSTRUCTABLE_H
#define _NAVAGRAHA_EXTENSIONS_STATIC_CONSTRUCTABLE_H

namespace navagraha {
namespace extensions {

template <class T>
class static_constructable {
private:
    struct constructor {
        constructor()
        {
            T::static_construct();
        }
    };

protected:
    static_constructable()
    {
        static constructor ctor;
    }
};

}
}

#endif
