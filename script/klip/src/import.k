//
//define import script for klip
//
//*-----import const & general function-----*/
import "const.k";
import "general.k";
klip_INST = pkgpath;
if ( use_curl ) {
	eval('import "./src/use/u_curl.k";');
} else {
	eval('import "./src/use/u_stream.k";');
}

//*-----import parser-----*/
import "form.k";
import "parser.k";
if ( klip_TYPE == "json" ) {
	eval('import "./src/pars/p_json.k";'); 
} else if ( klip_TYPE == "xml" ) {
	eval('import "./src/pars/p_xml.k";'); 
} else {
	sys_fail("import parser"); 
}

//*-----import operations-----*/
import "package.k";
if ( use_zl_lt ) {
	eval('import "./src/use/u_zl_lt.k";'); 
} else if ( use_posix ) {
	eval('import "./src/use/u_posix.k";');
} else {
	sys_fail("import getPackage");
}
import "extra.k";
import "main.k";
