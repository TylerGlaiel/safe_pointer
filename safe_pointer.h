#pragma once

namespace glaiel {
    class _safe_pointer_base {
        friend class safe_pointer_context;
        protected:
        void* ptr;
    };

    template <typename T>
    class safe_pointer : public _safe_pointer_base {
        T* _obj() { 
            return (T*)ptr; 
        }
        
        public:
        safe_pointer(T* obj = NULL){
            ptr = obj;
            if(ptr) _obj()->_safe_pointer_context.add(this);
        }
        safe_pointer(const safe_pointer<T>& rhs) : safe_pointer((T*)rhs.ptr) {
        }
        safe_pointer<T>& operator=(T* obj) {
            if(obj != ptr){
                if(ptr) _obj()->_safe_pointer_context.remove(this);

                ptr = obj;
                if(ptr) _obj()->_safe_pointer_context.add(this);
            }
            return *this;
        }
        safe_pointer<T>& operator=(const safe_pointer<T>& rhs) {
            *this = (T*)rhs.ptr;
            return *this;
        }
        
        ~safe_pointer(){
            if(ptr){
                _obj()->_safe_pointer_context.remove(this);
            }
        }
        
        operator T*(){
            return _obj();
        }

        T& operator*(){
            return *_obj();
        }

        T* operator->(){
            return _obj();
        }
    };


    class safe_pointer_context {
        public:
        std::unordered_set<_safe_pointer_base*> pointers;
        
        safe_pointer_context(){}
        safe_pointer_context(const safe_pointer_context& rhs){} //do not copy rhs's pointer set
        safe_pointer_context& operator=(const safe_pointer_context&rhs){} //do not copy rhs's pointer set
        
        
        void add(_safe_pointer_base* ptr){
            pointers.insert(ptr);
        }
        void remove(_safe_pointer_base* ptr){
            pointers.erase(ptr);
        }
        
        ~safe_pointer_context(){
            for(auto ptr : pointers){
                ptr->ptr = NULL;
            }
        }
    };
    
    #define SAFE_POINTABLE safe_pointer_context _safe_pointer_context
}
