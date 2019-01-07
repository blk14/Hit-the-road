# Hit-the-road
A mini google maps implementation


This application has the purpose to give the answer for 5 tasks which are frequently encountered in a applications like google maps or waze. Based on some input data such as:
 1. a list of cities
 2. the roads between them (source - destination). The roads are unidirectional and the distance is 1 unity by default
 3. a list of cities with gas station
 [4]. a list of cities and for each one I have to find out the cities at which
    it can't arrive
 [5]. a list of cars with the following details: the city where it is, how much gas does it has and the consumption per unity
 [6]. a list of bus routes with the following details: source_city, destination_city and the number of travelers

TASK 1
'''''' Is to find out the most crowded city. (the rule is that the most crowded city is the one which represent the destination for most roads)

Task 2
'''''' Is to find out if the map is valid. (the rule is: if there is a road between each city the map is valid, the cost for this road doesn't matter, in other words if the map is a strongly connected component)

Task 3
'''''' Is to take the list from [4] and find out the list for each city with inaccessible cities for it (there is not roud between them)

Task 4
'''''' Is to take the list from [5] and find out for each car the closest gas station from another city (the shortest road to a city with gas station) and print "DA" if the car can arrive in a city with gas station and the remaining fuel, or "NU" if it can't.

Task 5
'''''' Is to take the list from [6] and find out the route which is traveled by the most travelers, print the route and the number of travelers. It is known that every bus is going on the shortest route between 2 cities and the buses does not stop between source city and destination
