#pragma once
#include <unordered_set>
#include <unordered_map>

namespace glaiel {
    class _safe_pointer_base {
        friend class safe_pointer_context;
        protected:
        void* ptr;
    };

    template <typename T, typename base = T>
    class safe_pointer : public _safe_pointer_base {
        friend struct std::hash<glaiel::safe_pointer<T, base>>;

        T* _obj() { 
            return (T*)ptr; 
        }

        base* _base() { 
            return (base*)ptr; 
        }
        
        public:
        safe_pointer(T* obj = NULL){
            ptr = obj;
            if(ptr) _base()->_safe_pointer_context.add(this);
        }
        safe_pointer(const safe_pointer<T, base>& rhs) : safe_pointer((T*)rhs.ptr) {
        }
        safe_pointer<T, base>& operator=(T* obj) {
            if(obj != ptr){
                if(ptr) _base()->_safe_pointer_context.remove(this);

                ptr = obj;
                if(ptr) _base()->_safe_pointer_context.add(this);
            }
            return *this;
        }
        safe_pointer<T, base>& operator=(const safe_pointer<T, base>& rhs) {
            *this = (T*)rhs.ptr;
            return *this;
        }
        
        ~safe_pointer(){
            if(ptr){
                _base()->_safe_pointer_context.remove(this);
            }
        }

        operator bool() const {
            return ptr;
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

        template <typename U, typename UB>
        bool operator==(const safe_pointer<U, UB> rhs) const {
            return ptr==rhs.ptr;
        }

        template <typename U>
        bool operator==(const U* rhs) const {
            return ptr==rhs;
        }

        template <typename U>
        bool operator==(U* rhs) const {
            return ptr==rhs;
        }
    };


    class safe_pointer_context {
    public:
        typedef std::unordered_set<_safe_pointer_base*> pointerset;
        static std::unordered_map<safe_pointer_context*, pointerset> pointer_db;

        safe_pointer_context(){}
        safe_pointer_context(const safe_pointer_context& rhs){} //do not copy rhs's pointer set
        safe_pointer_context& operator=(const safe_pointer_context& rhs){} //do not copy rhs's pointer set
        pointerset& pointers();

        void add(_safe_pointer_base* ptr);
        void remove(_safe_pointer_base* ptr);
        ~safe_pointer_context();
    };
    
    #define SAFE_POINTABLE safe_pointer_context _safe_pointer_context
}


namespace std { //for addition to a unordered maps & sets
    template <typename T, typename base>
    struct hash<glaiel::safe_pointer<T, base>> {
        std::size_t operator()(const glaiel::safe_pointer<T, base>& k) const{
            return std::hash<void*>()(k.ptr);
        }
    };
}
