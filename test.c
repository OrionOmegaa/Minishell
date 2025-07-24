#include <stdio.h>

int main() {
    char buffer[1024];
    int count = 0;
    
    while (1) {
        printf("Test %d - avant lecture\n", ++count);
        fflush(stdout);
        
        if (!fgets(buffer, sizeof(buffer), stdin))
            break;
            
        printf("Reçu: %s", buffer);
    }
    return 0;
}
