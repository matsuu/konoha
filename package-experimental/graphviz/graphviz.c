#include <konoha.h>
#include <graphviz/gvc.h>


#ifdef __cplusplus
extern "C" {
#endif
    

  /*--------------------Const Data------------------------*/
static
knh_IntConstData_t IntConstData[] = {
  {"GV.AG_DIGRAPH",AGDIGRAPH},
  {NULL}
};

  /*--------------------Class GV--------------------------*/

METHOD GV_agSafeset(Ctx *ctx,knh_sfp_t *sfp)
{
  void *obj = (sfp[1].glue)->ptr;
  char *name = p_char(sfp[2]);
  char *value = p_char(sfp[3]);
  char *def = p_char(sfp[4]);
  agsafeset(obj,name,value,def);
  KNH_RETURN_void(ctx,sfp);
}

  /*---------------------Class GVC------------------------*/

METHOD GVC_new(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = gvContext();
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"graphviz.GVC",gvc,NULL));
}

METHOD GVC_gvParseArgs(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = (sfp[0].glue)->ptr;
  int i,argc;
  char **argv;
  Array *a = (Array *)sfp[1].o;
  argc = knh_Array_size(a);
  argv = (char **)alloca(argc * sizeof(char*));
  for (i = 0; i < argc; i++) {
	argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
  }
  gvParseArgs(gvc,argc,argv);
  KNH_RETURN_void(ctx,sfp);
}

METHOD GVC_gvLayoutJobs(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = (sfp[0].glue)->ptr;
  Agraph_t *g = (sfp[1].glue)->ptr;
  gvLayoutJobs(gvc,g);
  KNH_RETURN_void(ctx,sfp);
}

METHOD GVC_gvRenderJobs(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = (sfp[0].glue)->ptr;
  Agraph_t *g = (sfp[1].glue)->ptr;
  gvRenderJobs(gvc,g);
  KNH_RETURN_void(ctx,sfp);
}

METHOD GVC_gvFreeLayout(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = (sfp[0].glue)->ptr;
  Agraph_t *g = (sfp[1].glue)->ptr;
  gvFreeLayout(gvc,g);
  KNH_RETURN_void(ctx,sfp);
}

METHOD GVC_gvFreeContext(Ctx *ctx,knh_sfp_t *sfp)
{
  GVC_t *gvc = (sfp[0].glue)->ptr;
  gvFreeContext(gvc);
  KNH_RETURN_void(ctx,sfp);
}

  /*---------------------------Class Agraph-----------------------------*/

METHOD Agraph_new(Ctx *ctx,knh_sfp_t *sfp)
{
  char *name = p_char(sfp[1]);
  int kind = p_int(sfp[2]);
  Agraph_t *g = agopen(name,kind);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"graphviz.Agraph",g,NULL));
}

METHOD Agraph_agclose(Ctx *ctx,knh_sfp_t *sfp)
{
  Agraph_t *g = (sfp[0].glue)->ptr;
  agclose(g);
  KNH_RETURN_void(ctx,sfp);
}

  /*----------------------------Class Agnode-----------------------------*/

METHOD Agnode_new(Ctx *ctx,knh_sfp_t *sfp)
{
  Agraph_t *g = (sfp[1].glue)->ptr;
  char *name = p_char(sfp[2]);
  Agnode_t *ret = agnode(g,name);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"graphviz.Agnode",ret,NULL));
}

  /*---------------------------Class Agedge------------------------------*/

METHOD Agedge_new(Ctx *ctx,knh_sfp_t *sfp)
{
  Agraph_t *g = (sfp[1].glue)->ptr;
  Agnode_t *start = (sfp[2].glue)->ptr;
  Agnode_t *end = (sfp[3].glue)->ptr;
  Agedge_t *ret = agedge(g,start,end);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"graphviz.Agedge",ret,NULL));
}


/*----------------------------- init-------------------------------*/

KNH_EXPORTS(int) init(Ctx *ctx)
{
   KNH_NOTICE(ctx, "loading sample..");
   knh_loadIntConstData(ctx,IntConstData);
   return 1;
}

#ifdef __cplusplus
}
#endif
