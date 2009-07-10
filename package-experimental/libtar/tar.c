/* ************************************************************************ */

#include <libtar.h>
#include <fcntl.h>
#include <konoha.h>
#include <zlib.h>


/* ************************************************************************ */

METHOD Tar_extractTar(Ctx * ctx,knh_sfp_t * sfp)
{
	if(IS_String(sfp[1].o)){
		char * tarf = p_char(sfp[1]);
		TAR * t;
		int ret;
		if ((ret = tar_open(&t,tarf,NULL,O_RDONLY,0,0)) == 0 ) {
			char * pr = strrchr(tarf,'/');
			int pn;
			if ( pr != NULL ) {
				pn = (int) ( pr - tarf ) + 1;
			} else {
				pn = 2;
			}
			char rdir[pn+1];
			if ( pn == 2) { strncpy(rdir,"./",2); }
			else { strncpy(rdir,tarf,pn); }
			rdir[pn] = '\0';
			fprintf(stderr,"%s\n",rdir);
			ret = tar_extract_all(t,rdir);
			tar_close(t);
			if ( ret == 0 ) {
				KNH_RETURN_Boolean(ctx,sfp,1);
			} else {
				KNH_THROWs(ctx, "[libtar] tar_extract_all");
			}
		} else { 
			KNH_THROWs(ctx,"cannot open this file");
		}
	} else { 
		KNH_THROWs(ctx, "Type!!: data must be String");
	}
	KNH_RETURN_Boolean(ctx,sfp,0);
}

/* ************************************************************************ */

int knh_create_tar(char *tarfile, char *rootdir, libtar_list_t *l)
{
  TAR *t;
  char *pathname;
  char buf[255];
  libtar_listptr_t lp;
  if (tar_open(&t, tarfile,NULL,O_WRONLY | O_CREAT, 0644,0) == -1)
	{ return -1; }
  libtar_listptr_reset(&lp);
  while (libtar_list_next(l, &lp) != 0) {
	pathname = (char *)libtar_listptr_data(&lp);
	if (pathname[0] != '/' && rootdir != NULL) {
	  snprintf(buf, sizeof(buf), "%s/%s", rootdir, pathname);
	} else { 
	  strncpy(buf, pathname, sizeof(buf));
	}
	if (tar_append_tree(t, buf, pathname) != 0) {
	  tar_close(t);
	  return -1;
	}
  }
  if (tar_append_eof(t) != 0) {	tar_close(t); return -1; }
  if (tar_close(t) != 0) { return -1; }
  return 0;
}

METHOD Tar_createTar(Ctx * ctx,knh_sfp_t * sfp)
{
  if ( IS_bArray(sfp[1].o)) {
	if ( IS_String(sfp[2].o) ){
	  Array *a = (Array *)sfp[1].o;
	  char * outfile = p_char(sfp[2]);
	  int i, argc;
	  char **argv;
	  argc = knh_Array_size(a);
	  argv = (char **)alloca(argc * sizeof(char*));
	  libtar_list_t * l = libtar_list_new(LIST_QUEUE, NULL);
	  for (i = 0; i < argc; i++) {
		argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
		libtar_list_add(l, argv[i]);
	  }
	  if ( knh_create_tar(outfile,"./",l) == 0 ) {
		KNH_RETURN_Boolean(ctx,sfp,1);
	  } else {
		remove(outfile);
		KNH_THROWs(ctx,"[libtar] create_tar");
	  }
	} else {
	  KNH_THROWs(ctx,"Type!!: data[2] must be String");
	}
  } else {
	KNH_THROWs(ctx,"Type!!: data[1] must be String[]");
  }
  KNH_RETURN_Boolean(ctx,sfp,0);
}

/* ************************************************************************ */

