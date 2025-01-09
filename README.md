
Online E-Commerce Store

Introduction

The main idea of this project is to order products from the information provided. This project will focus on the development of a system for an online store that specializes in selling Samsung Phones. The system will be designed to streamline the process of managing inventory, processing orders, and handling customer information.

The project will utilize data structures and algorithms to manage the store's inventory and process orders efficiently. The system will also include features of a user-friendly interface for customers.

In addition to the features mentioned previously, this project will also incorporate the use of various data structures to enhance the efficiency and performance of the system.

Overall, this project will demonstrate the practical application of various data structures and algorithms in the design and development of an online shopping store management system that deliver and takeaway Samsung Phone, by providing efficient and optimized solutions for data storage, retrieval, and pathfinding

Implemented Data Structures

• Linked List:

Linked lists are a data structure that allows for efficient insertion and deletion of elements.

Reason

The program uses linked lists to manage customer information and orders. The data of the user (Delivery, Take Away) is saved in the linked List. We used a Linked List instead of an array because of dynamic size.

• AVL (Adelson-Velsky and Landis) tree:

The AVL tree is a self-balancing binary search tree that is well-suited for storing large amounts of data and allows for fast insertion, deletion, and search operations.

Reason

The AVL, for example, will be used to efficiently manage and maintain the store's inventory. All the operations of takeaway users are handled using the AVL tree. The operations like searching, deletion, and insertion are done in a better way. The insertion and deletion are done by the order ID that is given by the user.


• Graphs:

Graphs have been used in the project to show the areas where the parcel can be delivered. Graphs are represented through an adjacency matrix.

![Screenshot 2025-01-09 055409](https://github.com/user-attachments/assets/b01076bd-265b-4a97-810c-8b1c6a6f2339)

• Dijkstra’s algorithm:

Dijkstra's algorithm is used to implement efficient searching and navigation within the system. Dijkstra's algorithm is a shortest path algorithm that can be used to find the shortest path between two nodes in a graph. The nodes are represented as cities and this algorithm helps to provide the distance between cities.

Reason

This algorithm is often used in routing and as a subroutine in other graph algorithms. The nodes are represented as cities and this algorithm helps to provide the distance between cities.

![dj](https://github.com/user-attachments/assets/c036d211-713c-4cfc-84f1-cea164d4ddca)

• Prim’s algorithm:

Prim's algorithm can be used to find the minimum spanning tree of a graph. So, it provides the distances between areas in a city.

Reason

Prims is used between areas in a city. The reason for using this is that we wanted to give discount to user and previous distance is not used. The key idea behind Prim's algorithm is that at each step, we are adding a vertex to the tree that is connected to the tree by the minimum-weight edge. This ensures that the tree will have the minimum total weight of any spanning tree that can be formed from the graph.

![prims](https://github.com/user-attachments/assets/d2b0844c-91c4-4b33-9363-7c0e24f5839d)

.Output

![output](https://github.com/user-attachments/assets/464bf5db-af1f-4150-b669-c1277da45484)

1. Display the product and prices

![1](https://github.com/user-attachments/assets/d4632f5a-2c2d-4fef-be7a-92fe72d2a83a)

2. Place order for Take-Away from Warehouse

![2](https://github.com/user-attachments/assets/41e24d03-2b7f-47ac-a635-9aa9c01534f2)

3. Place order for Home Delivery

 ![3](https://github.com/user-attachments/assets/bf8474fb-ebec-4673-afa4-73d5eb855bd6)
 
4. Display all Delivery Orders

![4](https://github.com/user-attachments/assets/5b4d8020-7a74-4dcd-af65-c458ca946719)

5. Display all Take-Away Orders

 ![5](https://github.com/user-attachments/assets/dcbe074e-1fa3-4d9b-8ce9-ba5d0b4b822d)
