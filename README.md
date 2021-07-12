# Content-Recommender-System 
This system shows the contents which will be recommended to a user based on other users and the contents shared by them.

An input file contains the user (numeric) connected to other users and the contents (numeric) shared by each one of them.

An adjacency list, which is implemented using an array of linked lists, is created and every node is initially assigned NULL.

The input file is read and every node (user) connected to another is inserted in the adjacency list and a graph is created.
Also the contents shared by each user are also inserted into the list.

Once the graph is created, it is traversed using breadth first search algorithm in which a queue, implemented using linked list, is used.
One visited array is created which stores info whether a node is visited or not.  
Another array named contents is created which shows whether contents will be shown to a user or not.

Two inputs U and K are taken where U is the user for whom contents are to be recommended and K is the distance in the graph up to which contents are to be recommended.
During traversal, if the distance exceeds K then the loop exits and the recommended contents are printed.

Once the system has printed the output, the memory allocated for the linked list is freed and program terminates.


![ss1](https://user-images.githubusercontent.com/50799286/125318902-e9da7480-e357-11eb-9a36-425498b7a692.jpg)


![ss2](https://user-images.githubusercontent.com/50799286/125319035-09719d00-e358-11eb-8c76-400f9900272b.jpg)
