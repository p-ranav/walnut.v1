#include <object_type.h>

/* List of object type strings - Used for debug printing */
const char *const object_strings[] = {
#define OBJECT(label, string) string,
    OBJECT_LIST
#undef OBJECT
    "invalid" 
};