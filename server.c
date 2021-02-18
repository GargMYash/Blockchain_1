#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>
#include<sys/types.h>
#include<signal.h>
#include "file1.h"
#include <string.h>
#include <openssl/sha.h>
#define BUFSIZE 1024

#define MAXSIZE 100
#define MAX_CLIENTS 100
#define BUFFER_SZ 2048
#define NAME_LEN 32

static _Atomic unsigned int cli_count = 0;
static int uid = 10;


//Client structure will store information about client's address,name, id 
typedef struct{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[NAME_LEN];	
}

client_t;
client_t *clients[MAX_CLIENTS];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;


struct node
{
unsigned char prev_hash[MAXSIZE];
unsigned char curr_hash[MAXSIZE];
char *fdata;
struct node *link;
}*start;

char rs1[BUFSIZ];
unsigned char buffer[BUFSIZ];
int hash(char filename[]); 
void create(char *);
void disp();
void count();
void ser(char *);
char file[30];	
//void hashPrinter(char hash[]);
void myStrcpy(unsigned char a[],char b[]) {


    int i; 

    for (i = 0; b[i] != '\0'; i++) {

        a[i] = b[i];

    }

    a[i] = '\0';  

}

void myStrcpy1(unsigned char a[],unsigned char b[]) {


    int i; 

    for (i = 0; b[i] != '\0'; i++) {

        a[i] = b[i];

    }

    a[i] = '\0';  

}
void hashPrinter(unsigned char hash[])
{

    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
        printf("%02x",hash[i]);
}
int hash(char filename[])
{
  


       FILE *f;

       SHA256_CTX ctx;

       size_t len;

       if (strlen(filename) < 2) {

              fprintf(stderr, "usage: %s <file>\n", filename);

              return 1;

       }

       f = fopen(filename, "r");

       if (!f) {

              fprintf(stderr, "couldn't open %s\n", filename);

              return 1;

       }

       SHA256_Init(&ctx);

       do {

              len = fread(buffer, 1, BUFSIZ, f);

              SHA256_Update(&ctx, buffer, len);

       } while (len == BUFSIZ);

       SHA256_Final(buffer, &ctx);

       fclose(f);

       for (len = 0; len < SHA256_DIGEST_LENGTH; ++len)

            {  //printf("%02x", buffer[len]);
               
             //   printf("%02x", buffer[len]);
  	 rs1[len]=buffer[len];        
     }
      rs1[len]='\0';
     
putchar('\n');
// hashPrinter(rs1,SHA256_DIGEST_LENGTH);
return 0;
}

void str_overwrite_stdout(){
	printf("\r%s", "> ");
	fflush(stdout);
}
void str_trim_lf(char* arr,int length){
	for(int i=0; i<length; i++){
		if(arr[i] == '\n'){
		arr[i] = '\0';
		break;
		}
	}
}
//code for the file approval check
/*void approval()
{

char buffer1[BUFFER_SZ];
	int flag=0;
	int i;	
	
	

for(i=1;i<7;i++)
{

 printf("Enter Suggestion :");
 
 fgets(buffer1,BUFFER_SZ,stdin);
 
 if(strcmp(buffer1,"Y"))
 {
 flag=flag+1;
 
 if(flag==5)
{
    printf(":::::: File is Approved ::::: ");
    printf("APPROVAL CONCENT TAKEN :");
} 

 }


}

}
*/

char fileNa[10][MAXSIZE];
int currlo = -1;


void approval()
{

//char buffer1[1024];
	int flag=0;
	int i;	
	char arr[10];
	

for(i=1;i<8;i++)
{

 
 if(flag==6)
{
    printf(":::::: File is Approved ::::: ");
    printf("APPROVAL CONCENT TAKEN :");
    break;
} 
printf("Enter Suggestion :");
 
 //fgets(buffer1,1024,stdin);
 
 scanf("%s",&arr[i]);
 
 if(arr[i]=='Y')
 {
 flag=flag+1;
 
 }
 else
 {
 flag=flag-1;
 printf("FILE IS NOT APPROVED");
 break;
 }

}

}




int n;
char fileNameArr1[10][MAXSIZE];
int currloc = -1;

void count()
{
struct node *q;
int cnt=0;
q=start;
while(q!=NULL)
{
cnt++;
q=q->link;
}
printf("No Of Nodes Are\t %d",cnt);
}

int count11()
{
struct node *q;
int cnt=0;
q=start;
while(q!=NULL)
{
cnt++;
q=q->link;
}
//printf("No Of Nodes Are\t %d",cnt);
return cnt;
}
void create(char *str)
{


struct node *q,*tmp;
tmp=(struct node *)malloc(sizeof(struct node));//block creation

tmp->fdata=str;//file name in fdata linkedlist


tmp->link=NULL;
if(start==NULL)
{
start=tmp;
hash(str);//hash ->passed filename.txt


myStrcpy(tmp->curr_hash,rs1);//copy hash to linkedlist_current_hash

}
else
{
q=start;

while(q->link!=NULL)
{
q=q->link;} //end of link
q->link=tmp;
;

myStrcpy1(tmp->prev_hash,q->curr_hash);
hash(str);
myStrcpy(tmp->curr_hash,rs1);


}
}
void disp()
{
struct node *q;
if(start==NULL)
{
printf("\n\nLIST IS EMPTY");
}
else
{
q=start;
int flag=0;
while(q!=NULL)
{
printf(" ::::: Filename ::::: %s \n",q->fdata);
printf("\n\n");
printf("       Previous hash of the file --->>  :");
if(flag==0){
  printf("NULL \n");
  flag++;
}
else
{
hashPrinter(q->prev_hash);
flag++;
}
printf("\n");
printf("       Current hash of the file --->>  :");
hashPrinter(q->curr_hash);
printf("\n");
q=q->link;
}
printf("NULL");
}
}


void block()
{
int ch,i;

start=NULL;

do
{
printf(" \n\n\t BLOCKCHAIN FUNCTIONING :");
printf("\n\n\t     :MENU:\n\n");
printf("\n\t    1.CREATE\n");
printf("\n\t    2.DISPLAY\n");
printf("\n\t    3.COUNT\n");
printf("\n\t    4.SAVE\n");
printf("\n\t    5.EXIT\n");
printf("\n\t  ::::: ENTER UR CHOICE ::::: \n");
scanf("%d",&ch);
switch(ch)
{
case 1:
printf("\n\n   ::::::HOW MANY NODES U WANT TO CREATE::::::\n");
scanf("%d",&n);
char* str;

for(i=0;i<n;i++)
{
printf("\n::::: ENTER THE File name :::::");
	scanf("%s",fileNameArr1[++currloc]);
	str = fileNameArr1[currloc];
create(str);
}
break;
case 3:
count();
break;
case 2:
disp();
break;
case 4:
printf("Enter the file name of the ledger :");

struct node *q1;

if(start==NULL)
{
printf("\n\nLIST IS EMPTY");
}
else
{
q1=start;

while(q1!=NULL)
{
//printf(" ::::: Filename ::::: %s \n",q1->fdata);
file_trans(q1->fdata);

q1=q1->link;

}

//char *str1;
//scanf("%s",fileNa[++currlo]);
//	str1 = fileNa[currlo];
  

}
case 5:
exit(0);

}
}
while(ch!=7);

}

void doc()
{
FILE *fp1;
	char data[150];
	
	printf( "Opening the file in read mode .....\n\n" ) ;
		printf("\n\n");
         fp1 = fopen("approval.docx", "r" ) ;
         if ( fp1 == NULL )
         {
                 printf( "Could not open file \n" ) ;
               //  return;
         }
         printf( "Reading the file  \n" ) ;
         	printf("\n\n");
         while( fgets( data, 50, fp1 ) != NULL ){
         printf( "%s" , data ) ;
        
       //printf("Closing the file ") ;
         	printf("\n\n");
         }
         fclose(fp1) ;
         	printf("\n\n");
         printf("DO YOU WANT TO APPROVE IT OR NOT? (Y/N) \n");
         


}
void html()
{

FILE *fp1;
	char data[150];
	
	printf( "Opening the file in read mode" ) ;
		printf("\n\n");
         fp1 = fopen("pay_req.html", "r" ) ;
         if ( fp1 == NULL )
         {
                 printf( "Could not open file \n" ) ;
               //  return;
         }
         printf( "Reading the file \n" ) ;
         	printf("\n\n");
         while( fgets( data, 50, fp1 ) != NULL ){
         printf( "%s" , data ) ;
        // printf("Closing the file \n") ;
         	printf("\n\n");
         }
         fclose(fp1) ;
              printf("\n\n");
         printf("DO YOU WANT TO APPROVE IT OR NOT? (Y/N)");
         	
         
}


void pdf()
{
FILE *fp1;
	char data[150];
	
	printf( "Opening the file in read mode" ) ;
		printf("\n\n");
         fp1 = fopen("money_tra.pdf", "r" ) ;
         if ( fp1 == NULL )
         {
                 printf( "Could not open file \n" ) ;
               //  return;
         }
         printf( "Reading the file \n" ) ;
         	printf("\n\n");
         while( fgets( data, 50, fp1 ) != NULL ){
         printf( "%s" , data ) ;
         	printf("\n\n");
        // printf("Closing the file \n") ;
         }
         fclose(fp1) ;
         	printf("\n\n");
         printf("DO YOU WANT TO APPROVE IT OR NOT? (Y/N)");
         

}
//add the client to the queue
void queue_add(client_t *cl){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i<MAX_CLIENTS; i++){
		if(!clients[i]){
		clients[i] = cl;
		break;
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

//remove the client from the queue
void queue_remove(int uid){
	pthread_mutex_lock(&clients_mutex);
	
	for(int i=0; i<MAX_CLIENTS; i++){
		if(clients[i]){
			if(clients[i]->uid == uid){
			clients[i] = NULL;
			break;
			}
		}
	}

	pthread_mutex_unlock(&clients_mutex);
}

void print_ip_addr(struct sockaddr_in addr){
	printf("%d.%d.%d.%d",
		addr.sin_addr.s_addr &0xff,
		(addr.sin_addr.s_addr &0xff00)>>8,
		(addr.sin_addr.s_addr &0xff0000)>>16,
		(addr.sin_addr.s_addr &0xff000000)>>24);

}

//this function send the clients message and uid to other users.
void send_message(char *s, int uid){
	pthread_mutex_lock(&clients_mutex);

	for(int i=0; i<MAX_CLIENTS; i++){
		if(clients[i]){
			if(clients[i] ->uid != uid){
				if(write(clients[i]->sockfd, s, strlen(s)) < 0){
				printf("ERROR: write to descriptor failed\n");
				break;
				}
			
			}
		}
	}

	
	pthread_mutex_unlock(&clients_mutex);
}


void *handle_client(void *args){
	char buffer[BUFFER_SZ];
	char name[NAME_LEN];
	int leave_flag = 0;
	cli_count++;

	client_t *cli = (client_t*)args;

	//Name
	if(recv(cli->sockfd, name, NAME_LEN, 0) <=0 || strlen(name) < 2 || strlen(name) >= NAME_LEN -1){
		printf("Enter the name correctly \n");
		leave_flag = 1;
	}else{
		strcpy(cli->name, name);
		sprintf(buffer, "%s has joined\n", cli->name);
		printf("%s",buffer);
		send_message(buffer, cli->uid);
	     }

	bzero(buffer, BUFFER_SZ);
	
	while(1){
	if(leave_flag){
	break;
	}

	int receive = recv(cli->sockfd, buffer, BUFFER_SZ, 0);

	if(strncmp(buffer,"SEND",4)==0)
	{
	printf("\n");
	printf("Welcome TO the blockchain :\n");
	//fgets(buffer, BUFFER_SZ, stdin);
	
        block();
        //blockchain();
	}	
	

	
	if(strstr(buffer, ".txt") != NULL) 
	{ 
	
	
	FILE *fp1;
	char data[150];
	
	printf( "Opening the file in read mode........ \n" ) ;
	printf("\n\n");
         fp1 = fopen("prop.txt", "r" ) ;
         if ( fp1 == NULL )
         {
                 printf( "Could not open file \n" ) ;
               //  return;
         }
         printf( "Reading the file::::: \n" ) ;
         	printf("\n\n");
         while( fgets( data, 50, fp1 ) != NULL ){
         printf( "%s" , data ) ;
         //printf("Closing the file \n") ;
         }
         fclose(fp1) ;
         	printf("\n\n");
         printf("DO YOU WANT TO APPROVE IT OR NOT? (Y/N)");
         
         approval();
                     
}

	if(strstr(buffer, ".docx") != NULL) 
	{ 
	doc();
        approval(); }
         
         if(strstr(buffer, ".pdf") != NULL) 
	{ 

	pdf();
        approval(); }
         
         if(strstr(buffer, ".html") != NULL) 
	{ 
       
	html();
        approval(); 
         }
         

      

	if(receive> 0){
		if(strlen(buffer)> 0 && strncmp(buffer,"SEND",4)!=0 ){
			send_message(buffer, cli->uid);
			str_trim_lf(buffer, strlen(buffer));
	             // printf("%s -> %s",buffer,cli->name);
	             
		}
	}else if(receive ==0 || strcmp(buffer, "exit")== 0){
		sprintf(buffer, "%s has left\n", cli->name);
		printf("%s", buffer);
		send_message(buffer, cli->uid);
		leave_flag = 1;
	}else{
		printf("ERROR:-1\n");
		leave_flag = 1;
	}
bzero(buffer, BUFFER_SZ);
}
	close(cli->sockfd);
	queue_remove(cli->uid);
	free(cli);
	cli_count--;
	pthread_detach(pthread_self());

	return NULL;
}

int main(int argc, char **argv){
	if(argc !=2){
	printf("Usage: %s <port>\n",argv[0]);
	return EXIT_FAILURE;
	}

	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	
	int option = 1;
	int listenfd = 1, connfd=0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	//Socket setting
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	//signals
	signal(SIGPIPE,SIG_IGN);
	
	if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR),(char*)&option, sizeof(option))<0){
	printf("ERROR: setsockopt\n");
	return EXIT_FAILURE;
	}

	//Bind
	if(bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
	printf("ERROR: bind\n");
	return EXIT_FAILURE;
	}

	//listen
	if(listen(listenfd, 10)<0){
	printf("ERROR: listen\n");
	return EXIT_FAILURE;
	}

	printf("=== TRANSACTION AND APPROVAL PLATFORM ===\n");


	while(1){
	socklen_t clilen = sizeof(cli_addr);
	
	//accept connection from client
	connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);
 
	//check for max-clients
	if((cli_count + 1) == MAX_CLIENTS){
		printf("Maximum clients connected. Connection Rejected: ");
		print_ip_addr(cli_addr);
		close(connfd);
		continue;
		}
	

	//Client Settings
	client_t *cli = (client_t *)malloc(sizeof(client_t));
	cli->address = cli_addr;
	cli->sockfd = connfd;
	cli->uid = uid++;


	//Add client to queue
	queue_add(cli);
	pthread_create(&tid, NULL, &handle_client, (void*)cli);

	//Reduce CPU usage
	sleep(1);
	}


	return EXIT_SUCCESS;
}
