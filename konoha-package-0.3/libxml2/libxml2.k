class Xml;
class XmlNode;
class XPath;

Xml     Xml.new(String version);
XmlNode Xml.createNode(String name);
String  Xml.dump();
XmlNode Xml.getRoot();

XmlNode XmlNode.createNode(String name,String value);
void    XmlNode.addChild(XmlNode child);
void    XmlNode.setAttr(String name,String value);
Boolean XmlNode.hasChild();
Boolean XmlNode.hasNext();
XmlNode XmlNode.getChild();
XmlNode XmlNode.getNext();
String  XmlNode.getName();
String  XmlNode.getAttr(String name);
String  XmlNode.getContent();
void    XmlNode.dump();


XPath   XPath.new(Xml xml);
XmlNode XPath.find(String xpath);

class XmlReader{};
XmlReader! XmlReader.new(String filename);
void XmlReader.close();
String XmlReader.getQuoteChar();
Boolean XmlReader.read();
Int XmlReader.readState();
Int XmlReader.nodeType();
Int XmlReader.isNamespaceDecl();
Int XmlReader.isEmptyElement();
Int XmlReader.getAttributeCount();
Boolean XmlReader.hasAttributes();
Boolean XmlReader.hasValue();
Boolean XmlReader.getDepth();
Boolean XmlReader.moveToFirstAttribute();
Boolean XmlReader.moveToNextAttribute();
Boolean XmlReader.moveToElement();
String  XmlReader.constBaseUri();
String  XmlReader.constEncoding();
String  XmlReader.constValue();
String  XmlReader.constNamespaceUri();
String  XmlReader.constLocalName();
String  XmlReader.constName();
String  XmlReader.constXmlLang();
String  XmlReader.constPrefix();
String  XmlReader.getAttribute();
String  XmlReader.getAttributeNo(Int numer);
String  XmlReader.getAttributeNs(String ns, String name);
String  XmlReader.lookupNameSpace(String ns);
Int XmlReader.normalization();

