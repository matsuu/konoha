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

