///
/// define const data
///


/*-----system integer for main-----*/
EXIT_SUCCESS = 0;
EXIT_ERROR = 1;
CHECK = 0;
ADD = 1;
HIDE = 0;
SHOW = 1;


/*-----server's klip_data url(klip.xml or etc)-----*/
//DATAURL = "http://konoha.sourceforge.jp/klip/klip.xml";
DATAURL = "http://konoha.sourceforge.jp/klip/klip.json";


/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];


/*-----install directry-----*/
instDIR =  $env.HOME + "/.konoha/";


/*-----search list from server-----*/
//KLIPDATA = "./sys/klip.xml";
KLIPDATA = "./sys/klip.json";


/*-----already installed list & format to write -----*/
CURXML = "./sys/current.xml";
CURFORM = "<package><name>%s{0}</name><version>%s{1}</version><url>%s{2}</url></package>";


/*-----other files(for undo)-----*/
PREVXML = "./sys/previous.xml";
LATEST = "./sys/latest.txt";
TMPXML = "./sys/tmp.xml";		//use in replaceCURXML
BUFXML = "./sys/buffer.xml";	//use in main
