#include <konoha.h>
#include <bfd.h>
#include <assert.h>


static
knh_IntConstData_t IntConstData[] = {
  {"Bfd.BFD_UNKNOWN",bfd_unknown},
  {"Bfd.BFD_OBJECT", bfd_object},
  {"Bfd.BFD_ARCHIVE",bfd_archive},
  {"Bfd.BFD_CORE2",bfd_core},
  {NULL}
};

struct mini{
  size_t size;
  void *minisyms;
};

void knh_bfd_free(Ctx *ctx,knh_Glue_t *g){
   bfd * bfdp = (bfd*)g->ptr;

    if(bfdp!=NULL){
        bfd_close(bfdp);
    }
    g->ptr = NULL;
}

bfd *knh_bfd_openr(const char *filename,const char *target)
{
  bfd *abfd= bfd_openr(filename,target);
  return abfd;
}

METHOD Bfd_new(Ctx *ctx, knh_sfp_t *sfp)
{
  char * filename = (char *)p_char(sfp[1]);
  char * target = (char *)p_char(sfp[2]);
  bfd *abfd;
  if (strlen(target) == 0) {
    // its same as NULL
    abfd = knh_bfd_openr(filename, NULL);
  } else {
    abfd = knh_bfd_openr(filename, target);
  }
  assert(abfd);
  //  knh_Glue_t *glue = sfp[0].glue;
  //glue->ptr = (void *)abfd;
  knh_Glue_init(ctx,sfp[0].glue,abfd,knh_bfd_free);
  KNH_RETURN(ctx,sfp,sfp[0].o);
}

METHOD Bfd_checkformat(Ctx *ctx, knh_sfp_t *sfp)
{
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  assert(abfd);
  bfd_format format = p_int(sfp[1]);
  int ret = bfd_check_format(abfd, format);
  KNH_RETURN_Int(ctx,sfp,ret);
}

KNH_EXPORTS(int) init(Ctx *ctx)
{
  konoha_loadIntConstData(ctx, IntConstData);

  return 1;
}

METHOD Bfd_makeEmptySymbol(Ctx *ctx, knh_sfp_t *sfp)
{
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  asymbol *store = bfd_make_empty_symbol(abfd);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,(char *)"bfd.Asymbol",store,NULL));
}

struct mini *mini_new(Ctx *ctx)
{
  struct mini *ret =(struct mini*)KNH_MALLOC(ctx,sizeof(struct mini));
  ret->size=0;
  ret->minisyms=NULL;
  return ret;
}

METHOD Minisyms_new(Ctx *ctx, knh_sfp_t *sfp)
{
  struct mini *mi = mini_new(ctx);
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = (void *)mi;
  KNH_RETURN(ctx,sfp,sfp[0].o);
}

METHOD Bfd_readMinisymbols(Ctx *ctx, knh_sfp_t *sfp)
{
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  int dyn = p_int(sfp[1]);
  struct mini *mi = (struct mini *)p_cptr(sfp[2]);
  void *minisyms;
  size_t size = 0;
  int symnum;
  symnum = bfd_read_minisymbols(abfd,dyn,&minisyms,&size);
  mi->minisyms = minisyms;
  mi->size = size;
  knh_Glue_t *glue = sfp[2].glue;
  glue->ptr = (void *)mi;
  KNH_RETURN_Int(ctx,sfp,symnum);
}

METHOD Bfd_minisymbolToSymbol(Ctx *ctx, knh_sfp_t *sfp)
{
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  int dyn = p_int(sfp[1]);
  struct mini *mi = (struct mini *)p_cptr(sfp[2]);
  char *p = (char *)(mi->minisyms);
  asymbol *store = (asymbol *)p_cptr(sfp[3]);
  asymbol *sym = bfd_minisymbol_to_symbol(abfd,dyn,p,store);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,(char *)"bfd.Asymbol",sym,NULL));
}

METHOD Asymbol_getName(Ctx *ctx, knh_sfp_t *sfp)
{
  asymbol *sym = (asymbol *)p_cptr(sfp[0]);
  const char *name = bfd_asymbol_name(sym);
  String *ret=new_String(ctx,B(name),NULL);
  KNH_RETURN(ctx, sfp, ret);
}

METHOD Asymbol_getValue(Ctx *ctx, knh_sfp_t *sfp)
{
  asymbol *sym = (asymbol *)p_cptr(sfp[0]);
  int value = bfd_asymbol_value(sym);
  KNH_RETURN_Int(ctx, sfp, value);
}

METHOD Minisyms_copyPointer(Ctx *ctx, knh_sfp_t *sfp)
{
  struct mini *p = (struct mini *)p_cptr(sfp[0]);
  struct mini *t = (struct mini *)p_cptr(sfp[1]);
  p->minisyms = t->minisyms;
  p->size = t->size;
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = p;
  KNH_RETURN_void(ctx,sfp);
}

METHOD Minisyms_nextSymbol(Ctx *ctx, knh_sfp_t *sfp)
{
  struct mini *mi= (struct mini *)p_cptr(sfp[0]);
  void *p = mi->minisyms;
  size_t size = mi->size;
  p += size;
  mi->minisyms = p;
  knh_Glue_t *glue = sfp[0].glue;
  glue->ptr = mi;
  KNH_RETURN_void(ctx,sfp);
}

METHOD Bfd_printAllSymbols(Ctx *ctx, knh_sfp_t *sfp)
{
  void *minisyms;
  asymbol *store;
  int symnum,i;
  char *p;
  size_t size;
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  int dyn = p_int(sfp[1]);
  store = bfd_make_empty_symbol(abfd);
  symnum = bfd_read_minisymbols(abfd, dyn,&minisyms,&size);
  assert(symnum >= 0);
  
  p = (char *)minisyms;
  for(i = 0; i<symnum ; i++){
    asymbol *sym = bfd_minisymbol_to_symbol(abfd,dyn,p,store);
    const char *name = bfd_asymbol_name(sym);
    int value = bfd_asymbol_value(sym);
    printf("%08x  %s\n",value, name);
    p += size;
  }
  free(minisyms);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Bfd_getSymbolSize(Ctx *ctx, knh_sfp_t *sfp)
{
  asymbol *store;
  char *p,*q;
  void *minisyms;
  int symnum, i, j, k, value2, long_of_func=0;
  size_t size;
  bfd *abfd = (bfd *)p_cptr(sfp[0]);
  int dyn = p_int(sfp[1]);
  const char *funcname = (char *)p_char(sfp[2]);
  store = bfd_make_empty_symbol(abfd);
  symnum = bfd_read_minisymbols(abfd, dyn, &minisyms, &size);
  assert(symnum >= 0);
  p = q = (char *)minisyms;

  for(i = 0; i < symnum;i++){
    asymbol *sym = bfd_minisymbol_to_symbol(abfd, dyn, p, store);
    const char *name = bfd_asymbol_name(sym);
    if(strncmp(name,funcname,strlen(name))==0){
      int value = bfd_asymbol_value(sym);
      k=0;
      for(j = 0; j < symnum; j++){
	asymbol *sym2 = bfd_minisymbol_to_symbol(abfd, dyn, q, store);
	value2 = bfd_asymbol_value(sym2);
	if((value2>value)&&((value2<k)||(k == 0))){
	  k = value2;
	}
	q += size;
      }
      value2=k;
      long_of_func=value2-value;
    }
    p += size;
  }
  free(minisyms);
  KNH_RETURN_Int(ctx,sfp,long_of_func);
}
