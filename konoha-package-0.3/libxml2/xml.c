#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <konoha.h>

static void knh_xml_gfree(Ctx *ctx, knh_Glue_t *g)
{
    xmlDocPtr doc = (xmlDocPtr) g->ptr;
    xmlFreeDoc(doc);
}

METHOD Xml_new(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlChar* version = (xmlChar*)p_char(sfp[1]);
    xmlDocPtr doc = xmlNewDoc(version);
    knh_Glue_init(ctx,sfp[0].glue,doc,knh_xml_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

METHOD Xml_createNode(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlDocPtr doc = (xmlDocPtr) p_cptr(sfp[0]);
    xmlChar *name = (xmlChar*) p_char(sfp[1]);
    doc->children = xmlNewDocNode(doc, NULL, name , NULL);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",doc->children,NULL));
}

METHOD Xml_getRoot(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlDocPtr doc = (xmlDocPtr) p_cptr(sfp[0]);
    xmlNodePtr node = xmlDocGetRootElement(doc);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",node,NULL));
}

METHOD Xml_dump(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlDocPtr doc = (xmlDocPtr) p_cptr(sfp[0]);
    xmlChar* ret;
    int   size;
    xmlDocDumpMemory(doc,&ret,&size);
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)ret), NULL));
}

/* XmlNode */
METHOD XmlNode_createNode(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr parent = (xmlNodePtr) p_cptr(sfp[0]);
    xmlChar *name = (xmlChar*) p_char(sfp[1]);
    xmlChar *val  = (xmlChar*) p_char(sfp[2]);

    xmlNodePtr node = xmlNewChild(parent, NULL, name, val);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",node,NULL));
}

METHOD XmlNode_addChild(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr parent = (xmlNodePtr) p_cptr(sfp[0]);
    xmlNodePtr child  = (xmlNodePtr) p_cptr(sfp[1]);
    xmlAddChild(parent,child);
    KNH_RETURN_void(ctx,sfp);
}

METHOD XmlNode_setAttr(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    xmlChar *name = (xmlChar *) p_char(sfp[1]);
    xmlChar *val  = (xmlChar *) p_char(sfp[2]);
    xmlSetProp(node,name,val);
    KNH_RETURN_void(ctx,sfp);
}

METHOD XmlNode_getContent(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    xmlChar* ret = (xmlChar *)"";
    if(node->content){
        ret = node->content;
        fprintf(stdout,"[%s]\n",(char*)node->content);
    }
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)ret), NULL));
}

METHOD XmlNode_getName(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    xmlChar* ret = (xmlChar *)"";
    if(node->name){
        ret = (xmlChar *)node->name;
    }
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)ret), NULL));
}

METHOD XmlNode_getAttr(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    xmlChar *name = (xmlChar *) p_char(sfp[1]);
    xmlChar *ret  = (xmlChar *)"";
    if(node->properties){
        ret  = xmlGetProp(node,name);
    }
    KNH_RETURN(ctx, sfp, new_String(ctx, B((char*)ret), NULL));
}


METHOD XmlNode_getChild(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node  = (xmlNodePtr) p_cptr(sfp[0]);
    xmlNodePtr child = (xmlNodePtr) node->children;
    if(child == NULL){
        KNH_THROWs(ctx, "XmlNode: dont have child!");
    }
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",child,NULL));
}

METHOD XmlNode_getNext(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node = (xmlNodePtr) p_cptr(sfp[0]);
    xmlNodePtr next = (xmlNodePtr) node->next;
    if(next == NULL){
        KNH_THROWs(ctx, "XmlNode: dont have next!");
    }
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",next,NULL));
}

METHOD XmlNode_hasChild(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    if(node->children) {
        KNH_RETURN_Boolean(ctx, sfp, 1);
    }
    KNH_RETURN_Boolean(ctx, sfp, 0);
}

METHOD XmlNode_hasNext(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    if(node->next) {
        KNH_RETURN_Boolean(ctx, sfp, 1);
    }
    KNH_RETURN_Boolean(ctx, sfp, 0);
}

/*
static xmlDocPtr document = NULL;
METHOD XmlNode_dump(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlNodePtr node= (xmlNodePtr) p_cptr(sfp[0]);
    xmlElemDump(stdout,document,node);
    KNH_RETURN_void(ctx,sfp);
}
*/

/* XPath */
static void knh_xpath_gfree(Ctx *ctx, knh_Glue_t *g)
{
    xmlXPathContextPtr xctx = (xmlXPathContextPtr) g->ptr;
    xmlXPathFreeContext(xctx);
    xmlCleanupParser();
}

METHOD XPath_new(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlDocPtr doc = (xmlDocPtr) p_cptr(sfp[1]);
    xmlXPathContextPtr xctx;
    if (!(xctx = xmlXPathNewContext(doc))) {
        KNH_THROWs(ctx, "XPATH: cant create xmlXPathContext");
    }
    knh_Glue_init(ctx,sfp[0].glue,xctx,knh_xpath_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}
METHOD XPath_find(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlXPathContextPtr xctx = (xmlXPathContextPtr) p_cptr(sfp[0]);
    xmlChar *xpath = (xmlChar *) p_char(sfp[1]);
    xmlNodePtr node = NULL;
    xmlXPathObjectPtr xpobj;
    if (!(xpobj = xmlXPathEvalExpression( xpath, xctx))) {
        fprintf(stderr,"xpath:%s",(char*)xpath);
        KNH_THROWs(ctx, "XPATH: cant execute xmlXPathEvalExpression");
    }
    if (!xmlXPathNodeSetIsEmpty(xpobj->nodesetval)) {
        node = xmlXPathNodeSetItem(xpobj->nodesetval, 0);
    }
    xmlXPathFreeObject(xpobj);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,(char*)"libxml2.XmlNode",node,NULL));
}

