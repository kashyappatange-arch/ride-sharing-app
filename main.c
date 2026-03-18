#include <stdio.h>
#include <stdlib.h>
#include "ride_sharing.h"


static void print_menu(void) {
    printf("\n=== Ride Sharing CLI ===\n");
    printf("1) Add driver        - Add a new driver to the system\n");
    printf("2) Update location   - Update an existing driver's location\n");
    printf("3) Set availability  - Mark a driver available or busy\n");
    printf("4) Request ride      - Request a ride for a user\n");
    printf("5) Print drivers     - Show current drivers and status\n");
    printf("6) Exit              - Quit the program\n");
    printf("7) End ride          - End an active ride by rideId\n");
    printf("8) Shortest path     - Print a simple shortest path between two points\n");
    printf("Enter choice (1-8): ");
}

int main(void) {
    int choice;

    /* pre-populate a few drivers to explore scenarios */
    addDriver(1, (Point){0,0});
    addDriver(2, (Point){10,0});
    addDriver(3, (Point){3,4});

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            /* bad input: clear rest of line and continue */
            int c; while ((c = getchar()) != '\n' && c != EOF) ;
            printf("Invalid selection. Try again.\n");
            continue;
        }

        if (choice == 1) {
            int id, x, y;
            printf("Add driver - enter: driverId x y (example: 42 5 3): ");
            if (scanf("%d %d %d", &id, &x, &y) == 3) {
                addDriver(id, (Point){x,y});
                printf("Driver %d added at (%d,%d).\n", id, x, y);
            } else { printf("Invalid input. Please provide three integers.\n"); }
        } else if (choice == 2) {
            int id, x, y;
            printf("Update location - enter: driverId x y (example: 42 6 2): ");
            if (scanf("%d %d %d", &id, &x, &y) == 3) {
                updateDriverLocation(id, (Point){x,y});
                printf("Requested update: driver %d -> (%d,%d).\n", id, x, y);
            } else { printf("Invalid input. Please provide three integers.\n"); }
        } else if (choice == 3) {
            int id, avail;
            printf("Set availability - enter: driverId isAvailable(1 for available, 0 for busy) (example: 42 1): ");
            if (scanf("%d %d", &id, &avail) == 2) {
                setDriverAvailability(id, avail ? 1 : 0);
                printf("Driver %d availability set to %s.\n", id, avail ? "available" : "busy");
            } else { printf("Invalid input. Please provide two integers.\n"); }
        } else if (choice == 4) {
            int uid, px, py, dx, dy;
            printf("Request ride - enter: userId pickupX pickupY destX destY (example: 100 1 1 8 8): ");
            if (scanf("%d %d %d %d %d", &uid, &px, &py, &dx, &dy) == 5) {
                int rideId = requestRide(uid, (Point){px,py}, (Point){dx,dy});
                if (rideId > 0) printf("Ride created with id %d.\n", rideId);
                else printf("Your request was queued. We'll assign a driver when one becomes available.\n");
            } else { printf("Invalid input. Please provide five integers.\n"); }
        } else if (choice == 5) {
            printDrivers();
        } else if (choice == 7) {
            int rid;
            printf("End ride - enter rideId: ");
            if (scanf("%d", &rid) == 1) {
                endRide(rid);
            } else { printf("Invalid input.\n"); }
        } else if (choice == 8) {
            int sx, sy, ex, ey;
            printf("Shortest path - enter startX startY endX endY: ");
            if (scanf("%d %d %d %d", &sx, &sy, &ex, &ey) == 4) {
                findShortestPath((Point){sx,sy}, (Point){ex,ey});
            } else { printf("Invalid input.\n"); }
        } else if (choice == 6) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Unknown option. Please enter a number between 1 and 6.\n");
        }

        /* clear rest of line to avoid leftover input interfering */
        int c; while ((c = getchar()) != '\n' && c != EOF) ;
    }

    return 0;
}
