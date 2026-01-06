#include <stdio.h>


/*Usually Program Starts from main function*/
/*main can be defined in multiple ways like : void main() or vaid main (void) or int main (vaid) ...lets see and understand how each one works differently*/
#include <stdio.h>

int main() {
    int count = printf("Hello"); 
    // Prints "Hello" to the screen
    // count will be 5 because "Hello" has 5 characters

    printf("\nCharacters printed: %d", count);
    return 0;
}