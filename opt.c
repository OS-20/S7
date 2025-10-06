#include <stdio.h>

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f], faults = 0;
    for (int i = 0; i < f; i++)
        frames[i] = -1; // initialize empty frames

    printf("\nPage\tFrames\n-------------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i], found = 0;

        // Check if page already in frame
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            faults++;
            int replace = -1;

            // Find empty frame
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            // If no empty frame, replace the one used farthest in future
            if (replace == -1) {
                int farthest = -1, pos = -1;
                for (int j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k])
                            break;
                    }
                    if (k == n) { // not used again
                        pos = j;
                        break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
                replace = pos;
            }

            frames[replace] = page;
        }

        // Print frames after each step
        printf("%d\t", page);
        for (int j = 0; j < f; j++)
            if (frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        printf("\n");
    }

    printf("-------------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
