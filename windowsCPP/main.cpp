//Libraries
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;


#define M_PI 3.14159265358979323846

//Header for distance between function
double distanceBetween(const pair<double, double>& lhs, const pair<double, double>& rhs);

//Class for Adjacency Graph
class LocationAdjacencyGraph {
//Private members
private:
    //Basic node struct
    struct Node {
        //Vector containing adjacent nodes and their distances
        vector<Node*> adjacencyList;
        vector<double> distance;

        //Location of this vertex
        pair<double, double> storedLocation;
    };

    //Vector of every vertex
    vector<Node*> vertices;

    //Gets the closest vertex to a given location
    Node* getClosestNode(const pair<double, double>& insertedLocation) { //O(V) where V is the total number of location vertices in the graph
        //Variables to store minimum node and its distance
        double minimum; //O(1)
        Node* closest = NULL; //O(1)

        //For every vertex in the graph
        for (int i = 0; i < vertices.size(); i++) { //O(V) *
            //Find the distance between them
            double distance = distanceBetween(vertices.at(i)->storedLocation, insertedLocation); //O(1)

            //If this is the first vertex or the distance is smaller than the current minimum
            if (i == 0 || distance < minimum) { //O(1)
                //Set the new minimum
                minimum = distance; //O(1)
                closest = vertices.at(i); //O(1)
            }
        }

        //Return that vertex
        return closest; //O(1)
    }

//Public members
public:
    //Destructor
    ~LocationAdjacencyGraph() { //O(V)
        //Deletes every vertex
        for (int i = 0; i < vertices.size(); i++) { //O(V) *
            delete vertices.at(i); //O(1)
        }
    }

    //Adds a given coordinate location to the graph
    void addLocation(const pair<double, double>& insertedLocation) { //O(V) where V is the total number of location vertices in the graph
        //Get the closest node to the location
        Node* closest = getClosestNode(insertedLocation); //O(V)

        //If there is no other vertices in the graph
        if (closest == NULL) { //O(1)
            //Create a new node
            Node* currentNode = new Node; //O(1)

            //Store the location in this node
            currentNode->storedLocation = insertedLocation; //O(1)

            //Stores the node in the vertex vector
            vertices.push_back(currentNode); //O(1) or O(V) if resize
        }
            //Otherwise, if this is a unique location
        else if (closest->storedLocation != insertedLocation) { //O(1)
            //Create a new node
            Node* currentNode = new Node; //O(1)

            //Store the location in this node
            currentNode->storedLocation = insertedLocation; //O(1)

            //Add each node to the other's adjacency list
            currentNode->adjacencyList.push_back(closest); //O(1)
            closest->adjacencyList.push_back(currentNode); //O(1)

            //Find the distance between them
            double distance = distanceBetween(closest->storedLocation, insertedLocation); //O(1)

            //Add this distance to each node's distance vector
            currentNode->distance.push_back(distance); //O(1) or O(V) if resize
            closest->distance.push_back(distance); //O(1) or O(V) if resize

            //Add to the vertices list
            vertices.push_back(currentNode);
        }
    }

    //Calculates the most central vertex and its surrounding vertices
    vector<pair<double, double>> getCentralLocation() { //O(V * c) where V is the total number of location vertices and c is the number of edges per vertex
        //Store current most central vertex
        Node* central = NULL; //O(1)

        //For every vertex
        for (int i = 0; i < vertices.size(); i++) { //O(V) *
            //If this is the first iteration, or if the  vertex has more edges than the current most central vertex
            if (i == 0 || vertices.at(i)->adjacencyList.size() > central->adjacencyList.size()) { //O(1)
                //Set this as the new most central vertex
                central = vertices.at(i); //O(1)
            }
                //Otherwise, if there is a tie
            else if (vertices.at(i)->adjacencyList.size() == central->adjacencyList.size()) { //O(1)
                //Add up the distances for every edge in the current vertex
                double currentTotal = 0; //O(1)
                for (int j = 0; j < vertices.at(i)->distance.size(); j++) {  //O(c) *
                    currentTotal += vertices.at(i)->distance.at(j); //O(1)
                }

                //Add up the distances for every edge in the central vertex
                double centralTotal = 0;
                for (int j = 0; j < central->distance.size(); j++) { //O(c) *
                    centralTotal += central->distance.at(j); //O(1)
                }

                //If the current vertex has a lower total, set it as the new vertex
                if (currentTotal < centralTotal) { //O(1)
                    central = vertices.at(i); //O(1)
                }
            }
        }

        //Vector for every location
        vector<pair<double, double>> locations; //O(1)

        if (central == NULL) {
            return locations;
        }

        //Push back the most central location
        locations.push_back(central->storedLocation); //O(1) or O(V) if resize

        //Push back every location adjacent to the most central location
        for (int i = 0; i < central->adjacencyList.size(); i++) { //O(c) *
            locations.push_back(central->adjacencyList.at(i)->storedLocation); //O(1) or O(c) if resize
        }

        //Return the locations
        return locations; //O(1)
    }
};

//splay class
class splay
{
//Private members
private:
    //Basic node class
    struct node {
        pair<double, double> coordinates;
        string name;
        int frequency;
        node* left;
        node* right;
        node* parent;
        node* prev;
        node() {
            left = NULL;
            right = NULL;
            parent = NULL;
            prev = NULL;
            frequency = 0;
            name = "none";
        }
    };

//Public members
public:
    splay() {
        root = NULL;
    }
    //Root variable and getter
    node* root;
    node* getRoot()
    {
        return root;
    }

    //Find the node with the proper name
    node* find(string s, node* n)
    {
        if (n == NULL)
        {
            return NULL;
        }
        if (n->name == s) return n;
        node* ans =find(s, n->left);
        ans =find(s, n->right);
        return ans;
    }

    //Splay function for splay tree
    void splayFunction(node* n)
    {
        if (n->parent == NULL) {
            return;
        }
        node* temp = n->parent;
        if (n->parent->left = n) //zig, single right
        {
            n->right->parent = n->parent;
            n->parent->left = n->right;
            n->right = n->parent;
            n->parent = n->parent->parent;
            temp->parent = n;
        }
        else //zag, single left
        {
            n->left->parent = n->parent;
            n->parent->right = n->left;
            n->left = n->parent;
            n->parent = n->parent->parent;
            temp->parent = n;
        }
        if (temp != root) splayFunction(n);
        else root = n;


    }

    //Destructor
    ~splay() {
        deleteAll(root);
    }

    //For every node, deletes it
    void deleteAll(node* root) {
        if (root == NULL) {
            return;
        }
        if (root->left != NULL) {
            deleteAll(root->left);
        }
        if (root->right != NULL) {
            deleteAll(root->right);
        }

        delete root;
    }

    //Creates a new node for the tree
    void addLocation(pair<double, double> coords) {
        node* newNode = new node;
        newNode->frequency = 0;
        newNode->coordinates = coords;
        insert(newNode);
    }

    //Inserts a new node into the tree
    void insert(node* n) // splay tree should grab the nodes nearby since it should theoretically have accessed nodes  be close to eachother if in same area
    {
        //default to nodes on the right having higher numbers (count)
        if (root == NULL) {
            root = n;
            return;
        }
        node* found = find(n->name, root); //make sure to delete lol
        if (found == NULL)//inserts on top
        {
            node* move = root;
            while (move != NULL) //here maybe do coordinates to get distances and scale them this way
            {
                move->prev = move;
                n->prev = move->prev;
                if (move->right != NULL && move->left != NULL)move = move->right;
                else if (move->right != NULL) move = move->left;
                else move = move->right;

            }
            splayFunction(n);
            //splayFunction here
        }
        else
        {
            found->frequency++;
            delete n;
            splayFunction(found);
        }
    }

    //Make a guess at the central locations of the user's location
    vector<pair<double, double>> getCentralLocation()
    {
        if (root == NULL) return vector<pair<double, double>>();
        vector<pair<double, double>> ans;
        ans.push_back(root->coordinates);
        node* r = root->right;
        node* l = root->left;
        for (int i = 0; i < 10; i++)
        {
            if (r != NULL)
            {
                for (int j = 0; j < r->frequency; j++)
                {
                    ans.push_back(r->coordinates);
                }
                if (r->left != NULL) ans.push_back(r->left->coordinates);
                if (r->right != NULL) r = r->right;
                else r = r->left;
            }
            if (l != NULL)
            {
                for (int j = 0; j < l->frequency; j++)
                {
                    ans.push_back(l->coordinates);
                }
                if (l->left != NULL) ans.push_back(l->left->coordinates);
                if (l->right != NULL) l = l->right;
                else l = l->left;
            }
        }
        return ans;

    }
};

//Function that calculates the distance between two points given in decimal degrees
double distanceBetween(const pair<double, double>& lhs, const pair<double, double>& rhs) { //O(1)
    //Finds difference in latitude and longitude and converts to radians.
    double latDif = (lhs.first - rhs.first) * M_PI / 180.0; //O(1)
    double longDif = (lhs.second - rhs.second) * M_PI / 180.0; //O(1)

    //Converts latitude of each to radians
    double lhsLatRad = lhs.first * M_PI / 180.0; //O(1)
    double rhsLatRad = rhs.first * M_PI / 180.0; //O(1)

    //Radius of Earth in Miles
    double radius = 3961;

    //Calculates the Haversine Formula to find distance (from https://www.movable-type.co.uk/scripts/latlong.html)
    double a = pow(sin(latDif / 2), 2) + cos(lhsLatRad) * cos(rhsLatRad) * pow(sin(longDif / 2), 2); //O(1)
    double c = 2 * asin(sqrt(a)); //O(1)

    //Returns resulting distance in miles
    return radius * c; //O(1)
}

//Function that converts latitude and longitude into cartesian coordinates (fraction of the radius)
tuple<double, double, double> coordinatesToCartesian(const pair<double, double>& coordinates) { //O(1)
    //Convert latitude and longitude into radians
    double lat = coordinates.first * M_PI / 180.0; //O(1)
    double lon = coordinates.second * M_PI / 180.0; //O(1)

    //Get X, Y, and Z (from http://www.geomidpoint.com/calculation.html)
    double x = cos(lat) * cos(lon); //O(1)
    double y = cos(lat) * sin(lon); //O(1)
    double z = sin(lat); //O(1)

    //Return a tuple of the xyz coordinates
    return tuple<double, double, double>(x, y, z); //O(1)
}

//Function that converts cartesian coordinates (fraction of the radius) into latitude and longitude
pair<double, double> cartesianToCoordinates(const tuple<double, double, double>& cartesian) { //O(1)
    //Calculate the longitude, hypotenuse, and latitude (from http://www.geomidpoint.com/calculation.html)
    double lon = atan2(get<1>(cartesian), get<0>(cartesian)); //O(1)
    double hyp = sqrt(get<0>(cartesian) * get<0>(cartesian) + get<1>(cartesian) * get<1>(cartesian)); //O(1)
    double lat = atan2(get<2>(cartesian), hyp); //O(1)

    //Convert from radians to decimal degrees
    lat = lat * 180 / M_PI; //O(1)
    lon = lon * 180 / M_PI; //O(1)

    //Return a pair of the latitude and longitude
    return pair<double, double>(lat, lon); //O(1)
}

//Function that calculates the geographic midpoint of a set of latitude and longitude coordinates
pair<double, double> verticesToCenter(const vector<pair<double, double>>& vertices) { //O(v) where v is the number of vertices to be averaged
    //Totals for cartesian coordinates
    double xTotal = 0; //O(1)
    double yTotal = 0; //O(1)
    double zTotal = 0; //O(1)

    //For each coordinate
    for (int i = 0; i < vertices.size(); i++) { //O(v) *
        //Convert to cartesian coordinates
        tuple<double, double, double> xyzCoords = coordinatesToCartesian(vertices.at(i)); //O(1)

        //Add each to the total
        xTotal += get<0>(xyzCoords); //O(1)
        yTotal += get<1>(xyzCoords); //O(1)
        zTotal += get<2>(xyzCoords); //O(1)
    }

    //Find the average of each coordinate
    xTotal = xTotal / vertices.size(); //O(1)
    yTotal = yTotal / vertices.size(); //O(1)
    zTotal = zTotal / vertices.size(); //O(1)

    //Convert the averaged coordinates to latitude and longitude and return it
    return cartesianToCoordinates(tuple<double, double, double>(xTotal, yTotal, zTotal)); //O(1)
}

//Function that takes a set of coordinates and finds a circle at their midpoint that encompasses all of them
pair<pair<double, double>, double> verticesToMap(const vector<pair<double, double>>& vertices) { //O(v) where v is the number of vertices to be averaged
    //Find the geographic midpoint
    pair<double, double> center = verticesToCenter(vertices); //O(v)

    //Placeholder value for max radius
    double maxRadius = 0;

    //For each vertex, find which is farthest from the midpoint as that should be the radius in order to encompass every point
    for (int i = 0; i < vertices.size(); i++) { //O(v) *
        //Find distance from the current vertex to the midpoint
        double distance = distanceBetween(center, vertices.at(i)); //O(1)

        //If the first vertex or if the distance is greater, this is the new maximum
        if (i == 0 || distance > maxRadius) { //O(1)
            maxRadius = distance; //O(1)
        }
    }

    //Return the midpoint and radius of the circle
    return pair<pair<double, double>, double>(center, maxRadius); //O(1)
}

//Function that goes through a tweet, finding any cities mentioned in it and putting their coordinates into the list
void findLocations(const string& tweet, vector<pair<double, double>>& coordinateList) { //O(c) or O(c + v) if resize where c is the number of characters in a tweet and v is the number of coordinates
    //Data set of 139,698 cities with populations over 1000
    ifstream file("cities1000.txt"); //O(1)

    //String to hold the current city
    string city; //O(1)

    //While there are rows left
    while (getline(file, city, '\t')) { //O(139698) = O(1) *
        //Get the second column (contains the city name)
        getline(file, city, '\t'); //O(1)

        //If the tweet contains the city name
        if (tweet.find(city) != string::npos) { //O(c) where c is the number of characters in the tweet
            //Variables for the latitude and longitude
            string lat; //O(1)
            string lon; //O(1)

            //Go 3 more columns, storing the latitude for this city
            int count = 0; //O(1)
            while (count++ < 3) { //O(3) = O(1) *
                getline(file, lat, '\t'); //O(1)
            }

            //Get the next column, storing the longitude for this city
            getline(file, lon, '\t'); //O(1)

            //Convert to a pair of doubles, pushing back onto the coordinate list
            coordinateList.push_back(pair<double, double>(stod(lat), stod(lon))); //O(1) or O(v) if resize
        }

        //Go to the next line
        getline(file, city, '\n'); //O(1)
    }
}

//Function that takes a given data structure (splay or graph), adding the gps coordinates from a tweet into it
template<typename structure>
void populateDataStructures(const vector<string>& tweets, structure& data) { //O(t * (c + v * d)) where t = number of tweets, c = number of characters in tweet, v = number of locations in tweet, and d = data structure complexity
    //Vector to hold locations
    vector<pair<double, double>> locations; //O(1)

    //For each tweet
    for (int i = 0; i < tweets.size(); i++) { //O(t) *
        //Get tweet
        string tweet = tweets.at(i); //O(1)

        //Find locations in tweet
        findLocations(tweet, locations); //O(c) or O(c + v) if resize
    }

    //For every location in every tweet
    for (int i = 0; i < locations.size(); i++) { //O(t * v) *
        //Add that location to the data structure
        data.addLocation(locations.at(i)); //O(log V) amortized for splay, O(V) for adjacency graph = O(d)
    }
}

//Get the user id from a link
string getUserID (string profilelink) {
    //Get the start of the URL
    int start = profilelink.find("twitter.com/");

    //If doesn't exist, assume that a user ID was given
    if (start == string::npos) {
        return profilelink;
    }

    //Set to after the twitter.com/
    start += 12;

    //Default length
    int length = 0;

    //For every character until the /, add 1 to length
    for (int i = start; i < profilelink.size(); i++) {
        if (profilelink.at(i) != '/') {
            length++;
        }
    }

    //Return the user ID
    return profilelink.substr(start, length);
}


//Function that generates the command into a character array
void generateCommand(string command) {
    //New character array
    char* charArray = new char[command.size()];

    //For every character, put it in the array
    for (int i = 0; i < command.size(); i++) {
        charArray[i] = command.at(i);
    }

    //Execute the command
    system(charArray);

    //Delete the character array
    delete[] charArray;
}

//Function that gets data
vector<string> getData() {
    //Data holder
    vector<string> fileData;

    //Open the file
    ifstream data("data.txt");

    //Push every line into data
    string currData;
    while (getline(data, currData)) {
        fileData.push_back(currData);
    }

    //Close the file
    data.close();

    //Return the data
    return fileData;
}

//Looks up a random profile
string randomProfile() {
    string source = "python Finder.py";
    //Generate the command
    generateCommand(source);

    //Get the data
    vector<string> data = getData();

    //If there is data, return the first
    if (!data.empty()) {
        return data.at(0);
    }

    //Otherwise, return an empty string
    return string();
}

//Looks up a specific profile
vector<string> lookupProfile(const string& profilelink) {
    string source = "python Finder.py ";


    //Generate the command
    generateCommand(source + getUserID(profilelink));

    //Get the data
    return getData();
}

//Get the location in the profile's bio
string getBioLocation(const string& profilelink) {
    string source = "python Finder.py ";

    //Generate the command
    generateCommand(source + getUserID(profilelink) + "bioLocation");

    //Get the data
    vector<string> data = getData();

    //If there is data, return it
    if (!data.empty()) {
        return data.at(0);
    }

    //Otherwise, return an empty string
    return string();
}

//Function that takes the location field in their bio, and converts it to gps coordinates
pair<double, double> getRealLocation(string realLocation) { //O(c) or O(c + v) if resize
    //Vector to store possible locations
    vector<pair<double, double>> possibleLocations; //O(1)

    //Find gps coordinates of possible locations
    findLocations(realLocation, possibleLocations); //O(c) or O(c + v) if resize

    //Store selected location
    pair<double, double> location; //O(1)

    //If found at least one location
    if (!possibleLocations.empty()) { //O(1)
        //Select the first location
        location = possibleLocations.at(0); //O(1)
    }

    //Return the selected location
    return location; //O(1)
}

//Function that takes a set of tweets, and returns a map of their predicted location
template<typename structure>
pair<pair<double, double>, double> generateMap(const vector<string>& tweets) { //O(t * (c + v * d) + g) where t = number of tweets, c = number of characters in tweet, v = number of locations in tweet, d = data structure complexity for adding, and g = data structure complexity for calculating getCentralLocation
    //Create the data structure
    structure data; //O(1)

    //Add locations from tweets into the data structure
    populateDataStructures<structure>(tweets, data); //O(t * (c + v * d))

    //Get the coordinates of the getCentralLocation from the data structure
    vector<pair<double, double>> guess = data.getCentralLocation(); //O() for splay, O() for graph = O(g)

    //Get the circle of the map from the guessed coordinates
    pair<pair<double, double>, double> circle = verticesToMap(guess); //O(v)

    //Return the circle of the map
    return circle; //O(1)
}

//Main function that takes arguments and decides what to do
int main(int argc, char* argv[]) { //O()
    //Check if there is two arguments
    if (argc < 2) { //O(1)
        return -1; //O(1)
    }

    //Set the type
    string type = argv[1]; //O(1)

    //If running accuracy test
    if (type == "accuracy") { //O(1)
        //Get the profile
        string profileLink;
        if (argc == 2) {
            profileLink = randomProfile();
        } else {
            profileLink = argv[2]; //O(1)
        }

        //Variables to store statistics
        double accuracyAverageSplay = 0; //O(1)
        double accuracyAverageGraph = 0; //O(1)
        double timeAverageSplay = 0; //O(1)
        double timeAverageGraph = 0; //O(1)

        //Get a list of every tweet by the profile
        vector<string> tweets = lookupProfile(profileLink); //O()

        //Get the location indicated in the profile bio
        string profileLocation = getBioLocation(profileLink); //O()

        //Determine the coordinates of the profile location
        pair<double, double> realLocation = getRealLocation(profileLocation); //O()

        //Start a timer
        auto start = chrono::high_resolution_clock::now(); //O(1)

        //Generate a getCentralLocation for the splay tree
        pair<pair<double, double>, double> splayCircle = generateMap<splay>(tweets); //O(t * (c + v * d) + g)

        //Stop the timer
        auto stop = chrono::high_resolution_clock::now(); //O(1)

        //Find how long the splay data structure took, and add it to the total
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); //O(1)
        timeAverageSplay += duration.count(); //O(1)

        //Start a timer
        start = chrono::high_resolution_clock::now(); //O(1)

        //Generate a getCentralLocation for the graph
        pair<pair<double, double>, double> graphCircle = generateMap<LocationAdjacencyGraph>(tweets); //O(t * (c + v * d) + g)

        //Stop the timer
        stop = chrono::high_resolution_clock::now(); //O(1)

        //Find how long the graph data structure took, and add it to the total
        duration = chrono::duration_cast<chrono::milliseconds>(stop - start); //O(1)
        timeAverageGraph += duration.count(); //O(1)

        //Find the distance between the getCentralLocation and real location for each data structure, adding it to the total
        accuracyAverageSplay += distanceBetween(splayCircle.first, realLocation); //O(1)
        accuracyAverageGraph += distanceBetween(graphCircle.first, realLocation); //O(1)

        //Output the average distance and time for each profile for each data structure
        cout << accuracyAverageSplay << " " << timeAverageSplay << endl; //O(1)
        cout << accuracyAverageGraph << " " << timeAverageGraph << endl; //O(1)

    }
        //Otherwise, if running map test
    else if (type == "map") { //O(1)
        //Get the link to the profile
        string profileLink = argv[2]; //O(1)

        //Get a list of every tweet
        vector<string> tweets = lookupProfile(profileLink); //O()

        //Get circles for each data structure
        pair<pair<double, double>, double> splayCircle = generateMap<splay>(tweets); //O(t * (c + v * d) + g)
        pair<pair<double, double>, double> graphCircle = generateMap<LocationAdjacencyGraph>(tweets); //O(t * (c + v * d) + g)

        //Output the coordinates and radius for each circle
        cout << splayCircle.first.first << " " << splayCircle.first.second << " " << splayCircle.second << endl; //O(1)
        cout << graphCircle.first.first << " " << graphCircle.first.second << " " << graphCircle.second << endl; //O(1)
    }
        //Otherwise, invalid input
    else { //O(1)
        return -1; //O(1)
    }

    //End the program
    return 0; //O(1)
}