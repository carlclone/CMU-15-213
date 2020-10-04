#include "sbuf.h"
#include "csapp.h"


/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

#define NTHREADS 4
#define SBUFSIZE 16

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

void doit(int fd);
void read_requesthdrs(rio_t *rp);
void build_header(char *header, char *hostname, char *path, rio_t *client_rio);
void parse_uri(char *uri, char *hostname, char *filepath, int *port);
int connect_endserver(char *hostname,int port,char *http_header);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);
void *thread(void *vargp);

sbuf_t sbuf;    /* Shared buffer of connected descriptors */

int main(int argc, char **argv) {
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    /* Check command-line args */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    printf("%s", user_agent_hdr);

    /* 监听套接字 */
    listenfd = Open_listenfd(argv[1]);

    //参考csapp p705 , 预线程
    sbuf_init(&sbuf, SBUFSIZE);
    for (int i = 0; i < NTHREADS; i++) {    /* Create worker threads */
        Pthread_create(&tid, NULL, thread, NULL);
    }

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd); //
        Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        // Close(connfd);  /* 显式关闭连接 */
    }
}

void doit(int fd) {
    int end_serverfd, port = 80;    /* HTTP default port is 80 */
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filepath[MAXLINE], hostname[MAXLINE];
    char endserver_header[MAXLINE];
    rio_t client_rio, server_rio;

    /* Read request line and headers */
    Rio_readinitb(&client_rio, fd);
    Rio_readlineb(&client_rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcasecmp(method, "GET")) {
        clienterror(fd, method, "501", "Not implemented", "Proxy does not implement this method");
        return;
    }

    /* Parse the uri to get hostname, file, path and port */
    parse_uri(uri, hostname, filepath, &port);

    /* build the http header which will send to the end server */
    build_header(endserver_header, hostname, filepath, &client_rio);

    end_serverfd =  connect_endserver(hostname, port, endserver_header);
    if (end_serverfd < 0) {
        printf("Connection failed\n");
        return;
    }

    Rio_readinitb(&server_rio, end_serverfd);

    /* write the http header to end server */
    Rio_writen(end_serverfd, endserver_header, strlen(endserver_header));

    /* Receive mgs from end server and send to client */
    size_t n;
    while ((n = rio_readlineb(&server_rio, buf, MAXLINE)) != 0) {
        printf("proxy received %ld bytes, then send to client %d\n", n, fd);
        Rio_writen(fd, buf, n);
    }

    Close(end_serverfd);
}

void *thread(void *vargp) {
    Pthread_detach(pthread_self()); //detach后才能被系统自动回收
    //每个线程会轮询sbuf 取出connfd 进行处理
    while (1) {
        int connfd = sbuf_remove(&sbuf);
        doit(connfd);   /* Service client */
        Close(connfd);
    }
}

//helper func
void build_header(char *header, char *hostname, char *path, rio_t *client_rio) {
    char buf[MAXLINE], request_hdr[MAXLINE], other_hdr[MAXLINE], host_hdr[MAXLINE];
    static const char *connection_key = "Connection";
    static const char *user_agent_key= "User-Agent";
    static const char *proxy_connection_key = "Proxy-Connection";

    /* request line */
    sprintf(request_hdr, "GET %s HTTP/1.0\r\n", path);
    /* get other request header for client rio and change it */
    while (Rio_readlineb(client_rio, buf, MAXLINE) > 0) {
        if (strcmp(buf, "\r\n") == 0) {
            break;
        }

        if (!strncasecmp(buf, "Host", strlen("Host"))) {
            strcpy(host_hdr, buf);
            continue;
        }

        if (!strncasecmp(buf, connection_key, strlen(connection_key))
            && !strncasecmp(buf, proxy_connection_key, strlen(proxy_connection_key))
            && !strncasecmp(buf, user_agent_key, strlen(user_agent_key))) {
            strcat(other_hdr, buf);
        }
    }

    if (strlen(host_hdr) == 0) {
        sprintf(host_hdr, "GET %s HTTP/1.0\r\n", hostname);
    }

    sprintf(header, "%s%s%s%s%s%s%s",
            request_hdr,
            host_hdr,
            "Connection: close\r\n",
            "Proxy-Connection: close\r\n",
            user_agent_hdr,
            other_hdr,
            "\r\n");
}

//helper func
int connect_endserver(char *hostname,int port,char *http_header) {
    char portstr[100];
    sprintf(portstr, "%d", port);
    return Open_clientfd(hostname, portstr);
}

// helper func
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
    char buf[MAXLINE], body[MAXLINE];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "<hr><em>The Tiny Web Server</em>\r\n");

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}

void parse_uri(char *uri, char *hostname, char *filepath, int *port) {
    /*parse the uri to get hostname,file path ,port*/
    char* ptr = strstr(uri,"//");

    ptr = ptr != NULL? ptr+2 : uri;

    char *temp = strstr(ptr, ":");
    if(temp!=NULL) {
        *temp = '\0';
        sscanf(ptr, "%s", hostname);
        sscanf(temp+1, "%d%s", port, filepath);
    }
    else {
        temp = strstr(ptr,"/");
        if(temp != NULL) {
            *temp = '\0';
            sscanf(ptr, "%s", hostname);
            *temp = '/';
            sscanf(temp, "%s", filepath);
        }
        else {
            sscanf(ptr, "%s", hostname);
        }
    }
    return;
}

void read_requesthdrs(rio_t *rp) {
    char buf[MAXLINE];

    Rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
    }
    return;
}