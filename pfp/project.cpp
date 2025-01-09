#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#define size 50
#define V 11 // preprocessor directive that defines constant named v with 11 value. 
#define V1 6
struct user
{
    string name;//It is intended to store the name of the user.
    string product;//  It is intended to store the name of the product purchased by the user.
    int quantity; // It is intended to store the quantity of the product purchased by the user.
    double bill; //It is intended to store the total bill amount for the product purchased by the user.

    user() {}// default constructor

    user(string name, string product, int quantity, double bill)
    {
        this->name = name;
        this->product = product;
        this->quantity = quantity;
        this->bill = bill;
    }
};
struct deliveryUser
{
    user nUser;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    deliveryUser *next = NULL;//each deliveryUser can point to the next user in the list.

    deliveryUser(string name, string product, int quantity, double bill, string address, double deliveryCharges, int distanceDelivery)
    {
        this->nUser = user(name, product, quantity, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};
struct Shop
{
    string name;
    string *product;
    int *price;
    string address;
    deliveryUser *nextdeliveryUser;
};
Shop* shop=NULL;
string addressF;
int dist[V];
int distanceP[V1];
int optionDelivery = -999;
int optionDelivery1 = -999;
deliveryUser *currentdeliveryUser = NULL;

struct takeAway
{
    string name;
    string product;
    int quantity;
    double bill;
    int orderId;
    takeAway *left;
    takeAway *right;
    
    //takeAwayfromStore *next = NULL;

    takeAway(string name, string product, int quantity, double bill, int orderId)
    {
        this->name=name;
		this->product = product;
        this->quantity = quantity;
        this->bill = bill;
        this->orderId=orderId;
        this->left = NULL;
        this->right = NULL;
    }
};

takeAway *root = NULL; 

void display(takeAway *root)
{
	cout <<"\n----------------------------------"<< endl;
    cout << "Name :" << root->name << endl;
    cout << "product :" << root->product << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Order ID: " << root->orderId << endl;
    cout <<"-----------------------------------\n"<< endl;
}
takeAway *displayTakeAway(takeAway *root)
{

    if (root)
    {
        displayTakeAway(root->left);
        display(root); 
        displayTakeAway(root->right);
    }

    return root;
}
// isEmpty or not
int isEmpty(takeAway *root)
{
    return root == NULL;
}


// Height of takeAway tree
int height(takeAway* root) {
	if (root == NULL)
      return -1;
    else {
      int leftH = height(root -> left);
      int rightH = height(root -> right);

    return (1+max(leftH , rightH));
	}
}

// Balance Factor for each takeAway node
int balanceFactor(takeAway *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Maximum of two integers as a helper function for height
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Searching in takeAway tree

takeAway *search(takeAway *root, int id)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->orderId == id)
    {
        return root;
    }
    else if (root->orderId < id)
    {
        return search(root->right, id);
    }
    else if (root->orderId > id)
    {
        return search(root->left, id);
    }

    return root;
}

// Balancing the takeAway's Tree thorugh AVL Rotations

// LL Rotation
takeAway *LLRotation(takeAway *root)
{
    takeAway *x = root->left;
    takeAway *temp = x->right;

    x->right = root;
    root->left = temp;

    root = x;

    return x;
}

// RR Rotation
takeAway *RRRotation(takeAway *root)
{

    takeAway *x = root->right;
    takeAway *temp = x->left;

    x->left = root;
    root->right = temp;

    root = x;

    return x;
}

// LR Rotation
takeAway *LRRotation(takeAway *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
takeAway *RLRotation(takeAway *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

//  INSERTION in takeAway Tree

takeAway *insertion(string name, int quantity, string product, double bill, int orderId, takeAway *root)
{
    takeAway *newNode = new takeAway(name,  product, quantity, bill, orderId);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->orderId > newNode->orderId)
    {
        root->left = insertion(name, quantity, product, bill, orderId, root->left);
    }
    else if (root->orderId < newNode->orderId)
    {
        root->right = insertion(name, quantity, product, bill, orderId, root->right);
    }

    else
    {
        cout << "No duplicates Values are Allowed " << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->orderId > newNode->orderId)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->orderId < newNode->orderId)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->orderId < newNode->orderId)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->orderId > newNode->orderId)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

takeAway * minValue(takeAway *root) {
    takeAway *current = root;
    while (current-> left != NULL) {
      current = current -> left;
    }
    return current;
  }

takeAway *deleteNode(takeAway *root, int orderId)
{
    if (root == NULL)
        return root;
    else if (orderId < root->orderId)
        root->left = deleteNode(root->left, orderId);
    else if (orderId > root->orderId)
        root->right = deleteNode(root->right, orderId);
    else {
      if (root-> left == NULL) {
        takeAway* temp = root-> right;
        delete root;
        return temp;
      } 
	  else if (root-> right == NULL) {
        takeAway* temp = root-> left;
        delete root;
        return temp;
      } 
      
	  else {
        takeAway * temp = minValue(root-> right);
        root-> orderId = temp -> orderId;
        root-> right = deleteNode(root-> right, temp-> orderId );
      }
    }

    // getting the balance factor
    int balance = balanceFactor(root);

    // Rotation Cases
    // LEFT LEFT CASE
    if (balance > 1 && orderId < root->left->orderId)
        return LLRotation(root);

    // LEFT RIGHT CASE
    if (balance > 1 && orderId > root->left->orderId)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    // RIHGT RIGHT CASE
    if (balance < -1 && orderId > root->right->orderId)
        return RRRotation(root);

    // RIGHT LEFT CASE
    if (balance < -1 && orderId < root->right->orderId)
    {
        return RLRotation(root);
    }

    return root;
}
void placeOrderHomeDeliveryCustomer(string name, string product, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{

    currentdeliveryUser=new deliveryUser(name, product, quantity, bill, address, deliveryCharges, distanceDelivery);
    
    if (shop->nextdeliveryUser == NULL)
    {
        // if first insert in front
        shop->nextdeliveryUser= currentdeliveryUser;
    }
    else
    {
        // finding the last Node
        deliveryUser *temp = shop->nextdeliveryUser;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentdeliveryUser;
        currentdeliveryUser->next = NULL;
    }
    
   	cout << "\n***************Order Details***************";
    cout << "\n Customer Name : " << name << "\n Order name : " << product << "\n Quantity : " << quantity << "\n Total bill : " << bill;
    cout << "\n Address : " << address << "\n Distance in km : " << distanceDelivery <<"\n Delivery charges : " << deliveryCharges << endl;
}


void displayAllOrdersHomeDeliveryCustomers()
{
    if (shop->nextdeliveryUser == NULL)
    {
        cout << "There is no Order for Home Delivery Customer till yet" << endl;
    }
    else
    {
        deliveryUser *traversal = shop->nextdeliveryUser;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery Customer : " << traversal->nUser.name << endl;
            cout << "Product Name : " << traversal->nUser.product << endl;
            cout << "Quantity : " << traversal->nUser.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM"<<endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->nUser.bill << " RS/_" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
    
}





//-----------------------------------------------------------------------------------

int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}



void dijkstra(int graph[V][V], int dist[], int src)
{
    bool visited[V]; 

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);

        visited[u] = true;
        
        for (int v = 0; v < V; v++)

            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                	dist[v] = dist[u] + graph[u][v];
    }
}

//-----------------------------------------------------------------------------------

int minKey(int distanceP[], bool visitedP[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V1; v++)
		if (visitedP[v] == false && distanceP[v] < min)
			min = distanceP[v], min_index = v;

	return min_index;
}

void printMST(int parent[], int graph[V1][V1])
{
	cout << "Edge \tWeight\n";
	for (int i = 1; i < V1; i++)
		cout << parent[i] << " - " << i << " \t"
			<< graph[i][parent[i]] << " \n";
}

void prims(int graph[V1][V1], int distanceP[])
{
	int parent[V1];
	bool visitedP[V1];

	for (int i = 0; i < V1; i++)
		distanceP[i] = INT_MAX, visitedP[i] = false;

	distanceP[0] = 0;
	parent[0] = -1; 

	for (int count = 0; count < V1 - 1; count++) {

		int u = minKey(distanceP, visitedP);

		visitedP[u] = true;

		for (int v = 0; v < V1; v++)

			if (graph[u][v] && visitedP[v] == false && graph[u][v] < distanceP[v])
				parent[v] = u, distanceP[v] = graph[u][v];
	}

}
string CityName[] = {"WareHouse", "Patna ","Muzaffarpur", "Gaya", "Hajipur", "jehanabad", "Sasaram", "Siwan", "Chapra", "Bihar sarif ","Rohtas"};

string Patna[]={"patna", "Gulzarbagh", "Rajendranagar", "Fatuha", "PMCH", "Patnajunction"};
//string *Pat = new string[6]{"patna", "Gulzarbagh", "Rajendranagar", "Fatuha", "PMCH", "Patnajunction"};
//string *Gaya = new string[6]{"Gaya", "Imalichatti", "Jail chowk ", "Dharampur", "Silo", "Medical college"};

string Muzaffarpur[]={"Motijheel", "Kalambaghchowk" ,"Kampanibaghroad", "Jail chowk", "Medical college", "Muzaffarpur junction"};

string Hajipur[]={"Hajipur", "Paswan chowk", "Adalpur", "Konharaghat", "Mahua", "Bhagwanpur"};

string Gaya[]={"Gaya", "Imalichatti", "Jail chowk ", "Dharampur", "Silo", "Medical college"};

int graph[V][V]={   {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 3},   //Warehouse
					{4, 0, 0, 0, 0, 0, 0, 6, 0, 0, 2},	 //Patna    
					{0, 0, 0, 0, 9, 4, 0, 0, 0, 0, 11},	 //Muzaffarpur
					{0, 0, 0, 0, 1, 0, 0, 0, 16, 5, 0},	 //Gaya
					{0, 0, 9, 1, 0, 8, 13, 0, 10, 6, 0}, // Hajipur	
					{0, 0, 4, 0, 8, 0, 0, 3, 17, 0, 7},	 //Jehanabad
					{0, 0, 0, 0, 13, 0, 0, 0, 0, 0, 7},	 //Sasaram
					{0, 6, 0, 0, 0, 3, 0, 0, 5, 0, 0},	 //Siwan
					{0, 0, 0, 16, 10, 17, 0, 5, 0, 0, 0},//Chapra
					{0, 0, 0, 5, 6, 0, 0, 0, 0, 0, 0},	 //Bihar sarif
					{3, 2, 11, 0, 0, 7, 7, 0, 0, 0, 0}  };//Rohtas
					
//----------------------Patna--------------------------------				
int PatGraph[V1][V1]={ 	{ 0, 4, 4, 0, 0, 0 },  //patna
						{ 4, 0, 2, 0, 0, 0 },   //Gulzarbagh
						{ 4, 2, 0, 3, 2, 4 },	//Rajendranagar
						{ 0, 0, 3, 0, 0, 3 },	// fatuha
						{ 0, 0, 2, 0, 0, 3 },	//PMCH
						{ 0, 0, 4, 3, 3, 0 } };	// patnajunction
						
//---------------------Muzaffarpur------------------------------------
int MuzGraph[V1][V1]={ 	{ 0, 4, 0, 2, 0, 0 },//Muzaffarpur
						{ 4, 0, 3, 1, 0, 6 },	//Motijheel
						{ 0, 3, 0, 4, 0, 7 },	//kalambaghchowk
						{ 2, 1, 4, 0, 9, 0 },	//kampanibaghroad
						{ 0, 0, 0, 9, 0, 5 },	//jail chowk
						{ 0, 6, 7, 0, 5, 0 } };	//medical college

//-----------------------Hajipur---------------------------------------
int HajGraph[V1][V1]={ 	{ 0, 9, 15, 6, 0, 0 },// hajipur
						{ 9, 0, 7, 0, 0, 8 },// paswan chowk
						{ 15, 7, 0, 8, 9, 5 },//Adalpur
						{ 6, 0, 8, 0, 11, 0 },//konharaghat
						{ 0, 0, 9, 11, 0, 0 },// Mahua
						{ 0, 8, 5, 0, 0, 0 } };	// Bhagwanpur

//----------------------Gaya----------------------------------------
int GayGraph[V1][V1]={ 	{ 0, 6, 3, 0, 0, 1 },   //Gaya
						{ 6, 0, 0, 2, 0, 5 },	//imalichatti
						{ 3, 0, 0, 0, 3, 5 },	//jail chowk
						{ 0, 2, 0, 0, 6, 4 },	//Dharampur
						{ 0, 0, 3, 6, 0, 6 },	//silo
						{ 1, 5, 5, 4, 6, 0 } };	//medical college
//----------------------------------------------------------------------------------

int city(){
	int opt;
	cout << "\nThe delivery is available for following Areas : \n" << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |       City        |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Patna          |"<<endl;
    cout<<"\n |     2    |    Muzaffarpur    |"<<endl;
    cout<<"\n |     3    |    Gaya           |"<<endl;
	cout<<"\n |     4    |    Hajipur        |"<<endl;
    cout<<"\n |     5    |    Jehanabad      |"<<endl;
    cout<<"\n |     6    |    Sasaram        |"<<endl;
    cout<<"\n |     7    |    Siwan          |"<<endl;
    cout<<"\n |     8    |    Chapra         |"<<endl;
	cout<<"\n |     9    |    Bihar sarif    |"<<endl;
    cout<<"\n |    10    |    Rohtas         |"<<endl;
    cout<<"---------------------------------\n"<<endl;

    

	cout << "Enter your City Code (between 1 to 10) :" << endl;
    cin >> opt;
    return opt;
}
int Pat(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Patna: " << endl;
    
    cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Gulzarbagh     |"<<endl;
    cout<<"\n |     2    |    Rajendrnagar   |"<<endl;
    cout<<"\n |     3    |    Fatuha         |"<<endl;
	cout<<"\n |     4    |    PMCH           |"<<endl;
    cout<<"\n |     5    |    patnajunction |"<<endl;
    cout<<"---------------------------------\n"<<endl;
    cout << "Enter your city Code(between 1 to 5) :" << endl;
    cin >> opt;
    return opt;
                              
}
int Muz(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Muzaffarpur: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Motijheel      |"<<endl;
    cout<<"\n |     2    |    Kalambagh      |"<<endl;
    cout<<"\n |     3    |    kampanibagh    |"<<endl;
	cout<<"\n |     4    |    Jail chowk     |"<<endl;
    cout<<"\n |     5    |    Medical college|"<<endl;
    cout<<"---------------------------------\n"<<endl;
    
    cout << "Enter your City Code(between 1 to 5) :" << endl;
    cin >> opt;
    return opt;
                              
}
int Haj(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Hajipur: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |    Paswan chowk   |"<<endl;
    cout<<"\n |     2    |    Adalpur        |"<<endl;
    cout<<"\n |     3    |    konharaghat   |"<<endl;
	cout<<"\n |     4    |    Mahua          |"<<endl;
    cout<<"\n |     5    |    Bhagwanpur     |"<<endl;
    cout<<"---------------------------------\n"<<endl;
	
    
    cout << "Enter your City Code(between 1 to 5) :" << endl;
    cin >> opt;
    return opt;
                              
}
int Gay(){
	int opt;
	cout << "\nThe delivery is available for following Areas in Gaya: " << endl;
	
	cout<<"\n---------------------------------";
	cout<<"\n |CITY CODE |        AREA       |";
	cout<<"\n---------------------------------";
    cout<<"\n |     1    |  Imalichatti      |"<<endl;
    cout<<"\n |     2    |  Jail chowk       | "<<endl;
    cout<<"\n |     3    |  Dharampur        |"<<endl;
	cout<<"\n |     4    |  Silo             |"<<endl;
    cout<<"\n |     5    |  Medical college  |"<<endl;
    cout<<"---------------------------------\n"<<endl;
    
    cout << "Enter your City Code(between 1 to 5)  :" << endl;
    cin >> opt;
    return opt;                             
}
int FurthurArea(int option){
	int opt;
	switch(option){
			
			case 1: 
			{
				prims(PatGraph,distanceP);
				opt=Pat();
				addressF=Patna[opt];
			}
			break;
			
			case 2:
			{
				prims(MuzGraph,distanceP);
				opt=Muz();
				addressF=Muzaffarpur[opt];
			}
			break;
			case 3:
			{
				prims(GayGraph,distanceP);
				opt=Gay();
				addressF=Gaya[opt];
			}
			break;
            case 4:
			{
				prims(HajGraph,distanceP);
				opt=Haj();
				addressF=Hajipur[opt];
			}
			break;
		}
		
	return opt;
}
int main()
{
	shop =new Shop;
	shop->name="Samsung Mobile Mart";
	shop->address="Gandhi Maidan road, Patna-800001";

	shop->product=new string[11]{""," Samsung Galaxy A16 5G ", " Samsung Galaxy S24 FE ", "Samsung Galaxy M15 5G Prime Edition     ",
								 "  Samsung Galaxy M55s", "Samsung Galaxy F05"," Samsung Galaxy A06   ",
								  "   Samsung Galaxy M35 5G  ", "   Samsung Galaxy F55 5G   ", "Samsung Galaxy S24",
								"Samsung Galaxy Z Fold 5"};
								
								
	shop->price=new int[11]{0,15835, 59999, 11999, 20999, 6979,8999,15377, 19340, 74999, 95960};
	int choice = -99;

	
	do
    {

        cout << endl;
        cout << "************************  " << shop->name << "  ************************" << endl;
        cout << "Location : " << shop->address << endl;
        cout << endl;

        cout << endl;
        cout << "************************  Operations  ************************" << endl;
        cout << endl;


        // Order placing
        cout << "1. Display the product and prices" << endl;
		cout << "2. Place order for Take-Away from Warehouse" << endl;
        cout << "3. Place order for Home Delivery " << endl;
       // cout << "4. Get Order from Warehouse" << endl;
        cout << "4. Display all Delivery Orders" << endl;
        cout << "5. Display all Take-Away Orders" << endl;
        cout << "0.  EXIT " << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        // for taking input of Customer Details
        string name;
        int quantity;
        int productNumber;
        double bill;
        string address;
        int orderId;
        int distance;
         switch (choice)
        {
        
        //--------------------------------CASE 1-----------------------------------------------------
        case 1:
		{
		
		cout<<"\n---------------------------------------------------------------------";
        cout<<"\n | ITEM NO. |             ITEM NAME               | ORIGINAL PRICE  |";
        cout<<"\n---------------------------------------------------------------------";
        cout<<"\n |    1     | 		  Samsung Galaxy A16 5G        |       15835     |"<<endl;
        cout<<"\n |    2     | 		   Samsung Galaxy S24 FE       |       59999     |"<<endl;
        cout<<"\n |    3     | Samsung Galaxy M15 5G Prime Edition |       11999     |"<<endl;
        cout<<"\n |    4     |            Samsung Galaxy M55s      |       20999     |"<<endl;
        cout<<"\n |    5     |          Samsung Galaxy F05         |       6979      |"<<endl;
        cout<<"\n |    6     |             Samsung Galaxy A06      |       8999      |"<<endl;
        cout<<"\n |    7     |             Samsung Galaxy M35 5G   |       15377     |"<<endl;
        cout<<"\n |    8     |              Samsung Galaxy F55 5G  |       19340     |"<<endl;
        cout<<"\n |    9     |                Samsung Galaxy S24   |       74999     |"<<endl;
        cout<<"\n |    10    |           Samsung Galaxy Z Fold 5   |       95960     |";
        cout<<"\n---------------------------------------------------------------------"<<endl;
		}
		break ;	
        	
        	
        //-----------------------------------CASE 2--------------------------------------------------
        case 2:                                   
        { 
			cout << "Enter the name of the customer: ";
            cin >> name;
			cout << "Enter the Item Name: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;
            cout << "Enter orderID of one or two digits: ";
            cin >> orderId;


            bill = quantity * shop->price[productNumber];
            root=insertion(name, quantity, shop->product[productNumber], bill, orderId, root);
            cout <<"\n------------------------------------"<< endl;
            cout << "**** Your order has been placed *****" << endl;
            cout << "Total amount : " << bill << endl;
			cout << "order ID :" << orderId << endl;
            cout << "You can get your order from Warehouse " << endl;
            cout <<"-------------------------------------\n"<< endl;
            
        }
        break;

		//-----------------------------------CASE 3--------------------------------------------------
        case 3:

        {                                               
            dijkstra(graph,dist,0);

            do
            {
                optionDelivery=city();   //Return The index of city that has been selected

            } while (!(optionDelivery >= 0 && optionDelivery <= 10));
            
            
            if(optionDelivery==1 || optionDelivery==2 || optionDelivery==3 || optionDelivery==4 )
			{
            	
            	do
            	{
            		optionDelivery1=FurthurArea(optionDelivery);  //Return index of area in a city
            		
				} while(!(optionDelivery1 >=0 && optionDelivery1 <=5));
				
				address= CityName[optionDelivery] +" " +addressF;
				distance=dist[optionDelivery] + distanceP[optionDelivery1];
				
			}
			else 
			{
				address = CityName[optionDelivery];
				distance=dist[optionDelivery];
				
			}


            cout << "Enter the name of the customer: ";
            cin >> name;
            cout << "Enter the product Number: ";
            cin >> productNumber;
            cout << "Enter the quantity of the product: ";
            cin >> quantity;


            int deliveryChargesPerKM = 20;
            int deliveryCharges = deliveryChargesPerKM * distance;
            bill = quantity * shop->price[productNumber] + deliveryCharges;

            placeOrderHomeDeliveryCustomer(name, shop->product[productNumber], quantity, bill, address, deliveryCharges, distance );
        }
        break;
        
        //-----------------------------------CASE 2--------------------------------------------------
       /* case 4 :
        {
        	// Get Order from Warehouse

            cout << "Enter the Order Id: ";
            cin >> orderId;
			
			takeAway *cust=search(root,orderId);
			
			if (cust == NULL){
			
				cout << "\n----------------------------------"<< endl;
                cout << "No such order is in the Warehouse " << endl;
                cout << "-----------------------------------\n"<< endl;
            }else
			{
				
                root=deleteNode(root,orderId);
                cout << "\n----------------------------------"<< endl;
				cout << "Your order is ready for collection" << endl;
				cout << "  Please get it from the counter" << endl;
				cout << "-----------------------------------\n"<< endl;
			}
		}
		break;*/
		
		//-----------------------------------CASE 5--------------------------------------------------
		case 4 :
		{
			
            displayAllOrdersHomeDeliveryCustomers();
		}
        break;
        
        //-----------------------------------CASE 6--------------------------------------------------
        case  5:
    	{
    	
    		displayTakeAway(root);
			
		}
        break ;
        
    	}
    

    } while (choice != 0);
    cout << "Thank you for Using our Services " << endl;
	return 0;
}

