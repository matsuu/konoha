/* genffi.k */

using konohax.*;

void genFunc(Method method, OutputStream w) {
	String rtype = Method.getReturnType(0);
	String cname = (String)Method.getClass();
	String mn = Method.getName();
	if(t == "void") {
		METHOD String_sayHello(Ctx *ctx, knh_sfp_t *sfp)
		{
			INIT_RC;
			RVALUE = String_sayHello_(sfp[0], sfp[1] RC);
			CHECK_RC;
			KNH_RETURN(ctx, sfp, RVALUE);
		}		
	}
	else {
			
	}
	
	foreach(String t, String n in Method.params()) {
			
	}
}

void addMethodListener(genFunc);

void main(String[] args) {
	print |args|;
}

