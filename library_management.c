#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Book {
    int id;
    char title[50];
    char author[50];
    int quantity;
};
void addBook() {
    FILE *fp = fopen("library.dat", "ab");
    struct Book b;
    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Title: ");
    scanf(" %[^\n]", b.title);
    printf("Enter Author: ");
    scanf(" %[^\n]", b.author);
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);
    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("\nBook added successfully!\n");
}
void displayBooks() {
    FILE *fp = fopen("library.dat", "rb");
    struct Book b;
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    printf("\n--- Book List ---\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d\nTitle: %s\nAuthor: %s\nQuantity: %d\n",
               b.id, b.title, b.author, b.quantity);
    }
    fclose(fp);
}
void searchBook() {
    FILE *fp = fopen("library.dat", "rb");
    struct Book b;
    int id, found = 0;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found!\n");
            printf("Title: %s\nAuthor: %s\nQuantity: %d\n",
                   b.title, b.author, b.quantity);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nBook not found!\n");
    fclose(fp);
}
void issueBook() {
    FILE *fp = fopen("library.dat", "rb+");
    struct Book b;
    int id, found = 0;
    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id && b.quantity > 0) {
            b.quantity--;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("\nBook issued successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nBook not available!\n");
    fclose(fp);
}
void returnBook() {
    FILE *fp = fopen("library.dat", "rb+");
    struct Book b;
    int id, found = 0;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            b.quantity++;
            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);
            printf("\nBook returned successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\nBook not found!\n");
    fclose(fp);
}
int main() {
    int choice;
    while (1) {
        printf("\n===== Library Menu =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }
    return 0;
}
