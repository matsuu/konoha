
/*
 *  konoha library
 *  sfcc
 */

#include <konoha.h>
#include <cimc/cimc.h>
#include <CimClientLib/cmci.h>
#include <CimClientLib/native.h>
#include <CimClientLib/cmcimacs.h>
#include <unistd.h>
#include <stdlib.h>




#ifdef __cplusplus
extern "C" {
#endif
  /*
// NewCIMCEnv
METHOD Sfcc_mkCIMCEnv(Ctx *ctx, knh_sfp_t *sfp)
{
  char *sval = p_char(sfp[1]);
  int   ival = p_int(sfp[2]);
  int   rc = p_int(sfp[3]);
  char *msg = p_char(sfp[4]);
  CIMCEnv *ret;
  ret = NewCIMCEnv(sval, ival, &rc, &msg);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCEnv", ret, NULL));
}
  */
// NewCIMCEnv_rc
METHOD Sfcc_mkCIMCEnvrc(Ctx *ctx, knh_sfp_t *sfp)
{
  char *sval = p_char(sfp[1]);
  int   ival = p_int(sfp[2]);
  int rc;
  char *msg;
  CIMCEnv *ce;
  int ret;
  ce = NewCIMCEnv(sval, ival, &rc, &msg);
  ret = rc;
  KNH_RETURN_Int(ctx,sfp,ret);
}

// NewCIMCEnv_msg
METHOD Sfcc_mkCIMCEnvmsg(Ctx *ctx, knh_sfp_t *sfp)
{
  char *sval = p_char(sfp[1]);
  int   ival = p_int(sfp[2]);
  int   rc;
  char *ret;
  CIMCEnv *ce;
  ce = NewCIMCEnv(sval, ival, &rc, &ret);
  if(ret == NULL){
    KNH_RETURN(ctx, sfp, new_String(ctx, B(""), NULL));
  }
  else{
    KNH_RETURN(ctx, sfp, new_String(ctx, B(ret), NULL));
  }
}

// NewCIMCEnv_ce
METHOD Sfcc_mkCIMCEnvce(Ctx *ctx, knh_sfp_t *sfp)
{
  char *sval = p_char(sfp[1]);
  int   ival = p_int(sfp[2]);
  int   rc;
  char *msg;
  CIMCEnv *ret;
  ret = NewCIMCEnv(sval, ival, &rc, &msg);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCEnv", ret, NULL));
}





  /*
// CMRelease なくてもいいかも
METHOD Sfcc_CMRelease(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCStatus status;
  status.msg = p_char(sfp[1]);
  CMRelease(status.msg);
  KNH_RETURN_void(ctx,sfp); 
}
  */
// CIMCEnv_connect
   /*
METHOD CIMCEnv_connect(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv* self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  char *s2 = p_char(sfp[2]);
  char *s3 = p_char(sfp[3]);
  char *s4 = p_char(sfp[4]);
  char *s5 = p_char(sfp[5]);
  CIMCStatus status;// = ((sfp[6].glue)->ptr);
  CIMCClient *ret;
  ret = self->ft->connect(self, s1, s2, s3, s4, s5, &status);
  printf("rc=%d msg=%s\n",(int)status.rc,(char*)status.msg);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCClient", ret, NULL));
}
   */

METHOD CIMCEnv_connectrc(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv* self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  char *s2 = p_char(sfp[2]);
  char *s3 = p_char(sfp[3]);
  char *s4 = p_char(sfp[4]);
  char *s5 = p_char(sfp[5]);
  CIMCStatus status;
  CIMCClient *cl;
  int ret;
  cl = self->ft->connect(self, s1, s2, s3, s4, s5, &status);
  ret = (int)status.rc;
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD CIMCEnv_connectmsg(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv* self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  char *s2 = p_char(sfp[2]);
  char *s3 = p_char(sfp[3]);
  char *s4 = p_char(sfp[4]);
  char *s5 = p_char(sfp[5]);
  CIMCStatus status;
  CIMCClient *cl;
  cl = self->ft->connect(self, s1, s2, s3, s4, s5, &status);
  if(status.msg == NULL){
    KNH_RETURN(ctx, sfp, new_String(ctx, B(""), NULL));
  }
  else{
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)status.msg->hdl), NULL));
  }
}

METHOD CIMCEnv_connectcl(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv* self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  char *s2 = p_char(sfp[2]);
  char *s3 = p_char(sfp[3]);
  char *s4 = p_char(sfp[4]);
  char *s5 = p_char(sfp[5]);
  CIMCStatus status;
  CIMCClient *ret;
  ret = self->ft->connect(self, s1, s2, s3, s4, s5, &status);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCClient", ret, NULL));
}


 





/*
// CIMCEnv_newObjectPath
METHOD CIMCEnv_newObjectPath(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  CIMCStatus *status = ((sfp[2].glue)->ptr);
  CIMCObjectPath *ret;
  ret = self->ft->newObjectPath(self, s1, NULL, status);
  printf("op=%s\n",(char*)ret->hdl);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCObjectPath", ret, NULL));
}
*/


// CIMCEnv_newObjectPath_rc
METHOD CIMCEnv_newObjectPathrc(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  CIMCStatus status;
  CIMCObjectPath *op;
  int ret;
  op = self->ft->newObjectPath(self, s1, NULL, &status);
  ret = (int)status.rc;
  KNH_RETURN_Int(ctx,sfp,ret);
}

// CIMCEnv_newObjectPath_msg
METHOD CIMCEnv_newObjectPathmsg(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  CIMCStatus status;
  CIMCObjectPath *op;
  op = self->ft->newObjectPath(self, s1, NULL, &status);
  if(status.msg == NULL){
    KNH_RETURN(ctx, sfp, new_String(ctx, B(""), NULL));
  }
  else{
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)status.msg->hdl), NULL));
  }
}

// CIMCEnv_newObjectPath_op
METHOD CIMCEnv_newObjectPathop(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *self = ((sfp[0].glue)->ptr);
  char *s1 = p_char(sfp[1]);
  CIMCStatus status;
  CIMCObjectPath *ret;
  ret = self->ft->newObjectPath(self, s1, NULL, &status);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCObjectPath", ret, NULL));
}


  /*
// CIMCClient_enumClassNames
METHOD CIMCClient_enumClassNames(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *self = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  int ival = p_int(sfp[2]);
  CIMCStatus *status = ((sfp[3].glue)->ptr);
  CIMCEnumeration *ret;
  ret = self->ft->enumClassNames(self, op, ival, status);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCEnumeration", ret, NULL));
}
  */

// CIMCClient_enumClassNames_rc
METHOD CIMCClient_enumClassNamesrc(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *self = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  int ival = p_int(sfp[2]);
  CIMCStatus status;
  CIMCEnumeration *enm;
  int ret;
  enm = self->ft->enumClassNames(self, op, ival, &status);
  ret = (int)status.rc;
  KNH_RETURN_Int(ctx,sfp,ret);
}

// CIMCClient_enumClassNames_msg
METHOD CIMCClient_enumClassNamesmsg(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *self = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  int ival = p_int(sfp[2]);
  CIMCStatus status;
  CIMCEnumeration *enm;
  enm = self->ft->enumClassNames(self, op, ival, &status);
  if(status.msg == NULL){
    KNH_RETURN(ctx, sfp, new_String(ctx, B(""), NULL));
  }
  else{
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)status.msg->hdl), NULL));
  }
}

// CIMCClient_enumClassNames_enm
METHOD CIMCClient_enumClassNamesenm(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *self = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  int ival = p_int(sfp[2]);
  CIMCStatus status;
  CIMCEnumeration *ret;
  ret = self->ft->enumClassNames(self, op, ival, &status);
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCEnumeration", ret, NULL));
}


// CIMCEnumeration_hasNext
METHOD CIMCEnumeration_hasNext(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnumeration *self = ((sfp[0].glue)->ptr);
  int ret;
  if(self->ft->hasNext(self, NULL)){
    ret = 1;
  }
  else{
    ret = 0;
  }
  KNH_RETURN_Boolean(ctx, sfp, ret);
}

// CIMCEnumeration_getNext + op = data.value.ref
METHOD CIMCEnumeration_getNext(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnumeration *self = ((sfp[0].glue)->ptr);
  CIMCData data;
  CIMCObjectPath *ret;
  data = self->ft->getNext(self, NULL);
  ret = data.value.ref; 
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCObjectPath", ret, NULL));
}

// CIMCObjectPath_toString
METHOD CIMCObjectPath_toString(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCObjectPath *self = ((sfp[0].glue)->ptr);
  CIMCString *ret;
  //char *ret;
  ret = self->ft->toString(self, NULL);
  //ret = str->ft->getCharPtr(str,NULL);
  //printf("result: %s\n",(char*)ret->hdl);
  //KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMCString", ret, NULL));
  KNH_RETURN(ctx,sfp,new_String(ctx,B((char*)ret->hdl),NULL));
}

// CIMCString_getChar
METHOD CIMCString_getCharPtr(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCString *self = ((sfp[0].glue)->ptr);
  char ret[1024] = {0};
  char *str;
  int len;
  str = self->ft->getCharPtr(self, NULL);
  len = strlen(str);
  strncpy(ret,str,len);
  KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// CIMCEnv_release
METHOD CIMCEnv_release(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *self = ((sfp[0].glue)->ptr);
  self->ft->release(self);
  KNH_RETURN_void(ctx, sfp);
}

// CIMCClient_release
METHOD CIMCClient_release(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *self = ((sfp[0].glue)->ptr);
  self->ft->release(self);
  KNH_RETURN_void(ctx, sfp);
}

// CIMCObjectPath_release
METHOD CIMCObjectPath_release(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCObjectPath *self = ((sfp[0].glue)->ptr);
  self->ft->release(self);
  KNH_RETURN_void(ctx, sfp);
}

// CIMCEnumeration_release
METHOD CIMCEnumeration_release(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnumeration *self = ((sfp[0].glue)->ptr);
  self->ft->release(self);
  KNH_RETURN_void(ctx, sfp);
}




// init
KNH_EXPORTS(int) init(Ctx *ctx)
{
    KNH_NOTICE(ctx, "loading sfcc..");
    return 1;
}

#ifdef __cplusplus
}
#endif

