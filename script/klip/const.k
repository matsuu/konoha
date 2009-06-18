///
/// define const data
///
/*-----system integer for main-----*/
EXIT_SUCCESS = 0;
EXIT_ERROR = 1;
CHECK = 0;
ADD = 1;


/*-----server's klip.xml url(klip.xml)-----*/
XMLURL = "http://konoha.sourceforge.jp/klip/klip.xml";


/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];


/*-----install directry-----*/
INSTDIR = "/home/u.hira/.konoha/";  //***** REPLACE HERE


/*-----search list from server-----*/
KLIPXML = "./sys/klip.xml";


/*-----already installed list & format to write -----*/
CURXML = "./sys/current.xml";
CURFORM = "<package><name>%s{0}</name><version>%s{1}</version><url>%s{2}</url></package>"


/*-----other files(for undo)-----*/
PREVXML = "./sys/previous.xml";
LATEST = "./sys/latest.txt";
TMPXML = "./sys/tmp.xml";		//use in replaceCURXML
BUFXML = "./sys/buffer.xml";	//use in main
