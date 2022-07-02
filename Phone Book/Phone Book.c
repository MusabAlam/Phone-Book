#include<stdio.h>
#include<stdlib.h>
#include<string.h>
                    //structure//
struct node{
    char fname[40];
    char phone[12];
    char lname[40];
    char country[40];
    struct node*next;// left pointer
    struct node*prev;// right pointer
};
                    //Globally define variables//
struct node*start=NULL;
char temp_f[40];
char temp_l[40];
char temp_p[12];
char temp_c[40];
int flag_fname = 0;
int flag_phone = 0;
int flag_lname = 0;
int flag_del=0;
int asc_count=1;
int dsc_count = 1;
int count_count= 1;

                        //Create Node//
struct node* createNode(char *fname,char * lname,char *phone, char *country){
    struct node*newnode=(struct node*)malloc(sizeof(struct node));
    strcpy(newnode->fname,fname);
    strcpy(newnode->lname,lname);
    strcpy(newnode->phone,phone);
    strcpy(newnode->country,country);
    newnode->next=newnode->prev=NULL;
    return newnode;
}
                        //Insert//
void insert(char *fname,char *lname, char *phone, char *country){
    struct node*root=start;
    struct node *curr = NULL;
    if(root==NULL){
        struct node*newnode=createNode(fname,lname,phone,country);
        start=newnode;
        return;
    }
    while(root!=NULL){
        curr = root;
        if(strcmp(root->fname,fname)==0){
            printf("Name is already there !");
            return;
        }
        else if(strcmp(root->fname,fname)>0){ //going left
            root = root->next;
        }
        else{
            root = root->prev;
        }
    }
    struct node* newnode = createNode(fname,lname, phone,country);
        if(strcmp(curr->fname,fname)>0){
            curr->next = newnode;
        }
        else{
            curr->prev = newnode;
        }
}
void add_contact(){

        printf("\n\t\t\t\t\t\t\tEnter First Name : ");
        while((getchar())!='\n');
        scanf("%s",temp_f);

        printf("\n\t\t\t\t\t\t\tEnter Last Name : ");
        while((getchar())!='\n');
        scanf("%s",temp_l);

        printf("\n\t\t\t\t\t\t\tEnter Phone no. : ");
        while((getchar())!='\n');
        scanf("%s",temp_p);


        printf("\n\t\t\t\t\t\t\tEnter Country Name. : ");
        while((getchar())!='\n');
        scanf("%s",temp_c);

        insert(temp_f,temp_l,temp_p,temp_c);
}
                     //Create Node end//

                        //Delete//
struct node* inorderpre(struct node* node)
{
    while (node->prev != NULL)
        node = node->prev;

    return node;
}

struct node* deleteNode(struct node* root, char*fname)
{
    if (root == NULL)
        return root;

    if (strcmp(root->fname,fname)>0)
        root->next = deleteNode(root->next,fname);

    else if (strcmp(root->fname,fname)<0 )
        root->prev = deleteNode(root->prev, fname);
    else {
        if (root->next == NULL) {
            struct node* temp = root->prev;
            flag_del=1;
            free(root);
            return temp;
        }
        else if (root->prev == NULL) {
            struct node* temp = root->next;
            flag_del=1;
            free(root);
            return temp;
        }

        struct node* pre = inorderpre(root->next);
        strcpy(root->fname,pre->fname);
        root->next = deleteNode(root->next, pre->fname);
    }
    if (flag_del==0){
        printf("Name does not exist");
    }
    return root;

}

void delete_contact(){
        if(start==NULL){
            printf("No contacts to delete !\n");
        }
        else{
        printf("\n\t\t\t\t\t\t\tEnter Exact First Name to delete : ");
        while((getchar())!='\n');
        scanf("%[^\n]%*c",temp_f);
        start= deleteNode(start,temp_f);
        }
        main();
}                       //Delete Function end//

                        //Search Functions//
void search_phone(struct node*root,char *phone){
    if(root!=NULL){
        search_phone(root->next,phone);
        if(strstr(root->phone,phone)){
            printf("Name : %s %s, Phone No.: %-10s, Country Name :%-10s  \n",root->fname,root->lname,root->phone, root->country);
            flag_phone =1;
        }
        search_phone(root->prev,phone);
    }
}

void search_fname(struct node*root,char *fname){
    if(root!=NULL){
        search_fname(root->next,fname);
        if(strstr(root->fname,fname)){
           printf("Name : %s %s, Phone No.: %-10s, Country Name :%-10s  \n",root->fname,root->lname,root->phone, root->country);
            flag_fname=1;
        }
        search_fname(root->prev,fname);
    }
}

void search_lname(struct node*root,char *lname){
    if(root!=NULL){
        search_lname(root->next,lname);
        if(strstr(root->lname,lname)){
            printf("Name : %s %s, Phone No.: %-10s, Country Name :%-10s  \n",root->fname,root->lname,root->phone, root->country);
            flag_lname=1;
        }
        search_lname(root->prev,lname);
    }
}

void search_contact(){
     struct node*root=start;
     if(root==NULL){
            printf("\nNo Contacts to search !\n");
            main();
        }
     else{
        int key;
        printf("1.Search by First Name  2.Search by Last Name 3.Search by Phone Number\n");
        scanf("%d", &key);
        if (key ==1){
            printf("\n\t\t\t\t\t\t\tEnter First Name. : ");
            while((getchar())!='\n');
            scanf("%s",temp_f);
            printf("\n");
            search_fname(root,temp_f);
            printf("\n");
        }
        else if (key==2){
            printf("\n\t\t\t\t\t\t\tEnter Last Name. : ");
            while((getchar())!='\n');
            scanf("%s",temp_l);
            printf("\n");
            search_lname(root,temp_l);
            printf("\n");
        }
        else if (key==3){
            printf("\n\t\t\t\t\t\t\tEnter Phone no. : ");
            while((getchar())!='\n');
            scanf("%s",temp_p);
            printf("\n");
            search_phone(root,temp_p);
            printf("\n");
        }
        else{
            printf("inappropriate input ");

        }

     }

    if (flag_phone==0){
            if (flag_fname==0){
                if(flag_lname==0){
                      printf("Not in the list");
                }
            }
        }
    flag_phone=flag_fname=flag_lname=0;
    main();
}                         //Search Functions end//

                        //Print Functions//
void ascending(struct node*root){
    if(root!=NULL){
        ascending(root->next);
         printf(" %d  Name : %s %s, Phone No.: %-10s, Country Name :%-10s  \n",asc_count,root->fname,root->lname,root->phone, root->country);
         asc_count++;
        ascending(root->prev);
    }
}

void descending(struct node*root){
    if(root!=NULL){
        descending(root->prev);
          printf(" %d  Name : %s %s, Phone No.: %-10s, Country Name :%-10s  \n",dsc_count,root->fname,root->lname,root->phone, root->country);
          dsc_count++;
        descending(root->next);
    }
}

void print_wrt_country(struct node *root,char *country){
    if(root!=NULL){
        print_wrt_country(root->prev,country);
        if(strcmp(root->country,country)==0){
              printf(" %d  Name : %s %s, Phone No.: %-10s \n",count_count,root->fname,root->lname,root->phone,root->country);
        }
        count_count++;
        print_wrt_country(root->next, country);
    }
}

void display_list(){
struct node*root=start;
        if(root==NULL){
            printf("\n\t\t\t\t\t\t\tNo Contacts are there !\n");
        }
        else{
            struct node*root=start;
            int key;
            printf("1.Ascending Order 2.Descending Order 3.Printing Country-wise");
            scanf("%d",&key);
            if (key==1){
            printf("\n\t\t\t\t\t\t\tPrinting in Ascending Order :\n");
            ascending(root);
            asc_count = 1;
            printf("\n");
            }

            else if(key==2){
                printf("\n\t\t\t\t\t\t\tPrinting in Descending Order :\n");
                descending(root);
                dsc_count = 1;
                printf("\n");
            }

            else if (key==3){
               char country[20];
               printf("\n\t\t\t\t\t\t\tEnter Country Name : ");
               while((getchar())!='\n');
               scanf("%s",country);
               print_wrt_country(root,country);
               count_count=1;
               printf("\n");
            }

            else{
                printf("Inappropriate input");
            }
        }

}                        //Pint Functions end//


                        //MAIN FUNCTION//
int main(){
    menu:
    printf("\n\n\t\t\t\t\t\t\t----PHONE BOOK----\n");
    printf("\n\t\t\t\t\t\t\t1. Add Contact\n");
    printf("\n\t\t\t\t\t\t\t2. Delete Contact\n");
    printf("\n\t\t\t\t\t\t\t3. Search Contact\n");
    printf("\n\t\t\t\t\t\t\t4. Display List\n");
    printf("\n\t\t\t\t\t\t\t5. Exit Program\n");
    int choice;
    printf("\n\t\t\t\t\t\t\tEnter Choice :\n");
    scanf("%d",&choice);
    printf("\n");

    if(choice==1){
            add_contact();
    }
    else if(choice==2){
        delete_contact();
        }

    else if(choice==3){
            search_contact();
        }

    else if(choice==4){
        display_list();
    }
    else if(choice==6){
        exit(0);
    }
    else{
        printf("\n\t\t\t\t\t\t\tChoose correct number from menu !\n");
    }
    goto menu;
return 0;
}
