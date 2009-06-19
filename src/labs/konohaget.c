/* ------------------------------------------------------------------------
 * konohaget - package importing function
 * implemented by Satoshi Kobayashi and Shinpei Nakata
 *
 * ------------------------------------------------------------------------ */

#include"commons.h" // added by Kimio Kuramitsu

#ifndef KONOHA_OS__LKM

#ifndef KONOHA_OS__WINDOWS
//#ifdef KNH_USING_POSIX
#include<unistd.h>
//#endif

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef SOCK_BUF_SIZE
#define SOCK_BUF_SIZE 256
#endif

struct knhget_sock_t {
	int sd;
	char domain[SOCK_BUF_SIZE];
	char path[SOCK_BUF_SIZE];
	int port;

};

static void separate_domain_path(char *url, char *domain, char *path){
	char *domain_path;
	char *p;
	if((p = strstr(url, "http://")) != NULL){
		domain_path = p + 7;
	}else{
		domain_path = url;
	}
	if((p = strstr(domain_path, "/")) != NULL){
		strncpy(path, p, strlen(p)+1);
		*p = '\0';
	}else{
		path = NULL;
	}
	strncpy(domain, domain_path, strlen(domain_path) + 1);
}

int knhget_openSocket(Ctx *ctx, char *url, struct knhget_sock_t *sock){
	char domain[SOCK_BUF_SIZE] = {0};
	char path[SOCK_BUF_SIZE] = {0};
	int port = 80;
	struct in_addr addr;
	struct hostent *host;
	struct sockaddr_in server;
	int sd = -1;

	separate_domain_path(url, domain, path);
	//	if (domain[0] = '\0')
	//	  return -1;
	if((addr.s_addr = inet_addr(domain)) == -1){
	  host = gethostbyname(domain);
		if (host == NULL) {
		  printf("%s %s\n", domain, hstrerror(h_errno));
		  return -1;
		  }
		memcpy(&addr, (struct in_addr *)*host->h_addr_list, sizeof(struct in_addr));
	}
	server.sin_family = AF_INET;
	server.sin_addr = addr;
	server.sin_port = htons(port);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	  KNH_PERRNO(ctx, "Socket!!", "open_socket");
	  return -1;
	}
	if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1){
	  KNH_PERRNO(ctx, "Socket!!", "open_socket");
	  return -1;
	}
	sock->sd = sd;
	strncpy(sock->domain, domain, sizeof(domain));
	strncpy(sock->path, path, sizeof(path));
	sock->port = port;
	return 0;
}

static
int knhget_parseHtml(Ctx *ctx, char *url, char *new_url){
	char send_buf[SOCK_BUF_SIZE] = {0};
	struct knhget_sock_t sock;
	int read_size;
	int sd;

	if (knhget_openSocket(ctx, url, &sock) == -1) {
	  // error 
	  return -1;
	}
	sd = sock.sd;
	snprintf(send_buf, SOCK_BUF_SIZE, "GET %s HTTP/1.0\r\n", sock.path);
	write(sd, send_buf, strlen(send_buf));
	snprintf(send_buf, SOCK_BUF_SIZE, "Host: %s:%d\r\n", sock.domain, sock.port);
	write(sd, send_buf, strlen(send_buf));
	write(sd, "\r\n", 2);

	while(1){
		char buf[SOCK_BUF_SIZE] = {0};
		memset(buf, 0, SOCK_BUF_SIZE);
		char *str = "<meta http-equiv=\"refresh\" content=\"1; url=";
		read_size = read(sd, buf, SOCK_BUF_SIZE);
		if(read_size > 0){
			char *p, *end;
			if((p = strstr(buf, str)) != NULL){
			    DBG_P("%s", p);
				if((end = strstr(p, "\">")) != NULL){
					*end = '\0';
				}
				p += strlen(str);
				strcpy(new_url, p);
				DBG_P("%s", new_url);
			}
		}else{
			break;
		}
	}

	return 0;
}

static
int knhget_getID(Ctx *ctx, char *check_url, char *id){
	struct knhget_sock_t *sock = (struct knhget_sock_t*)malloc(sizeof(struct knhget_sock_t));

	if (knhget_openSocket(ctx, check_url, sock) == -1) {
	  printf("hi");
	  return -1;
	}
	int sd = sock->sd;
	char send_buf[SOCK_BUF_SIZE];
	memset(send_buf, 0, SOCK_BUF_SIZE);
	snprintf(send_buf, SOCK_BUF_SIZE,  "GET %s HTTP/1.0\r\n", sock->path);
	write(sd, send_buf, strlen(send_buf));

	snprintf(send_buf, SOCK_BUF_SIZE, "Host: %s:%d\r\n", sock->domain, sock->port);
	write(sd, send_buf, strlen(send_buf));

	write(sd, "\r\n", 2);

	while(1){
		char buf[SOCK_BUF_SIZE] = {0};
		int read_size;
		read_size = read(sd, buf, SOCK_BUF_SIZE);
		if(read_size > 0){
			char *p;
			if((p = strstr(buf, "\r\n\r\n")) != NULL){
				p+=4;
				strncpy(id, p, read_size - (p - buf));
			}
		}else{
			break;
		}
	}
	free(sock);
	return 0;
}

static
int konoha_getPackageURL(Ctx *ctx, knh_bytes_t pkgname, char *url, size_t bufsiz)
{
	char check_url[] = "http://www.ubicg.ynu.ac.jp/cgi-bin/knh_rss_read.pl";
	char baseurl[] = "http://sourceforge.jp/projects/konoha/downloads/";
	unsigned char *package = pkgname.buf;
	size_t package_len = pkgname.len;
	char id[16] = {0};

	if (knhget_getID(ctx, check_url, id) == -1) {
	  return -1;
	}

	strncpy(url, baseurl, strlen(baseurl));
	strncat(url, id, strlen(id));
	strncat(url, "/", 1);
	strncat(url, (char *)package, package_len);
	strncat(url, "-0.1.0.tar.gz", 13);
	//	DBG_P("url:%s", url);
	return 0;
}

static
int konoha_getPackageArchive(Ctx *ctx, knh_bytes_t pkgname, char *argurl)
{
	unsigned char *package = pkgname.buf;
	char send_buf[SOCK_BUF_SIZE] = {0};
	char url[SOCK_BUF_SIZE] = {0};
	char old_url[SOCK_BUF_SIZE] = {0};
	memcpy(old_url, argurl, SOCK_BUF_SIZE);
	knhget_parseHtml(ctx, old_url, url);

	struct knhget_sock_t sock;

	if (knhget_openSocket(ctx, url, &sock) == -1){
	  KNH_PERRNO(ctx,  "Socket!!", "getPackageArchive");
	  return -1;
	}
	int sd = sock.sd;
	snprintf(send_buf, SOCK_BUF_SIZE,  "GET %s HTTP/1.0\r\n", sock.path);
	write(sd, send_buf, strlen(send_buf));
	//DBG_P("host:%s", sock.domain);
	snprintf(send_buf, SOCK_BUF_SIZE, "Host: %s:%d\r\n", sock.domain, sock.port);
	write(sd, send_buf, strlen(send_buf));
	write(sd, "\r\n", 2);

	FILE *f;
	char filename[SOCK_BUF_SIZE];
	snprintf(filename, SOCK_BUF_SIZE,  "%s.tar.gz", package);
	if((f = fopen(filename, "wb")) == NULL){
		printf("error:cannot open\n");
		return -1;
	}
	int content_flag = 0;
	while(1){
		char buf[SOCK_BUF_SIZE] = {0};

		int read_size;
		read_size = read(sd, buf, SOCK_BUF_SIZE);
		if(read_size > 0){
			if(content_flag){
			  fwrite(buf, read_size, sizeof(char), f);
			}else{
			  char *p;
				if((p = strstr(buf, "\r\n\r\n")) != NULL){
					p+=4;
					content_flag = 1;
					fwrite(p, sizeof(char), read_size - (p - buf), f);
				}
			}
		}else{
		  break;
		}
	}

	close(sd);
	fclose(f);
	return 0;
}

static
int konoha_installPackage(Ctx *ctx, knh_bytes_t pkgname)
{
	/* have a flexibility for archive types */

	static const char *decomp_prog = "tar xfz ";
	static const char *extends = ".tar.gz";

	char command[256] = {0};
	char *cur = command;
	size_t decomp_prog_len = strlen(decomp_prog);
	size_t extends_len = strlen(extends);

	strncpy(cur, decomp_prog, decomp_prog_len);
	cur += decomp_prog_len;
	strncpy(cur, (char*)pkgname.buf, pkgname.len);
	cur += pkgname.len;
	strncpy(cur, extends, extends_len);
	cur += extends_len;
	cur[0] = '\0';


	if (system(command) == -1) return -1;
#ifdef KONOHA_OS__MACOSX
	memset(command, 0, sizeof(command));
	snprintf(command, sizeof(command), "mkdir -p .konoha/%s", pkgname.buf);
	if (system(command) == -1) return -1;
	memset(command, 0, sizeof(command));
	snprintf(command, sizeof(command), "cp %s.dylib %s.k .konoha/%s", pkgname.buf, pkgname.buf, pkgname.buf);

	if (system(command) == -1) return -1;
#else
	if (system("make") == -1) return -1;
	if (system("make konoha_install") == -1) return -1;
#endif
	printf("konohaget success!\n");
	return 0;

}

/* ------------------------------------------------------------------------- */
/* konohaget has been modified since ... By K */

int konohaget(Ctx *ctx, knh_bytes_t pkgname)
{
	char urlbuf[256] = {0};
	if (konoha_getPackageURL(ctx, pkgname, urlbuf, sizeof(urlbuf)) == -1) {
		printf("ERROR:cannot find package on the web...\n");
		return 0;
	}

	if (konoha_getPackageArchive(ctx, pkgname, urlbuf) == -1) {
		printf("ERROR:cannot fetch package from web...\n");
		return 0;
	}

	if (konoha_installPackage(ctx, pkgname) == -1) {
		printf("ERROR: cannot make package...\n");
		return 0;
	}
	return 1;
}

/* ------ end of konohaget implementation ----------------*/
#endif

#endif
