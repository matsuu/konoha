//
//define controller of operations
//
class Operater {

	String opr;
	Package pkg;
	FileHandler fh;
	
	Operater(String[] args)
	{
		int ret;
		String name = "";
		if ( |args| >= 2 && |args| <= 3 ) {
			this.opr = args[1];
			if ( |args| == 3 ) {
				name = args[2];
			}
		}
		this.pkg = new Package(name,"","");
		this.fh = new FileHandler();
	}

	/*-----opr in? operations-----*/
	boolean checkOpr()
	{
		String[] ops = ["search","install","update","remove","undo","clean"];
		return ( opr in? ops );
	}

	/*-----do operation-----*/
	int exec()
	{
		int ret;
		boolean flag;
		if ( opr == "undo" ) {
			ret = undoMain(); 
		} else if ( opr == "clean" ) {
			ret = cleanMain(); 
		} else if ( opr == "remove" ) {
			ret = removeMain();
		} else {
			flag = searchKlip();
			if( opr == "install" ) {
				if ( flag ) {
					if ( |pkg.depend| > 1 ) {
						ret = dinstallMain();
					} else {
						ret = installMain();
					}
				}
			} else if ( opr == "update" ) {
				if ( flag ) ret = updateMain();
			} else if ( opr == "search" ) {
				ret = EXIT_SUCCESS;
			}
		}
		if ( ret == EXIT_ERROR ) {
			OUT.println("!ERR : " + opr + " faild");
		}
		return ret;
	}

	/*-----update KLIPDATA & search pkg from it-----*/
	boolean searchKlip()
	{
		fh.getklipdata();
		String ret;
		pkg.setMember(KLIPDATA);
		if ( |pkg.url| == 0 ) {
			OUT.println("KLIP : package is NOT FOUND...");
			return false;
		} else {
			OUT.println(%("KLIP : %s{0} ver=%s{1} is FOUND", pkg.name, pkg.version));
			return true;
		}
	}
	
	/*-----main of install-----*/
	int installMain()
	{
		int ret;
		fh.mkBufCurData();
		fh.updateLatest("install", pkg.name + "=" + pkg.version );
		ret = pkg.install();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],ADD);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of update-----*/
	int updateMain()
	{
		int ret;
		fh.mkBufCurData();
		fh.updateLatest("install", pkg.name + "=" + pkg.version);
		ret = pkg.update();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],REPLACE);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of remove-----*/
	int removeMain()
	{
		int ret;
		fh.mkBufCurData();
		ret = pkg.remove();
		if ( ret == EXIT_SUCCESS ) {
			fh.modCurData([pkg.name,pkg.version,pkg.url],DELETE);
			fh.cpBufCur2Prev();
		}
		fh.rmBufCurData();
		return ret;
	}
	
	/*-----main of clean-----*/
	int cleanMain()
	{
		fh.rmKlipData();
		fh.resetCurPrev();
		fh.updateLatest("install"," None");
		return EXIT_SUCCESS;
	}


	/*-------------------------------------------------
	  define methods of dinstall (not only 1 package)
	-------------------------------------------------*/

	/*-----main of install with depenency(dinstall)------*/
	int dinstallMain()
	{
		int ret;
		fh.mkBufCurData();
		ret = dinstall();
		if ( ret == 0 ) {
			print("!ERR : OperationController.dinstallMain : dinstall");
			fh.rmBufCurData();
			return EXIT_ERROR;
		}
		fh.cpBufCur2Prev();
		fh.rmBufCurData();
		OUT.println(%("KLIP : %d{0} packages are installed",ret));
		return EXIT_SUCCESS;
	}

	/*-----dinstall------*/
	int dinstall()
	{
		String[] list = [pkg.name + "=" + pkg.version];
		resolveDepend(pkg,list);
		int num = |list|;
		int ret = 0;
		while( num > 0 ) {
			Package pac = new Package(
									list[num - 1].split("=",0)[0],
									list[num - 1].split("=",0).pop(),
									"");
			pac.setMember(KLIPDATA);
			if ( |pac.url| == 0 ) {
				OUT.println(%("!ERR : %s{0} ver=%s{1} is NOT FOUND",
							  pac.name,
							  pac.version));
				num--;
				continue;
			}
			fh.updateLatest("install", pac.name + "=" + pac.version);
			if ( pac.install() == EXIT_ERROR ) {
				print("!ERR : OperationController.dinstall : install " + pac.name + "=" + pac.version);
				num--;
				continue;
			}
			fh.modCurData([pac.name,pac.version,pac.url],ADD);
			ret++;
			num--;
		}
		return ret;
	}

	/*-----resolve dependency & make list for dinstall-----*/
	void resolveDepend (Package cur,String[] list)
	{
		print("KLIP : resolve dependency...");
		foreach( String ce from cur.depend ) {
			if( !searchList(ce,list,0) ) continue;
			Package pac = new Package(ce.split("=",0)[0],
									  ce.split("=",0).pop(),
									  "");
			pac.setMember(KLIPDATA);
			if( |pac.url| == 0 ) {
				print("!ERR : OperationController.resolveDepend : setMember :" + pac.name);
				continue;
			}
			searchList(pac.name + "=" + pac.version,list,1);
			resolveDepend(pac,list);
		}
	}
	
	/*-----search install list-----*/
	boolean searchList(String pack,String[] list,int mode)
	{
		foreach ( String ce from list ) {
			if( pack.split("=",0)[0] == ce.split("=",0)[0] ) {
				if ( pack.split("=",0).pop() <= ce.split("=",0).pop() ) {
					return false;
				} else if ( mode == 1 ) {
					list[list.indexOf(ce)] = pack;
					return true;
				}
			}
		}
		if( mode == 1 ) {
			list << pack;
		}
		return true;
	}


	/*------------------------
	  define methods of undo
	------------------------*/

	/*-----undo main-----*/
	int undoMain()
	{
		boolean flag = true;
		fh.mkBufCurData();
		if ( undo("u_remove") == EXIT_ERROR ) { flag = false; }
		if ( undo("u_install") == EXIT_ERROR ) { flag = false; }
		fh.cpBufCur2Prev();
		fh.rmBufCurData();
		if ( !flag ) {
			OUT.println("!ERR : some was failed in undo...");
			return EXIT_NORMAL;
		}
		return EXIT_SUCCESS;
	}

	/*-----undo(install/remove)-----*/
	int undo(String u_opr)
	{
		int ret;
		String[] list = fh.changeDiff(u_opr);
		if ( |list| == 0 ) {
			return EXIT_SUCCESS;
		}
		foreach( String ce from list ) {
			Package pac = new Package( 
									   filter(ce,"name"),
									   filter(ce,"version"),
									   filter(ce,"url"));
			if( u_opr == "u_install") {
				ret = pac.install();
				fh.modCurData([pac.name,pac.version,pac.url],ADD);
			} else if ( u_opr == "u_remove" ) {
				ret = pac.remove();
				fh.modCurData([pac.name,pac.version,pac.url],DELETE);
			}
		}
		return ret;
	}

	/*-----filter for undo-----*/
	String filter(String cell,String member)
	{
		String bef = %('"%s{0}":"',member);
		String aft = '"';
		String ret = cell.split(bef,0).pop();
		return ret.split(aft,0)[0];
	}

}