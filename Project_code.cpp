
/*
	Content Recommender System

	Compilation command : g++ proj.cpp
	Execution Command : ./a.out <input_file> <U> <K>
						Eg. ./a.out input.txt 0 2


*/

#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

//To store the users and contents of Adjacency list
typedef struct node{
	int data;
	node *next;
}list;

//To store the nodes and distances for a BFS queue
typedef struct bfsqueue{
	int data;
	int distance;
	bfsqueue *next;
}queue;

//function to insert a node at the end of the adjacency list
void insert(list **head, int value){
	list *newnode;
	newnode = (list*)malloc(sizeof(list));
	newnode->data = value;
	newnode->next = NULL;
	if(*head == NULL) 
		*head = newnode;
	else {
		list *temp = *head ;
		while(temp->next != NULL){
			temp = temp->next; 
		}
		temp->next = newnode;
	}
}

//function to insert node at the end of a queue 
//the queue is implemented using linked list 

void enqueue(queue **head, int value, int dist){
	queue *newnode;
	newnode = (queue*)malloc(sizeof(queue));
	newnode->data = value;
	newnode->distance = dist;
	newnode->next = NULL;
	if(*head == NULL) 
		*head = newnode;
	else {
		queue *temp = *head ;
		while(temp->next != NULL){
			temp = temp->next; 
		}
		temp->next = newnode;
	}	
}

//function to delete node from the beginning of the queue
void dequeue(queue **head, int *value, int *dist){
	queue *temp,*currnode;
	currnode = *head;
	temp = (*head)->next;
	*value = (*head)->data;
	*dist = (*head)->distance;
	*head = temp;
	free(currnode);

}

//function to delete a node from the beginning of the linked list
int delfrombeg(list **head){
	list *temp,*currnode;
	int val;
	currnode = *head;
	temp = (*head)->next;
	val = (*head)->data;
	*head = temp;
	free(currnode);
	return val;
}

//function to show elements of the queue (if needed)
/*void showQ(queue **head){
	queue *temp = *head;
	while(temp!=NULL){
		cout << temp->data<<" "<<temp->distance<< " -- ";
		temp = temp->next;
	}
	cout<<endl;
}*/

//function to show the adjacency list (if needed)
void showLL(list **head){
	list *temp = *head;
	if(temp == NULL) {
		cout<<"None";
	}
	while(temp!=NULL){
		cout << temp->data<< " ";
		temp = temp->next;
	}
	cout<<endl;
}

//function to free the nodes of the queue
void freeQ(queue *head){
	queue *temp ;
	while(head!=NULL){
		temp = head;
		head = (head)->next;
		free(temp);

	}
	head = NULL;
}

//function to free the nodes of the adjacency list
void freeLL(list *head){
	list *temp ;
	while(head!=NULL){
		temp = head;
		head = (head)->next;
		free(temp);

	}
	head = NULL;
}

//bfs function to traverse the adjacency list
void bfs(list **adjlist, int n, int m, int U, int K){
	queue *Q = NULL;
	int val = -1 , dist = -1; // this will hold the dequeued node and distance 
	int visited[n] = {0} ; // it marks whether a node has been already visited or not
	int contents[m+1] = {0};  // 0 : unvisited , 1 : recommended , -1 : belongs to U 
	enqueue(&Q, U, 0);
	visited[U] = 1;
	while(Q!=NULL){
		dequeue(&Q , &val, &dist);
		if(dist>=K) break;
		//Used to traverse through  the child nodes 
		list *temp = adjlist[val*2]; 
		while(temp!=NULL){
			if(visited[temp->data] == 0){
				//if the node is not visited then enqueue it 
				//(incrementing the distance) and mark it visited 
				enqueue(&Q, temp->data, dist+1);
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
		//used to traverse through the contents of the dequeued node
		temp = adjlist[(val*2)+1];
		while(temp!=NULL){			
			if(val != U && contents[temp->data] != -1){
				//if the node is not U and the content is not shared by U 
				//then it can be recommended to U 
				contents[temp->data] = 1;
			}
			else if(val == U){
				//if the node is U then mark the contents as -1
				//which cannot be recommended to U
				contents[temp->data] = -1;
			}
			temp = temp->next;
		}
	}
	//to free the dynamically allocated queue used
	freeQ(Q);
	//to view the contents recommended to U
	for(int i=0;i<m+1;i++){
		if(contents[i] == 1) cout<<i<<" ";
	}
}

//function to convert string to integer (used for processing the input)
int str2int(char *str){
	int i =0, sum = 0 ;
	while(str[i] != '\0'){
		sum = sum * 10 + (str[i] - 48);
		i++;
	}
	return sum;
}

/* Main function that takes the input file along with
   U(the node to which the contents should be recommended)
   and K(upto what distance the content should be recommended)
*/

int main(int argc, char **argv){
	FILE *ptr;
	ptr = fopen(argv[1], "r"); 
	if(!ptr) printf("Error! Cannot open file.");

	int c, i=0, n;// c reads the file char by char and n is the no of users
	char ch[100];
	//Reading input from the file
	while((c = fgetc(ptr))){
		if(c >=48 && c<= 57){
			ch[i] = (char) c;
			i++; 
		}	
		else if(c == '\n'){
			ch[i] = '\0';
			if(ch[0]!='\0') n = str2int(ch);
			i=0;
			break;
		}	
	}

	//Declaring the adjacency list
	list *adjlist[n*2]; 

	//Initialising the adjacency list 
	for(int i=0;i<n*2;i++){
		adjlist[i] = NULL; 
	}

	// Here ep1 stores the user and ep2 stores the other user who is a friend to user ep1
    int ep1=-1,ep2=-1; 
    int k=0;

    //Reading the friend list from the input file
	while(k<n && (c = fgetc(ptr))){
 		if(c >=48 && c<= 57){
			ch[i] = (char) c;
			i++; 
		}
		else if(c == ':'){
			ch[i] = '\0';
			if(ch[0]!='\0') ep1 = str2int(ch); 
			i=0;
		}

		else if(c == ',' || c == '\n' || c == EOF) {
			ch[i] = '\0';
			i=0;
			if(ch[0]!='\0') {
				ep2 = str2int(ch);
			insert(&adjlist[(ep1*2)+0], ep2);
			}
			if(c=='\n') k++;
			if(c == EOF) break;
			
		}

	}
	
	int m;
	
	//Reading the no of distinct content to be shared
	while((c = fgetc(ptr))){
		if(c >=48 && c<= 57){
			ch[i] = (char) c;
			i++; 
		}	
		else if(c == '\n'){
			ch[i] = '\0';
			if(ch[0]!='\0') m = str2int(ch);
			i=0;
			break;
		}	
	}
	
	ep1=-1,ep2=-1;
    k=0;

    //Reading the contents shared by users from the file
	while((c = fgetc(ptr)) && k<n){
 		if(c >=48 && c<= 57){
			ch[i] = (char) c;
			i++; 
		}
		else if(c == ':'){
			ch[i] = '\0';
			if(ch[0]!='\0') ep1 = str2int(ch); 
			i=0;
		}
		else if(c == ',' || c == '\n' || c == EOF) {
			ch[i] = '\0';
			i=0;
			if(ch[0]!='\0') {
				ep2 = str2int(ch);
				insert(&adjlist[(ep1*2)+1], ep2);
			}
			if(c == '\n') k++;
			if(c == EOF) break;
			
		}

	}


	fclose(ptr);// Closing the input file after reading and storing it in the adjacency list

	cout<< "\nData has been fetched ! "<<endl;
	cout<< "Graph has been created (Using hybrid adjacency list)! "<<endl<<endl;
	char option;
	cout<<"Do you want to view the graph? (Y/N) : ";
	cin>> option;
	if(option == 'Y' || option == 'y'){
		cout<<"\nDisplaying Adjacency List : "<<endl<<endl;
		for(i=0;i<n;i++){
			cout<<"Information of user "<<i<<" "<<endl;
			for(int j=0;j<2;j++){
				if(j == 0) cout<<"Friends  --> ";
				else cout<<"Contents shared --> "; 
				showLL(&adjlist[i*2+j]);
			}
			cout<<endl;
		}
	}

	int U = str2int(argv[2]) , K = str2int(argv[3]);

	cout<<"\nRecommended contents : ";
	bfs(adjlist,n,m,U,K);
	cout<<endl<<endl; 
	
	cout<<"Destroying Graph ..."<<endl;
	for(int i=0;i<n*2;i++){
		freeLL(adjlist[i]);
	}

	cout<<"Graph Destroyed ."<<endl;

return 0;
}
