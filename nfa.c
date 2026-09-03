#include <stdio.h>

int main() {
    char input[100];
    int state = 0;
    int i;

    printf("Enter a string (over s, b, *, /): ");
    scanf("%99s", input);

    for (i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        switch (state) {
            case 0: state = (c == '/') ? 1 : 5; break;                 // q0
            case 1: state = (c == '*') ? 2 : 5; break;                 // q1
            case 2: state = (c == '*') ? 3 : 2; break;                 // q2 (s, b, / stay here)
            case 3:
                if (c == '*') state = 3;
                else if (c == '/') state = 4;
                else state = 2;
                break;
            case 4: state = 5; break;                                  // q4 (final, no symbols after)
            default: state = 5; break;                                 // qtrap
        }
    }

    if (state == 4)
        printf("ACCEPTED\n");
    else
        printf("REJECTED\n");

    return 0;
}
