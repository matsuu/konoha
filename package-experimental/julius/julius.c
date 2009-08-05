#include <konoha.h>
#include <julius/jfunc.h>
#include <julius/juliuslib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

  /*--------------------Const Data------------------------*/
static
knh_IntConstData_t IntConstData[] = {
  {"Julius.SP_NETAUDIO",SP_NETAUDIO},
  {"Julius.SP_MIC",SP_MIC},
  {"Julius.MAX_HMMNAME_LEN",MAX_HMMNAME_LEN},
  {"Julius.CALLBACK_EVENT_SPEECH_READY",CALLBACK_EVENT_SPEECH_READY},
  {"Julius.CALLBACK_EVENT_SPEECH_START",CALLBACK_EVENT_SPEECH_START},
  {"Julius.CALLBACK_RESULT",CALLBACK_RESULT},
  {"Julius.J_RESULT_STATUS_REJECT_POWER",J_RESULT_STATUS_REJECT_POWER},
  {"Julius.J_RESULT_STATUS_TERMINATE",J_RESULT_STATUS_TERMINATE},
  {"Julius.J_RESULT_STATUS_ONLY_SILENCE",J_RESULT_STATUS_ONLY_SILENCE},
  {"Julius.J_RESULT_STATUS_REJECT_GMM",J_RESULT_STATUS_REJECT_GMM},
  {"Julius.J_RESULT_STATUS_REJECT_SHORT",J_RESULT_STATUS_REJECT_SHORT},
  {"Julius.J_RESULT_STATUS_FAIL",J_RESULT_STATUS_FAIL},
  {"Julius.LM_PROB",LM_PROB},
  {"Julius.LM_DFA",LM_DFA},
  {"Julius.PER_WORD",PER_WORD},
  {"Julius.PHONE_ME",PER_PHONEME},
  {"Julius.PER_STATE",PER_STATE},
  {"Julius.SP_MFCFILE",SP_MFCFILE},
  {"Julius.MAX_PATH_LEN",MAXPATHLEN},
  {"Julius.MAX_SEQ_NUM",MAXSEQNUM},
  {NULL}
};

  /*-------------------------Closure--------------------------------*/

Closure *func_recready = NULL;
Closure *func_recstart = NULL;
Closure *func_output_result = NULL;
Ctx julius_ctx;

static void knh_callback_recready(Recog* recog,char* data)
{ 
  Ctx *lctx = &julius_ctx;
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);
  Object *arg1 = new_Glue(lctx,"julius.Recog",recog,NULL);
  Object *arg2 = (Object*)new_String(lctx,B(" "),NULL);
  knh_putsfp(lctx,lsfp,2,(Object*)arg1);
  knh_putsfp(lctx,lsfp,3,(Object*)arg2);
  knh_Closure_invokesfp(lctx,func_recready,lsfp,2);
}
METHOD Recog_callbackAddFuncRecReady(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int code = p_int(sfp[1]);
  func_recready = sfp[2].cc;
  char* data = NULL;
  // fprintf(stderr, "thread");
  callback_add(recog,code,(void*)knh_callback_recready,data);
  KNH_RETURN_void(ctx,sfp);
}
  
static void knh_callback_recstart(Recog* recog,char* data)
{
  Ctx *lctx = &julius_ctx;
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);
  Object *arg1 = new_Glue(lctx,"julius.Recog",recog,NULL);
  Object *arg2 = (Object*)new_String(lctx,B(" "),NULL);
  knh_putsfp(lctx,lsfp,2,(Object*)arg1);
  knh_putsfp(lctx,lsfp,3,(Object*)arg2);
  knh_Closure_invokesfp(lctx,func_recstart,lsfp,2);
}
METHOD Recog_callbackAddFuncRecStart(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int code = p_int(sfp[1]);
  func_recstart = sfp[2].cc;
  char* data = NULL;
  // fprintf(stderr, "thread");
  callback_add(recog,code,(void*)knh_callback_recstart,data);
  KNH_RETURN_void(ctx,sfp);
}
static void knh_callback_output_result(Recog* recog,char* data)
{
  Ctx *lctx = &julius_ctx;
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);
  Object *arg1 = new_Glue(lctx,"julius.Recog",recog,NULL);
  Object *arg2 = (Object*)new_String(lctx,B(" "),NULL);
  knh_putsfp(lctx,lsfp,2,(Object*)arg1);
  knh_putsfp(lctx,lsfp,3,(Object*)arg2);
  knh_Closure_invokesfp(lctx,func_output_result,lsfp,2);
}
METHOD Recog_callbackAddFuncOutputResult(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int code = p_int(sfp[1]);
  func_output_result = sfp[2].cc;
  char* data = NULL;
  //fprintf(stderr, "thread");
  callback_add(recog,code,(void*)knh_callback_output_result,data);
  KNH_RETURN_void(ctx,sfp);
}


METHOD RecogProcess_new(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[1].glue)->ptr;
  RecogProcess* r = recog->process_list;
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"julius.RecogProcess",r,NULL));
}


METHOD WordInfo_new(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess *r = (sfp[1].glue)->ptr;
  WORD_INFO *winfo = r->lm->winfo;
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"julius.WordInfo",winfo,NULL));
}

METHOD Sentence_new(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess* r = (sfp[1].glue)->ptr;
  int n = p_int(sfp[2]);
  WORD_INFO* winfo = (sfp[3].glue)->ptr;  
  Sentence *s = &(r->result.sent[n]);
  WORD_ID *seq = s->word;
  int seqnum = s->word_num;
  int i;  
  printf("sentence%d:", n+1);
  for(i=0;i<seqnum;i++) printf(" %s", winfo->woutput[seq[i]]);
  printf("\n");  
  printf("wseq%d:", n+1);
  for(i=0;i<seqnum;i++) printf(" %s", winfo->wname[seq[i]]);
  printf("\n");
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"julius.Sentence",s,NULL));
}


/*-----------------------API for sample----------------------------------*/

METHOD RecogProcess_sentNum(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess* r = (sfp[0].glue)->ptr;
  int ret = r->result.sentnum;
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD RecogProcess_outputWordScore(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess* r = (sfp[0].glue)->ptr;
  int n = p_int(sfp[1]);
  Sentence *s = &(r->result.sent[n]);
  int seqnum = s->word_num;
  int i;
  printf("cmscore%d:", n+1);
  for (i=0;i<seqnum; i++) printf(" %5.3f", s->confidence[i]);
  printf("\n");
  printf("score%d: %f", n+1, s->score);
  if (r->lmtype == LM_PROB) {
    printf(" (AM: %f  LM: %f)", s->score_am, s->score_lm);
    }
    printf("\n");
    if (r->lmtype == LM_DFA) { 
	if (multigram_get_all_num(r->lm) > 1) {
	    printf("grammar%d: %d\n", n+1, s->gram_id);
	}
    }
    KNH_RETURN_void(ctx,sfp);
}

METHOD WordInfo_outputAlignment(Ctx *ctx,knh_sfp_t *sfp)
{
  WORD_INFO* winfo = (sfp[0].glue)->ptr;
  int n = p_int(sfp[1]);
  RecogProcess* r = (sfp[2].glue)->ptr;
  Sentence *s = &(r->result.sent[n]);
  
  if (1) {
    HMM_Logical *p;
    int i;   
    printf("=== begin forced alignment ===\n");
    printf(" id: from  to    n_score    unit\n");
    printf(" ----------------------------------------\n");
    for(i=0;i<s->align->num;i++) {
      printf("[%4d %4d]  %f  ", s->align->begin_frame[i], s->align->end_frame[i], s->align->avgscore[i]);
      switch(s->align->unittype) {
      case PER_WORD:
	printf("%s\t[%s]\n", winfo->wname[s->align->w[i]], winfo->woutput[s->align->w[i]]);
	break;
      case PER_PHONEME:
	p = s->align->ph[i];
	if (p->is_pseudo) {
	  printf("{%s}\n", p->name);
	} else if (strmatch(p->name, p->body.defined->name)) {
	  printf("%s\n", p->name);
	} else {
	  printf("%s[%s]\n", p->name, p->body.defined->name);
	}
	break;
      case PER_STATE:
	p = s->align->ph[i];
	if (p->is_pseudo) {
	  printf("{%s}", p->name);
	} else if (strmatch(p->name, p->body.defined->name)) {
	  printf("%s", p->name);
	} else {
	  printf("%s[%s]", p->name, p->body.defined->name);
	}
	if (r->am->hmminfo->multipath) {
	  if (s->align->is_iwsp[i]) {
	    printf(" #%d (sp)\n", s->align->loc[i]);
	  } else {
	    printf(" #%d\n", s->align->loc[i]);
	  }
	} else {
	  printf(" #%d\n", s->align->loc[i]);
	}
	break;
      }
    }
    printf("re-computed AM score: %f\n", s->align->allscore);	
    printf("=== end forced alignment ===\n");
  }
  KNH_RETURN_void(ctx,sfp);
}

METHOD Julius_fflush(Ctx *ctx,knh_sfp_t *sfp)
{
  int ret;
  ret = fflush(stdout);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Jconf_openInputStream(Ctx *ctx,knh_sfp_t *sfp)
{
  Jconf* jconf = (sfp[0].glue)->ptr;
  char speechfilename[MAXPATHLEN];
  Recog* recog = (sfp[1].glue)->ptr;
  int ret;
  
  if (jconf->input.speech_input == SP_MFCFILE) {
    while (get_line_from_stdin(speechfilename, MAXPATHLEN, "enter MFCC filename->") != NULL) {
      
      if (verbose_flag) printf("\ninput MFCC file: %s\n", speechfilename);
      ret = j_open_stream(recog, speechfilename);
      switch(ret) {
      case 0:			
	break;
      case -1:      		
	continue;
      case -2:	
	exit(1);
      }  
      ret = j_recognize_stream(recog);
      if (ret == -1) exit(1);   
    }
    
  } else {
     switch(j_open_stream(recog, NULL)) {
    case 0:	
       break;
    case -1:
      fprintf(stderr, "error in input stream\n");
      exit(1);
    case -2:
      fprintf(stderr, "failed to begin input stream\n");
      exit(1);
    }
     memcpy((void *)&julius_ctx, ctx, sizeof(Ctx)+1);
    ret = j_recognize_stream(recog);
    if (ret == -1) exit(1);	
  }
  KNH_RETURN_void(ctx,sfp);
}
METHOD RecogProcess_getNext(Ctx *ctx,knh_sfp_t *sfp)
{
  int ret = 1;
  RecogProcess* r = (sfp[0].glue)->ptr; 
  r = r->next;
  (sfp[0].glue)->ptr = r;
  if ( r == NULL ) {ret = 0;}
  KNH_RETURN_Boolean(ctx,sfp,ret);
}

METHOD Sentence_getSeq(Ctx *ctx,knh_sfp_t *sfp)
{
  Sentence *s = (sfp[0].glue)->ptr;
  int i = p_int(sfp[1]);
  KNH_RETURN_Int(ctx,sfp,s->word[i]);
}

METHOD Sentence_getWordNum(Ctx *ctx,knh_sfp_t *sfp)
{
  Sentence *s = (sfp[0].glue)->ptr;
  int ret = s->word_num;
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD WordInfo_getWlen(Ctx *ctx,knh_sfp_t *sfp)
{
  WORD_INFO *winfo = (sfp[0].glue)->ptr; 
  WORD_ID w = p_int(sfp[1]);
  int ret = winfo->wlen[w];
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD WordInfo_centerName(Ctx *ctx,knh_sfp_t *sfp)
{
  WORD_INFO* winfo = (sfp[0].glue)->ptr;
  int j = p_int(sfp[1]);
  WORD_ID w = (WORD_ID)p_int(sfp[2]);
  char buf[MAX_HMMNAME_LEN];
  char* hmmname = winfo->wseq[w][j]->name;
  char* ret = center_name(hmmname,buf);
  KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

METHOD Recog_speechInput(Ctx *ctx,knh_sfp_t *sfp)
{
    Recog* recog = (sfp[0].glue)->ptr;
    int ret = 0;
    if(recog->jconf->input.speech_input == SP_MIC){
	ret = 1;
    }
    else if(recog->jconf->input.speech_input == SP_NETAUDIO){
	ret = 1;
    }
    KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD RecogProcess_checkLive(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess *r = (sfp[0].glue)->ptr;
  int ret = 1;
  if(r == NULL){
    ret = -1;
  } else if(! r->live){
    ret = 0;
  }
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Jconf_mfccFileInput(Ctx *ctx, knh_sfp_t *sfp)
{
  /*Jconf *jconf = (sfp[0].glue)->ptr;
  int ret = 0;
  if(jconf->input.speech_input == SP_MFCCFILE){
	ret = 1;
	}*/
  //KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD RecogProcess_checkResultStatus(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess* r = (sfp[0].glue)->ptr;
  int ret = 1;
  if (r->result.status < 0) {
    switch(r->result.status) {
    case J_RESULT_STATUS_REJECT_POWER:
      printf("<input rejected by power>\n");
      break;
    case J_RESULT_STATUS_TERMINATE:
      printf("<input teminated by request>\n");
      break;
    case J_RESULT_STATUS_ONLY_SILENCE:
      printf("<input rejected by decoder (silence input result)>\n");
	break;
    case J_RESULT_STATUS_REJECT_GMM:
      printf("<input rejected by GMM>\n");
      break;
    case J_RESULT_STATUS_REJECT_SHORT:
      printf("<input rejected by short input>\n");
	break;
    case J_RESULT_STATUS_FAIL:
      printf("<search failed>\n");
      break;
    }
    ret = 0;
    }
  KNH_RETURN_Int(ctx,sfp,ret);
}









  /*--------------------basic API-------------------------*/

METHOD Recog_adinInit(Ctx *ctx, knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  if(j_adin_init(recog) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx, sfp,0);   
  }
}

METHOD Julius_getCurrentFilename(Ctx *ctx,knh_sfp_t *sfp)
{
  char* ret = j_get_current_filename(); 
  KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}
  //void j_recog_info(Recog* recog)
METHOD Recog_recogInfo(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  j_recog_info(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Julius_outputArgumentHelp(Ctx *ctx,knh_sfp_t *sfp)
{
  FILE* fp = (FILE*)p_cptr(sfp[1]);
  j_output_argument_help(fp);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Recog_openStream(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  char* file_or_dev_name = p_char(sfp[1]);
  int ret = j_open_stream(recog,file_or_dev_name);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Recog_recognizeStream(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int ret = j_recognize_stream(recog);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Julius_strmatch(Ctx *ctx,knh_sfp_t *sfp)
{
  char* ch1 = p_char(sfp[1]);
  char* ch2 = p_char(sfp[2]);
  int ret = !strcmp(ch1,ch2);
  KNH_RETURN_Int(ctx,sfp,ret);
}
METHOD Julius_putVersion(Ctx *ctx,knh_sfp_t *sfp)
{
  FILE* strm = (FILE*)p_cptr(sfp[1]);
  j_put_version(strm);
  KNH_RETURN_void(ctx,sfp);
}
METHOD Jconf_new(Ctx *ctx,knh_sfp_t *sfp)
{
  char* argv[3];
  argv[0] = "julius";
  argv[1] = "-C";
  argv[2] = "fast.jconf";
  Jconf* jconf = j_config_load_args_new(3,argv);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"julius.Jconf",jconf,NULL));
}

METHOD Recog_new(Ctx *ctx,knh_sfp_t *sfp)
{
  Jconf* jconf = (sfp[1].glue)->ptr;
  Recog* ret = j_create_instance_from_jconf(jconf);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"julius.Recog",ret,NULL));
}

METHOD Julius_getLineFromStdin(Ctx *ctx,knh_sfp_t *sfp)
{
  char* buf = p_char(sfp[1]);
  int buflen = p_int(sfp[2]);
  char* prompt = p_char(sfp[3]);
  char* ret = get_line_from_stdin(buf,buflen,prompt);
  KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

METHOD Recog_recogFree(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog *recog = (sfp[0].glue)->ptr;
  j_recog_free(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Recog_closeStream(Ctx *ctx,knh_sfp_t *sfp)
{  
  Recog* recog = (sfp[0].glue)->ptr;
  j_close_stream(recog);
  KNH_RETURN_void(ctx,sfp);
}

 /*---------------Callback API----------------------*/

METHOD Recog_callbackExist(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int code = p_int(sfp[1]);
  if(callback_exist(recog,code) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Recog_callbackDelete(Ctx *ctx,knh_sfp_t *sfp)
{
   Recog* recog = (sfp[0].glue)->ptr;
  int id = p_int(sfp[1]);
  if(callback_delete(recog,id) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

  /*----------------Pause and Resume API---------------*/

METHOD Recog_requestPause(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  j_request_pause(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Recog_requestTerminate(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  j_request_terminate(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Recog_requestResume(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  j_request_resume(recog);
  KNH_RETURN_void(ctx,sfp);
}

  /*---------------Process API---------------------*/

METHOD Recog_processDeactivateById(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  int id = p_int(sfp[1]);
  if(j_process_deactivate_by_id(recog,id) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Recog_processActivate(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  char* name = p_char(sfp[1]);
  if(j_process_activate(recog,name) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}
  /*
METHOD Recog_processAddLm(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  JCONF_LM* lmconf = (sfp[1].glue)->ptr;
  JCONF_SEARCH* sconf = (sfp[2].glue)->ptr;
  char* name = p_char(sfp[3]);
  if(j_process_add_lm(recog,lmconf,sconf,name) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}
  */
  /*---------------Grammer/Dictionary API---------------*/
   /*
METHOD Jconflm_multigramRemoveGramlist(Ctx *ctx,knh_sfp_t *sfp)
{
  JCONF_LM* j = (sfp[0].glue)->ptr;
  multigram_remove_gramlist(j);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Jconflm_multigramAddPrefixList(Ctx *ctx,knh_sfp_t *sfp)
{
  JCONF_LM* j = (sfp[0].glue)->ptr;
  char* prefix_list = p_char(sfp[1]);
  char* cwd = p_char(sfp[2]);
  int lmvar = p_int(sfp[3]);
  if(multigram_add_prefix_list(prefix_list,cwd,j,lmvar) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Jconflm_multigramAddPrefixFilelist(Ctx *ctx,knh_sfp_t *sfp)  
{
  JCONF_LM* j = (sfp[0].glue)->ptr;
  char* listfile = p_char(sfp[1]);
  int lmvar = p_int(sfp[2]);
  if(multigram_add_prefix_filelist(listfile,j,lmvar) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}
*/

METHOD Recog_scheduleGrammarUpdate(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  schedule_grammar_update(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Recog_resetReload(Ctx *ctx,knh_sfp_t *sfp)
{
  Recog* recog = (sfp[0].glue)->ptr;
  j_reset_reload(recog);
  KNH_RETURN_void(ctx,sfp);
}

METHOD RecogProcess_multigramBuild(Ctx *ctx,knh_sfp_t *sfp)
{
  RecogProcess* r = (sfp[0].glue)->ptr;
  if(multigram_build(r) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}
  /*
METHOD Processlm_multigramAdd(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  DFA_INFO* dfa = (sfp[1].glue)->ptr;
  WORD_INFO* winfo = (sfp[2].glue)->ptr;
  char* name = p_char(sfp[3]);
  multigram_add(dfa,winfo,name,lm);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Processlm_multigramDelete(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  int delid = p_int(sfp[1]);
  if(multigram_delete(delid,lm) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Processlm_multigramDeleteAll(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  multigram_delete_all(lm);
  KNH_RETURN_void(ctx,sfp);
}

METHOD Processlm_multigramActivate(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  int gid = p_int(sfp[1]);
  int ret = multigram_activate(gid,lm);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Processlm_multigramDeactivate(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  int gid = p_int(sfp[1]);
  int ret = multigram_deactivate(gid,lm);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Processlm_multigramUpdate(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  if(multigram_update(lm) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Processlm_multigramGetGramFromCategory(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  int category = p_int(sfp[1]);
  int ret = multigram_get_gram_from_category(category,lm);
  KNH_RETURN_Int(ctx,sfp,ret);
}

METHOD Processlm_multigramGetGrammarByName(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  char* gramname = p_char(sfp[1]);
  MULTIGRAM* ret = multigram_get_grammar_by_name(lm,gramname);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"MULTIGRAM",ret,NULL));
}

METHOD Processlm_multigramGetGrammarById(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  unsigned short id = p_int(sfp[1]);
  MULTIGRAM* ret = multigram_get_grammar_by_id(lm,id);
  KNH_RETURN(ctx,sfp,new_Glue(ctx,"MULTIGRAM",ret,NULL));
}

METHOD Processlm_multigramAddWordsToGrammar(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  MULTIGRAM* m = (sfp[1].glue)->ptr;
  WORD_INFO* winfo = (sfp[2].glue)->ptr;
  if(multigram_add_words_to_grammar(lm,m,winfo) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Processlm_multigramAddWordsToGrammarByName(Ctx *ctx,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  char* gramname = p_char(sfp[1]);
  WORD_INFO* winfo = (sfp[2].glue)->ptr;
  if(multigram_add_words_to_grammar_by_name(lm,gramname,winfo) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}

METHOD Processlm_multigramAddWordsToGrammarById(Ctx *ctx ,knh_sfp_t *sfp)
{
  PROCESS_LM* lm = (sfp[0].glue)->ptr;
  unsigned short id = p_int(sfp[1]);
  WORD_INFO* winfo = (sfp[2].glue)->ptr;
  if(multigram_add_words_to_grammar_by_id(lm,id,winfo) == TRUE){
    KNH_RETURN_Boolean(ctx,sfp,1);
  }
  else{
    KNH_RETURN_Boolean(ctx,sfp,0);
  }
}
  */


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
