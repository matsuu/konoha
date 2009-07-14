///
/// define const data
///
/*-----system integer for main-----*/
EXIT_SUCCESS = 0; EXIT_ERROR = -1; EXIT_NORMAL=2;

ADD = 3; REPLACE = 6; DELETE = 7; //touchList

/*-----already installed list & format to write -----*/
CURDATA = "./sys/current.json";
CURFORM = '{"name":"%s{0}","version":"%s{1}","url":"%s{2}"},';

/*-----other files(for undo)-----*/
PREVDATA = "./sys/previous.json";
LATEST = "./sys/latest.klip";

/*-----server's klip_data url(klip.xml or etc)-----*/
//KLIPURL = "http://konoha.sourceforge.jp/klip/%s{0}";
KLIPURL = "http://localhost/klip/%s{0}";

/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];

/*-----KLIPDATA-----*/
KLIPDATA = "./sys/klip.json";
klip_TYPE = KLIPDATA.split(".",0).pop(); 

/*-----KLIPINST-----*/
String klip_INST;
