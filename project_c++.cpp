#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<dos.h>
#include<windows.h>
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

using namespace std;
int cnt=0;


void gotoxy(short x,short y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

struct address{
	char doorno[90];
	char streetname[90];
	char area[90];
	char state[90];
	char country[90];
};

struct trienode{
	struct trienode *children[26];
	bool isend;
	int id;
};

struct numsearch{
	int id;
	char num[20];
	struct address ad[90];
	struct numsearch *next;
};

struct numsearch *start=NULL;

void insert_numsearch(int x,char pno[20]){
	struct numsearch *t,*temp;
	t=(struct numsearch *)malloc(sizeof(struct numsearch));
	if(start==NULL){
		start=t;
		start->id=x;
		strcpy(start->num,pno);
		start->next=NULL;
	}
	else{
		temp=start;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=t;
		t->id=x;
		strcpy(t->num,pno);
		t->next=NULL;
	}
}

bool isLeafNode(struct trienode *root) 
{ 
    return root->isend != false; 
} 


void display(struct trienode *root, char str[], int level) 
{ 
    // If node is leaf node, it indiicates end 
    // of string, so a null charcter is added 
    // and string is displayed 
    if (isLeafNode(root))  
    { 
        str[level] = '\0'; 
        cout<<str; 
    } 
  
    int i; 
    for (i = 0; i <26; i++)  
    { 
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        { 
            str[level] = i + 'a'; 
            display(root->children[i], str, level + 1); 
        } 
    } 
} 

void search_numsearch(int x){
	struct numsearch *temp;
	temp=start;
	while(temp->next!=NULL){
		if(temp->id==x){
			cout<<"The phone number of the person is "<<temp->num<<endl;
		}
		temp=temp->next;
	}
	if(temp->id==x){
			cout<<"The phone number of the person is "<<temp->num<<endl;
		}
}

void search_existing_numsearch(int x){
	struct numsearch *temp;
	temp=start;
	int flag=0;
	while(temp->next!=NULL){
		if(temp->id==x){
			cout<<"The name already exists in the list\nAdd the new number\n";
			char strtemp[90];
			cin>>strtemp;
			insert_numsearch(x,strtemp);
			cout<<"Phone number added\n";
			flag=1;
			break;
		}
		temp=temp->next;
	}
	
	if(temp->id==x&&flag==0){
			cout<<"The name already exists in the list\nAdd the new number\n";
			char strtemp[90];
			cin>>strtemp;
			insert_numsearch(x,strtemp);
			cout<<"Phone number added\n";
		}
}

int count_numsearch(int x){
	struct numsearch *temp;
	temp=start;
	int count=0;
	while(temp->next!=NULL){
		if(temp->id==x){
			count++;
			
		}
		temp=temp->next;
	}
	if(temp->id==x){
			count++;
		}
		return count;
}


void del_numsearch_number(char str[20]){
	struct numsearch *temp;
	temp=start;
	if(temp==NULL){
		cout<<"Empty phone list\n";
	}
	else{
	
	if(strcmp(temp->num,str)==0){
		if(temp->next==NULL){
		temp=NULL;
		}
        else{
		temp=temp->next;
	}
}
	else{
	
	while(temp->next!=NULL){
		if(strcmp(temp->next->num,str)==0){
			temp->next=temp->next->next;
		}
		else
		temp=temp->next;
	}
}
cout<<"\nPhone number has been deleted\n";
}
}

void del_numsearch(int x){
	struct numsearch *temp;
	temp=start;
	if(temp==NULL){
		cout<<"Empty phone list\n";
	}
	else{
	
	if(start->id==x){
		if(start->next==NULL)
		start=NULL;
        else{
		start=start->next;
		temp=start;
	}
}
	else{
	
	while(temp!=NULL){
		if(temp->next->id==x){
			temp->next=temp->next->next;
		}
		temp=temp->next;
	}
}
cout<<"\nName has been deleted\n";
}
}

void display_numsearch(){
	struct numsearch *temp;
	temp=start;
	if(temp==NULL){
		cout<<"Empty list\n";}
	else{
	
	while(temp->next!=NULL){
		cout<<temp->id<<" "<<temp->num<<endl;
		temp=temp->next;
	}
	cout<<temp->id<<" "<<temp->num<<endl;
		
}
}

struct trienode* newnode(){
	struct trienode *sample=(struct trienode *)malloc(sizeof(struct trienode));
	int i;
	for(i=0;i<26;i++){
		sample->children[i]=NULL;
		
	}
	sample->isend=false;
	return sample;
}


bool isemptytrie(struct trienode *root){
	int i;
	for(i=0;i<26;i++){
		if(root->children[i]!=NULL){
			return false;
		}
	}
	return true;
}

void deletetrie(struct trienode *root, char str[20]){

		
	int i,flag=0,index;
	struct trienode *current=root;
		for(i=0;i<strlen(str);i++){
		index=str[i]-'a';
		if(current->children[index]==NULL){
			cout<<"\nGiven name is not found\n";
			flag=1;
			break;
		}
		current=current->children[index];
	}
	current->isend=false;
	
	if(flag==0){
	
	del_numsearch(current->id);
	current->id=-1;
}
}


void insert(struct trienode *root,char str[20]){
	int i,index;
	char pho[10];
	struct trienode *current=root;
	for(i=0;i<strlen(str);i++){
		index=str[i]-'a';
		if(current->children[index]==NULL){
			current->children[index]=newnode();
		}
		current=current->children[index];
	}
	current->isend=true;
	current->id=cnt;
	cout<<"Enter the phone number";
	cin>>pho;
	insert_numsearch(cnt,pho);
	cnt++;
}

bool isLastNode(struct trienode *root) 
{ 
    int i;
	for ( i = 0; i < 26; i++) 
        if (root->children[i]!=NULL) 
            return 0; 
    return 1; 
} 


void suggestionsRec(struct trienode *root, char currPrefix[20]) 
{ 
    // found a string in Trie with the given prefix
	int t=strlen(currPrefix); 
    if (root->isend==true) 
    {   
        cout<<currPrefix<<endl;
		currPrefix[strlen(currPrefix)]='\0'; 
    } 
  
    // All children struct node pointers are NULL 
    if (isLastNode(root)) 
        return; 
     int i;
    for (i = 0; i < 26; i++) 
    { 
        if (root->children[i]) 
        { 
            // append current character to currPrefix string 
            currPrefix[t]=(97+i);
			currPrefix[t+1]='\0'; 
            //printf("%s\n",currPrefix);
            
            
			suggestionsRec(root->children[i], currPrefix);
		}
			
             
            
			
    } 
} 
 


int printAutoSuggestions(struct trienode *root, char query[20]) 
{ 
    struct trienode *pCrawl = root; 
  
    // Check if prefix is present and find the 
    // the node (of last level) with last character 
    // of given string. 
    int level; 
    int n = strlen(query); 
    for (level = 0; level < n; level++) 
    { 
        int index = CHAR_TO_INDEX(query[level]); 
  
        // no string in the Trie has this prefix 
        if (!pCrawl->children[index]) 
            return 0; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // If prefix is present as a word. 
    bool isWord = (pCrawl->isend == true); 
  
    // If prefix is last node of tree (has no 
    // children) 
    bool isLast = isLastNode(pCrawl); 
  
    // If prefix is present as a word, but 
    // there is no subtree below the last 
    // matching node. 
    if (isWord && isLast) 
    { 
        cout<<query<<endl; 
        return -1; 
    } 
  
    // If there are are nodes below last 
    // matching character. 
    if (!isLast) 
    { 
        char prefix[90]="\0";
		strcpy(prefix,query); 
        suggestionsRec(pCrawl, prefix); 
        return 1; 
    } 
} 




int search(struct trienode *root,char str[20]){
	int i,index;
	struct trienode *current=root;
	for(i=0;i<strlen(str);i++){
		index=str[i]-'a';
		if(current->children[index]==NULL)
		return -1;
		else{
			current=current->children[index];
		}
	}
	if(current!=NULL && current->isend==true)
		return current->id;
	else
		return -1;
}

int main(){
	cout<<"                                                         PHONEBOOK   DIRECTORY                                                         \n\n";
	
	fstream f;
    f.open("names.txt",ios::in|ios::out);
    char fl[90];
    f.seekg(0,ios::beg);
	struct trienode *t=newnode();
	struct trienode *sample=(struct trienode *)malloc(sizeof(struct trienode));
	int i,choice,ch=1;
	char str[20];
	/*while(!f.eof())
    {
    f>>fl;
    insert(t,fl);
    }
	*/
	cout<<"Enter an option\n";
	do{
	
	cout<<"1.Insert\n2.Search\n3.Delete\n4.display_numsearch\n5.Display_all_names\n";
	cin>>choice;
	
	
	switch(choice){
	case 1:{
		cout<<"Enter the string to be inserted\n";
	    cin>>str;
	int x=search(t,str);
	if(x==-1){
	insert(t,str);
	cout<<"Word inserted\n";
    }
	else{
		search_existing_numsearch(x);
	}
	
		break;
	}
	case 2:{
		int i=0,x;
		int temp=0,comp;
		char str[90];
		char name[20]={0};
		/*printf("Enter the name to be searched\n");
		
		scanf("%s",name);*/
		while((int)(name[temp-1])!=13)
    {
    system("cls");
		gotoxy(1,1);	
	cout<<"Enter the name to be searched "<<name<<endl;
	
	comp = printAutoSuggestions(t,name);
    if (comp == -1)
    {
	cout<<"No other strings found with this prefix\n";
	break;
    }

    else if (comp == 0)
    {
	cout<<"No string found with this prefix\n";
	break;
    }
    else
    {
     gotoxy(32+temp,1);	
    name[temp]=getch();
    if((int)(name[temp])==13){
    	name[temp]='\0';
    	break;
	}
	else{
	temp++;
    
    //printf("%c",name[temp-1]);
    name[temp]='\0';}
    }
}
		system("cls");
		char trial[90]="\0";
		strcpy(trial,name);
		//printf("\nHi %s\n",trial);
		x=search(t,trial);
		if(x==-1){
			cout<<"\nNo such name in list\n";
			break;
		}	
search_numsearch(x);
		break;
}
		
		
	case 3:{
		char name[20];
		if(isemptytrie(t)){
		cout<<"Empty trie!!\n";
	}
		else{
		int choice;
		char strtemp[20];
		cout<<"Enter the name to be deleted\n";
		cin>>name;
		int x=search(t,name);
		if(x==-1){
			cout<<"No such name in list\n";
		}
		else{
		int y=count_numsearch(x);
		if(y==1)
		deletetrie(t,name);
		else{
		search_numsearch(x);
		cout<<"1.Delete specific number\n2.Delete Entire contact\n";
		cin>>choice;
		switch(choice){
			case 2:{
			deletetrie(t,name);
			break;
		}
		case 1:{
			cout<<"ENter the number to be deleted\n";
			cin>>strtemp;
			del_numsearch_number(strtemp);
			break;
		}
		
	}
}
}
}
		break;
	}
	case 4:{
		display_numsearch();
		break;
	}
	case 5:{
		if(isemptytrie(t))
		cout<<"EMpty trie!!\n";
		else{
		char str[90];
		int level=0;
		display(t,str,level);
	}
		break;
	}
	default:{
		cout<<"Wrong choice\n";
		break;
	}
}
cout<<"Do you want to continue? (Press 1 for yes and others for no )\n";
cin>>ch;
}while(ch==1);
return 0;
}
