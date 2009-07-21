

if(!System.hasLib("cimcclient0")) {
	OUT << "you need sfcc (libcimcclient0)" << EOL;
}


/* ------------------------------------------------------------------------ */
/* Class Definition */

class CIMObjectPath;
class CIMClient;

/* ------------------------------------------------------------------------ */
/* CIMObjectPath */

/**
 * CIMObjectPath を作る
 * @param path オブジェクトパス
 */

CIMObjectPath CIMObjectPath.new(String path);

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
 */

String.. CIMClient.enumClassNames(CIMObjectPath op, Int? flag);
