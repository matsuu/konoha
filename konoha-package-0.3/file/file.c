#include <konoha.h>
#include <string.h>

void knh_file_free(Ctx *ctx,knh_Glue_t *g){
    FILE* fp = (FILE*)g->ptr;
    if(fp!=NULL){
        fclose(fp);
    }
    g->ptr = NULL;
}
FILE* knh_file_open(const char* fname,const char* mode){
    FILE* fp;
    if(mode[0] == 'w'){
        if(mode[1] == 'b'){
            fp = fopen(fname,"wb");
        } else {
            fp = fopen(fname,"w");
        }
        return fp;
    } else if(mode[0] == 'r'){
        if(mode[1] == 'b'){
            fp = fopen(fname,"r");
        } else {
            fp = fopen(fname,"rb");
        }
        return fp;
    } else {
        // fprintf(stderr,"unrecognized mode. %s\n",mode);
    }
    return NULL;
}
METHOD File_new(Ctx *ctx,knh_sfp_t *sfp){
    char* filename = p_char(sfp[1]);
    char* mode     = p_char(sfp[2]);

    FILE* fp = knh_file_open(filename,mode);
    knh_Glue_init(ctx,sfp[0].glue,fp,knh_file_free);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

METHOD File_open(Ctx *ctx,knh_sfp_t *sfp){
    FILE* fp = (FILE*) p_cptr(sfp[0]);
    
    if(fp != NULL) {
        knh_file_free(ctx,sfp[0].glue);
    }
    fp = knh_file_open(p_char(sfp[1]),p_char(sfp[1]));
    KNH_RETURN_void(ctx,sfp);
}

METHOD File_putc(Ctx *ctx,knh_sfp_t *sfp){
    FILE* fp = (FILE*) p_cptr(sfp[0]);
    int i    = (int) p_int(sfp[1]);

    if(fp == NULL){
        KNH_THROWs(ctx,"file is not open.");
    }
    fputc(i,fp);
    KNH_RETURN_void(ctx,sfp);
}

METHOD File_close(Ctx *ctx,knh_sfp_t *sfp){
    FILE* fp = (FILE*) p_cptr(sfp[0]);

    if(fp == NULL){
        KNH_WARNING(ctx, "file is already closed.");
    } else{
        knh_file_free(ctx,sfp[0].glue);
    }
    KNH_RETURN_void(ctx,sfp);
}
