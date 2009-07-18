///
/// define const data
///
/*-----system const integer-----*/
EXIT_SUCCESS = 1;
EXIT_NORMAL  = 0;
EXIT_ERROR   = -1;

ADD = 1;
REPLACE = 2;
DELETE = 3;

/*-----already installed list & format to write -----*/
CURDATA = "./sys/current.json";
CURFORM = '{"name":"%s{0}","version":"%s{1}","url":"%s{2}"},';

/*-----other files(for undo)-----*/
PREVDATA = "./sys/previous.json";
LATEST = "./sys/latest.log";

/*-----server's klip_data url(klip.xml or etc)-----*/
KLIPFILE = "klip.json";
//KLIPURL = "http://konoha.sourceforge.jp/klip/" + KLIPFILE;
KLIPURL = "http://localhost/klip/" +  KLIPFILE;

/*-----sourceforge's mirror server-----*/
sites = ["keihanna" ,"jaist" ,"globalbase", "osdn", "iij"];

/*-----KLIPDATA-----*/
KLIPDATA = "./sys/" + KLIPFILE;

/*-----system flag-----*/
boolean root;
boolean fail = false;
boolean use_curl = false;
boolean use_zlib = false;
boolean use_libtar = false;
boolean use_posix = false;
boolean use_zllt = false;

/*-----install path-----*/
String path;
