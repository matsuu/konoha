#!/usr/local/bin/konoha
/*----------------------------------------------------------*/
print "[import]:const.k";

/** スクリプトの簡易説明 */
usage="""
*************************************
*  klip ( Konoha LIbrary Provider ) *
*          version 0.1.8 (09/08/28) *
*************************************

usage:
  klip option [pkg]

options:

  list        : list of package on server

  installed   : list of packages already installed

  search  pkg : search package from list on server

  install pkg : install package

  update  pkg : update package

  remove  pkg : remove package

  undo        : undo previous operation
""";

/** intでreturnする一般メソッド用の定数 */
EXIT_SUCCESS = 1;
EXIT_NORMAL  = 0;
EXIT_ERROR   = -1;

/** システムファイルを保存するディレクトリ */
klipdir = $env.home + "/.konoha/klip";

/** パッケージのデータを一時保存するディレクトリ */
tmpdir = klipdir + "/tmp";

/** パッケージをインストールするディレクトリ(後に代入) */
instdir = "";

/** インストール済みのパッケージを記録するシステムファイル */
curdata = klipdir + "/current.json";

/** curdataに記録するテキストの書式 */
CURFORM = '{"name":"%s{0}","version":"%s{1}","url":"%s{2}"},';

/** 一つ前のcurdataのバックアップファイル */
prevdata = klipdir + "/previous.json";

/** 最新のシステム情報のログファイル */
latest = klipdir + "/latest.log";

/** latest.log操作時のモード指定の定数 */
ADD = 1;
REPLACE = 2;
DELETE = 3;

/** サーバーから取得するパッケージリスト名 */
KLIPFILE = "klip.json";

/** パッケージリストの存在するURL */
KLIPURL = "http://konoha.sourceforge.jp/klip/" + KLIPFILE;
//KLIPURL = "http://localhost/klip/" +  KLIPFILE;

/** sourceforgeのミラーサイトのドメイン */
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];

/** ローカルに保存したパッケージリストのパス */
klipdata = klipdir + "/" + KLIPFILE;

/** システム情報のチェック用フラグ */
boolean root;
boolean plat;
boolean fail = false;
boolean use_curl = false;
boolean use_zlib = false;
boolean use_libtar = false;
boolean use_posix = false;
boolean use_zllt = false;
/*----------------------------------------------------------*/
print "[import]:env.k";

/** システムディレクトリの作成 */
if ( !os.hasDir(klipdir) ) os.mkdir(klipdir);
if ( !os.hasDir(tmpdir) ) os.mkdir(tmpdir);
tmpdir += "/";

/** ユーザーモードのチェック */
userdir = $user.package.path;
try {
	assert(userdir);
} catch (Exception e) {
  OUT.println("Null!! : $user.package.path");
}

rootdir = $konoha.package.path;
try {
	assert(rootdir);
} catch (Exception e) {
  OUT.println("Null!! : $konoha.package.path");
}

instdir = rootdir;
if ( !os.hasDir( instdir ) )
	root = os.mkdir( instdir );
else {
	String home = $env.HOME;
	if ( "root" in? home )
		root = true;
	else
		root = false;
}
if ( !root ) {
	instdir = userdir;
	if ( !os.hasDir( instdir ) )
		os.mkdir( instdir );
}
instdir += "/";

/**
 * 利用するライブラリパッケージのチェック
 */

//curl

String libcurl = instdir + "curl";
class Curl {
	boolean easyPerform();
	void easySetOpt(int type, Any? data);
}
if ( os.hasDir( libcurl ) ) {
	if ( os.hasLib("libcurl") ) {
		eval ( "using curl.*;");
		use_curl = true;
	}
}
		
//zlib

String libzlib = instdir + "zlib";
class Zlib {
	boolean decompGZ(String gzfile,String outfile);
}
if ( os.hasDir( libzlib ) ) {
	if ( os.hasLib("libz") ) {
		eval ( "using zlib.*;" );
		use_zlib = true;
	}
}

//libtar

String liblibtar = instdir + "libtar";
class Tar {
	boolean extractTar(String tarfile);
}
if ( os.hasDir( liblibtar ) ) {
	if ( os.hasLib("libtar") ) {
		eval ( "using libtar.*;" );
		use_libtar = true;
	}
}
		
//posix

String libposix = instdir + "posix";
plat = true;
String shared = $konoha.platform;
if ( "linux" in? shared ) {
	shared += ".so";
} else if ( "macosx" in? shared ) {
	shared += ".dylib";
} else {
	plat = false;
}
int System.system(String cmd);
if ( os.hasDir( libposix ) ) {
	if ( os.hasLib( libposix + "/posix_" + shared ) ) {
		eval ( "using posix.*;" );
		use_posix = true;
	}
}
/*----------------------------------------------------------*/
print "[import]:pkg_arc.k";

/** 
 * パッケージの.tar.gzアーカイブのクラス
 */
class PackageArc {

	/** パッケージの名前 */
	String name;

	/** アーカイブの存在するパス */
	String filepath;

	/**
	 * PackageArcクラスのコンストラクタ
	 * @param name 名前
	 * @param filepath アーカイブのパス
	 */
	PackageArc(String name,String filepath){
		this.name = name;
		this.filepath = filepath;
	}

	/**
	 * アーカイブの解凍を行う
	 * @return boolean 解凍の成否を返す
	 */
	@Virtual boolean decompress();

}
/*----------------------------------------------------------*/
print "[import]:pkg_arc_sys.k";

/**
 * パッケージの.tar.gzアーカイブのクラス
 * posixパッケージのSystem.system関数から、
 * tarコマンドを呼び出すことで解凍する
 * @see PackageArc
 */
class PackageArcSys extends PackageArc {

	/**
	 * system関数からtarコマンドを呼び出して解凍する
	 * @return 解凍の成否
	 */
	boolean decompress(){
		int ret;
		ret = System.system("tar -xzf " + filepath);
		if ( ret != 0 || !os.hasDir(name) ) {
			print("!ERR : PackageArcSys.decompress : System.system");
			return false;
		}
		os.rename(name,__instdir + name);
		return true;
	}
}
/*----------------------------------------------------------*/
print "[import]:pkg_arc_zllt.k";

/**
 * パッケージの.tar.gzアーカイブのクラス
 * libtarパッケージのTar.extractTarと、
 * zlibパッケージのZlib.decompGZを利用して解凍する
 * @see PackageArc
 */
class PackageArcZllT extends PackageArc {

	/**
	 * Zlib.decompGZと、Tar.extractTarを呼び出して解凍する
	 * @return 解凍の成否
	 */
	boolean decompress(){
		String tarfile = filepath - ".gz";
		if ( !Zlib.decompGZ(filepath,tarfile) ) {
			print("!ERR : PackageArcZllT.decompress : Zlib.decompGZ");
			return false;
		}
		boolean res = Tar.extractTar(tarfile);
		os.unlink(tarfile);
		String pkgdir = __tmpdir + name;
		if ( !res || !os.hasDir(pkgdir) ) {
			print("!ERR : PackageArcZllT.decompress : Tar.extractTar");
			return false;
		}
		os.rename(pkgdir,__instdir + name);
		return true;
	}
	
}
/*----------------------------------------------------------*/
print "[import]:pkg_get.k";

/**
 * パッケージのtar.gzアーカイブを取得するクラス
 */
class PackageGet {

	/** パッケージのアーカイブのURL */
	String url;
	/** アーカイブの保存先のパス */
	String filepath;

	/**
	 * PackageGetクラスのコンストラクタ
	 * @param url URL
	 * @param filepath 保存先のパス
	 */
	PackageGet(String url,String filepath){
		this.url = url;
		this.filepath = filepath;
	}

	/**
	 * アーカイブの取得を行う
	 * @return 取得の成否
	 */
	@Virtual boolean get();

}
/*----------------------------------------------------------*/
print "[import]:pkg_get_curl.k";

/**
 * パッケージの取得を行うクラス
 * curlパッケージを利用して取得する
 * @see PackageGet
 */
class PackageGetCurl extends PackageGet
{

	/**
	 * Curl.easyPerformを呼び出してアーカイブを取得する
	 * @return 取得の成否
	 */
	boolean get()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]);
		ous = new OutputStream(filepath,"wb");
		Curl c = new Curl();
		c.easySetOpt(10002,pkgurl);  //Curl.OPT_URL
		c.easySetOpt(10001,ous);     //Curl.OPT_FILE
		c.easyPerform();
		ous.close();
		if ( !os.hasFile(filepath) ) {
			print("!ERR : PackageGetCurl.get : Curl.easyPerform");
			return false;
		}
		return true;
	}
	
}
/*----------------------------------------------------------*/
print "[import]:pkg_get_strm.k";

/**
 * パッケージの取得を行うクラス
 * Streamでの通信を利用して取得する
 * @see PackageGet
 */
class PackageGetStream extends PackageGet {

	/**
	 * StreamからHTTP経由でアーカイブを取得する
	 * @return 取得の成否
	 */
	boolean get()
	{
		String pkgurl = %(url,__sites[Int.random(|sites|)]) + "@@" - "@@";
		ous = new OutputStream(filepath,"wb");
		ins = new InputStream(pkgurl);
		int count = 0;
		int buf;
		while(true){
			buf = ins.getChar();
			if ( count >= 3 ) {
				if ( buf == -1 ){ break; }
				else {
					ous.putChar(buf);
				}
			} else if ( buf == 10 ) {
				if ( count == 2 || count == 0 ) {
					count++;
				}
			} else if ( buf == 13 && count == 1 ) {
				count++;
			} else {
				count = 0;
			}
		}
		ous.close();
		ins.close();
		if ( !os.hasFile(filepath) ) {
			print("!ERR : PackageGetStream.get : stream");
			return false;
		}
		return true;
	}

}
/*----------------------------------------------------------*/
print "[import]:parser.k";

/**
 * パッケージリストをパースするクラス
 */
class Parser
{
	/** パースして抜き出すパッケージの名前 */
	String name;
	/** 抜き出したパッケージのバージョン */
	String version;
	/** 抜き出したパッケージのURL */
	String url;
	/** 抜き出したパッケージが依存するパッケージの情報 */
	String[] depend;
	/** パースするリストのファイル名 */
	String file;

	/**
	 * Parserのコンストラクタ
	 * @param name パースするパッケージ名
	 * @param file パースするリストファイル名
	 */
	Parser(String name, String file)
	{
		this.name = name;
		this.depend = [];
		this.file = file;
 	}

	/** パースした各フィールドの情報を自身に設置する */
	@Virtual void getMember();

	/** 
	 * 自身のフィールドの情報から、
	 * リストの書式に沿ったパッケージ情報を生成する
	 * @return パッケージ情報のリスト書式での文字列
	 */
	@Virtual String generate();

	/**
	 * リストファイルにある全パッケージの名前を出力する
	 * @return パッケージ名のString配列
	 */
	@Virtual String[] getNameList();

}
/*----------------------------------------------------------*/
print "[import]:parser_sql.k";

/**
 * sqlite3のdbからメンバを得るクラス
 * @see Parser
 */
class ParserSqlite extends Parser
{
	/** sqlite3のdbへのコネクション */
	Connection con;
	
	/**
	 * ParserSqliteのコンストラクタ
	 * @param name データを取得するパッケージ名
	 * @param file sqlite3のdbファイル名
	 */
	ParserSqlite(String name, String file)
	{
		super(name,file);
		db = "sqlite3:" + this.file;
		this.con = new Connection(db);
	}

	/** 取得した各フィールドの情報を自身に設置する */
	void getMember()
	{
		rs = con.query("select * from package");
		while(rs.next()) {
			nm = rs.getString("name");
			if ( nm == this.name ) break;
		}
		this.version = rs.getString("version");
		this.url = rs.getString("url");
		rs.close();
		this.depend = getDepend();
	}

	/**
	 * dbにある全パッケージの名前を出力する
	 * @return パッケージ名のString配列
	 */
	String[] getNameList()
	{
		String[] ret = [];
		rs = con.query("select name from package");
		while(rs.next()) {
			ret << rs.getString("name");
		}
		rs.close();
		return ret;
	}

	/**
	 * 自身の依存するパッケージの情報を取得する
	 * @return 依存するパッケージの情報の文字列配列
	 */
	String[] getDepend()
	{
		String[] ret = [];
		cn = new Connection("sqlite3:" + file);
		rs = cn.query("select * from dependency");
		while(rs.next()) {
			if ( rs.getString("name") == name ) {
				nm = rs.getString("dname");
				ver = rs.getString("dver");
				ret << (nm + "=" + ver);
			}
		}
		rs.close();
		return ret;
	}

}
/*----------------------------------------------------------*/
print "[import]:parser_json.k";

/**
 * json形式のパッケージリストをパースするクラス
 * @see Parser
 */
class ParserJson extends Parser
{

	/** パースした各フィールドの情報を自身に設置する */
	void getMember()
	{
		this.version = getElement("version");
		this.url = getElement("url");
		this.depend = getElement("depend").split("&",0);
	}

	/**
	 * リストファイルにある全パッケージの名前を出力する
	 * @return パッケージ名のString配列
	 */
	String[] getNameList()
	{
		String[] ret = [];
		String[] box;
		String raw = rawjs();
		String check = '"name":"';
		box = raw.split(check,0);
		foreach(String txt from box) {
			ret << txt / '"';
		}
		ret.remove(0);
		return ret;
	}

	/** 
	 * 自身のフィールドの情報から、
	 * jsonの書式に沿ったパッケージ情報を生成する
	 * @return パッケージ情報のjson書式での文字列
	 */
	String generate()
	{
		String ret;
		if ( this.url == "" ) { return ret; }
		ret += "{\n";
		ret += setNode("name",this.name) + ",\n";
		ret += setNode("version",this.version) + ",\n";
		ret += setNode("url",this.url);
		if ( this.depend[0] != "" ) { ret += ",\n" + arrayNode("depend",this.depend); }
		return ret + "\n}\n";
	}

	/** 
	 * リストファイルから各フィールドの情報を抜き出す
	 * @param elemname リクエストするフィールド
	 * @return リスト内から抜き出したフィールド情報の文字列
	 */
	String getElement(String elemname)
	{
		String ret;
		String raw = rawjs();
		String check = %('"name":"%s{0}"',this.name);
		while( true ) {
			if ( raw == "" ) { break; }
			else if ( check in? ( raw / "," ) ) {
				ret = parseThisTree(raw,elemname); 
				break;
			}
			raw = succRaw(raw);
		}
		return ret;
	}

	/** 
	 * リストファイル内での目的のパッケージの位置、
	 * 指定されたフィールド部分を抜き出す
	 * @param raw 目的のパッケージ情報以降のリストの全文字列
	 * @param elemname リクエストするフィールド
	 * @return リスト内から抜き出したフィールド情報の文字列
	 */
	String parseThisTree(String raw,String elemname)
	{
		String ret;
		String key = %('"%s{0}":',elemname);
		while(true) {
			if ( raw == "" ) { break; }
			String pic = raw / ",";
			if ( key in? pic ) { 
				if ( elemname != "depend" ) {
					ret = pic.split('":"',0).pop();
					ret = ret.split('"',0)[0];
					return ret;
				}
				else { return getDependencies(raw); }
			} else if ( "}" in? pic && !("{0}" in? pic) ) { break; }			
			raw = succRaw(raw);
		}
		return ret;
	}

	/** 
	 * パッケージの依存情報を、単純に記号連結した文字列として出力する
	 * @param raw 目的のパッケージの依存情報以降のリストの全文字列
	 * @return 連結した依存情報の文字列
	 */
	String getDependencies(String raw)
	{
		String ret;
		String base = ( raw - "]" ) % '"depend":["';
		while( base != "") {
			ret += base.split('"',0)[0] + "&";
 			base %= '","';
		}
		return ret;
	}

	/** 
	 * リストファイルのテキストを全て連結し、
	 * 改行文字を消去した文字列で返す
	 * @return 連結したテキストの文字列
	 */
	String rawjs()
	{
		String ret;
		ins = new InputStream(this.file,"r");
		foreach( String txt from ins ) {
			ret += txt;
		}
		ins.close();
		return ret - "\t";
	}

	/** 
	 * jsonの区切り文字(,)単位で現在の読み取り位置を進める
	 * @param raw 現在の読み取り位置以降の文字列
	 * @return １単位進めた位置以降の文字列
	 */
	String succRaw (String raw)	{ return raw % ","; }

	/** 
	 * jsonのノードの文字列を生成する
	 * @param name ノード名
	 * @param data ノードのデータ
	 * @return 生成したノードの文字列
	 */
	String setNode(String name,String data)
	{
		return %('"%s{0}":"%s{1}"',name,data );
	}

	/** 
	 * jsonの配列ノードの文字列を生成する
	 * @param name ノード名
	 * @param data ノードのデータ配列
	 * @return 生成した配列ノードの文字列
	 */
	String arrayNode(String name,String[] data)
	{
		String ret;
		ret += %('"%s{0}":[',name);
		foreach ( String cell from data) {
			ret += %('"%s{0}",',cell);
		}
		return ret[..|ret|-2] + "]";
	}

}
/*----------------------------------------------------------*/
print "[import]:files.k";

/**
 * システムファイルを操作するクラス
 */
class Files {

	//latest

	/** 
	 * latestの特定セクションを更新する
	 * @param section 変更するセクション名
	 * @param diff 書き換える内容
	 */
	void updateLatest(String section, String diff)
	{
		boolean flag = false;
		ins = new InputStream(__latest,"r");
		ous = new OutputStream(__latest + "~","a");
		String form;
		if ( section == "install" )
			form = "Last-Installed-Package:";
		else if ( section == "modified" )
			form = "Last-Modified:";
		foreach( String txt from ins ) {
			if ( txt.startsWith(form) ) {
				flag = true;
				txt = form + diff;
			}
			ous.println(txt);
		}
		if ( !flag ) ous.println(form + diff);
		ous.close();
		ins.close();
		os.rename(__latest + "~",__latest);
	}

	/** 
	 * latestの全セクションリセットする
	 */
	void resetLatest() {
		os.unlink(__latest);
		ous = new OutputStream(__latest,"a");
		ous.close();
		updateLatest("install"," None");
		updateLatest("modified"," None");
	}

	//klipdata

	/** 
	 * klipdataをサーバーから取得する
	 * @return 取得の成否
	 */
	boolean getKlipData()
	{
		if ( checkLastMod() ) { return true; }
		os.unlink(__klipdata);
		boolean write = false;
		ins = new InputStream(KLIPURL,"r");
		ous = new OutputStream(__klipdata,"a");
		foreach ( String txt from ins ) {
			if ( "{" == txt || write ) {
				write = true;
				ous.println(txt);
				if ( txt == "}" ) {	break; }
			} else if ( "Last-Modified:" in? txt ) {
				updateLatest("modified",
							 txt.split("Last-Modified:",0).pop());
            }
		}
		ins.close();
		ous.close();
		return true;
	}

	/** 
	 * サーバーとローカルとのklipdataの、
	 * Last-Modifiedの情報を比較して、
	 * 更新されているかをチェックする
	 * @return 更新の有無
	 */
	boolean checkLastMod()
	{
		String las = getLastMod(__latest);
		String net = getLastMod(KLIPURL);
		if ( las != net )
			return false;
		else return true;
	}

	/** 
	 * ローカルのklipdataを削除し、
	 * latestのinstallセクションリセットする
	 */
	void rmKlipData()
	{
		os.unlink(__klipdata);
		updateLatest("modified"," None");
	}

	//curdata & prevdata

	/** 
	 * curdataの一時的なバックアップファイルを作成する
	 */
	void mkBufCurData()	{
		copyText(__curdata,__curdata + "~");
	}

	/** 
	 * curdataのバックアップファイルを削除する
	 */
	void rmBufCurData() {
		os.unlink(__curdata + "~");
	}

	/** 
	 * curdataのバックアップの内容でprevdataを書き換える
	 */
	void cpBufCur2Prev() {
		copyText(__curdata + "~",__prevdata);
	}

	/** 
	 * curdataとprevdataの内容を初期の状態にリセットする
	 */
	void resetCurPrev() {
		resetText2Js(__curdata);
		resetText2Js(__prevdata);
	}

	/** 
	 * curdataの内容を更新する
	 * @param data 更新するパッケージ情報の文字列配列
	 * @param mode 更新のモード
	 */
	void modCurData(String[] data,int mode)
	{
		InputStream ins = new InputStream(__curdata,"r");
		OutputStream ous = new OutputStream(__curdata + "#","a");
		String base = %('"name":"%s{0}"',data[0]);
		String put = %(CURFORM,data[0],data[1],data[2]);
		if ( mode == ADD ){
			addPkgData(ins,ous,put);
		} else if ( mode == REPLACE ) {
			replPkgData(ins,ous,base,put);
		} else if ( mode == DELETE ) {
			delPkgData(ins,ous,base);
		}
		ins.close();
		ous.close();
		os.rename(__curdata + "#",__curdata);
	}

	/** 
	 * curdataとprevdataの内容を比較して、
	 * 基準側から見て削除されている部分を返す
	 * @param opr 差分の基準側のファイル
	 * @return 差分の文字列配列
	 */
	String[] changeDiff(String base)
	{
		String bef;
		String aft;
		if( base == "prev"){
			bef = __prevdata;
			aft = __curdata;
		} else if( base == "cur" ) {
			bef = __curdata;
			aft = __prevdata;
		}
		return getDiff(bef,aft);
	}

	/** 
	 * 入力ストリームからのテキストを読み取って、
	 * 更に新しいパッケージの情報文字列を追加して出力ストリームに出力する
	 * @param ins 入力ストリーム
	 * @param ous 出力ストリーム
	 * @param put 新しく挿入するパッケージ情報の文字列
	 */
	void addPkgData(InputStream ins, OutputStream ous, String put)
	{
		String base = put;
		String name = put % '"name":"' / '"';
		String txtname;
		foreach( String txt from ins ) {
			if ( txt == "}" ) break;
			txtname = txt % '"name":"' / '"';
			if ( txtname > name && base != "" ) {
				ous.println(base);
				base = "";
			}
			ous.println(txt);
		}
		if ( base != "" ) ous.println(base);
		ous.println("}");
	}

	/** 
	 * 入力ストリームからのテキスト内の、
	 * 特定のパッケージ情報を更新して出力ストリームに出力する
	 * @param ins 入力ストリーム
	 * @param ous 出力ストリーム
	 * @param base 置き換える元のパッケージ情報のキー文字列
	 * @param put 新しく置き換えるパッケージ情報の文字列
	 */
	void replPkgData(InputStream ins, OutputStream ous, String base,String put)
	{
		foreach ( String txt from ins ) {
			if ( base in? txt )	ous.println(put);
			else ous.println(txt);
		}
	}

	/** 
	 * 入力ストリームからのテキストから、
	 * 特定のパッケージ情報を除いて出力ストリームに出力する
	 * @param ins 入力ストリーム
	 * @param ous 出力ストリーム
	 * @param base 出力から除外するパッケージのキー文字列
	 */
	void delPkgData(InputStream ins, OutputStream ous, String base)
	{
		foreach ( String txt from ins )
			if ( !(base in? txt) ) ous.println(txt);
	}

	//common methods

	/**
	 * ファイルまたはストリームから、
	 * Last-Modifiedセクションのデータを取得する
	 * @param fist 読み込むファイルストリーム名
	 * @return 取得したデータ文字列
	 */
	String getLastMod(String fist)
	{
		ins = new InputStream(fist,"r");
		foreach( String txt from ins ) {
			if ( "Last-Modified:" in? txt ) {
				ins.close();
				return txt; 
			}
		}
		ins.close();
		print("!WARN: Files.getLastMod : NOT FOUND");
		return "";
	}

	/**
	 * json形式のファイルの内容をリセットする
	 * @param filename リセットするファイル名
	 */
	void resetText2Js(String filename)
	{
		if ( filename.split(".",0).pop() == "json" ) {
			os.unlink(filename);
			ous = new OutputStream(filename,"w");
			String[] form = ["{","}"];
			foreach( String txt from form) {
				ous.println(txt);
			}
			ous.close();
		}
	}
	
	/**
	 * テキストファイルの内容をコピーする
	 * @param infile コピー元ファイル名
	 * @param outfile コピー先ファイル名
	 */
	void copyText(String infile ,String outfile)
	{
		os.unlink(outfile);
		ins = new InputStream(infile,"r");
		ous = new OutputStream(outfile,"w");
		foreach(String txt from ins) {
			ous.println(txt);
		}
		ous.close();
		ins.close();
	}

	/**
	 * ２つのテキストファイルを比較して、
	 * 対象側に無い部分の文字列配列を返す
	 * @param bef 比較の基準となるファイル名
	 * @param ouf 比較の対象となるファイル名
	 * @return 比較から得た差分の文字列配列を返す
	 */
	String[] getDiff(String bef, String aft)
	{
		String[] ret =[];
		base = new InputStream(bef,"r"); 
		boolean chk;
		foreach( String txt from base ) {
			chk = true;
			targ = new InputStream(aft,"r");	
			foreach( String txt2 from targ )
				if( txt == txt2 ) chk = false;
			targ.close();
			if (chk) ret << txt;
		}
		base.close();
		return ret;
	}	

}
/*----------------------------------------------------------*/
print "[import]:package.k";

class Package
{
	/** パッケージの名前 */
	String name;
	/** パッケージのバージョン */
	String version;
	/** パッケージのURL */
	String url;
	/** パッケージが依存するパッケージの情報 */
	String[] depend;

	/**
	 * Packageクラスのコンストラクタ
	 * @param name パッケージの名前
	 */
	Package(String name)
	{
		this.name = name;
	}

	/**
	 * パッケージの名前をパーサーから取得する
	 * @param pars このパッケージの情報をパースしたパーサー
	 */
	void setMember(Parser pars)
	{
		this.version = pars.version;
		this.url = pars.url;
		this.depend = pars.depend;
	}

	//operations

	/**
	 * パッケージをインストールする
	 * @return インストールの結果
	 */
	int install()
	{
		OUT.println(%("KLIP : install ... : %s{0}\tver=%s{1}",name,version));
		if( !askYorN("install it?") ) { 
			OUT.println("KLIP : denyed to install");
			return EXIT_NORMAL;
		} else {
			OUT.println("KLIP : install this package");
		}
		return do_install();
	}
		
	/**
	 * パッケージを更新する
	 * @return 更新の結果
	 */
	int update()
	{
		OUT.println(%("KLIP : update  : %s{0}\tver=%s{1}",name,version));
		if( !askYorN("update it?") ) {
			OUT.println("KLIP : denyed to update");
			return EXIT_NORMAL;
		} else {
			OUT.println("KLIP : update this package");
		}
		if ( do_remove() == EXIT_ERROR ) {
			print("!ERR : Package.update : do_remove");
			return EXIT_ERROR;
		}
		return do_install();
	}

	/**
	 * パッケージを削除する
	 * @return 削除の結果
	 */
	int remove()
	{
		OUT.println(%("KLIP : remove  : %s{0}\tver=%s{1}",name,version));
		if( !askYorN("remove it?") ) {
			OUT.println("KLIP : denyed to remove");
			return EXIT_NORMAL;
		} else {
			OUT.println("KLIP : remove this package");
		}
		return do_remove();
	}

	/**
	 * インストールにおける実際のファイル操作を行う
	 * @return 操作の結果
	 */
	int do_install()
	{
		String filepath = __tmpdir + url.split("/",0).pop();
		if ( !os.hasFile( filepath ) ) {
			if ( !getPackage(filepath) ) {
				print("!ERR : Package.do_install : getPackage");
				return EXIT_ERROR;
			}
		}
		boolean ret = decompPackage(filepath);
		if ( !ret ) {
			print("!ERR : Package.do_install : decompPackage");
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	/**
	 * 削除における実際のファイル操作を行う
	 * @return 操作の結果
	 */
	int do_remove()
	{
		String pkgdir = __instdir + name;
		String[] files = os.listDir(pkgdir);
		if ( |files| == 0 ) {
			print("!ERR : Package.do_remove : NOT FOUND");
			return EXIT_ERROR;
		}
		removeFiles(pkgdir,files);
		if ( !os.rename(pkgdir,__tmpdir + name ) ) {
			print("!ERR : Package.do_remove : rename");
			return EXIT_ERROR;
		}
		OUT.println("KLIP : done!");
		return EXIT_SUCCESS;
	}

	/**
	 * パッケージのファイル（アーカイブ）を取得する
	 * @param filepath ファイルの保存パス
	 * @return 取得の成否
	 */
	boolean getPackage(String filepath)
	{
		PackageGet pg;
		if ( __use_curl ) {
			pg = (PackageGet) new PackageGetCurl(url,filepath);
		} else {
			pg = (PackageGet) new PackageGetStream(url,filepath);
		}
		return pg.get();
	}
	
	/**
	 * パッケージのファイル（アーカイブ）を解凍する
	 * @param filepath アーカイブの存在するパス
	 * @return 解凍の成否
	 */
	boolean decompPackage(String filepath)
	{
		PackageArc pa;
		if ( __use_zllt ) {
			pa = (PackageArc) new PackageArcZllT(name,filepath);
		} else if ( __use_posix ) {
			pa = (PackageArc) new PackageArcSys(name,filepath);
		} else {
			print("!ERR : Package.decompPackage : no way to decompPackage");
			return false;
		}
		return pa.decompress();
	}

	//common methods

	/**
	 * ユーザーにYes／Noの選択肢を選ばせる
	 * @param message 選択肢に表示させるメッセージ文字列
	 * @return 選択の結果(Yesならtrue)
	 */
	boolean askYorN(String message)
	{
		OUT.print(%("!ASK : %s{0} [y/n] : ",message));
		while( true ){
			input = IN.readLine();
			if ( input == "y" ) {
				return true;
			} else if ( input == "n" ) {
				return false;
			} else {
				OUT.print("!ASK : please input [y/n] : "); 
			}
		}
		return false;
	}

	/**
	 * ディレクトリ内の全ファイルを削除する
	 * (ただし、空のディレクトリは削除できないので残る)
	 * @param dir 指定するディレクトリ名
	 * @param files ディレクトリ内のファイル名の文字列配列
	 */
	void removeFiles(String dir,String[] files)
	{
		foreach (String file from files) {
			String filepath = dir + "/" + file;
			if ( os.hasFile(filepath) ) {
				os.unlink(filepath);
			} else if ( os.hasDir(filepath) ) {
				String[] subfiles = os.listDir(filepath);
				removeFiles(filepath,subfiles);
			}
		}
	}

}
/*----------------------------------------------------------*/

print "[import]:operator.k";

/**
 * オペレーションの実行を管理するクラス
 */
class Operator {
	/** オペレーションの名前 */
	String opr;
	/** オペレーションの対象となるパッケージ名 */
	String name;
	/** オペレーションで使用するシステムファイル */
	Files fs;
	
	/**
	 * Operatorクラスのコンストラクタ
	 * @param args メイン関数から引き渡されたコマンドライン引数
	 */
	Operator(String[] args)
	{
		int ret;
		String name = "";
		if ( |args| >= 2 && |args| <= 3 ) {
			this.opr = args[1];
			if ( |args| == 3 ) {
				name = args[2];
			}
		}
		this.name = name;
		this.fs = new Files();
	}

	/**
	 * コマンドラインから指定されたオペレーションが正しいかチェックする
	 * @return オペレーションの有無
	 */
	boolean check()
	{
		String[] ops = ["search",
						"install",
						"update",
						"remove",
						"undo",
						"list",
						"installed",
						"clean"];
		return ( opr in? ops );
	}

	/**
	 * システムファイルが無い場合に新規作成する
	 */
	void init()
	{
		if ( !os.hasFile(__latest) ) {
			fs.resetLatest();
		}
		if ( !os.hasFile(__curdata) ) {
			fs.resetCurPrev();
		}
	}

	/**
	 * オペレーションの開始
	 * @return オペレーションの結果
	 */
	int start()
	{
		int ret;
		String[] need_none = ["undo",
							  "clean"];
		String[] need_cur = ["installed",
							 "remove"];
		String[] need_klip = ["search",
							  "list",
							  "update",
							  "install"];
		if ( opr in? need_none )
			ret = systemOpr(opr);
		else if ( opr in? need_cur )
			ret = localOpr(opr);
		else if ( opr in? need_klip )
			ret = globalOpr(opr);
		if ( ret == EXIT_ERROR )
			OUT.println("!ERR : " + opr + " faild");
		return ret;
	}

	//common

	/**
	 * パッケージの情報をパースするパーサーを、
	 * パースするリストファイルに対応させて生成する
	 * @param pkgname パッケージの名前
	 * @param filename パースするリストファイル名
	 * @return ファイルに対応したパーサー
	 */
	Parser getParser(String pkgname,String filename)
	{
		String type = filename.split(".",0).pop();
		Parser pars;
		if ( type == "json" )
			pars = new ParserJson(pkgname,filename);
		else print("!ERR : Operator.getParser : type");
		return pars;
	}

	/**
	 * リストファイルに存在するパッケージ名の配列を取得する
	 * @param filename リストファイル名
	 * @return パッケージ名の配列
	 */
	String[] mkNameList(String filename)
	{
		Parser pars = getParser("",filename);
		pars.getMember();
		return pars.getNameList();
	}

	/**
	 * 特定パッケージのインスタンスを作成し、
	 * 指定したリストファイルからの情報をセットして返す
	 * @param pkgname パッケージ名
	 * @param filename リストファイル名
	 * @return 作成したパッケージインスタンス
	 */
	Package mkPackage(String pkgname, String filename)
	{
		Package pac = new Package(pkgname);
		Parser pars = getParser(pkgname,filename);
		pars.getMember();
		pac.setMember(pars);
		return pac;
	}

	/**
	 * パッケージの正当性をチェックする
	 * @param pkg チェック対象のパッケージ
	 * @return 正当性の是非
	 */
	boolean checkPackage(Package pkg)
	{
		if ( |pkg.version| == 0 ) return false;
		if ( |pkg.url| == 0 ) return false;
		return true;
	}

	//search & list

	/**
	 * リストファイルからパッケージの情報を検索する
	 * @param filename リストファイル名
	 * @return 検索の結果
	 */
	int searchPackage(String filename)
	{
		String form = "PACK : %s{0}\tver=%s{1}";
		Package pac = mkPackage(name,filename);
		if ( checkPackage(pac) ) {
			OUT.println("INFO : package FOUND!");
			OUT.println(%(form,pac.name,pac.version));
		} else {
			OUT.println("INFO : package NOT FOUND");
		}
		return EXIT_SUCCESS;
	}

	/**
	 * リストファイルの全パッケージ情報の一覧を表示する
	 * @param filename リストファイル名
	 * @return リスト表示の結果
	 */
	int showList(String filename)
	{
		if ( !os.hasFile(filename) ) return EXIT_ERROR;
		String[] list = mkNameList(filename);
		String form = "PACK : %s{0}\tver=%s{1}";
		foreach (String nm from list) {
			Package pac = mkPackage(nm,filename);
			if ( !checkPackage(pac) ) continue;
			OUT.println(%(form,pac.name,pac.version));
		}
		OUT.println("KLIP : theere are [" + |list| + "] packages");
		return EXIT_SUCCESS;
	}

	//operation groups

	/**
	 * スクリプトの内部を操作するオペレーションを実行する
	 * @param opr 指定されたオペレーション
	 * @return オペレーションの結果
	 */
	int systemOpr(String opr)
	{
		if ( opr == "undo" ) return undoMain();
		if ( opr == "clean" ) return cleanMain(); 
		return EXIT_ERROR;
	}

	/**
	 * ローカルのみの操作を行うオペレーションを実行する
	 * @param opr 指定されたオペレーション
	 * @return オペレーションの結果
	 */
	int localOpr(String opr)
	{
		if ( opr == "installed" ) return showList(__curdata);
		Package pkg = mkPackage(name,__curdata);
		if ( opr == "remove" ) {
			if ( checkPackage(pkg) ) { 
				return removeMain(pkg);
			} else if (os.hasDir(__instdir + pkg.name)) {
				OUT.println("INFO : package is installed by klip");
			} else {
				OUT.println("INFO : package isn't installed");
			}
			return EXIT_NORMAL;
		}
		return EXIT_ERROR;
	}

	/**
	 * ネットへの接続が可能なことが前提になるオペレーションを実行する
	 * @param opr 指定されたオペレーション
	 * @return オペレーションの結果
	 */
	int globalOpr(String opr)
	{
		fs.getklipdata();
		if ( opr == "list" ) return showList(__klipdata);
		if ( opr == "search" ) return searchPackage(__klipdata);
		Package chk = mkPackage(name,__curdata);
		Package pkg = mkPackage(name,__klipdata);
		if ( !checkPackage(pkg) ) {
			OUT.println("INFO : package is NOT FOUND");
			return EXIT_NORMAL;
		}
		if ( opr == "install" )
			if ( !checkPackage(chk) ) return installMain(pkg);
			else {
				OUT.println("INFO : package is already installed");
				if ( chk.version >= pkg.version ) return EXIT_NORMAL;
				return updateMain(pkg);
			}
		if ( opr == "update" )
			if ( checkPackage(chk) ) {
				if ( chk.version >= pkg.version ) return EXIT_NORMAL;
				return updateMain(pkg);
			} else {
				OUT.println("INFO : package isn't installed");
				return installMain(pkg);
			}
		return EXIT_ERROR;
	}

	//for each operations

	/**
	 * パッケージをインストールの為の依存性の確認や、
	 * 実行に伴ったシステムファイル操作等を行う
	 * @param pkg インストールするパッケージ
	 * @return インストールの結果
	 */
	int installMain(Package pkg)
	{
		int ret;
		fs.mkBufCurData();
		fs.updateLatest("install", pkg.name + "=" + pkg.version );
		if ( |pkg.depend| == 0 ) ret = pkg.install();
		else ret = dinstall(pkg);
		if ( ret == EXIT_SUCCESS ) {
			if ( |pkg.depend| == 0 )
				fs.modCurData([pkg.name,pkg.version,pkg.url],ADD);
			fs.cpBufCur2Prev();
		}
		fs.rmBufCurData();
		return ret;
	}
	
	/**
	 * パッケージ更新に伴ったシステムファイル操作等を行う
	 * @param pkg 更新するパッケージ
	 * @return 更新の結果
	 */
	int updateMain(Package pkg)
	{
		int ret;
		fs.mkBufCurData();
		fs.updateLatest("install", pkg.name + "=" + pkg.version);
		ret = pkg.update();
		if ( ret == EXIT_SUCCESS ) {
			fs.modCurData([pkg.name,pkg.version,pkg.url],REPLACE);
			fs.cpBufCur2Prev();
		}
		fs.rmBufCurData();
		return ret;
	}
	
	/**
	 * パッケージ削除に伴ったシステムファイル操作等を行う
	 * @param pkg 削除するパッケージ
	 * @return 削除の結果
	 */
	int removeMain(Package pkg)
	{
		int ret;
		fs.mkBufCurData();
		ret = pkg.remove();
		if ( ret == EXIT_SUCCESS ) {
			fs.modCurData([pkg.name,pkg.version,pkg.url],DELETE);
			fs.cpBufCur2Prev();
		}
		fs.rmBufCurData();
		return ret;
	}
	
	/**
	 * システムファイルを最初期の状態に初期化する
	 * @return 初期化の結果を返す
	 */
	int cleanMain()
	{
		fs.rmKlipData();
		fs.resetCurPrev();
		fs.updateLatest("install"," None");
		return EXIT_SUCCESS;
	}

	/**
	 * アンドゥの実行に伴うシステムファイル操作を行う
	 * @return アンドゥの結果を返す
	 */
	int undoMain()
	{
		String[] u_fail = [];
		fs.mkBufCurData();
		if ( undo("cur") != EXIT_SUCCESS ) u_fail << "u_rm";
		if ( undo("prev") != EXIT_SUCCESS ) u_fail << "u_in";
		if ( |u_fail| != 0 ) {
			fs.rmBufCurData();
			if ( "u_in" in? u_fail ) OUT.println("!ERR : undo : uninstall failed");
			if ( "u_rm" in? u_fail ) OUT.println("!ERR : undo : unremove failed");
			return EXIT_NORMAL;
		}
		fs.cpBufCur2Prev();
		fs.rmBufCurData();
		return EXIT_SUCCESS;
	}

	//dinstall

	/**
	 * 依存性のあるパッケージも含めたインストールを行う
	 * @param pkg インストールの主目的となるパッケージ
	 * @return インストールしたパッケージの数
	 */
	int dinstall(Package pkg)
	{
		String[] list = getDependList(pkg);
		int num = |list|;
		int ret = 0;
		while( num > 0 ) {
			setver = list[num - 1].split("=",0).pop();
			setnm = list[num - 1].split("=",0)[0];
			Package pac = mkPackage(setnm,__klipdata);
			num--;
			if ( pac.install() == EXIT_SUCCESS ) {
				fs.modCurData([pac.name,pac.version,pac.url],ADD);
				ret++;
			}
		}
		return ret;
	}
	
	/**
	 * パッケージが依存するパッケージ情報を文字列配列に出力する
	 * @param pkg 基準となるパッケージ
	 * @return 依存するパッケージ情報の文字列配列
	 */
	String[] getDependList(Package pkg)
	{
		String[] list = [pkg.name + "=" + pkg.version];
		resolveDepend(pkg,list);
		return list;
	}

	/**
	 * パッケージの依存するパッケージ情報のリストを、
	 * 子となるパッケージの依存性も含めて再帰的に取得する
	 * @param cur 現在の基準となるパッケージ
	 * @param list 情報を追加していくリスト
	 */
	void resolveDepend (Package cur,String[] list)
	{
		print("KLIP : resolve dependency...");
		foreach( String txt from cur.depend ) {
			if( !searchList(txt,list,0) ) continue;
			String setnm = txt.split("=",0)[0];
			String setver = txt.split("=",0).pop();
			Package pac = mkPackage(setnm,__klipdata);
			if( !checkPackage(pac) ) {
				print("!ERR : Operator.resolveDepend : setMember :" + pac.name);
				continue;
			}
			if ( setver > pac.version ) {
				OUT.println("!ERR : cannot find required version");
				OUT.println("!ERR : " + setnm + " NEED==" + setver + " < FOUND==" + pac.version);
				continue;
			}
			searchList(pac.name + "=" + pac.version,list,1);
			resolveDepend(pac,list);
		}
	}
	
	/**
	 * 依存パッケージのリストから、指定のパッケージが既に存在するかを検索する
	 * @param pack パッケージ名
	 * @param list リストとなる文字列配列
	 * @param mode 発見した場合に更新するか否か
	 * @return 検索の結果
	 */
	boolean searchList(String pack,String[] list,int mode)
	{
		foreach ( String txt from list ) {
			if( pack.split("=",0)[0] == txt.split("=",0)[0] ) {
				if ( pack.split("=",0).pop() <= txt.split("=",0).pop() ) 
					return false;
				else if ( mode == 1 ) {
					list[list.indexOf(txt)] = pack;
					return true;
				}
			}
		}
		if( mode == 1 ) list << pack;
		return true;
	}

	//undo

	/**
	 * アンドゥの実動作として、パッケージのインストール、または削除を行う
	 * @param base 基準を指定する文字列
	 * @return アンドゥの結果
	 */
	int undo(String base)
	{
		int ret;
		int mode;
		String[] list = fs.changeDiff(base);
		if ( |list| == 0 ) return EXIT_SUCCESS;
		foreach( String txt from list ) {
			String setnm = nameFilter(txt);
			if ( base == "prev") {
				Package pac = mkPackage(setnm,__prevdata);
				if ( !checkPackage(pac) ) continue;
				ret = pac.install();
				mode = ADD;
			} else if ( base == "cur" ) {
				Package pac = mkPackage(setnm,__curdata);
				if ( !checkPackage(pac) ) continue;
				ret = pac.remove();
				mode = DELETE;
			}
			if ( ret == EXIT_SUCCESS )
				fs.modCurData([pac.name,pac.version,pac.url],mode);
		}
		return ret;
	}

	/**
	 * アンドゥ用の情報文字列のフィルタリングを行う
	 * @param cell フィルタリングする文字列
	 * @return フィルタリング結果
	 */
	String nameFilter(String cell)
	{
		String bef = '"name":"';
		String aft = '"';
		String ret = cell.split(bef,0).pop();
		return ret.split(aft,0)[0];
	}

}
/*----------------------------------------------------------*/
print "[import]:klip.k";

class Klip {
	/** メイン関数からのコマンドライン引数の文字列配列 */	
	String[] args;
	/** 設定のチェックの際、検知した問題を格納する文字列配列 */	
	String[] ecode;

	/**
	 * Klipクラスのコンストラクタ
	 * @param args メイン関数からのコマンドライン引数
	 */
	Klip(String[] args)
	{
		this.args  = args;
	}

	/**
	 * 設定のチェックに成功していれば、オペレーションを実行する
	 * 問題があるならシステムメッセージを表示する
	 * @return オペレーションの結果
	 */
	int start()
	{
		if ( !__fail ) {
			Operator op = new Operator(args);
			op.init();
			if ( op.check() ) return op.start();
			OUT.println(__usage);
		} 
		info();
		return EXIT_ERROR;
	}
	
	/**
	 * usingするライブラリのフラグと、
	 * 端末内にライブラリの有無とを調査し、
	 * 問題がある場合はecode配列に指定文字列を格納する
	 */
	void check()
	{
		ecode = [];

		if ( !os.hasLib("libcurl") && !__use_curl ) ecode << "curl";
		
		if ( !os.hasLib("libz") && !__use_zlib) ecode << "zlib";

		if ( !os.hasLib("libtar") && !__use_libtar) ecode << "libtar";
		
		if ( __use_zlib && __use_libtar ) __use_zllt = true;
		else __use_zllt = false;
		
		if ( !__use_zllt && !__use_posix ) {
			ecode << "e_decomp";
			__fail = true;
		}

		if ( !__plat ) ecode << "e_plat";
	}

	/**
	 * ecodeを読み、対応するシステムメッセージを表示する
	 */
	void info()
	{
		String[] e_ret = [];
		String[] ret = [];
		if ( "e_user" in? ecode ) {
			e_ret << "!ERR : unknown_user_mode";
		}

		if ( "e_plat" in? ecode ) {
			e_ret << "!ERR : unknown_platform";
		}
		
		if ( "e_decomp" in? ecode ) {
			e_ret << '!ERR : package NOTFOUND : zlib+libtar / posix';
			e_ret << '     : "klip" uses either of these packages'
		}
		
		if ( "libtar" in? ecode )
			ret << "INFO : you should install libtar(-devel)";
		
		if ( "zlib" in? ecode )
			ret << "INFO : you should install zlib(-devel)";
		
		if ( "curl" in? ecode )
			ret << "INFO : you should install libcurl(-devel)";

		if ( |e_ret| != 0 ) {
			foreach( String txt from e_ret ) OUT.println(txt);
		} else if ( |ret| != 0 ) {
			foreach( String txt from ret ) OUT.println(txt);
		}
	}

}
/*----------------------------------------------------------*/

/**
 * スクリプトのメイン関数
 * @param args 実行する処理を指定した文字列配列
 * @return 全行程の結果
 */
int main (String[] args)
{
        Klip klip = new Klip(args);
        klip.check();
        return klip.start();
}
