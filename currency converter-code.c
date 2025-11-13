#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Currency {
    char code[10];
    char name[50];
    double rate_to_usd;
};

int main() {
    
    struct Currency currencies[200];
    int currency_count = 0;
    FILE *file;

    file = fopen("rates.txt", "r");
    
    if (file == NULL) {
        printf("Error: Could not open rates.txt file.\n");
        printf("Please make sure the file is in the same folder as the program.\n");
        printf("Press Enter to exit.\n");
        getchar();
        return 1;
    }

    while(fscanf(file, "%[^,],%[^,],%lf\n", 
           currencies[currency_count].code, 
           currencies[currency_count].name, 
           &currencies[currency_count].rate_to_usd) == 3) 
    {
        currency_count++;
        if (currency_count >= 200) {
            printf("Warning: Hit currency limit. Loaded 200 currencies.\n");
            break;
        }
    }
    
    fclose(file);

    int choice;
    
    while (1) {
        printf("===================================================\n");
        printf("         Welcome to the ZenCoders Currency Converter\n");
        printf("         (Loaded %d Currencies from file)\n", currency_count);
        printf("===================================================\n");
        printf("   1. Convert a Currency\n");
        printf("   2. List all Available Currencies\n");
        printf("   3. Exit Program\n");
        printf("---------------------------------------------------\n");
        printf("Enter your choice (1-3): ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("\nInvalid input. Please enter a number.\n\n");
            continue;
        }
        printf("\n");

        switch (choice) {
            
            case 1: {
                char from_code[10], to_code[10];
                char from_upper[10], to_upper[10];
                double amount;
                char again;
                
                while(1) {
                    printf("Enter amount to convert: ");
                    if (scanf("%lf", &amount) != 1) {
                        while(getchar() != '\n');
                        printf("Invalid amount. Please try again.\n");
                        continue;
                    }

                    printf("Enter 'from' currency code (e.g., PKR): ");
                    scanf("%s", from_code);

                    printf("Enter 'to' currency code (e.g., USD): ");
                    scanf("%s", to_code);

                    for (int i = 0; i <= strlen(from_code); i++) {
                        from_upper[i] = toupper(from_code[i]);
                    }
                    for (int i = 0; i <= strlen(to_code); i++) {
                        to_upper[i] = toupper(to_code[i]);
                    }

                    double from_rate = 0.0, to_rate = 0.0;
                    int from_found = 0, to_found = 0;

                    for(int i = 0; i < currency_count; i++) {
                        if (strcmp(from_upper, currencies[i].code) == 0) {
                            from_rate = currencies[i].rate_to_usd;
                            from_found = 1;
                        }
                        if (strcmp(to_upper, currencies[i].code) == 0) {
                            to_rate = currencies[i].rate_to_usd;
                            to_found = 1;
                        }
                    }

                    printf("\n------------------ Result ------------------\n");
                    if (from_found == 0 || to_found == 0) {
                        printf("Error: Invalid currency code entered.\n");
                    } else {
                        double base_amount = amount / from_rate;
                        double final_amount = base_amount * to_rate;
                        
                        printf("%.2f %s = %.2f %s\n", amount, from_upper, final_amount, to_upper);
                    }
                    printf("--------------------------------------------\n\n");

                    printf("Do another conversion? (y/n): ");
                    scanf(" %c", &again); 

                    while(again != 'y' && again != 'Y' && again != 'n' && again != 'N') {
                        printf("Invalid option. Please enter 'y' or 'n': ");
                        scanf(" %c", &again);
                    }

                    if (again == 'n' || again == 'N') {
                        printf("\n");
                        break;
                    }
                }
                break;
            }
            
            case 2: {
                printf("--- Listing all %d Available Currencies ---\n", currency_count);
                for (int i = 0; i < currency_count; i++) {
                    printf("   Code: %-10s Name: %s\n", currencies[i].code, currencies[i].name);
                }
                printf("---------------------------------------------------\n\n");
                printf("Press Enter to return to the menu...");
                
                getchar();
                getchar();
                
                break;
            }

            case 3:
                printf("Thank you for using the ZenCoders Currency converter!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n\n");
                break;
        }
    }
    
    return 0;
}
