#include "string.h"

int main() {
    string s;
    string s2;
    str_init(&s);
    str_init(&s2);

    str_xmove(&s, "This is a sample sentence with a placeholder.");
    str_xmove(&s2, "Thisa is a sample sentence with a placeholder.");

    printf("%i\n", str_same(&s, &s2));
}
