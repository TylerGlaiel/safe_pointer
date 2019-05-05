# safe_pointer
A pointer that automatically becomes NULL if the object it's pointing to is deleted

The class or struct you're pointing to needs to contain a safe_pointer_context named "_safe_pointer_context". A macro, "SAFE_POINTABLE" is provided to make adding this to your class or struct easy.

The context contains a list of all living safe_pointers to the object itself. When the object is deleted, the context goes through and alerts all of those pointers that the object has been deleted (by setting them to NULL)

Unlike std::shared_ptr, safe_pointer does not control the lifetime of the object it is pointing at, it is simply aware of it. Unlike std::weak_ptr, you are free to manage the lifetime of the underlying object however you want. 
