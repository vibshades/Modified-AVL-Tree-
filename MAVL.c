#include<stdio.h>
#include<stdlib.h>

typedef struct MAVL_tag
{
	int data;
	int height;
	struct MAVL_tag *prev;
	struct MAVL_tag *next;
	struct MAVL_tag *left;
	struct MAVL_tag *right;
}tree_node;

int height(tree_node *node);
int max(tree_node *p,tree_node *q);
void Coonect(tree_node *par);
tree_node *rightrotate(tree_node *y, tree_node *par);
tree_node *leftrotate(tree_node *y, tree_node *par);
int getbalance(tree_node *node);
void printInOrder(tree_node *root);
void printPreOrder(tree_node *root);
tree_node *MakeNode(int key);
void JoinLeft(tree_node *child, tree_node *par);
void JoinRight(tree_node *child, tree_node *par);
tree_node *Insert(tree_node *root, tree_node *par, int key);
tree_node * min_value_tree_node(tree_node* n);
tree_node *delete_tree_node(tree_node *root ,tree_node *par, int key);
void printlevel(tree_node *root);
tree_node *Nextbhau(tree_node **par, tree_node *child);
void Makelink(tree_node *x, tree_node *par);
void Coonect(tree_node *par);
void PrintTree(tree_node *root);
void level_min_max(tree_node *root ,int level_key);
void search_tree(tree_node *root, int key);
tree_node *readfromfile(tree_node *root);



int height(tree_node *node) //function to return height
{
	int retval = 0;
	if(node!=NULL)
	{
		retval=node->height;
	}
	return retval;
}

int max(tree_node *p,tree_node *q) //function to find max height of two tree from a node
{
	return height(p)>height(q)?height(p):height(q);
} 

//void CoonectTrees(tree_node *parentL, tree_node *parentR, tree_node *LFT, tree_node *RIT);


tree_node *rightrotate(tree_node *y, tree_node *par)
{
	tree_node *x = y->left;
	tree_node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(y->left,y->right)+1;
	x->height = max(x->left,x->right)+1;
	if(par==NULL)
	{
		x->next=x;
		x->prev=x;
		//printf("\n I AM IN leftrotate WITH NO PARENT\n ");
		Coonect(x);
	}
	else
	{
		if(par->left==y)
		{
			par->left = x;
		}
		else if(par->right==y)
		{
			par->right = x;
		}
		Coonect(par);
		//printf("\n I AM IN leftrotate WITH SOME PARENT\n ");
	}
	return x;
}

tree_node *leftrotate(tree_node *y, tree_node *par)
{
	tree_node *x = y->right;
	tree_node *T2 = x->left;
	x->left = y;
	y->right = T2;
	y->height = max(y->left,y->right)+1;
	x->height = max(x->left,x->right)+1;
	if(par==NULL)
	{
		x->next=x;
		x->prev=x;
		//printf("\n I AM IN leftrotate WITH NO PARENT\n ");
		Coonect(x);
	}
	else
	{
		if(par->left==y)
		{
			par->left = x;
		}
		else if(par->right==y)
		{
			par->right = x;
		}
		//printf("\n I AM IN leftrotate WITH SOME PARENT\n ");
		Coonect(par);
	}
	return x;
}

int getbalance(tree_node *node)
{
	int retval=0;
	if(node != NULL)
	{
		//	printf("\nFor %d left height is %d",node->data, height(node->left));
		//	printf("\nRight height is %d\n", height(node->right));

		 	retval=height(node->left)-height(node->right);
	}
	//printf("....%d....return value...",retval);
	return retval;
}

void printInOrder(tree_node *root)
{
	if(root!=NULL)
	{
		printInOrder(root->left);
		printf("(%d)",root->data);
		printInOrder(root->right);
	}
}

void printPreOrder(tree_node *root)
{
	if(root!=NULL)
	{
		printf("[%d]",root->data);
		printPreOrder(root->left);
		printPreOrder(root->right);
	}
}

tree_node *MakeNode(int key)
{
	tree_node *retval = (tree_node *)malloc(sizeof(tree_node));
	retval->data = key;
	retval->prev = NULL;
	retval->next = NULL;
	retval->left = NULL;
	retval->right = NULL;
	retval->height=1;
	return retval;
}

void JoinLeft(tree_node *child, tree_node *par)
{
	tree_node *leftBro=NULL;
	tree_node *leftkaka=NULL;
	if(par==NULL)
	{
		leftBro = child;
	}
	else if(par->left!=NULL && par->left!= child)
	{
		leftBro = par->left;
	}
	else
	{
	//	printf("I am in else of leftjoin\n");
		leftkaka=par->prev;
		//printf("I am leftkaka--%d\n",leftkaka->data);
		//printf(" I should be leftBro--%d\n",leftkaka->right->data);
		leftBro = leftkaka->right?leftkaka->right:leftkaka->left;
		//printf(" and I am leftBro--%d",leftBro->data);
		while(leftBro==NULL)
		{
			leftkaka=leftkaka->prev;
			leftBro = leftkaka->right?leftkaka->right:leftkaka->left;
		}
	//	printf("I have finished else of leftjoin\n");
	}
	leftBro->next = child;
	child->prev = leftBro;
}

void JoinRight(tree_node *child, tree_node *par)
{
	tree_node *RightBro;
	tree_node *Rightkaka;
	if(par==NULL)
	{
		RightBro = child;
	}
	else if(par->right!=NULL && par->right != child)
	{
		RightBro = par->right;
	}
	else
	{
		//printf("I am in else of rightjoin\n");
		Rightkaka=par->next;
		//printf("I am the Rightkaka--%d\n",Rightkaka->data);
		RightBro = Rightkaka->left?Rightkaka->left:Rightkaka->right;
		while(RightBro==NULL)
		{
		//printf("beep..beep!!");
			Rightkaka = Rightkaka->next;
			RightBro = Rightkaka->left?Rightkaka->left:Rightkaka->right;
		}
		//printf("I have finished else of rightjoin\n");	
	}
	RightBro->prev = child;
	child->next = RightBro;
}

tree_node *Insert(tree_node *root, tree_node *par, int key)
{
	//\printf("%d is key",key);
	tree_node *retval=NULL;
	int balance;
	if(root==NULL && par==NULL)
	{
		//printf("  I am in ");
		retval = MakeNode(key);
		JoinLeft(retval,par);
		JoinRight(retval,par);
	}
	else if(root==NULL)
	{
		retval = MakeNode(key);
	}
	else
	{
		if(key < root->data)
		{
			root->left = Insert(root->left,root,key);
			JoinLeft(root->left,root);
			JoinRight(root->left,root);
		}
		else if(key > root->data)
		{
			root->right = Insert(root->right,root,key);
			JoinLeft(root->right,root);
			JoinRight(root->right,root);
		}
		root->height = 1 + max(root->right,root->left);
		balance = getbalance(root);
		//printf(" %d  I am th balance",balance);
		if(balance > 1 && key < root->left->data)
		{
			retval = rightrotate(root,par);
		} 
		else if(balance < -1 && key > root->right->data)
		{
			retval = leftrotate(root,par);
		} 
		else if(balance > 1 && key > root->left->data)
		{
			root->left = leftrotate(root->left,root);
			retval = rightrotate(root,par);
		} 
		else if(balance < -1 && key < root->right->data)
		{
			root->right = rightrotate(root->right,root);
			retval = leftrotate(root,par);
		} 
		else
		{
			retval = root; 
		}
	}
	return retval;
}

tree_node * min_value_tree_node(tree_node* n)
{
    tree_node *current = n;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {    
    	current = current->left;
 	}
    return current;
}


tree_node *delete_tree_node(tree_node *root ,tree_node *par, int key)
{
	tree_node *prevn,*nextn;
	tree_node *retval=NULL;
	if( root == NULL)
	{
		retval=root;
		//return root;
	}
	
	// If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    else
    {
	   	if( key < root->data)
	    {
	    	root->left = delete_tree_node(root->left, root, key);
	    }
	    // If the key to be deleted is greater than the root's key, then it lies in right subtree
	    else if(key > root->data)
	    {
	    	root->right= delete_tree_node(root->right, root, key);
		}
		// if both are equal then we delete the tree_node
		else
		{
			//case 1 tree_node with only one child or no child
			if( (root->left==NULL)  || (root->right==NULL))
			{
				tree_node *temp;
				temp = root->left ? root->left : root->right ;

				//No child case
				if (temp==NULL)
				{
					prevn = root->prev;
					nextn = root->next;
					if(prevn && nextn)
					{	
						prevn->next = nextn;
						nextn->prev = prevn;
					}	
					temp=root;
					root=NULL;
					free(temp);
				}
				else //one child case
				{

					*root = *temp;  //copying the contents
					free(temp);
					if(par!=NULL)
					{
						Coonect(par);
					}
					else
					{
						root->next = root;
						root->prev = root;
					}
				}
			}

			else // two children case
			{
				//we take the smallest element in the right subtree
				tree_node *temp2;
				temp2 = min_value_tree_node(root->right);
				root->data = temp2->data;
				root->right = delete_tree_node(root->right ,root, temp2->data ); 
				if(par==NULL)
				{
					root->prev = root;
					root->next= root;
					Coonect(root);
				}
				else
				{
					Coonect(par);
				}

			}
		}

		//if tree had only one tree_node
		if(root==NULL)
		{
			retval=root;
		}
		else
		{
			//STEP 2: UPDATE the height
			root->height= 1 + max(root->left,root->right);

			//STEP 3: GEt the balance factor of this tree_node (check whether it became unbalanced)
			int bal2= getbalance(root);

			//1.LL
			if(bal2 > 1  && getbalance(root->left)>=0 )
			{
				retval=rightrotate(root,par);
				
			}
			else if(bal2>1 && getbalance(root->left)<0 )
			{
				//LR
				root->left = leftrotate(root->left,root);
				retval=rightrotate(root,par);
				
			}
			else if( bal2<-1 && getbalance(root->right)<=0 )
			{
				//RR
				retval=leftrotate(root,par);
				
			}
			else if(bal2<-1 && getbalance(root->right)>0)
			{
				root->right = rightrotate(root->right,root);
				retval=leftrotate(root,par);
				
			}
			else
			{
				//bal2==0
				retval=root;
			}
		}
	}
	return retval;
	//return root;

}

void printlevel(tree_node *root)
{
	tree_node *trav=root;
	tree_node *levelhead=root;
	tree_node* child;
	do
	{
		child = trav->left?trav->left:trav->right;
			do
			{
				printf(" %d ",trav->data);
				trav=trav->next;
				if(child==NULL)
				{
					child = trav->left?trav->left:trav->right;
				}
			}while(trav!=levelhead);
			trav=child;
			levelhead=child;
	}while (child!=NULL);	
}


tree_node *Nextbhau(tree_node **par, tree_node *child)
{
	tree_node *nextbhau = NULL;
		if(child == (*par)->left)
		{
			nextbhau = (*par)->right;
		}
		while(nextbhau == NULL)
		{
			(*par) = (*par)->next;
			nextbhau = (*par)->left?(*par)->left:(*par)->right;
		}
	return nextbhau;
}

/*void Makelink(tree_node *x, tree_node *par)
{
	if(par==NULL)
	{
		x->next=x;
		x->prev=x;
		//printf("\n I AM IN leftrotate WITH NO PARENT\n ");
		Coonect(x);
	}
	else
	{
		Coonect(par);
		//printf("\n I AM IN leftrotate WITH SOME PARENT\n ");
	}
}*/

void Coonect(tree_node *par)
{
	while(par->data > (par->prev)->data)
	{
		par = par->prev;
	}
	tree_node *levelhead = par;
	tree_node *childhead = NULL;
	tree_node *prechild, *currchild;
	do
	{
		childhead = par->left?par->left:par->right;
		par = par->next;
	}while(childhead == NULL && par != levelhead);

	par = par->prev;

	if(childhead)
	{
		prechild = childhead;
		//printf("\n MAI BAAP HU..%d \n",par->data);
		//printf("\n {I AM THE CHILD HEAD %d} : \n",childhead->data);
		currchild = Nextbhau(&par,prechild);
		do
		{
			//if(currchild)
			//{
				prechild->next = currchild;
				currchild->prev = prechild;
				prechild = currchild;
				//printf("(AND I AM CURRENT CHILD %d)\n",currchild->data);

			//}
			currchild = Nextbhau(&par,prechild);
		}while(currchild != childhead);
		prechild->next = currchild;
		currchild->prev = prechild;
		Coonect(childhead);
	}
	//printf("\n [CONNECTED] \n");
}

void PrintTree(tree_node *root)
{
	if(root==NULL)
	{
		printf("the tree is currently empty\n");
	}
	else
	{
		printf("\nInOrder : ");
		printInOrder(root);
		printf("\nPreOrder : ");
		printPreOrder(root);
		printf("\nLevelBased : ");
		printlevel(root);
	}
}


void level_min_max(tree_node *root ,int level_key)
{
	int count=1;
	tree_node *p=root;
	//printf("height %d\n",height(root));
	//printf("level_key %d\n",level_key);
	if(level_key <= height(root))
	{	
		//printf("inside if--\n");
		while(count<level_key)
		{
			//printf("inside outer while. count : %d \n",count);
			while((count<level_key) && (p->left!=NULL || p->right!=NULL))
			{
				//printf("inside inner while. count : %d \n",count);
				//printf("root : %d\n",root->data);
				p=p->left?p->left:p->right;
				count++;	
			}
			//printf("count outside inner while : %d\n",count );
			if(p->left==NULL  && p->right==NULL && count<level_key)
			{
				p=p->next;
			}
			else if(count==level_key)
			{	
				do
				{
					printf("%d  ",p->data);
					p=p->next;
				}while(p->data > p->prev->data);

				printf("Minimum is %d\n",p->data);
				printf("Maximum is %d\n",p->prev->data);
			}
			else
			{
				printf("Level doesn't Exist\n");
			}
		}
	}
	else
	{
		printf("level exceeds number of levels present in tree\n");
	}	
}


void search_tree(tree_node *root, int key)
{
	int level=0,found=0,count=1;
	tree_node *p=root;
	while(p!=NULL && found==0)
	{
		if(key < p->data)
		{
			p=p->left;
		}
		else if(key > p->data)
		{
			p=p->right;
		}
		else
		{
			found=1;
		}
		level++;
	}
	if(found!=0)
	{
		while(p->data > p->prev->data)
		{
			p=p->prev;
			count++;
		}
		printf("On level %d , the Required Node is %d Position\n",level,count);
	}
	else
	{
		printf("Element Not Found\n");
	}
}


tree_node *readfromfile(tree_node *root)
{
	FILE *fin;
	int elem;
	root=NULL;
	fin=fopen("treeinput.txt","r");
	if(fin==NULL)
		{
			printf("\n***********************************ERROR IN READING FILE*********************************************\n");
		}
		else
		{	
			char ch = getc(fin);
			while(ch!= EOF)
			{
				fscanf(fin,"%d\n",&elem);
				printf("%d\n",elem);
				ch = getc(fin);
				root = Insert(root,NULL,elem);
			}
		}
		fclose(fin);

return root;

}


void main()
{


	tree_node *root=NULL;
	int num,i=0,input_choice=0;

	int choice=0,menu1=0,elem;
	char c='Y',c2='Y';

	//Creation of List

	printf("\n Read from File or Manual Input\n");
	printf("1.Read from file\n");
	printf("2.Console Input\n");
	scanf("%d",&input_choice);

	switch(input_choice)
	{
		case 1: printf("File Input\n");
				root=readfromfile(root);
				PrintTree(root);
				break;

		case 2:printf("Console Input\n");
				printf("Enter the number of Elements of the tree\n");
				scanf("%d",&num);
			do
			{
				printf("Enter Element\n");
				fflush(stdin);
				scanf("%d",&elem);
				//insert function;
				root = Insert(root,NULL,elem);
				i++;
			}while(i<num);

		default: printf("Wrong Choice \n");
					break;
	}

	//Now Tree has been Prepared


	do
	{
		do
		{
			printf("\n**********************************************************\n");
			printf("1.Search an Element\n");
			printf("2.Insert an Element\n");
			printf("3.Delete an Element\n");
			printf("4.Min Max\n");
			printf("5.Print the tree\n");
			printf("6.Do as provided\n");
			printf("Enter your choice\n");
			fflush(stdin);
			scanf("%d",&choice);

			switch(choice)
			{
				case 1: printf("You chose to search an Element\n");
						printf("Enter to Search\n");
						int search_key;
						fflush(stdin);
						scanf("%d",&search_key);
						search_tree(root,search_key);

						menu1=1;
						break;

				case 2: printf("You chose to Insert a New Element\n");
						printf("Element to Insert\n");
						int insert_key;
						fflush(stdin);
						scanf("%d",&insert_key);
						root = Insert(root,NULL,insert_key);
						menu1=1;
						break;

				case 3: printf("You chose to Delete an Element\n");
						printf("Element to Delete\n");
						int delete_key;
						fflush(stdin);
						scanf("%d",&delete_key);
						root = delete_tree_node(root,NULL,delete_key);
						menu1=1;
						break;

				case 4: printf("You chose Level Based Traversal along with Min and Max\n");
						printf("Level to Print\n");
						int level_key;
						fflush(stdin);
						scanf("%d",&level_key);

						level_min_max(root,level_key);


						menu1=1;
						break;

				case 5: PrintTree(root);
						break;
				
				case 6: /*root=root->left;
						root=root->left;
						printf("\n %d ",root->data);
						root=root->next;
						printf(" %d ",root->data);
						root=root->next;
						printf(" %d ",root->data);
						root=root->next;
						printf(" %d ",root->data);
						root=root->next;
						printf(" %d \n",root->data);
						root=root->prev;
						printf(" %d ",root->data);
						root=root->prev;
						printf(" %d ",root->data);
						root=root->prev;
						printf(" %d ",root->data);
						root=root->prev;
						printf(" %d ",root->data);
						root=root->prev;
						printf(" %d \n",root->data);*/
						printf("%d ",root->data);
						root=root->next;
						printf("%d ",root->data);


						break;
					
				default: printf("Wrong Choice Try Again \n");
						 menu1=0;
						break;
			}

		}while(menu1==0);

		printf("\n Wanna Try Again?\n");
		fflush(stdin);
		scanf("%c",&c);

	}while(c=='y' || c=='Y');
}

