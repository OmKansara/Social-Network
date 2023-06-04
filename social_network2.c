#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 100

typedef struct User {
    int id;
    char name[50];
} User;

typedef struct Graph {
    int numUsers;
    User users[MAX_USERS];
    bool adjMatrix[MAX_USERS][MAX_USERS];
} Graph;

Graph createGraph() {
    Graph graph;
    graph.numUsers = 0;

    // Initializing adjacency matrix with all false values i.e 0 for bool
    int i,j;
	for (i = 0; i < MAX_USERS; i++) {
        for (j = 0; j < MAX_USERS; j++) {
            graph.adjMatrix[i][j] = false;
        }
    }

    return graph;
}

int addUser(Graph* graph, char* name) {
    if (graph->numUsers == MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return -1;
    }

    int id = graph->numUsers++;
    User user;
    user.id = id;
    printf("Enter name : ");
    strcpy(user.name, name);
    graph->users[id] = user;

    return id;
}

void addFriendship(Graph* graph, int userId1, int userId2) {
    if (userId1 < 0 || userId1 >= graph->numUsers || userId2 < 0 || userId2 >= graph->numUsers) {
        printf("Invalid user IDs.\n");
        return;
    }

    graph->adjMatrix[userId1][userId2] = true;
    graph->adjMatrix[userId2][userId1] = true;
}

void removeFriendship(Graph* graph, int userId1, int userId2) {
    if (userId1 < 0 || userId1 >= graph->numUsers || userId2 < 0 || userId2 >= graph->numUsers) {
        printf("Invalid user IDs.\n");
        return;
    }

    graph->adjMatrix[userId1][userId2] = false;
    graph->adjMatrix[userId2][userId1] = false;
}

void displayFriends(Graph* graph, int userId) {
    if (userId < 0 || userId >= graph->numUsers) {
        printf("Invalid user ID.\n");
        return;
    }

    printf("Friends of %s:\n", graph->users[userId].name);
    int i;
	for (i = 0; i < graph->numUsers; i++) {
        if (graph->adjMatrix[userId][i]) {
            printf("- %s\n", graph->users[i].name);
        }
    }
}

void mutualFriends(Graph* graph, int userId1, int userId2) {
    if (userId1 < 0 || userId1 >= graph->numUsers || userId2 < 0 || userId2 >= graph->numUsers) {
        printf("Invalid user IDs.\n");
        return;
    }

    printf("Mutual Friends of %s and %s:\n", graph->users[userId1].name, graph->users[userId2].name);
    bool hasMutualFriends = false;
    int i;
	for (i = 0; i < graph->numUsers; i++) {
        if (graph->adjMatrix[userId1][i] && graph->adjMatrix[userId2][i]) {
            printf("- %s\n", graph->users[i].name);
            hasMutualFriends = true;
        }
    }

    if (!hasMutualFriends) {
        printf("No mutual friends found.\n");
    }
}


int main() {
    Graph socialNetwork = createGraph();
    int choice;

    while (1) {
        printf("+--------------------------+\n");
        printf("¦    Social Network Menu   ¦\n");
        printf("+--------------------------+\n");
        printf("1. Add User\n");
        printf("2. Add Friendship\n");
        printf("3. Remove Friendship\n");
        printf("4. Display Friends\n");
        printf("5. Mutual Friends\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                printf("Enter user name: ");
                scanf("%s", name);
                int userId = addUser(&socialNetwork, name);
                if (userId != -1) {
                    printf("User added successfully with ID: %d\n", userId);
                }
                break;
            }
            case 2: {
                int userId1, userId2;
                printf("Enter user ID 1: ");
                scanf("%d", &userId1);
                printf("Enter user ID 2: ");
                scanf("%d", &userId2);
                addFriendship(&socialNetwork, userId1, userId2);
                printf("Friendship added successfully.\n");
                break;
            }
            case 3: {
                int userId1, userId2;
                printf("Enter user ID 1: ");
                scanf("%d", &userId1);
                printf("Enter user ID 2: ");
                scanf("%d", &userId2);
                removeFriendship(&socialNetwork, userId1, userId2);
                printf("Friendship removed successfully.\n");
                break;
            }
            case 4: {
                int userId;
                printf("Enter user ID: ");
                scanf("%d", &userId);
                displayFriends(&socialNetwork, userId);
                break;
            }
            case 5: {
                int userId1, userId2;
                printf("Enter user ID 1: ");
                scanf("%d", &userId1);
                printf("Enter user ID 2: ");
                scanf("%d", &userId2);
                mutualFriends(&socialNetwork, userId1, userId2);
                break;
            }
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

