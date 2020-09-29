#include <stdio.h>

int main() {
    char **s;
    char *foo = "Hello World";  // for the consistency, changed char[] to char*
    s = &foo;  // s is a pointer to pointer, thus, to initialize it we have to take an address of
               // the pointer we want to assign there. Dereferncing fails and causes SEGFAULT as
               // initially s is unitialized
    printf("s is %s\n", *s);  // here we have to derefence s to obtain the string pointed by s
    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    return (0);
}
