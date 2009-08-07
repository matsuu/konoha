#include <libvirt/libvirt.h>
#include <konoha.h>

/* @method void Virt.init() */
METHOD Virt_init(Ctx *ctx, knh_sfp_t *sfp)
{
    virInitialize();
    KNH_RETURN_void(ctx,sfp);
}

// @method This! Connection.new(String name);
METHOD Connection_new(Ctx *ctx, knh_sfp_t *sfp)
{
    char* name = (char*)p_char(sfp[1]);
    virConnectPtr connect = virConnectOpen(name);
    knh_Glue_init(ctx,sfp[0].glue,connect,NULL);
    KNH_RETURN(ctx, sfp, sfp[0].o);
}

// @method void Connection.close();
METHOD Connection_close(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    virConnectClose(connect);
    KNH_RETURN_void(ctx, sfp);
}

// @method String Connection.getType();
METHOD Connection_getType(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    char *ret = virConnectGetType(connect);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// @method String Connection.getHostname();
METHOD Connection_getHostname(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    char *ret = virConnectGetHostname(connect);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// @method String Connection.getURI();
METHOD Connection_getURI(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    char *ret = virConnectGetURI(connect);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// @method Int Connection.getFreeMemory();
METHOD Connection_getFreeMemory(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    knh_int_t ret = virNodeGetFreeMemory(connect);
    KNH_RETURN_Int(ctx,sfp,ret);
}

// @method Domain Connection.getDomainByName(String name);
METHOD Connection_getDomainByName(Ctx *ctx, knh_sfp_t *sfp)
{
    virConnectPtr connect = (virConnectPtr) p_cptr(sfp[0]);
    char* domname = (char*)p_char(sfp[1]);
    virDomainPtr dom = virDomainLookupByName(connect, domname);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libvirt.Domain",dom,NULL));
}

// @method Connection Domain.getConnection();
METHOD Domain_getConnection(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    virConnectPtr connect = virDomainGetConnect(dom);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libvirt.Connection",connect,NULL));
}

// @method String Domain.getName();
METHOD Domain_getName(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    char* ret = virDomainGetName(dom);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// @method Int Domain.getID();
METHOD Domain_getID(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    int ret = virDomainGetID(dom);
    KNH_RETURN_Int(ctx,sfp,ret);
}

// @method String Domain.getOSType();
METHOD Domain_getOSType(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    char* ret = virDomainGetOSType(dom);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

// @method Boolean Domain.create();
METHOD Domain_create(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    int ret = virDomainCreate(dom);
    KNH_RETURN_Boolean(ctx, sfp, !ret);
}

// @method Boolean Domain.reboot();
METHOD Domain_reboot(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    int ret = virDomainReboot(dom,0);
    KNH_RETURN_Boolean(ctx, sfp, !ret);
}

// @method Boolean Domain.shutdown();
METHOD Domain_shutdown(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    int ret = virDomainShutdown(dom);
    KNH_RETURN_Boolean(ctx, sfp, !ret);
}

// @method Boolean Domain.destroy();
METHOD Domain_destroy(Ctx *ctx, knh_sfp_t *sfp)
{
    virDomainPtr dom = (virDomainPtr) p_cptr(sfp[0]);
    int ret = virDomainDestroy(dom);
    KNH_RETURN_Boolean(ctx, sfp, !ret);
}


/*
int main() {

    //fprintf(stderr, "%d\n",virDomainRef(dom));
    //fprintf(stderr, "shutdown=%d\n",virDomainShutdown(dom));
    //fprintf(stderr, "reboot  =%d\n",virDomainReboot(dom,0));
    //fprintf(stderr, "destroy =%d\n",virDomainDestroy(dom));
    return 0;
}
*/
