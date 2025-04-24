#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRIPS 1000
#define MAX_STR 31

typedef struct {
    char code_route[MAX_STR];
    char departure[MAX_STR];
    char destination[MAX_STR];
    char date[11];            //    Format: yyyy/mm/dd
    char time_departure[9];   //    Format: hh:mm:ss
    char time_arrival[9];     //    Format: hh:mm:ss
    int delay;
} Trip;

typedef enum {
    c_date,
    c_departure,
    c_destination,
    c_delay,
    c_tot_delay,
    c_end,
    c_invalid
} t_command;

t_command readCommand(char *command) {
    if (strcmp(command, "date") == 0) return c_date;
    if (strcmp(command, "departure") == 0) return c_departure;
    if (strcmp(command, "destination") == 0) return c_destination;
    if (strcmp(command, "delay") == 0) return c_delay;
    if (strcmp(command, "tot-delay") == 0) return c_tot_delay;
    if (strcmp(command, "end") == 0) return c_end;
    return c_invalid;
}

void readTrips(Trip trips[], int *n) {
    FILE *fp = fopen("log.txt", "r");
    if (!fp) {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(fp, "%d\n", n);
    for (int i = 0; i < *n; i++) {
        fscanf(fp, "%s %s %s %s %s %s %d\n",
               trips[i].code_route, trips[i].departure, trips[i].destination,
               trips[i].date, trips[i].time_departure, trips[i].time_arrival,
               &trips[i].delay);
    }
    fclose(fp);
}

void printTrip(Trip t) {
    printf("%s %s %s %s %s %s %d\n",
           t.code_route, t.departure, t.destination,
           t.date, t.time_departure, t.time_arrival, t.delay);
}

void menuWord(Trip trips[], int n) {
    char line[100], cmd[20];
    t_command command;
    while (1) {
        printf("Enter command: ");
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s", cmd);
        command = readCommand(cmd);

        switch (command) {
            case c_date: {
                char date1[11], date2[11];
                sscanf(line, "%*s %s %s", date1, date2);
                for (int i = 0; i < n; i++) {
                    if (strcmp(trips[i].date, date1) >= 0 && strcmp(trips[i].date, date2) <= 0) {
                        printTrip(trips[i]);
                    }
                }
                break;
            }
            case c_departure: {
                char dep[MAX_STR];
                sscanf(line, "%*s %s", dep);
                for (int i = 0; i < n; i++) {
                    if (strcmp(trips[i].departure, dep) == 0) {
                        printTrip(trips[i]);
                    }
                }
                break;
            }
            case c_destination: {
                char dest[MAX_STR];
                sscanf(line, "%*s %s", dest);
                for (int i = 0; i < n; i++) {
                    if (strcmp(trips[i].destination, dest) == 0) {
                        printTrip(trips[i]);
                    }
                }
                break;
            }
            case c_delay: {
                char date1[11], date2[11];
                sscanf(line, "%*s %s %s", date1, date2);
                for (int i = 0; i < n; i++) {
                    if (trips[i].delay > 0 && strcmp(trips[i].date, date1) >= 0 && strcmp(trips[i].date, date2) <= 0) {
                        printTrip(trips[i]);
                    }
                }
                break;
            }
            case c_tot_delay: {
                char code[MAX_STR];
                int total = 0;
                sscanf(line, "%*s %s", code);
                for (int i = 0; i < n; i++) {
                    if (strcmp(trips[i].code_route, code) == 0) {
                        total += trips[i].delay;
                    }
                }
                printf("Total delay for route %s: %d minutes\n", code, total);
                break;
            }
            case c_end:
                return;
            case c_invalid:
                printf("Invalid command.\n");
                break;
        }
    }
}

int main() {
    Trip trips[MAX_TRIPS];
    int n;
    readTrips(trips, &n);
    menuWord(trips, n);
    return 0;
}
