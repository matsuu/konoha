#!/usr/local/bin/konoha
using libxml2.*;
// parse xml file and get title.

XmlReader reader = new XmlReader("rss.xhtml");
while(reader.read()){
    type = reader.nodeType();
    if(type == XmlReader.TYPE_ELEMENT && reader.constName() == "title"){
        reader.read();
        if(reader.nodeType() == XmlReader.TYPE_TEXT){
            OUT  << reader.constValue() << EOL;
        }
    }
}

reader.close();

