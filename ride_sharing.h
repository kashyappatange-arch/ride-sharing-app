#ifndef RIDE_SHARING_H
#define RIDE_SHARING_H

#include <stdbool.h>

/* Simple 2D integer point */
typedef struct Point { int x; int y; } Point;

/* Public API */
void addDriver(int driverId, Point location);
void updateDriverLocation(int driverId, Point newLocation);
void setDriverAvailability(int driverId, bool isAvailable);
/* requestRide now returns a rideId (>0) on success or -1 if queued / failed */
int requestRide(int userId, Point pickup, Point destination);
/* End a ride by rideId (marks driver available and updates driver location to destination) */
void endRide(int rideId);
/* Simple shortest-path helper that prints steps between two points (educational) */
void findShortestPath(Point start, Point end);

/* helper to print current drivers (debug/demo) */
void printDrivers(void);

#endif /* RIDE_SHARING_H */
