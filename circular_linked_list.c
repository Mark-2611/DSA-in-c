#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *next;
};

struct node *first = NULL, *last = NULL, *newnode, *temp, *pred, *succ;

void insertend(int val) {
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->info = val;
    if (first == NULL) {
        first = last = newnode;
        newnode->next = first;
    } else {
        last->next = newnode;
        last = newnode;
        last->next = first;
    }
    printf("%d inserted at end.\n", val);
}

void insertbeforepos(int val, int pos) {
    int i = 1;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->info = val;

    if (pos <= 1 || first == NULL) {
        newnode->next = first;
        first = newnode;
        if (last == NULL)
            last = newnode;
        last->next = first;
        printf("%d inserted at position %d (beginning).\n", val, pos);
        return;
    }

    temp = first;
    while (i < pos - 1 && temp->next != first) {
        temp = temp->next;
        i++;
    }

    pred = temp;
    newnode->next = pred->next;
    pred->next = newnode;
    if (pred == last)
        last = newnode;

    printf("%d inserted before position %d.\n", val, pos);
}

void deletefirst() {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (first == last) {
        printf("%d deleted (last node).\n", first->info);
        free(first);
        first = last = NULL;
    } else {
        temp = first;
        printf("%d deleted (first node).\n", temp->info);
        first = first->next;
        last->next = first;
        free(temp);
    }
}

void deleteafterpos(int pos) {
    int i = 1;
    if (first == NULL || first->next == first) {
        printf("List is too small to delete after position.\n");
        return;
    }

    temp = first;
    while (i < pos && temp->next != first) {
        temp = temp->next;
        i++;
    }

    pred = temp;
    succ = pred->next;

    if (succ == first) {
        first = first->next;
        last->next = first;
        free(succ);
        printf("Deleted node after position %d (was first node).\n", pos);
    } else {
        printf("%d deleted (after position %d).\n", succ->info, pos);
        pred->next = succ->next;
        if (succ == last)
            last = pred;
        free(succ);
    }
}

void display() {
    if (first == NULL) {
        printf("List is empty.\n");
        return;
    }

    temp = first;
    printf("List: ");
    do {
        printf("%d ", temp->info);
        temp = temp->next;
    } while (temp != first);
    printf("\n");
}

int main() {
    int choice, val, pos;

    do {
        printf("\n---- Circular Linked List Menu ----\n");
        printf("1. Insert at end\n");
        printf("2. Insert before position\n");
        printf("3. Delete first node\n");
        printf("4. Delete after position\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at end: ");
                scanf("%d", &val);
                insertend(val);
                break;

            case 2:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                printf("Enter position: ");
                scanf("%d", &pos);
                insertbeforepos(val, pos);
                break;

            case 3:
                deletefirst();
                break;

            case 4:
                printf("Enter position after which to delete: ");
                scanf("%d", &pos);
                deleteafterpos(pos);
                break;

            case 5:
                display();
                break;

            case 6:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice. Try again.\n");
        }
    }while(choice!=6);

    return 0;
}
