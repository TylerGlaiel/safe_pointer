#include "safe_pointer.h"

namespace glaiel {
    std::unordered_map<safe_pointer_context*, safe_pointer_context::pointerset> safe_pointer_context::pointer_db;

    safe_pointer_context::pointerset& safe_pointer_context::pointers(){
        return pointer_db[this];
    }


    void safe_pointer_context::add(_safe_pointer_base* ptr){
        pointers().insert(ptr);
    }
    void safe_pointer_context::remove(_safe_pointer_base* ptr){
        pointers().erase(ptr);
    }

    safe_pointer_context::~safe_pointer_context(){
        for(auto& ptr : pointers()){
            ptr->ptr = NULL;
        }

        pointer_db.erase(this);
    }
}