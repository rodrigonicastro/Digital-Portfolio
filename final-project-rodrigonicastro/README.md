# Which hash collision resolution method did you choose and why?

I chose to use chaining, as I was already familiar with linked lists and it seemed like it would be a smoother implementation. I also believe that chaining would be more efficient than other methods, especially in an eventual deletion algorithm.

# Explain your hash function

To minimize collisions, I added "weight" to each of the movie title's charachters using my IdentiKey. As I loop through the movie title, I also loop through the digits of my IdentiKey, multiplying the ASCII value of the movie title's charachter by the ASCII value of the IdentiKey's digit. Doing this for all charachters in the movie's title and summing the results, I get the ASCIIsum, then I set the hashIndex equal to the remainder of the division of the ASCIIsum by the hashKe (which is the table_size specified by the user).

# Did you implement skiplist to search for director specific information? If not, what alternative data structure did you use, and why?

Yes, I used skiplist to store and search for the directors and their information.

# Explain any additional features you have implemented.

As extras, I implemented a Graph that stores all actors in the CSV file. To construct the Graph, I run through the Hash Table, and if there is a movie stored at index [i], I get all actors that worked in that movie, separating them using stringstream, and taking care of the spaces between the commas and the actors's names. I then create a new Actor* node and add the movie to that actor. I also add a connection between all actors that acted in that specific movie. After doing this, I also verify if there are more movies linked at index [i] due to collisions, and add those actors to the Graph as well. With this Graph, it is possible to search for the number of movies by an actor, list all of these movies, and find the number of movies separating two actors.