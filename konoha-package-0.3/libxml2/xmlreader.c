#include <libxml/xmlreader.h>

#define KNH_USING_ICONV

#include <konoha.h>

/* ----------------------------------------------------------------- */
/* [xmlTextReader] */
static void knh_xmlreader_gfree(Ctx *ctx, knh_Glue_t *g)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) g->ptr;
    xmlFreeTextReader(reader);
}

/* @method This! XmlReader.new(String filename) */
METHOD XmlReader_new(Ctx *ctx, knh_sfp_t *sfp)
{
    char* filename = (char*)p_char(sfp[1]);
    xmlTextReaderPtr reader = xmlNewTextReaderFilename(filename);
    if(reader == NULL) {
        KNH_THROWs(ctx, "XmlReader: cant load file");
    }
    knh_Glue_init(ctx,sfp[0].glue,reader,knh_xmlreader_gfree);
    KNH_RETURN(ctx,sfp,sfp[0].o);
}

/* @method void XmlReader.close() */
METHOD XmlReader_close(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    xmlTextReaderClose(reader);
    KNH_RETURN_void(ctx,sfp);
}

/* @method String XmlReader.getQuoteChar() */
METHOD XmlReader_getQuoteChar(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int num = xmlTextReaderQuoteChar(reader);
    char* ret = " ";
    if(num == 34){
        ret[0] = '"';
    } else {
        ret[0] = '\0';
    }
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method Boolean XmlReader.read() */
METHOD XmlReader_read(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
     if(reader == NULL) {
        KNH_THROWs(ctx, "XmlReader.read(): xmlReader is not readable");
    }
    int ret = xmlTextReaderRead(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Int XmlReader.readState() */
METHOD XmlReader_readState(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderReadState(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Int XmlReader.nodeType() */
METHOD XmlReader_nodeType(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderNodeType(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Int XmlReader.isNamespaceDecl() */
METHOD XmlReader_isNamespaceDecl(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderIsNamespaceDecl(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Int XmlReader.isEmptyElement() */
METHOD XmlReader_isEmptyElement(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderIsEmptyElement(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Boolean XmlReader.hasAttributes() */
METHOD XmlReader_hasAttributes(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderHasAttributes(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method Boolean XmlReader.hasValue() */
METHOD XmlReader_hasValue(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderHasValue(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method Boolean XmlReader.getDepth() */
METHOD XmlReader_getDepth(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderDepth(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method Int XmlReader.getAttributeCount() */
METHOD XmlReader_getAttributeCount(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderAttributeCount(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

/* @method Boolean XmlReader.moveToFirstAttribute() */
METHOD XmlReader_moveToFirstAttribute(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderMoveToFirstAttribute(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method Boolean XmlReader.moveToNextAttribute() */
METHOD XmlReader_moveToNextAttribute(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderMoveToNextAttribute(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method Boolean XmlReader.moveToElement() */
METHOD XmlReader_moveToElement(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderMoveToElement(reader);
    KNH_RETURN_Boolean(ctx,sfp,ret);
}

/* @method String XmlReader.constBaseUri() */
METHOD XmlReader_constBaseUri(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstBaseUri(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constEncoding() */
METHOD XmlReader_constEncoding(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*)xmlTextReaderConstEncoding(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constValue() */
METHOD XmlReader_constValue(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstValue(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constNamespaceUri() */
METHOD XmlReader_constNamespaceUri(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstNamespaceUri(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constLocalName() */
METHOD XmlReader_constLocalName(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstLocalName(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constName() */
METHOD XmlReader_constName(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstName(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constXmlLang() */
METHOD XmlReader_constXmlLang(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstXmlLang(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.constPrefix() */
METHOD XmlReader_constPrefix(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    char* ret = (char*) xmlTextReaderConstPrefix(reader);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}


/* @method String XmlReader.getAttribute() */
METHOD XmlReader_getAttribute(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    xmlChar * ns = (xmlChar *) p_char(sfp[1]);
    char* ret = (char*) xmlTextReaderGetAttribute(reader,ns);
    if(ret == NULL){
        ret = "";
    }
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.getAttributeNo(Int numer) */
METHOD XmlReader_getAttributeNo(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int num = p_int(sfp[1]);
    char* ret = (char*) xmlTextReaderGetAttributeNo(reader,num);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.getAttributeNs(String ns, String name) */
METHOD XmlReader_getAttributeNs(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    xmlChar* ns   = (xmlChar*) p_char(sfp[1]);
    xmlChar* name = (xmlChar*) p_char(sfp[2]);
    char* ret = (char*) xmlTextReaderGetAttributeNs(reader,ns,name);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method String XmlReader.lookupNameSpace(String ns) */
METHOD XmlReader_lookupNameSpace(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    xmlChar* ns   = (xmlChar*) p_char(sfp[1]);
    char* ret = (char*) xmlTextReaderLookupNamespace(reader,ns);
    KNH_RETURN(ctx,sfp,new_String(ctx,B(ret),NULL));
}

/* @method Int XmlReader.normalization() */
METHOD XmlReader_normalization(Ctx *ctx, knh_sfp_t *sfp)
{
    xmlTextReaderPtr reader = (xmlTextReaderPtr) p_cptr(sfp[0]);
    int ret = xmlTextReaderNormalization(reader);
    KNH_RETURN_Int(ctx,sfp,ret);
}

static knh_IntConstData_t IntConstData[] = {
    {"XmlReader.TYPE_NONE",         XML_READER_TYPE_NONE},
    {"XmlReader.TYPE_ELEMENT",      XML_READER_TYPE_ELEMENT},
    {"XmlReader.TYPE_ATTRIBUTE",    XML_READER_TYPE_ATTRIBUTE},
    {"XmlReader.TYPE_TEXT",         XML_READER_TYPE_TEXT},
    {"XmlReader.TYPE_CDATA",        XML_READER_TYPE_CDATA},
    {"XmlReader.TYPE_REFERENCE",    XML_READER_TYPE_ENTITY_REFERENCE},
    {"XmlReader.TYPE_ENTITY",       XML_READER_TYPE_ENTITY},
    {"XmlReader.TYPE_PROCESSING_INSTRUCTION",  XML_READER_TYPE_PROCESSING_INSTRUCTION},
    {"XmlReader.TYPE_COMMENT",      XML_READER_TYPE_COMMENT},
    {"XmlReader.TYPE_DOCUMENT",     XML_READER_TYPE_DOCUMENT},
    {"XmlReader.TYPE_DOCUMENT_TYPE",XML_READER_TYPE_DOCUMENT_TYPE},
    {"XmlReader.TYPE_DOCUMENT_FRAGMENT",      XML_READER_TYPE_DOCUMENT_FRAGMENT},
    {"XmlReader.TYPE_NOTATION",     XML_READER_TYPE_NOTATION},
    {"XmlReader.TYPE_WHITESPACE",   XML_READER_TYPE_WHITESPACE},
    {"XmlReader.TYPE_SIGNIFICANT_WHITESPACE", XML_READER_TYPE_SIGNIFICANT_WHITESPACE},
    {"XmlReader.TYPE_END_ELEMENT",  XML_READER_TYPE_END_ELEMENT},
    {"XmlReader.TYPE_END_ENTITY",   XML_READER_TYPE_END_ENTITY},
    {"XmlReader.TYPE_XML_DECLATION",XML_READER_TYPE_XML_DECLARATION},
    {NULL} // end of const
};

KNHAPI(int) init(Ctx *ctx)
{
    KNH_NOTICE(ctx, "loading xmlreader...");
    konoha_loadIntConstData(ctx, IntConstData);
    return 1;
}
