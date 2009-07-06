///
/// define const data
///
/*-----system integer for main-----*/
ROOT = 0;
USER = 1;

EXIT_SUCCESS = 0;
EXIT_ERROR = 1;

HIDE = 0;
SHOW = 1;
CHECK = 2;
ADD = 3;
COPY = 4;
RENAME = 5;
REPLACE = 6;
DELETE = 7;

/*-----server's klip_data url(klip.xml or etc)-----*/
KLIPURL = "http://konoha.sourceforge.jp/klip/%s{0}";

/*-----install directry-----*/
int usermode = USER;
instDIR =  $konoha.path.user.package;
//if ( !os.mkdir(instDir) ) {
//	usermode = USER;
//	instDir = $konoha.path.user.package; 
//} else { usermode = ROOT; }


/*-----search list from server-----*/
KLIPDATA = "./sys/klip.json";

/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];

/*-----already installed list & format to write -----*/
CURDATA = "./sys/current.json";
CURFORM = '{"name":"%s{0}","version":"%s{1}","url":"%s{2}"},';

/*-----other files(for undo)-----*/
PREVDATA = "./sys/previous.json";
LATEST = "./sys/latest.klip";
TMPDATA = "./sys/tmp.json";		//use in replaceCURXML
BUFDATA = "./sys/buffer.json";	//use in main
EMPTY = "./sys/empty.json";