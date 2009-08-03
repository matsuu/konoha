using julius.*;

String str;
Julius julius;

void statusRecready(Recog recog,String dummy){
   if(recog.speechInput() == 1){
       OUT << "<<<please speak>>>" << EOL;
   }
}

void statusRecstart(Recog recog,String dummy){
    if(recog.speechInput() == 1){
       OUT << "<<<Rec start>>>" << EOL;
    }
}

void getName(int[] seq,int n,WordInfo winfo,Recog recog){
    int i,j,k;
    String buf;
    int w;
    while(true){
      if(seq == NULL) break;
      for(i = 0;i < n;i++){
	  if(i < 0) break;
          OUT << " |" ;
	  w = seq[i];
	  k = winfo.getWlen(w);
	  s = new String[n];
          for(j = 0;j < k ;j++){
	      buf = winfo.centerName(j,w);  
	      s[i]  = s[i] + buf;
	  }
	  OUT << s[i] << EOL;
	  /*------Add you want to get name-------------*/
	  if("konoha" == s[i]){
	      str = "konoha";
	      recog.closeStream();
	  }
	  else if("yokohama" == s[i]){
	      str = "yokohama";
	      recog.closeStream();
	  }
	  else if("sp" == s[i]){
	      str = "sp";
	      recog.closeStream();
	  }
      }
      break;
    }
    OUT << EOL;
}

void outputResult(Recog recog,String dummy){
   
    r = new RecogProcess(recog);
    do{
	int live = r.checkLive();
	if ( live == -1 ) break;
	else if(live == 0) continue;
	int ret = r.checkResultStatus();
	if(ret == 0) break; 

	winfo = new WordInfo(r);

	for( n = 0 ;n < r.sentNum();n++){

	    s = new Sentence(r,n,winfo);

	    OUT << "phseq" << n+1;
	    seq = new Int[Julius.MAX_SEQ_NUM];
	    for(int i = 0; i < Julius.MAX_SEQ_NUM; i++){
		seq[i] = s.getSeq(i);
	    }
	    getName(seq,s.getWordNum(),winfo,recog);
	    OUT << EOL;
	    r.outputWordScore(n);
	} 
    }while(r.getNext());
    julius.fflush();
}

int main(String[] args){

    julius = new Julius();
 
    jconf = new Jconf();
    recog = new Recog(jconf);
    
    Closure c1 = delegate(statusRecready);
    Closure c2 = delegate(statusRecstart);
    Closure c3 = delegate(outputResult);
    		    
    recog.callbackAddFuncRecReady(Julius.CALLBACK_EVENT_SPEECH_READY,c1,"NULL");  
    recog.callbackAddFuncRecStart(Julius.CALLBACK_EVENT_SPEECH_START,c2,"NULL");
    recog.callbackAddFuncOutputResult(Julius.CALLBACK_RESULT,c3,"NULL");
    
    if (recog.adinInit() == FALSE) {   
    return -1;
    }
    recog.recogInfo();
    jconf.openInputStream(recog);
    recog.recogFree();
    
    OUT << "getname = " << str << EOL;
    return 0;
}

 
	