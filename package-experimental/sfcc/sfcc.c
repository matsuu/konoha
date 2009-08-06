/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2005-2008, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Software Foundation
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * See www.konohaware.org/license.html for further information.
 *
 * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
 * (2) Konoha Software Foundation License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <konoha.h>
#include <konoha/gen/konoha_proto_.h>
#include <unistd.h>
#include <stdlib.h>
#include <cimc/cimc.h>
#include <CimClientLib/cmci.h>
#include <CimClientLib/native.h>
#include <CimClientLib/cmcimacs.h>
#include "show.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================== */
/* Exception  */

static
void knh_throw_CIMException(Ctx *ctx, int rc, char *msg)
{
  //TODO: throw CIM!! with parameters
  KNH_THROWs(ctx, msg);
}

/* ------------------------------------------------------------------------ */

static
void knh_throw_CIMCStatus(Ctx *ctx, CIMCStatus *status)
{
  //TODO: throw CIM!! with parameters
  KNH_THROWs(ctx, (char*)status->msg->hdl);
}

/* ======================================================================== */
/* [CIMCEnv] WBET/XML Only */

static CIMCEnv *knh_sharedCIMEnv = NULL;

static CIMCEnv *getCIMCEnv(Ctx *ctx)
{
  if(knh_sharedCIMEnv == NULL) {
    int rc;
    char *msg;
    knh_sharedCIMEnv = NewCIMCEnv("XML", 0, &rc, &msg);
    if(knh_sharedCIMEnv == NULL) {
      knh_throw_CIMException(ctx, rc, msg);
    }
  }
  return knh_sharedCIMEnv;
}

/* ======================================================================== */
/* [CIMObjectPath] */

static void knh_fgfree_CIMCObjectPath(Ctx *ctx, knh_Glue_t *g)
{
  CIMCObjectPath *op = (CIMCObjectPath*)g->ptr;
  op->ft->release(op);
}

/* ------------------------------------------------------------------------ */
/* @method CIMObjectPath CIMObjectPath.new(String! path,String packname) */

METHOD CIMObjectPath_new(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *env = getCIMCEnv(ctx);
  char *path = p_char(sfp[1]);
  CIMCStatus status;
  char *packname = p_char(sfp[2]);
  if(strncmp(packname,"",1) == 0){
    packname = NULL;
  }
  CIMCObjectPath *op = env->ft->newObjectPath(env, path, packname, &status);
  if(op == NULL || status.rc != 0) {
    knh_throw_CIMCStatus(ctx, &status);
  }
  knh_Glue_init(ctx, sfp[0].glue, op, knh_fgfree_CIMCObjectPath);
  KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method CIMObjectPath CIMObjectPath.addKey(String! path,String packname) */
METHOD CIMObjectPath_addKey(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCObjectPath *self = ((sfp[0].glue)->ptr);
  char *name = p_char(sfp[1]);
  char *value = p_char(sfp[2]);
  CIMCStatus status;
  status = self->ft->addKey(self, name, (CIMCValue*)value,CIMC_chars);
  if(status.rc != 0){
    knh_throw_CIMCStatus(ctx, &status);
  }
  else{
    KNH_RETURN_void(ctx,sfp);
  }
}


/* ------------------------------------------------------------------------ */
/* @method void CIMObjectPath.%s(OutputStream! w, String! m) ??? */

METHOD CIMObjectPath_toString(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCObjectPath *op = ((sfp[0].glue)->ptr);
  CIMCStatus status;
  CIMCString *cs = op->ft->toString(op, &status);
  if(status.rc){
    knh_throw_CIMCStatus(ctx,&status);
  }
  KNH_RETURN(ctx,sfp,new_String(ctx,B((char*)cs->hdl),NULL));
}

/* ======================================================================== */
/* [CIMClient] */

static
void knh_fgfree_CIMCClient(Ctx *ctx, knh_Glue_t *g)
{
  CIMCClient *cc = (CIMCClient*)g->ptr;
  cc->ft->release(cc);
}

/* ------------------------------------------------------------------------ */
/* @method CIMClient CIMClient.new(String! url) */

METHOD CIMClient_new(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *env = getCIMCEnv(ctx);
  CIMCClient *cc;
  CIMCStatus status;
  /*
  if(IS_NULL(sfp[0].s)) {
  char *pwd = knh_getPassword(ctx, STEXT("konoha"));
  cc = env->ft->connect(env, "localhost", "http", "5988", "konoha", pwd, &status);
  }
  else {
    knh_bytes_t url = knh_String_tobytes(sfp[1].s);
    char bfscheme[20], bfhost[256];
    char bfuname[20], bfport[20];
    int port = 5988;
    knh_bytes_parseURLscheme(url, bfscheme, sizeof(bfscheme));
    knh_bytes_parseURLhost(url, bfhost, sizeof(bfhost));
    knh_bytes_parseURLuname(url, bfuname, sizeof(bfuname));
    knh_bytes_parseURLport(url, &port);
    knh_snprintf(bfport, sizeof(bfport), "%d", port);
    cc = env->ft->connect(env, bfhost, bfscheme, bfport, bfuname, knh_getPassword(ctx, url), &status);
    }
  */

  char *cimhost = p_char(sfp[1]);
  char *s3 = "5988";
  char *s4 = "root";
  char *s5 = "password";
  cc = env->ft->connect(env, cimhost, "http", s3, s4, s5, &status);

  if(cc == NULL || status.rc != 0) {
    knh_throw_CIMCStatus(ctx, &status);
  }
  knh_Glue_init(ctx, sfp[0].glue, cc, knh_fgfree_CIMCClient);
  KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */

static
ITRNEXT knh_enumClassNames(Ctx *ctx, knh_sfp_t *sfp, int n)
{
  //asm("int3");
  CIMCEnumeration *enm = (CIMCEnumeration *)DP(sfp[0].it)->ref;
  if(enm != NULL) {
    if(enm->ft->hasNext(enm, NULL)) {
      CIMCData data = enm->ft->getNext(enm, NULL);
      CIMCObjectPath *op = data.value.ref;
      CIMCString *path = op->ft->toString(op, NULL);
      String *s = new_String(ctx, B((char*)path->hdl), NULL);
      KNH_ITRNEXT(ctx, sfp, n, s);
    }
  }
  KNH_ITREND(ctx, sfp, n);
}

/* ------------------------------------------------------------------------ */

static
void knh_ffree_CIMCEnumeration(void *ref)
{
  CIMCEnumeration *enm = (CIMCEnumeration *)ref;
  if(enm != NULL) {
    enm->ft->release(enm);
  }
}

/* ------------------------------------------------------------------------ */
/* @method String.. CIMClient.enumClassNames(CIMObjectPath! path) */

METHOD CIMClient_enumClassNames(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *cc = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  CIMCEnumeration *enm;
  if(cc != NULL && op != NULL) {
    CIMCStatus status;
    enm = cc->ft->enumClassNames(cc, op, 0, &status);
    if(status.rc != 0) {
      knh_throw_CIMCStatus(ctx, &status);
    }
  }
  KNH_RETURN(ctx, sfp,new_GlueIterator(ctx, CLASS_String, enm, knh_enumClassNames, knh_ffree_CIMCEnumeration));
}

/* ------------------------------------------------------------------------ */
/* @method String CIMClient.invokeMethod(CIMObjectPath op, String name, String arg) */

METHOD CIMClient_invokeMethod(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCEnv *env = getCIMCEnv(ctx);
  CIMCClient *cc = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  char *name =  p_char(sfp[2]);
  char *arg = p_char(sfp[3]);
  //int i,argc;
  char *ret;
  //char **argv;
  CIMCStatus check;
  CIMCArgs *inargs = env->ft->newArgs(env,&check);
  CIMCArgs *outargs = NULL;
  CIMCData data;
  CIMCStatus status;
  //char c[64] = {0};
  //argc = knh_Array_size(a);

  //argv = (char **)alloca(argc * sizeof(char*));
  //for (i = 0; i < argc; i++) {
  //argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
  //}

  //for(i=0;i<argc;i++){
  //if(strncmp(argv[i],"",1) != 0){
  //snprintf(c,64,"a%d",i);
  ((CMPIArgs*)inargs)->ft->addArg((CMPIArgs*)inargs, "a0", (CMPIValue*)arg, CMPI_chars);
  //}
  //}
  if(cc != NULL && op != NULL) {
    data = cc->ft->invokeMethod(cc, op, name, inargs, outargs, &status);
    if(status.rc != 0) {
      knh_throw_CIMCStatus(ctx, &status);
    }
  };
  ret = value2Chars(data.type,&data.value);
  KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* ------------------------------------------------------------------------ */

static
ITRNEXT knh_enumInstanceNames(Ctx *ctx, knh_sfp_t *sfp, int n)
{
  CIMCEnumeration *enm = (CIMCEnumeration *)DP(sfp[0].it)->ref;
  if(enm != NULL) {
    if(enm->ft->hasNext(enm, NULL)) {
      CIMCData data = enm->ft->getNext(enm, NULL);
      CIMCObjectPath *op = data.value.ref;
      CIMCString *path = op->ft->toString(op, NULL);
      String *s = new_String(ctx, B((char*)path->hdl), NULL);
      KNH_ITRNEXT(ctx, sfp, n, s);
    }
  }
  KNH_ITREND(ctx, sfp, n);
}


/* ------------------------------------------------------------------------ */
/* @method String.. CIMClient.enumInstanceNames(CIMObjectPath! path) */

METHOD CIMClient_enumInstanceNames(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCClient *cc = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  CIMCEnumeration *enm;
  if(cc != NULL && op != NULL) {
    CIMCStatus status;
    enm = cc->ft->enumInstanceNames(cc, op, &status);
    if(status.rc != 0) {
      knh_throw_CIMCStatus(ctx, &status);
    }
  }
  KNH_RETURN(ctx, sfp,new_GlueIterator(ctx, CLASS_String, enm, knh_enumInstanceNames, knh_ffree_CIMCEnumeration));
}

/* ------------------------------------------------------------------------ */

static
ITRNEXT knh_referenceNames(Ctx *ctx, knh_sfp_t *sfp, int n)
{
  asm("int3");
  CIMCEnumeration *enm = (CIMCEnumeration *)DP(sfp[0].it)->ref;
  if(enm != NULL) {
    if(enm->ft->hasNext(enm, NULL)) {
      CIMCData data = enm->ft->getNext(enm, NULL);
      CIMCObjectPath *op = data.value.ref;
      CIMCString *path = op->ft->toString(op, NULL);
      String *s = new_String(ctx, B((char*)path->hdl), NULL);
      KNH_ITRNEXT(ctx, sfp, n, s);
    }
  }
  KNH_ITREND(ctx, sfp, n);
}


/* ------------------------------------------------------------------------ */
/* @method String.. CIMClient.referenceNames(CIMObjectPath! path) */

METHOD CIMClient_referenceNames(Ctx *ctx, knh_sfp_t *sfp)
{
  //asm("int3");
  CIMCClient *cc = ((sfp[0].glue)->ptr);
  CIMCObjectPath *op = ((sfp[1].glue)->ptr);
  CIMCEnumeration *enm;
  if(cc != NULL && op != NULL) {
    CIMCStatus status;
    enm = cc->ft->referenceNames(cc, op, NULL, NULL, &status);
    if(status.rc != 0) {
      knh_throw_CIMCStatus(ctx, &status);
    }
  }
  KNH_RETURN(ctx, sfp,new_GlueIterator(ctx, CLASS_String, enm, knh_referenceNames, knh_ffree_CIMCEnumeration));
}

/* ======================================================================== */
/* [CIMInstance] */

static
void knh_fgfree_CIMInstance(Ctx *ctx, knh_Glue_t *g)
{
  CIMCInstance *ins = (CIMCInstance*)g->ptr;
  ins->ft->release(ins);
}

/* ------------------------------------------------------------------------ */
/* @method CIMInstance CIMInstance.new(CIMClient cc,CIMObjectPath op) */

METHOD CIMInstance_new(Ctx *ctx, knh_sfp_t *sfp)
{
  //asm("int3");
  CIMCClient *cc = ((sfp[1].glue)->ptr);
  CIMCObjectPath *op = ((sfp[2].glue)->ptr);
  CIMCStatus status;
  CIMCInstance *ins;
  ins = cc->ft->getInstance(cc, op, 0, NULL, &status);
  if(ins == NULL || status.rc != 0) {
    knh_throw_CIMCStatus(ctx, &status);
  }
  knh_Glue_init(ctx, sfp[0].glue, ins, knh_fgfree_CIMInstance);
  KNH_RETURN(ctx, sfp, sfp[0].o);
}

/* ------------------------------------------------------------------------ */
/* @method CIMObjectPath CIMInstance.getObjectPath() */

METHOD CIMInstance_getObjectPath(Ctx *ctx, knh_sfp_t *sfp)
{
  //asm("int3");
  CIMCObjectPath *ret;
  CIMCStatus status;
  CIMCInstance *ins = ((sfp[0].glue)->ptr);
  ret = ins->ft->getObjectPath(ins,&status);
  if(ret == NULL || status.rc != 0) {
    knh_throw_CIMCStatus(ctx, &status);
  }
  KNH_RETURN(ctx,sfp, new_Glue(ctx,"sfcc.CIMObjectPath", ret, NULL));
}


/* ------------------------------------------------------------------------ */
/* @method String[] CIMInstance.getProperty() */

METHOD CIMInstance_getProperty(Ctx *ctx, knh_sfp_t *sfp)
{
  CIMCInstance *ins = ((sfp[0].glue)->ptr);
  CIMCStatus status;
  CIMCObjectPath *op = ins->ft->getObjectPath(ins,&status);
  CIMCString * opname = op->ft->toString(op, NULL);
  CIMCString * namespace = op->ft->getNameSpace(op, NULL);
  CIMCString * classname = op->ft->getClassName(op, NULL);
  int numproperties = ins->ft->getPropertyCount(ins, NULL);
  int i;
  char *valuestr;
  char ret[128]={0};
  Array *a = new_Array(ctx, CLASS_String, 0);
  if(numproperties){
    for(i=0; i<numproperties; i++){
      CIMCString * propertyname;
      CIMCData data = ins->ft->getPropertyAt(ins, i,
						  &propertyname, NULL);
      if(data.state == CIMC_goodValue){
        if(CMIsArray(data)){
	  CIMCArray *arr   = data.value.array;
	  CIMCType  eletyp = data.type & ~CIMC_ARRAY;
	  int j, n;
	  n = (int)arr->ft->getSize(arr, NULL);
	  for(j = 0; j < n; ++j){
	    CIMCData ele = arr->ft->getElementAt(arr, (CIMCCount)j, NULL);
	    valuestr = value2Chars(eletyp, &ele.value);
	    snprintf(ret,128,"%s = %s",(char*)propertyname->hdl,valuestr);
	    knh_Array_add(ctx, a, UP(new_String(ctx, B(ret), NULL)));
	    free (valuestr);
	  }
        }
        else{
	  if(data.state == CIMC_goodValue){
	    valuestr = value2Chars(data.type, &data.value);
	    snprintf(ret,128,"%s = %s",(char*)propertyname->hdl,valuestr);
	    knh_Array_add(ctx, a, UP(new_String(ctx, B(ret), NULL)));
	    free (valuestr);
	  }
	}
      }
      CMRelease(propertyname);
    }
  }
  else{
    knh_Array_add(ctx, a, UP(new_String(ctx, B("No properties!"), NULL)));
  }
  if (classname) CMRelease(classname);
  if (namespace) CMRelease(namespace);
  if (opname) CMRelease(opname);
  if (op) CMRelease(op);
  if(a == NULL || status.rc != 0) {
    knh_throw_CIMCStatus(ctx, &status);
  }
  KNH_RETURN(ctx, sfp, a);
}

/* ======================================================================== */
// init
KNH_EXPORTS(int) init(Ctx *ctx)
{
  KNH_NOTICE(ctx, "loading sfcc..");
  return 1;
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

