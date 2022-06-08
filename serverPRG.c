    #include <stdlib.h>
    #include <strings.h>
    #include <string.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include<unistd.h>
     
    int main(int argc, char** argv )
    { 
	char datas[] = "hello\n";
      int    sockfd,newsockfd,clilen;
      char c;
      struct sockaddr_in cli_addr,serv_addr;
      
      if (argc!=2) {printf ("usage: socket_server port\n");exit(0);}
     
      printf ("server starting...\n");  
     
      /* ouverture du socket */
      sockfd = socket (AF_INET,SOCK_STREAM,0);
      if (sockfd<0) {printf ("impossible d'ouvrir le socket\n");exit(0);}
     
      /* initialisation des parametres */
      bzero((char*) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family       = AF_INET;
      serv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
      serv_addr.sin_port         = htons(atoi(argv[1]));
     
      /* effectue le bind */
      if (bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
         {printf ("impossible de faire le bind\n");exit(0);}

    if(fork() == 0){
        execl("/bin/gcc","gcc", "main.c", "TpPrgSys.c", "-o", "prj", NULL);
        }
      /* �coute */
      listen(sockfd,1);
     
      /* attente de connection d'un client */
      clilen = sizeof (cli_addr);
      newsockfd = accept (sockfd,(struct sockaddr*) &cli_addr, &clilen);
      if (newsockfd<0) {printf ("accept error\n"); exit(0);}
      write(1,"connection accepted\n",20);
        

     char  buff[100];
     bzero(buff,sizeof(buff));
    int n;

      while (1)
        {
                n = recv(newsockfd,&buff,20,0);
                buff[n] = '\0';
                if(fork() == 0)
                {
                    char* path_name = "./prj";

                    
                    char **vars = (char **)malloc(9*sizeof(char *));
                    vars[0]= "./prj";
                    vars[1] = strtok(buff,"\n ");
                    int i ;
                    for(i = 2 ; i < 9; i++)
                    {
                        vars[i] = strtok(NULL, "\n ");
                        if(vars[i] == NULL)
                            break;                        
                    }
                    vars[i] = NULL;
                    execvp("./prj", vars);
                }
       }
     
       return 1;
     }


