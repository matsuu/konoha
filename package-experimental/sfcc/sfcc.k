

if(!System.hasLib("cimcclient")) {
	OUT << "you need sfcc (libcimcclient)" << EOL;
}


/* ------------------------------------------------------------------------ */
/* Class Definition */

class CIMObjectPath;
class CIMClient;
class CIMInstance;
class CIMEnumeration;

/* ------------------------------------------------------------------------ */
/* CIMObjectPath */

/**
 * CIMObjectPath を作る
 * @param path オブジェクトパス
 * @param packname パッケージの名前
 */

CIMObjectPath CIMObjectPath.new(String path, String packname);

/**
 * Key を追加する
 * @param name keyの名前
 * @param value keyの値
 */

void CIMObjectPath.addKey(String name, String value);

/**
 * String を得る
 */

String CIMObjectPath.toString();


/**
 * NameSpace を得る
 */

//String CIMObjectPath.getNameSpace();

/**
 * ClassName を得る
 */

//String CIMObjectPath.getClassName();

/**
 * KeyCount を得る
 */

//int CIMObjectPath.getKeyCount();

/* ------------------------------------------------------------------------ */
/* CIMClient */

/**
 * CIMClient を作る
 * @param url - 接続先のCIM Object Manager をあらわすURL
 */

CIMClient CIMClient.new(String url);

/**
 * クラス名の一覧をイテレータとしてえる
 * @param op CIMObjectPath
 * @param flag フラグ（省略可能)
 * @return クラス名の一覧
 * とりあえず前の感じで
 */

String.. CIMClient.enumClassNames(CIMObjectPath op, Int? flag);

 /** 
  * invokeMethod
  * @param op CIMObjectPath 
  * @param name Method name
  * @param arg Input parameter
  * @return Method return value.
  */
String CIMClient.invokeMethod(CIMObjectPath op, String name, String arg);

/**
 * インスタンス名の一覧をイテレータとしてえる
 * @param op CIMObjectPath
 * @return インスタンス名の一覧
 * とりあえず前の感じで
 */

String.. CIMClient.enumInstanceNames(CIMObjectPath op);

/*------------------------------------------------------------------------ */
/* CIMInstance */

/**
 * CIMInstance を作る
 * @param cc CIMClient
 * @param op CIMObjectPath
 * @return CIMInsatnce
 */

CIMInstance CIMInstance.new(CIMClient cc, CIMObjectPath op);

/**
 * CIMInsatnceからCIMObjectPathを得る
 */

CIMObjectPath CIMInstance.getObjectPath();

/**
 * Property を得る
 */

String[] CIMInstance.getProperty();

/**
 * PropertyCount を得る
 */

//int CIMInstance.getPropertyCount();


/*------------------------------------------------------------------------ */
/* CIMEnmumeration */

//void CIMEnumeration.printEnm(CIMObjectPath op);
