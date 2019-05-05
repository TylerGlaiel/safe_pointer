# safe_pointer
A pointer that automatically becomes NULL if the object it's pointing to is deleted

The class you're pointing to needs to contain a safe_pointer_context named "_safe_pointer_context". A macro, "SAFE_POINTABLE" is provided to make adding this to your class easy.

The context contains a list of all living safe_pointers to the object itself. When the object is deleted, the context goes through and alerts all of those pointers that the object has been deleted (by setting them to NULL)

