#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for exit()

int main() {
    int i, j, k, l, m, next_state[20], n, mat[10][10][10], flag, p;
    int num_states, final_state[5], num_symbols, num_final;
    int present_state[20], prev_trans, new_trans;
    char input[20];
    int symbol[5];

    printf("How many states in the NFA : ");
    scanf("%d", &num_states);

    printf("How many symbols in the input alphabet : ");
    scanf("%d", &num_symbols);

    for (i = 0; i < num_symbols; i++) {
        printf("Enter the input symbol %d : ", i + 1);
        scanf("%d", &symbol[i]);
    }

    printf("How many final states : ");
    scanf("%d", &num_final);

    for (i = 0; i < num_final; i++) {
        printf("Enter the final state %d : ", i + 1);
        scanf("%d", &final_state[i]);
    }

    // Initialize all entries with -1 in Transition table
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            for (k = 0; k < 10; k++) {
                mat[i][j][k] = -1;
            }
        }
    }

    // Get input from the user and fill the 3D transition table
    for (i = 0; i < num_states; i++) {
        for (j = 0; j < num_symbols; j++) {
            printf("How many transitions from state %d for the input %d : ", i, symbol[j]);
            scanf("%d", &n);
            for (k = 0; k < n; k++) {
                printf("Enter the transition %d from state %d for the input %d : ", k + 1, i, symbol[j]);
                scanf("%d", &mat[i][j][k]);
            }
        }
    }

    printf("The transitions are stored as shown below\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            for (k = 0; k < 10; k++) {
                if (mat[i][j][k] != -1)
                    printf("mat[%d][%d][%d] = %d\n", i, j, k, mat[i][j][k]);
            }
        }
    }

    while (1) {
        printf("Enter the input string : ");
        scanf("%s", input);

        present_state[0] = 0;
        prev_trans = 1;
        l = strlen(input);

        for (i = 0; i < l; i++) {
            if (input[i] == '0')
                m = 0;
            else if (input[i] == '1')
                m = 1;
            else {
                printf("Invalid input\n");
                exit(1);
            }

            new_trans = 0;
            for (j = 0; j < prev_trans; j++) {
                p = present_state[j];
                k = 0;
                while (mat[p][m][k] != -1) {
                    next_state[new_trans++] = mat[p][m][k];
                    k++;
                }
            }
            prev_trans = new_trans;
            memcpy(present_state, next_state, sizeof(next_state));
        }

        flag = 0;
        for (i = 0; i < prev_trans; i++) {
            for (j = 0; j < num_final; j++) {
                if (present_state[i] == final_state[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }

        if (flag == 1)
            printf("Accepted\n");
        else
            printf("Not accepted\n");
        printf("Try with another input\n");
    }
    return 0;
}

