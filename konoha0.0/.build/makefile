#Makefiile by gen_konoha.py

CC = gcc
CFLAGS_MONO = -O2 -g -Wall
CFLAGS_DEBUG = -O0 -g3 -Wall -fmessage-length=0
CFLAGS_LIB = -O2 -g -Wall

program = konoha
library = libkonoha

.PHONY: all
all: $(program)



objs_M = \
	knh_Int_api0M.o\
	knh_String_api2M.o\
	knh_Class_api2M.o\
	knh_Array_api1M.o\
	knh_Bytes_api1M.o\
	knh_Bytes_api2M.o\
	knh_Int_api1M.o\
	knh_HashMap_api1M.o\
	knh_Float_api2M.o\
	knh_System_api1M.o\
	knh_any_api0M.o\
	knh_Context_api1M.o\
	knh_DictSet_api1M.o\
	knh_Object_api0M.o\
	knh_OutputStream_api0M.o\
	knh_Exception_api1M.o\
	knh_HashSet_api1M.o\
	knh_String_api1M.o\
	knh_HashMap_api2M.o\
	knh_DictSet_api2M.o\
	knh_Object_api2M.o\
	knh_HashSet_api2M.o\
	knh_Bool_api1M.o\
	knh_Object_api1M.o\
	knh_Class_api1M.o\
	knh_Float_api1M.o\
	knh_Context_api0M.o\
	knh_DictMap_api1M.o\
	knh_Exception_api0M.o\
	knh_Connection_api1M.o\
	knh_DictMap_api2M.o\
	knh_MethodFieldM.o\
	knh_TupleM.o\
	knh_DictIdxM.o\
	knh_InputStreamM.o\
	knh_ArrayM.o\
	knh_SocketM.o\
	knh_String_charsetM.o\
	knh_IntM.o\
	knh_RegexM.o\
	knh_ClassStructM.o\
	knh_FloatM.o\
	knh_BoolM.o\
	knh_DictMapM.o\
	knh_HashMapM.o\
	knh_AffineConvM.o\
	knh_MapMapM.o\
	knh_PrototypeM.o\
	knh_Socket_utilsM.o\
	knh_NueM.o\
	knh_IteratorM.o\
	knh_HashSetM.o\
	knh_OutputStreamM.o\
	konoha_printM.o\
	konoha_tnameM.o\
	konoha_throwcatchM.o\
	konoha_extM.o\
	konoha_initM.o\
	konoha_callM.o\
	konoha_tconstM.o\
	konoha_tstructM.o\
	konoha_shellM.o\
	konoha_hobjectM.o\
	konoha_tmemoryM.o\
	konoha_typesystemM.o\
	konoha_texptM.o\
	konoha_metadataM.o\
	konoha_tglobalM.o\
	konoha_apiM.o\
	konoha_tclassM.o\
	konoha_tmethodM.o\
	konoha_tmapmapM.o\
	konoha_loaderM.o\
	knh_VocabularyM.o\
	knh_ContextM.o\
	knh_NameSpaceM.o\
	knh_MethodM.o\
	knh_Class_type_tM.o\
	knh_IntUnitM.o\
	knh_ResultSetM.o\
	knh_Context_bufferM.o\
	knh_BytesM.o\
	knh_BytesConvM.o\
	knh_WriterM.o\
	knh_ExceptionM.o\
	knh_NumberM.o\
	knh_SystemM.o\
	knh_ObjectM.o\
	knh_ConnectionM.o\
	knh_Mutex__pthreadM.o\
	knh_FloatUnitM.o\
	knh_DictSetM.o\
	knh_RuntimeM.o\
	knh_ClassM.o\
	knh_Class_spec_tM.o\
	knh_Connection__ubiqlM.o\
	knh_ClosureM.o\
	knh_Bytes_byte_tM.o\
	knh_dlopen__posixM.o\
	knh_socket__posixM.o\
	knh_socket__btronM.o\
	knh_socket__win32M.o\
	file__windowsM.o\
	file__linuxM.o\
	file__macosxM.o\
	file__tkM.o\
	knh_Int64M.o\
	knh_StringM.o\
	knh_ClassRelM.o\
	knh_ExceptionHandlerM.o\
	konohac_visitor_M.o\
	math_M.o\
	konohac_M.o\
	konoha_M.o\
	naruto_M.o\
	konoha_tuple_M.o\
	konohac_asm_M.o\
	driver_mysql_M.o\
	konoha_vm_M.o\
	konoha_load_M.o\
	konohac_parser_M.o\
	konoha_spec_M.o\
	mt19937arM.o\
	knh_Counter_api1M.o\
	knh_AmazonM.o\
	knh_CounterM.o\
	knh_Cmpl_arithmeticM.o\
	knh_Stmt_valueM.o\
	knh_Cmpl_classM.o\
	knh_StmtM.o\
	knh_Token_parserM.o\
	knh_Stmt_exprM.o\
	knh_VirtualMachineCodeM.o\
	knh_Stmt_usingM.o\
	stmtvisit_declvM.o\
	knh_Stmt_foreachM.o\
	knh_String_parserM.o\
	knh_CmplM.o\
	stmtvisit_asmM.o\
	knh_Stmt_methodM.o\
	knh_Cmpl_labelM.o\
	knh_Cmpl_variableM.o\
	stmtvisit_declmM.o\
	knh_Cmpl_methodM.o\
	stmtvisit_declcM.o\
	knh_TokenM.o\
	knh_Cmpl_runM.o\
	knh_Token_genericsM.o\
	knh_Cmpl_annotationM.o\
	knh_Cmpl_sevalM.o\
	knh_Stmt_metaM.o\
	knh_Stmt_trycatchM.o\
	knh_Cmpl_eprintM.o\
	knh_Cmpl_asmM.o\
	knh_Cmpl_asmvM.o\
	math_MathM.o\
	knh_Connection__mysqlM.o

objs_D = \
	knh_Int_api0D.o\
	knh_String_api2D.o\
	knh_Class_api2D.o\
	knh_Array_api1D.o\
	knh_Bytes_api1D.o\
	knh_Bytes_api2D.o\
	knh_Int_api1D.o\
	knh_HashMap_api1D.o\
	knh_Float_api2D.o\
	knh_System_api1D.o\
	knh_any_api0D.o\
	knh_Context_api1D.o\
	knh_DictSet_api1D.o\
	knh_Object_api0D.o\
	knh_OutputStream_api0D.o\
	knh_Exception_api1D.o\
	knh_HashSet_api1D.o\
	knh_String_api1D.o\
	knh_HashMap_api2D.o\
	knh_DictSet_api2D.o\
	knh_Object_api2D.o\
	knh_HashSet_api2D.o\
	knh_Bool_api1D.o\
	knh_Object_api1D.o\
	knh_Class_api1D.o\
	knh_Float_api1D.o\
	knh_Context_api0D.o\
	knh_DictMap_api1D.o\
	knh_Exception_api0D.o\
	knh_Connection_api1D.o\
	knh_DictMap_api2D.o\
	knh_MethodFieldD.o\
	knh_TupleD.o\
	knh_DictIdxD.o\
	knh_InputStreamD.o\
	knh_ArrayD.o\
	knh_SocketD.o\
	knh_String_charsetD.o\
	knh_IntD.o\
	knh_RegexD.o\
	knh_ClassStructD.o\
	knh_FloatD.o\
	knh_BoolD.o\
	knh_DictMapD.o\
	knh_HashMapD.o\
	knh_AffineConvD.o\
	knh_MapMapD.o\
	knh_PrototypeD.o\
	knh_Socket_utilsD.o\
	knh_NueD.o\
	knh_IteratorD.o\
	knh_HashSetD.o\
	knh_OutputStreamD.o\
	konoha_printD.o\
	konoha_tnameD.o\
	konoha_throwcatchD.o\
	konoha_extD.o\
	konoha_initD.o\
	konoha_callD.o\
	konoha_tconstD.o\
	konoha_tstructD.o\
	konoha_shellD.o\
	konoha_hobjectD.o\
	konoha_tmemoryD.o\
	konoha_typesystemD.o\
	konoha_texptD.o\
	konoha_metadataD.o\
	konoha_tglobalD.o\
	konoha_apiD.o\
	konoha_tclassD.o\
	konoha_tmethodD.o\
	konoha_tmapmapD.o\
	konoha_loaderD.o\
	knh_VocabularyD.o\
	knh_ContextD.o\
	knh_NameSpaceD.o\
	knh_MethodD.o\
	knh_Class_type_tD.o\
	knh_IntUnitD.o\
	knh_ResultSetD.o\
	knh_Context_bufferD.o\
	knh_BytesD.o\
	knh_BytesConvD.o\
	knh_WriterD.o\
	knh_ExceptionD.o\
	knh_NumberD.o\
	knh_SystemD.o\
	knh_ObjectD.o\
	knh_ConnectionD.o\
	knh_Mutex__pthreadD.o\
	knh_FloatUnitD.o\
	knh_DictSetD.o\
	knh_RuntimeD.o\
	knh_ClassD.o\
	knh_Class_spec_tD.o\
	knh_Connection__ubiqlD.o\
	knh_ClosureD.o\
	knh_Bytes_byte_tD.o\
	knh_dlopen__posixD.o\
	knh_socket__posixD.o\
	knh_socket__btronD.o\
	knh_socket__win32D.o\
	file__windowsD.o\
	file__linuxD.o\
	file__macosxD.o\
	file__tkD.o\
	knh_Int64D.o\
	knh_StringD.o\
	knh_ClassRelD.o\
	knh_ExceptionHandlerD.o\
	konohac_visitor_D.o\
	math_D.o\
	konohac_D.o\
	konoha_D.o\
	naruto_D.o\
	konoha_tuple_D.o\
	konohac_asm_D.o\
	driver_mysql_D.o\
	konoha_vm_D.o\
	konoha_load_D.o\
	konohac_parser_D.o\
	konoha_spec_D.o\
	mt19937arD.o\
	knh_Counter_api1D.o\
	knh_AmazonD.o\
	knh_CounterD.o\
	knh_Cmpl_arithmeticD.o\
	knh_Stmt_valueD.o\
	knh_Cmpl_classD.o\
	knh_StmtD.o\
	knh_Token_parserD.o\
	knh_Stmt_exprD.o\
	knh_VirtualMachineCodeD.o\
	knh_Stmt_usingD.o\
	stmtvisit_declvD.o\
	knh_Stmt_foreachD.o\
	knh_String_parserD.o\
	knh_CmplD.o\
	stmtvisit_asmD.o\
	knh_Stmt_methodD.o\
	knh_Cmpl_labelD.o\
	knh_Cmpl_variableD.o\
	stmtvisit_declmD.o\
	knh_Cmpl_methodD.o\
	stmtvisit_declcD.o\
	knh_TokenD.o\
	knh_Cmpl_runD.o\
	knh_Token_genericsD.o\
	knh_Cmpl_annotationD.o\
	knh_Cmpl_sevalD.o\
	knh_Stmt_metaD.o\
	knh_Stmt_trycatchD.o\
	knh_Cmpl_eprintD.o\
	knh_Cmpl_asmD.o\
	knh_Cmpl_asmvD.o\
	math_MathD.o\
	knh_Connection__mysqlD.o

LDLIBS_M = \
	-lm

objs_L = \
	knh_Int_api0L.o\
	knh_String_api2L.o\
	knh_Class_api2L.o\
	knh_Array_api1L.o\
	knh_Bytes_api1L.o\
	knh_Bytes_api2L.o\
	knh_Int_api1L.o\
	knh_HashMap_api1L.o\
	knh_Float_api2L.o\
	knh_System_api1L.o\
	knh_any_api0L.o\
	knh_Context_api1L.o\
	knh_DictSet_api1L.o\
	knh_Object_api0L.o\
	knh_OutputStream_api0L.o\
	knh_Exception_api1L.o\
	knh_HashSet_api1L.o\
	knh_String_api1L.o\
	knh_HashMap_api2L.o\
	knh_DictSet_api2L.o\
	knh_Object_api2L.o\
	knh_HashSet_api2L.o\
	knh_Bool_api1L.o\
	knh_Object_api1L.o\
	knh_Class_api1L.o\
	knh_Float_api1L.o\
	knh_Context_api0L.o\
	knh_DictMap_api1L.o\
	knh_Exception_api0L.o\
	knh_Connection_api1L.o\
	knh_DictMap_api2L.o\
	knh_MethodFieldL.o\
	knh_TupleL.o\
	knh_DictIdxL.o\
	knh_InputStreamL.o\
	knh_ArrayL.o\
	knh_SocketL.o\
	knh_String_charsetL.o\
	knh_IntL.o\
	knh_RegexL.o\
	knh_ClassStructL.o\
	knh_FloatL.o\
	knh_BoolL.o\
	knh_DictMapL.o\
	knh_HashMapL.o\
	knh_AffineConvL.o\
	knh_MapMapL.o\
	knh_PrototypeL.o\
	knh_Socket_utilsL.o\
	knh_NueL.o\
	knh_IteratorL.o\
	knh_HashSetL.o\
	knh_OutputStreamL.o\
	konoha_printL.o\
	konoha_tnameL.o\
	konoha_throwcatchL.o\
	konoha_extL.o\
	konoha_initL.o\
	konoha_callL.o\
	konoha_tconstL.o\
	konoha_tstructL.o\
	konoha_shellL.o\
	konoha_hobjectL.o\
	konoha_tmemoryL.o\
	konoha_typesystemL.o\
	konoha_texptL.o\
	konoha_metadataL.o\
	konoha_tglobalL.o\
	konoha_apiL.o\
	konoha_tclassL.o\
	konoha_tmethodL.o\
	konoha_tmapmapL.o\
	konoha_loaderL.o\
	knh_VocabularyL.o\
	knh_ContextL.o\
	knh_NameSpaceL.o\
	knh_MethodL.o\
	knh_Class_type_tL.o\
	knh_IntUnitL.o\
	knh_ResultSetL.o\
	knh_Context_bufferL.o\
	knh_BytesL.o\
	knh_BytesConvL.o\
	knh_WriterL.o\
	knh_ExceptionL.o\
	knh_NumberL.o\
	knh_SystemL.o\
	knh_ObjectL.o\
	knh_ConnectionL.o\
	knh_Mutex__pthreadL.o\
	knh_FloatUnitL.o\
	knh_DictSetL.o\
	knh_RuntimeL.o\
	knh_ClassL.o\
	knh_Class_spec_tL.o\
	knh_Connection__ubiqlL.o\
	knh_ClosureL.o\
	knh_Bytes_byte_tL.o\
	knh_dlopen__posixL.o\
	knh_socket__posixL.o\
	knh_socket__btronL.o\
	knh_socket__win32L.o\
	file__windowsL.o\
	file__linuxL.o\
	file__macosxL.o\
	file__tkL.o\
	knh_Int64L.o\
	knh_StringL.o\
	knh_ClassRelL.o\
	knh_ExceptionHandlerL.o\
	konohac_visitor_L.o\
	math_L.o\
	konohac_L.o\
	konoha_L.o\
	naruto_L.o\
	konoha_tuple_L.o\
	konohac_asm_L.o\
	driver_mysql_L.o\
	konoha_vm_L.o\
	konoha_load_L.o\
	konohac_parser_L.o\
	konoha_spec_L.o\
	mt19937arL.o\
	knh_Counter_api1L.o\
	knh_AmazonL.o\
	knh_CounterL.o\
	knh_Cmpl_arithmeticL.o\
	knh_Stmt_valueL.o\
	knh_Cmpl_classL.o\
	knh_StmtL.o\
	knh_Token_parserL.o\
	knh_Stmt_exprL.o\
	knh_VirtualMachineCodeL.o\
	knh_Stmt_usingL.o\
	stmtvisit_declvL.o\
	knh_Stmt_foreachL.o\
	knh_String_parserL.o\
	knh_CmplL.o\
	stmtvisit_asmL.o\
	knh_Stmt_methodL.o\
	knh_Cmpl_labelL.o\
	knh_Cmpl_variableL.o\
	stmtvisit_declmL.o\
	knh_Cmpl_methodL.o\
	stmtvisit_declcL.o\
	knh_TokenL.o\
	knh_Cmpl_runL.o\
	knh_Token_genericsL.o\
	knh_Cmpl_annotationL.o\
	knh_Cmpl_sevalL.o\
	knh_Stmt_metaL.o\
	knh_Stmt_trycatchL.o\
	knh_Cmpl_eprintL.o\
	knh_Cmpl_asmL.o\
	knh_Cmpl_asmvL.o

LDLIBS_L = 

packages_dylib = \
	libkonoha.dylib\
	pkg_math.dylib\
	drv_mysql.dylib

packages_so = \
	libkonoha.so\
	pkg_math.so\
	drv_mysql.so

packages_dll = \
	libkonoha.dll\
	pkg_math.dll\
	drv_mysql.dll

objs_konohaL = \
	knh_Int_api0L.o\
	knh_String_api2L.o\
	knh_Class_api2L.o\
	knh_Array_api1L.o\
	knh_Bytes_api1L.o\
	knh_Bytes_api2L.o\
	knh_Int_api1L.o\
	knh_HashMap_api1L.o\
	knh_Float_api2L.o\
	knh_System_api1L.o\
	knh_any_api0L.o\
	knh_Context_api1L.o\
	knh_DictSet_api1L.o\
	knh_Object_api0L.o\
	knh_OutputStream_api0L.o\
	knh_Exception_api1L.o\
	knh_HashSet_api1L.o\
	knh_String_api1L.o\
	knh_HashMap_api2L.o\
	knh_DictSet_api2L.o\
	knh_Object_api2L.o\
	knh_HashSet_api2L.o\
	knh_Bool_api1L.o\
	knh_Object_api1L.o\
	knh_Class_api1L.o\
	knh_Float_api1L.o\
	knh_Context_api0L.o\
	knh_DictMap_api1L.o\
	knh_Exception_api0L.o\
	knh_Connection_api1L.o\
	knh_DictMap_api2L.o\
	knh_MethodFieldL.o\
	knh_TupleL.o\
	knh_DictIdxL.o\
	knh_InputStreamL.o\
	knh_ArrayL.o\
	knh_SocketL.o\
	knh_String_charsetL.o\
	knh_IntL.o\
	knh_RegexL.o\
	knh_ClassStructL.o\
	knh_FloatL.o\
	knh_BoolL.o\
	knh_DictMapL.o\
	knh_HashMapL.o\
	knh_AffineConvL.o\
	knh_MapMapL.o\
	knh_PrototypeL.o\
	knh_Socket_utilsL.o\
	knh_NueL.o\
	knh_IteratorL.o\
	knh_HashSetL.o\
	knh_OutputStreamL.o\
	konoha_printL.o\
	konoha_tnameL.o\
	konoha_throwcatchL.o\
	konoha_extL.o\
	konoha_initL.o\
	konoha_callL.o\
	konoha_tconstL.o\
	konoha_tstructL.o\
	konoha_shellL.o\
	konoha_hobjectL.o\
	konoha_tmemoryL.o\
	konoha_typesystemL.o\
	konoha_texptL.o\
	konoha_metadataL.o\
	konoha_tglobalL.o\
	konoha_apiL.o\
	konoha_tclassL.o\
	konoha_tmethodL.o\
	konoha_tmapmapL.o\
	konoha_loaderL.o\
	knh_VocabularyL.o\
	knh_ContextL.o\
	knh_NameSpaceL.o\
	knh_MethodL.o\
	knh_Class_type_tL.o\
	knh_IntUnitL.o\
	knh_ResultSetL.o\
	knh_Context_bufferL.o\
	knh_BytesL.o\
	knh_BytesConvL.o\
	knh_WriterL.o\
	knh_ExceptionL.o\
	knh_NumberL.o\
	knh_SystemL.o\
	knh_ObjectL.o\
	knh_ConnectionL.o\
	knh_Mutex__pthreadL.o\
	knh_FloatUnitL.o\
	knh_DictSetL.o\
	knh_RuntimeL.o\
	knh_ClassL.o\
	knh_Class_spec_tL.o\
	knh_Connection__ubiqlL.o\
	knh_ClosureL.o\
	knh_Bytes_byte_tL.o\
	knh_dlopen__posixL.o\
	knh_socket__posixL.o\
	knh_socket__btronL.o\
	knh_socket__win32L.o\
	file__windowsL.o\
	file__linuxL.o\
	file__macosxL.o\
	file__tkL.o\
	knh_Int64L.o\
	knh_StringL.o\
	knh_ClassRelL.o\
	knh_ExceptionHandlerL.o\
	konohac_visitor_L.o\
	math_L.o\
	konohac_L.o\
	konoha_L.o\
	naruto_L.o\
	konoha_tuple_L.o\
	konohac_asm_L.o\
	driver_mysql_L.o\
	konoha_vm_L.o\
	konoha_load_L.o\
	konohac_parser_L.o\
	konoha_spec_L.o\
	mt19937arL.o
LDLIBS_konohaL = 

knh_Int_api0M.o : ../api/konoha/knh_Int_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Int_api0.c" -oknh_Int_api0M.o

knh_Int_api0D.o : ../api/konoha/knh_Int_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Int_api0.c" -oknh_Int_api0D.o

knh_Int_api0L.o : ../api/konoha/knh_Int_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Int_api0.c" -oknh_Int_api0L.o


knh_String_api2M.o : ../api/konoha/knh_String_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_String_api2.c" -oknh_String_api2M.o

knh_String_api2D.o : ../api/konoha/knh_String_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_String_api2.c" -oknh_String_api2D.o

knh_String_api2L.o : ../api/konoha/knh_String_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_String_api2.c" -oknh_String_api2L.o


knh_Class_api2M.o : ../api/konoha/knh_Class_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Class_api2.c" -oknh_Class_api2M.o

knh_Class_api2D.o : ../api/konoha/knh_Class_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Class_api2.c" -oknh_Class_api2D.o

knh_Class_api2L.o : ../api/konoha/knh_Class_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Class_api2.c" -oknh_Class_api2L.o


knh_Array_api1M.o : ../api/konoha/knh_Array_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Array_api1.c" -oknh_Array_api1M.o

knh_Array_api1D.o : ../api/konoha/knh_Array_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Array_api1.c" -oknh_Array_api1D.o

knh_Array_api1L.o : ../api/konoha/knh_Array_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Array_api1.c" -oknh_Array_api1L.o


knh_Bytes_api1M.o : ../api/konoha/knh_Bytes_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Bytes_api1.c" -oknh_Bytes_api1M.o

knh_Bytes_api1D.o : ../api/konoha/knh_Bytes_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Bytes_api1.c" -oknh_Bytes_api1D.o

knh_Bytes_api1L.o : ../api/konoha/knh_Bytes_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Bytes_api1.c" -oknh_Bytes_api1L.o


knh_Bytes_api2M.o : ../api/konoha/knh_Bytes_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Bytes_api2.c" -oknh_Bytes_api2M.o

knh_Bytes_api2D.o : ../api/konoha/knh_Bytes_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Bytes_api2.c" -oknh_Bytes_api2D.o

knh_Bytes_api2L.o : ../api/konoha/knh_Bytes_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Bytes_api2.c" -oknh_Bytes_api2L.o


knh_Int_api1M.o : ../api/konoha/knh_Int_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Int_api1.c" -oknh_Int_api1M.o

knh_Int_api1D.o : ../api/konoha/knh_Int_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Int_api1.c" -oknh_Int_api1D.o

knh_Int_api1L.o : ../api/konoha/knh_Int_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Int_api1.c" -oknh_Int_api1L.o


knh_HashMap_api1M.o : ../api/konoha/knh_HashMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_HashMap_api1.c" -oknh_HashMap_api1M.o

knh_HashMap_api1D.o : ../api/konoha/knh_HashMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_HashMap_api1.c" -oknh_HashMap_api1D.o

knh_HashMap_api1L.o : ../api/konoha/knh_HashMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_HashMap_api1.c" -oknh_HashMap_api1L.o


knh_Float_api2M.o : ../api/konoha/knh_Float_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Float_api2.c" -oknh_Float_api2M.o

knh_Float_api2D.o : ../api/konoha/knh_Float_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Float_api2.c" -oknh_Float_api2D.o

knh_Float_api2L.o : ../api/konoha/knh_Float_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Float_api2.c" -oknh_Float_api2L.o


knh_System_api1M.o : ../api/konoha/knh_System_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_System_api1.c" -oknh_System_api1M.o

knh_System_api1D.o : ../api/konoha/knh_System_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_System_api1.c" -oknh_System_api1D.o

knh_System_api1L.o : ../api/konoha/knh_System_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_System_api1.c" -oknh_System_api1L.o


knh_any_api0M.o : ../api/konoha/knh_any_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_any_api0.c" -oknh_any_api0M.o

knh_any_api0D.o : ../api/konoha/knh_any_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_any_api0.c" -oknh_any_api0D.o

knh_any_api0L.o : ../api/konoha/knh_any_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_any_api0.c" -oknh_any_api0L.o


knh_Context_api1M.o : ../api/konoha/knh_Context_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Context_api1.c" -oknh_Context_api1M.o

knh_Context_api1D.o : ../api/konoha/knh_Context_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Context_api1.c" -oknh_Context_api1D.o

knh_Context_api1L.o : ../api/konoha/knh_Context_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Context_api1.c" -oknh_Context_api1L.o


knh_DictSet_api1M.o : ../api/konoha/knh_DictSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_DictSet_api1.c" -oknh_DictSet_api1M.o

knh_DictSet_api1D.o : ../api/konoha/knh_DictSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_DictSet_api1.c" -oknh_DictSet_api1D.o

knh_DictSet_api1L.o : ../api/konoha/knh_DictSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_DictSet_api1.c" -oknh_DictSet_api1L.o


knh_Object_api0M.o : ../api/konoha/knh_Object_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Object_api0.c" -oknh_Object_api0M.o

knh_Object_api0D.o : ../api/konoha/knh_Object_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Object_api0.c" -oknh_Object_api0D.o

knh_Object_api0L.o : ../api/konoha/knh_Object_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Object_api0.c" -oknh_Object_api0L.o


knh_OutputStream_api0M.o : ../api/konoha/knh_OutputStream_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_OutputStream_api0.c" -oknh_OutputStream_api0M.o

knh_OutputStream_api0D.o : ../api/konoha/knh_OutputStream_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_OutputStream_api0.c" -oknh_OutputStream_api0D.o

knh_OutputStream_api0L.o : ../api/konoha/knh_OutputStream_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_OutputStream_api0.c" -oknh_OutputStream_api0L.o


knh_Exception_api1M.o : ../api/konoha/knh_Exception_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Exception_api1.c" -oknh_Exception_api1M.o

knh_Exception_api1D.o : ../api/konoha/knh_Exception_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Exception_api1.c" -oknh_Exception_api1D.o

knh_Exception_api1L.o : ../api/konoha/knh_Exception_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Exception_api1.c" -oknh_Exception_api1L.o


knh_HashSet_api1M.o : ../api/konoha/knh_HashSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_HashSet_api1.c" -oknh_HashSet_api1M.o

knh_HashSet_api1D.o : ../api/konoha/knh_HashSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_HashSet_api1.c" -oknh_HashSet_api1D.o

knh_HashSet_api1L.o : ../api/konoha/knh_HashSet_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_HashSet_api1.c" -oknh_HashSet_api1L.o


knh_String_api1M.o : ../api/konoha/knh_String_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_String_api1.c" -oknh_String_api1M.o

knh_String_api1D.o : ../api/konoha/knh_String_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_String_api1.c" -oknh_String_api1D.o

knh_String_api1L.o : ../api/konoha/knh_String_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_String_api1.c" -oknh_String_api1L.o


knh_HashMap_api2M.o : ../api/konoha/knh_HashMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_HashMap_api2.c" -oknh_HashMap_api2M.o

knh_HashMap_api2D.o : ../api/konoha/knh_HashMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_HashMap_api2.c" -oknh_HashMap_api2D.o

knh_HashMap_api2L.o : ../api/konoha/knh_HashMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_HashMap_api2.c" -oknh_HashMap_api2L.o


knh_DictSet_api2M.o : ../api/konoha/knh_DictSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_DictSet_api2.c" -oknh_DictSet_api2M.o

knh_DictSet_api2D.o : ../api/konoha/knh_DictSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_DictSet_api2.c" -oknh_DictSet_api2D.o

knh_DictSet_api2L.o : ../api/konoha/knh_DictSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_DictSet_api2.c" -oknh_DictSet_api2L.o


knh_Object_api2M.o : ../api/konoha/knh_Object_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Object_api2.c" -oknh_Object_api2M.o

knh_Object_api2D.o : ../api/konoha/knh_Object_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Object_api2.c" -oknh_Object_api2D.o

knh_Object_api2L.o : ../api/konoha/knh_Object_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Object_api2.c" -oknh_Object_api2L.o


knh_HashSet_api2M.o : ../api/konoha/knh_HashSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_HashSet_api2.c" -oknh_HashSet_api2M.o

knh_HashSet_api2D.o : ../api/konoha/knh_HashSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_HashSet_api2.c" -oknh_HashSet_api2D.o

knh_HashSet_api2L.o : ../api/konoha/knh_HashSet_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_HashSet_api2.c" -oknh_HashSet_api2L.o


knh_Bool_api1M.o : ../api/konoha/knh_Bool_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Bool_api1.c" -oknh_Bool_api1M.o

knh_Bool_api1D.o : ../api/konoha/knh_Bool_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Bool_api1.c" -oknh_Bool_api1D.o

knh_Bool_api1L.o : ../api/konoha/knh_Bool_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Bool_api1.c" -oknh_Bool_api1L.o


knh_Object_api1M.o : ../api/konoha/knh_Object_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Object_api1.c" -oknh_Object_api1M.o

knh_Object_api1D.o : ../api/konoha/knh_Object_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Object_api1.c" -oknh_Object_api1D.o

knh_Object_api1L.o : ../api/konoha/knh_Object_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Object_api1.c" -oknh_Object_api1L.o


knh_Class_api1M.o : ../api/konoha/knh_Class_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Class_api1.c" -oknh_Class_api1M.o

knh_Class_api1D.o : ../api/konoha/knh_Class_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Class_api1.c" -oknh_Class_api1D.o

knh_Class_api1L.o : ../api/konoha/knh_Class_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Class_api1.c" -oknh_Class_api1L.o


knh_Float_api1M.o : ../api/konoha/knh_Float_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Float_api1.c" -oknh_Float_api1M.o

knh_Float_api1D.o : ../api/konoha/knh_Float_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Float_api1.c" -oknh_Float_api1D.o

knh_Float_api1L.o : ../api/konoha/knh_Float_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Float_api1.c" -oknh_Float_api1L.o


knh_Context_api0M.o : ../api/konoha/knh_Context_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Context_api0.c" -oknh_Context_api0M.o

knh_Context_api0D.o : ../api/konoha/knh_Context_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Context_api0.c" -oknh_Context_api0D.o

knh_Context_api0L.o : ../api/konoha/knh_Context_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Context_api0.c" -oknh_Context_api0L.o


knh_DictMap_api1M.o : ../api/konoha/knh_DictMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_DictMap_api1.c" -oknh_DictMap_api1M.o

knh_DictMap_api1D.o : ../api/konoha/knh_DictMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_DictMap_api1.c" -oknh_DictMap_api1D.o

knh_DictMap_api1L.o : ../api/konoha/knh_DictMap_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_DictMap_api1.c" -oknh_DictMap_api1L.o


knh_Exception_api0M.o : ../api/konoha/knh_Exception_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Exception_api0.c" -oknh_Exception_api0M.o

knh_Exception_api0D.o : ../api/konoha/knh_Exception_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Exception_api0.c" -oknh_Exception_api0D.o

knh_Exception_api0L.o : ../api/konoha/knh_Exception_api0.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Exception_api0.c" -oknh_Exception_api0L.o


knh_Connection_api1M.o : ../api/konoha/knh_Connection_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_Connection_api1.c" -oknh_Connection_api1M.o

knh_Connection_api1D.o : ../api/konoha/knh_Connection_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_Connection_api1.c" -oknh_Connection_api1D.o

knh_Connection_api1L.o : ../api/konoha/knh_Connection_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_Connection_api1.c" -oknh_Connection_api1L.o


knh_DictMap_api2M.o : ../api/konoha/knh_DictMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/konoha/knh_DictMap_api2.c" -oknh_DictMap_api2M.o

knh_DictMap_api2D.o : ../api/konoha/knh_DictMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/konoha/knh_DictMap_api2.c" -oknh_DictMap_api2D.o

knh_DictMap_api2L.o : ../api/konoha/knh_DictMap_api2.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/konoha/knh_DictMap_api2.c" -oknh_DictMap_api2L.o


knh_MethodFieldM.o : ../class/konoha/knh_MethodField.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_MethodField.c" -oknh_MethodFieldM.o

knh_MethodFieldD.o : ../class/konoha/knh_MethodField.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_MethodField.c" -oknh_MethodFieldD.o

knh_MethodFieldL.o : ../class/konoha/knh_MethodField.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_MethodField.c" -oknh_MethodFieldL.o


knh_TupleM.o : ../class/konoha/knh_Tuple.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Tuple.c" -oknh_TupleM.o

knh_TupleD.o : ../class/konoha/knh_Tuple.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Tuple.c" -oknh_TupleD.o

knh_TupleL.o : ../class/konoha/knh_Tuple.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Tuple.c" -oknh_TupleL.o


knh_DictIdxM.o : ../class/konoha/knh_DictIdx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_DictIdx.c" -oknh_DictIdxM.o

knh_DictIdxD.o : ../class/konoha/knh_DictIdx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_DictIdx.c" -oknh_DictIdxD.o

knh_DictIdxL.o : ../class/konoha/knh_DictIdx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_DictIdx.c" -oknh_DictIdxL.o


knh_InputStreamM.o : ../class/konoha/knh_InputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_InputStream.c" -oknh_InputStreamM.o

knh_InputStreamD.o : ../class/konoha/knh_InputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_InputStream.c" -oknh_InputStreamD.o

knh_InputStreamL.o : ../class/konoha/knh_InputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_InputStream.c" -oknh_InputStreamL.o


knh_ArrayM.o : ../class/konoha/knh_Array.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Array.c" -oknh_ArrayM.o

knh_ArrayD.o : ../class/konoha/knh_Array.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Array.c" -oknh_ArrayD.o

knh_ArrayL.o : ../class/konoha/knh_Array.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Array.c" -oknh_ArrayL.o


knh_SocketM.o : ../class/konoha/knh_Socket.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Socket.c" -oknh_SocketM.o

knh_SocketD.o : ../class/konoha/knh_Socket.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Socket.c" -oknh_SocketD.o

knh_SocketL.o : ../class/konoha/knh_Socket.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Socket.c" -oknh_SocketL.o


knh_String_charsetM.o : ../class/konoha/knh_String_charset.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_String_charset.c" -oknh_String_charsetM.o

knh_String_charsetD.o : ../class/konoha/knh_String_charset.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_String_charset.c" -oknh_String_charsetD.o

knh_String_charsetL.o : ../class/konoha/knh_String_charset.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_String_charset.c" -oknh_String_charsetL.o


knh_IntM.o : ../class/konoha/knh_Int.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Int.c" -oknh_IntM.o

knh_IntD.o : ../class/konoha/knh_Int.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Int.c" -oknh_IntD.o

knh_IntL.o : ../class/konoha/knh_Int.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Int.c" -oknh_IntL.o


knh_RegexM.o : ../class/konoha/knh_Regex.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Regex.c" -oknh_RegexM.o

knh_RegexD.o : ../class/konoha/knh_Regex.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Regex.c" -oknh_RegexD.o

knh_RegexL.o : ../class/konoha/knh_Regex.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Regex.c" -oknh_RegexL.o


knh_ClassStructM.o : ../class/konoha/knh_ClassStruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_ClassStruct.c" -oknh_ClassStructM.o

knh_ClassStructD.o : ../class/konoha/knh_ClassStruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_ClassStruct.c" -oknh_ClassStructD.o

knh_ClassStructL.o : ../class/konoha/knh_ClassStruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_ClassStruct.c" -oknh_ClassStructL.o


knh_FloatM.o : ../class/konoha/knh_Float.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Float.c" -oknh_FloatM.o

knh_FloatD.o : ../class/konoha/knh_Float.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Float.c" -oknh_FloatD.o

knh_FloatL.o : ../class/konoha/knh_Float.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Float.c" -oknh_FloatL.o


knh_BoolM.o : ../class/konoha/knh_Bool.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Bool.c" -oknh_BoolM.o

knh_BoolD.o : ../class/konoha/knh_Bool.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Bool.c" -oknh_BoolD.o

knh_BoolL.o : ../class/konoha/knh_Bool.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Bool.c" -oknh_BoolL.o


knh_DictMapM.o : ../class/konoha/knh_DictMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_DictMap.c" -oknh_DictMapM.o

knh_DictMapD.o : ../class/konoha/knh_DictMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_DictMap.c" -oknh_DictMapD.o

knh_DictMapL.o : ../class/konoha/knh_DictMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_DictMap.c" -oknh_DictMapL.o


knh_HashMapM.o : ../class/konoha/knh_HashMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_HashMap.c" -oknh_HashMapM.o

knh_HashMapD.o : ../class/konoha/knh_HashMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_HashMap.c" -oknh_HashMapD.o

knh_HashMapL.o : ../class/konoha/knh_HashMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_HashMap.c" -oknh_HashMapL.o


knh_AffineConvM.o : ../class/konoha/knh_AffineConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_AffineConv.c" -oknh_AffineConvM.o

knh_AffineConvD.o : ../class/konoha/knh_AffineConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_AffineConv.c" -oknh_AffineConvD.o

knh_AffineConvL.o : ../class/konoha/knh_AffineConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_AffineConv.c" -oknh_AffineConvL.o


knh_MapMapM.o : ../class/konoha/knh_MapMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_MapMap.c" -oknh_MapMapM.o

knh_MapMapD.o : ../class/konoha/knh_MapMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_MapMap.c" -oknh_MapMapD.o

knh_MapMapL.o : ../class/konoha/knh_MapMap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_MapMap.c" -oknh_MapMapL.o


knh_PrototypeM.o : ../class/konoha/knh_Prototype.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Prototype.c" -oknh_PrototypeM.o

knh_PrototypeD.o : ../class/konoha/knh_Prototype.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Prototype.c" -oknh_PrototypeD.o

knh_PrototypeL.o : ../class/konoha/knh_Prototype.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Prototype.c" -oknh_PrototypeL.o


knh_Socket_utilsM.o : ../class/konoha/knh_Socket_utils.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Socket_utils.c" -oknh_Socket_utilsM.o

knh_Socket_utilsD.o : ../class/konoha/knh_Socket_utils.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Socket_utils.c" -oknh_Socket_utilsD.o

knh_Socket_utilsL.o : ../class/konoha/knh_Socket_utils.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Socket_utils.c" -oknh_Socket_utilsL.o


knh_NueM.o : ../class/konoha/knh_Nue.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Nue.c" -oknh_NueM.o

knh_NueD.o : ../class/konoha/knh_Nue.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Nue.c" -oknh_NueD.o

knh_NueL.o : ../class/konoha/knh_Nue.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Nue.c" -oknh_NueL.o


knh_IteratorM.o : ../class/konoha/knh_Iterator.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Iterator.c" -oknh_IteratorM.o

knh_IteratorD.o : ../class/konoha/knh_Iterator.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Iterator.c" -oknh_IteratorD.o

knh_IteratorL.o : ../class/konoha/knh_Iterator.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Iterator.c" -oknh_IteratorL.o


knh_HashSetM.o : ../class/konoha/knh_HashSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_HashSet.c" -oknh_HashSetM.o

knh_HashSetD.o : ../class/konoha/knh_HashSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_HashSet.c" -oknh_HashSetD.o

knh_HashSetL.o : ../class/konoha/knh_HashSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_HashSet.c" -oknh_HashSetL.o


knh_OutputStreamM.o : ../class/konoha/knh_OutputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_OutputStream.c" -oknh_OutputStreamM.o

knh_OutputStreamD.o : ../class/konoha/knh_OutputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_OutputStream.c" -oknh_OutputStreamD.o

knh_OutputStreamL.o : ../class/konoha/knh_OutputStream.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_OutputStream.c" -oknh_OutputStreamL.o


konoha_printM.o : ../class/konoha/vm/konoha_print.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_print.c" -okonoha_printM.o

konoha_printD.o : ../class/konoha/vm/konoha_print.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_print.c" -okonoha_printD.o

konoha_printL.o : ../class/konoha/vm/konoha_print.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_print.c" -okonoha_printL.o


konoha_tnameM.o : ../class/konoha/vm/konoha_tname.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tname.c" -okonoha_tnameM.o

konoha_tnameD.o : ../class/konoha/vm/konoha_tname.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tname.c" -okonoha_tnameD.o

konoha_tnameL.o : ../class/konoha/vm/konoha_tname.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tname.c" -okonoha_tnameL.o


konoha_throwcatchM.o : ../class/konoha/vm/konoha_throwcatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_throwcatch.c" -okonoha_throwcatchM.o

konoha_throwcatchD.o : ../class/konoha/vm/konoha_throwcatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_throwcatch.c" -okonoha_throwcatchD.o

konoha_throwcatchL.o : ../class/konoha/vm/konoha_throwcatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_throwcatch.c" -okonoha_throwcatchL.o


konoha_extM.o : ../class/konoha/vm/konoha_ext.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_ext.c" -okonoha_extM.o

konoha_extD.o : ../class/konoha/vm/konoha_ext.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_ext.c" -okonoha_extD.o

konoha_extL.o : ../class/konoha/vm/konoha_ext.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_ext.c" -okonoha_extL.o


konoha_initM.o : ../class/konoha/vm/konoha_init.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_init.c" -okonoha_initM.o

konoha_initD.o : ../class/konoha/vm/konoha_init.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_init.c" -okonoha_initD.o

konoha_initL.o : ../class/konoha/vm/konoha_init.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_init.c" -okonoha_initL.o


konoha_callM.o : ../class/konoha/vm/konoha_call.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_call.c" -okonoha_callM.o

konoha_callD.o : ../class/konoha/vm/konoha_call.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_call.c" -okonoha_callD.o

konoha_callL.o : ../class/konoha/vm/konoha_call.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_call.c" -okonoha_callL.o


konoha_tconstM.o : ../class/konoha/vm/konoha_tconst.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tconst.c" -okonoha_tconstM.o

konoha_tconstD.o : ../class/konoha/vm/konoha_tconst.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tconst.c" -okonoha_tconstD.o

konoha_tconstL.o : ../class/konoha/vm/konoha_tconst.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tconst.c" -okonoha_tconstL.o


konoha_tstructM.o : ../class/konoha/vm/konoha_tstruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tstruct.c" -okonoha_tstructM.o

konoha_tstructD.o : ../class/konoha/vm/konoha_tstruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tstruct.c" -okonoha_tstructD.o

konoha_tstructL.o : ../class/konoha/vm/konoha_tstruct.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tstruct.c" -okonoha_tstructL.o


konoha_shellM.o : ../class/konoha/vm/konoha_shell.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_shell.c" -okonoha_shellM.o

konoha_shellD.o : ../class/konoha/vm/konoha_shell.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_shell.c" -okonoha_shellD.o

konoha_shellL.o : ../class/konoha/vm/konoha_shell.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_shell.c" -okonoha_shellL.o


konoha_hobjectM.o : ../class/konoha/vm/konoha_hobject.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_hobject.c" -okonoha_hobjectM.o

konoha_hobjectD.o : ../class/konoha/vm/konoha_hobject.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_hobject.c" -okonoha_hobjectD.o

konoha_hobjectL.o : ../class/konoha/vm/konoha_hobject.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_hobject.c" -okonoha_hobjectL.o


konoha_tmemoryM.o : ../class/konoha/vm/konoha_tmemory.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tmemory.c" -okonoha_tmemoryM.o

konoha_tmemoryD.o : ../class/konoha/vm/konoha_tmemory.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tmemory.c" -okonoha_tmemoryD.o

konoha_tmemoryL.o : ../class/konoha/vm/konoha_tmemory.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tmemory.c" -okonoha_tmemoryL.o


konoha_typesystemM.o : ../class/konoha/vm/konoha_typesystem.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_typesystem.c" -okonoha_typesystemM.o

konoha_typesystemD.o : ../class/konoha/vm/konoha_typesystem.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_typesystem.c" -okonoha_typesystemD.o

konoha_typesystemL.o : ../class/konoha/vm/konoha_typesystem.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_typesystem.c" -okonoha_typesystemL.o


konoha_texptM.o : ../class/konoha/vm/konoha_texpt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_texpt.c" -okonoha_texptM.o

konoha_texptD.o : ../class/konoha/vm/konoha_texpt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_texpt.c" -okonoha_texptD.o

konoha_texptL.o : ../class/konoha/vm/konoha_texpt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_texpt.c" -okonoha_texptL.o


konoha_metadataM.o : ../class/konoha/vm/konoha_metadata.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_metadata.c" -okonoha_metadataM.o

konoha_metadataD.o : ../class/konoha/vm/konoha_metadata.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_metadata.c" -okonoha_metadataD.o

konoha_metadataL.o : ../class/konoha/vm/konoha_metadata.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_metadata.c" -okonoha_metadataL.o


konoha_tglobalM.o : ../class/konoha/vm/konoha_tglobal.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tglobal.c" -okonoha_tglobalM.o

konoha_tglobalD.o : ../class/konoha/vm/konoha_tglobal.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tglobal.c" -okonoha_tglobalD.o

konoha_tglobalL.o : ../class/konoha/vm/konoha_tglobal.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tglobal.c" -okonoha_tglobalL.o


konoha_apiM.o : ../class/konoha/vm/konoha_api.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_api.c" -okonoha_apiM.o

konoha_apiD.o : ../class/konoha/vm/konoha_api.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_api.c" -okonoha_apiD.o

konoha_apiL.o : ../class/konoha/vm/konoha_api.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_api.c" -okonoha_apiL.o


konoha_tclassM.o : ../class/konoha/vm/konoha_tclass.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tclass.c" -okonoha_tclassM.o

konoha_tclassD.o : ../class/konoha/vm/konoha_tclass.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tclass.c" -okonoha_tclassD.o

konoha_tclassL.o : ../class/konoha/vm/konoha_tclass.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tclass.c" -okonoha_tclassL.o


konoha_tmethodM.o : ../class/konoha/vm/konoha_tmethod.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tmethod.c" -okonoha_tmethodM.o

konoha_tmethodD.o : ../class/konoha/vm/konoha_tmethod.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tmethod.c" -okonoha_tmethodD.o

konoha_tmethodL.o : ../class/konoha/vm/konoha_tmethod.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tmethod.c" -okonoha_tmethodL.o


konoha_tmapmapM.o : ../class/konoha/vm/konoha_tmapmap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_tmapmap.c" -okonoha_tmapmapM.o

konoha_tmapmapD.o : ../class/konoha/vm/konoha_tmapmap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_tmapmap.c" -okonoha_tmapmapD.o

konoha_tmapmapL.o : ../class/konoha/vm/konoha_tmapmap.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_tmapmap.c" -okonoha_tmapmapL.o


konoha_loaderM.o : ../class/konoha/vm/konoha_loader.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/vm/konoha_loader.c" -okonoha_loaderM.o

konoha_loaderD.o : ../class/konoha/vm/konoha_loader.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/vm/konoha_loader.c" -okonoha_loaderD.o

konoha_loaderL.o : ../class/konoha/vm/konoha_loader.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/vm/konoha_loader.c" -okonoha_loaderL.o


knh_VocabularyM.o : ../class/konoha/knh_Vocabulary.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Vocabulary.c" -oknh_VocabularyM.o

knh_VocabularyD.o : ../class/konoha/knh_Vocabulary.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Vocabulary.c" -oknh_VocabularyD.o

knh_VocabularyL.o : ../class/konoha/knh_Vocabulary.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Vocabulary.c" -oknh_VocabularyL.o


knh_ContextM.o : ../class/konoha/knh_Context.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Context.c" -oknh_ContextM.o

knh_ContextD.o : ../class/konoha/knh_Context.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Context.c" -oknh_ContextD.o

knh_ContextL.o : ../class/konoha/knh_Context.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Context.c" -oknh_ContextL.o


knh_NameSpaceM.o : ../class/konoha/knh_NameSpace.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_NameSpace.c" -oknh_NameSpaceM.o

knh_NameSpaceD.o : ../class/konoha/knh_NameSpace.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_NameSpace.c" -oknh_NameSpaceD.o

knh_NameSpaceL.o : ../class/konoha/knh_NameSpace.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_NameSpace.c" -oknh_NameSpaceL.o


knh_MethodM.o : ../class/konoha/knh_Method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Method.c" -oknh_MethodM.o

knh_MethodD.o : ../class/konoha/knh_Method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Method.c" -oknh_MethodD.o

knh_MethodL.o : ../class/konoha/knh_Method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Method.c" -oknh_MethodL.o


knh_Class_type_tM.o : ../class/konoha/knh_Class_type_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Class_type_t.c" -oknh_Class_type_tM.o

knh_Class_type_tD.o : ../class/konoha/knh_Class_type_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Class_type_t.c" -oknh_Class_type_tD.o

knh_Class_type_tL.o : ../class/konoha/knh_Class_type_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Class_type_t.c" -oknh_Class_type_tL.o


knh_IntUnitM.o : ../class/konoha/knh_IntUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_IntUnit.c" -oknh_IntUnitM.o

knh_IntUnitD.o : ../class/konoha/knh_IntUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_IntUnit.c" -oknh_IntUnitD.o

knh_IntUnitL.o : ../class/konoha/knh_IntUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_IntUnit.c" -oknh_IntUnitL.o


knh_ResultSetM.o : ../class/konoha/knh_ResultSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_ResultSet.c" -oknh_ResultSetM.o

knh_ResultSetD.o : ../class/konoha/knh_ResultSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_ResultSet.c" -oknh_ResultSetD.o

knh_ResultSetL.o : ../class/konoha/knh_ResultSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_ResultSet.c" -oknh_ResultSetL.o


knh_Context_bufferM.o : ../class/konoha/knh_Context_buffer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Context_buffer.c" -oknh_Context_bufferM.o

knh_Context_bufferD.o : ../class/konoha/knh_Context_buffer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Context_buffer.c" -oknh_Context_bufferD.o

knh_Context_bufferL.o : ../class/konoha/knh_Context_buffer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Context_buffer.c" -oknh_Context_bufferL.o


knh_BytesM.o : ../class/konoha/knh_Bytes.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Bytes.c" -oknh_BytesM.o

knh_BytesD.o : ../class/konoha/knh_Bytes.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Bytes.c" -oknh_BytesD.o

knh_BytesL.o : ../class/konoha/knh_Bytes.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Bytes.c" -oknh_BytesL.o


knh_BytesConvM.o : ../class/konoha/knh_BytesConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_BytesConv.c" -oknh_BytesConvM.o

knh_BytesConvD.o : ../class/konoha/knh_BytesConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_BytesConv.c" -oknh_BytesConvD.o

knh_BytesConvL.o : ../class/konoha/knh_BytesConv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_BytesConv.c" -oknh_BytesConvL.o


knh_WriterM.o : ../class/konoha/knh_Writer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Writer.c" -oknh_WriterM.o

knh_WriterD.o : ../class/konoha/knh_Writer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Writer.c" -oknh_WriterD.o

knh_WriterL.o : ../class/konoha/knh_Writer.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Writer.c" -oknh_WriterL.o


knh_ExceptionM.o : ../class/konoha/knh_Exception.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Exception.c" -oknh_ExceptionM.o

knh_ExceptionD.o : ../class/konoha/knh_Exception.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Exception.c" -oknh_ExceptionD.o

knh_ExceptionL.o : ../class/konoha/knh_Exception.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Exception.c" -oknh_ExceptionL.o


knh_NumberM.o : ../class/konoha/knh_Number.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Number.c" -oknh_NumberM.o

knh_NumberD.o : ../class/konoha/knh_Number.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Number.c" -oknh_NumberD.o

knh_NumberL.o : ../class/konoha/knh_Number.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Number.c" -oknh_NumberL.o


knh_SystemM.o : ../class/konoha/knh_System.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_System.c" -oknh_SystemM.o

knh_SystemD.o : ../class/konoha/knh_System.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_System.c" -oknh_SystemD.o

knh_SystemL.o : ../class/konoha/knh_System.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_System.c" -oknh_SystemL.o


knh_ObjectM.o : ../class/konoha/knh_Object.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Object.c" -oknh_ObjectM.o

knh_ObjectD.o : ../class/konoha/knh_Object.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Object.c" -oknh_ObjectD.o

knh_ObjectL.o : ../class/konoha/knh_Object.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Object.c" -oknh_ObjectL.o


knh_ConnectionM.o : ../class/konoha/knh_Connection.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Connection.c" -oknh_ConnectionM.o

knh_ConnectionD.o : ../class/konoha/knh_Connection.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Connection.c" -oknh_ConnectionD.o

knh_ConnectionL.o : ../class/konoha/knh_Connection.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Connection.c" -oknh_ConnectionL.o


knh_Mutex__pthreadM.o : ../class/konoha/knh_Mutex__pthread.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Mutex__pthread.c" -oknh_Mutex__pthreadM.o

knh_Mutex__pthreadD.o : ../class/konoha/knh_Mutex__pthread.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Mutex__pthread.c" -oknh_Mutex__pthreadD.o

knh_Mutex__pthreadL.o : ../class/konoha/knh_Mutex__pthread.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Mutex__pthread.c" -oknh_Mutex__pthreadL.o


knh_FloatUnitM.o : ../class/konoha/knh_FloatUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_FloatUnit.c" -oknh_FloatUnitM.o

knh_FloatUnitD.o : ../class/konoha/knh_FloatUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_FloatUnit.c" -oknh_FloatUnitD.o

knh_FloatUnitL.o : ../class/konoha/knh_FloatUnit.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_FloatUnit.c" -oknh_FloatUnitL.o


knh_DictSetM.o : ../class/konoha/knh_DictSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_DictSet.c" -oknh_DictSetM.o

knh_DictSetD.o : ../class/konoha/knh_DictSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_DictSet.c" -oknh_DictSetD.o

knh_DictSetL.o : ../class/konoha/knh_DictSet.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_DictSet.c" -oknh_DictSetL.o


knh_RuntimeM.o : ../class/konoha/knh_Runtime.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Runtime.c" -oknh_RuntimeM.o

knh_RuntimeD.o : ../class/konoha/knh_Runtime.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Runtime.c" -oknh_RuntimeD.o

knh_RuntimeL.o : ../class/konoha/knh_Runtime.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Runtime.c" -oknh_RuntimeL.o


knh_ClassM.o : ../class/konoha/knh_Class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Class.c" -oknh_ClassM.o

knh_ClassD.o : ../class/konoha/knh_Class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Class.c" -oknh_ClassD.o

knh_ClassL.o : ../class/konoha/knh_Class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Class.c" -oknh_ClassL.o


knh_Class_spec_tM.o : ../class/konoha/knh_Class_spec_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Class_spec_t.c" -oknh_Class_spec_tM.o

knh_Class_spec_tD.o : ../class/konoha/knh_Class_spec_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Class_spec_t.c" -oknh_Class_spec_tD.o

knh_Class_spec_tL.o : ../class/konoha/knh_Class_spec_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Class_spec_t.c" -oknh_Class_spec_tL.o


knh_Connection__ubiqlM.o : ../class/konoha/knh_Connection__ubiql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Connection__ubiql.c" -oknh_Connection__ubiqlM.o

knh_Connection__ubiqlD.o : ../class/konoha/knh_Connection__ubiql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Connection__ubiql.c" -oknh_Connection__ubiqlD.o

knh_Connection__ubiqlL.o : ../class/konoha/knh_Connection__ubiql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Connection__ubiql.c" -oknh_Connection__ubiqlL.o


knh_ClosureM.o : ../class/konoha/knh_Closure.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Closure.c" -oknh_ClosureM.o

knh_ClosureD.o : ../class/konoha/knh_Closure.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Closure.c" -oknh_ClosureD.o

knh_ClosureL.o : ../class/konoha/knh_Closure.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Closure.c" -oknh_ClosureL.o


knh_Bytes_byte_tM.o : ../class/konoha/knh_Bytes_byte_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Bytes_byte_t.c" -oknh_Bytes_byte_tM.o

knh_Bytes_byte_tD.o : ../class/konoha/knh_Bytes_byte_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Bytes_byte_t.c" -oknh_Bytes_byte_tD.o

knh_Bytes_byte_tL.o : ../class/konoha/knh_Bytes_byte_t.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Bytes_byte_t.c" -oknh_Bytes_byte_tL.o


knh_dlopen__posixM.o : ../class/konoha/deps/api/posix/knh_dlopen__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/api/posix/knh_dlopen__posix.c" -oknh_dlopen__posixM.o

knh_dlopen__posixD.o : ../class/konoha/deps/api/posix/knh_dlopen__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/api/posix/knh_dlopen__posix.c" -oknh_dlopen__posixD.o

knh_dlopen__posixL.o : ../class/konoha/deps/api/posix/knh_dlopen__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/api/posix/knh_dlopen__posix.c" -oknh_dlopen__posixL.o


knh_socket__posixM.o : ../class/konoha/deps/api/posix/knh_socket__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/api/posix/knh_socket__posix.c" -oknh_socket__posixM.o

knh_socket__posixD.o : ../class/konoha/deps/api/posix/knh_socket__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/api/posix/knh_socket__posix.c" -oknh_socket__posixD.o

knh_socket__posixL.o : ../class/konoha/deps/api/posix/knh_socket__posix.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/api/posix/knh_socket__posix.c" -oknh_socket__posixL.o


knh_socket__btronM.o : ../class/konoha/deps/api/btron/knh_socket__btron.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/api/btron/knh_socket__btron.c" -oknh_socket__btronM.o

knh_socket__btronD.o : ../class/konoha/deps/api/btron/knh_socket__btron.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/api/btron/knh_socket__btron.c" -oknh_socket__btronD.o

knh_socket__btronL.o : ../class/konoha/deps/api/btron/knh_socket__btron.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/api/btron/knh_socket__btron.c" -oknh_socket__btronL.o


knh_socket__win32M.o : ../class/konoha/deps/api/win32/knh_socket__win32.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/api/win32/knh_socket__win32.c" -oknh_socket__win32M.o

knh_socket__win32D.o : ../class/konoha/deps/api/win32/knh_socket__win32.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/api/win32/knh_socket__win32.c" -oknh_socket__win32D.o

knh_socket__win32L.o : ../class/konoha/deps/api/win32/knh_socket__win32.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/api/win32/knh_socket__win32.c" -oknh_socket__win32L.o


file__windowsM.o : ../class/konoha/deps/os/windows/file__windows.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/os/windows/file__windows.c" -ofile__windowsM.o

file__windowsD.o : ../class/konoha/deps/os/windows/file__windows.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/os/windows/file__windows.c" -ofile__windowsD.o

file__windowsL.o : ../class/konoha/deps/os/windows/file__windows.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/os/windows/file__windows.c" -ofile__windowsL.o


file__linuxM.o : ../class/konoha/deps/os/linux/file__linux.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/os/linux/file__linux.c" -ofile__linuxM.o

file__linuxD.o : ../class/konoha/deps/os/linux/file__linux.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/os/linux/file__linux.c" -ofile__linuxD.o

file__linuxL.o : ../class/konoha/deps/os/linux/file__linux.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/os/linux/file__linux.c" -ofile__linuxL.o


file__macosxM.o : ../class/konoha/deps/os/macosx/file__macosx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/os/macosx/file__macosx.c" -ofile__macosxM.o

file__macosxD.o : ../class/konoha/deps/os/macosx/file__macosx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/os/macosx/file__macosx.c" -ofile__macosxD.o

file__macosxL.o : ../class/konoha/deps/os/macosx/file__macosx.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/os/macosx/file__macosx.c" -ofile__macosxL.o


file__tkM.o : ../class/konoha/deps/os/tk/file__tk.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/deps/os/tk/file__tk.c" -ofile__tkM.o

file__tkD.o : ../class/konoha/deps/os/tk/file__tk.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/deps/os/tk/file__tk.c" -ofile__tkD.o

file__tkL.o : ../class/konoha/deps/os/tk/file__tk.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/deps/os/tk/file__tk.c" -ofile__tkL.o


knh_Int64M.o : ../class/konoha/knh_Int64.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_Int64.c" -oknh_Int64M.o

knh_Int64D.o : ../class/konoha/knh_Int64.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_Int64.c" -oknh_Int64D.o

knh_Int64L.o : ../class/konoha/knh_Int64.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_Int64.c" -oknh_Int64L.o


knh_StringM.o : ../class/konoha/knh_String.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_String.c" -oknh_StringM.o

knh_StringD.o : ../class/konoha/knh_String.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_String.c" -oknh_StringD.o

knh_StringL.o : ../class/konoha/knh_String.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_String.c" -oknh_StringL.o


knh_ClassRelM.o : ../class/konoha/knh_ClassRel.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_ClassRel.c" -oknh_ClassRelM.o

knh_ClassRelD.o : ../class/konoha/knh_ClassRel.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_ClassRel.c" -oknh_ClassRelD.o

knh_ClassRelL.o : ../class/konoha/knh_ClassRel.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_ClassRel.c" -oknh_ClassRelL.o


knh_ExceptionHandlerM.o : ../class/konoha/knh_ExceptionHandler.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konoha/knh_ExceptionHandler.c" -oknh_ExceptionHandlerM.o

knh_ExceptionHandlerD.o : ../class/konoha/knh_ExceptionHandler.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konoha/knh_ExceptionHandler.c" -oknh_ExceptionHandlerD.o

knh_ExceptionHandlerL.o : ../class/konoha/knh_ExceptionHandler.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konoha/knh_ExceptionHandler.c" -oknh_ExceptionHandlerL.o


konohac_visitor_M.o : ../gen/konohac_visitor_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konohac_visitor_.c" -okonohac_visitor_M.o

konohac_visitor_D.o : ../gen/konohac_visitor_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konohac_visitor_.c" -okonohac_visitor_D.o

konohac_visitor_L.o : ../gen/konohac_visitor_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konohac_visitor_.c" -okonohac_visitor_L.o


math_M.o : ../gen/package/math_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/package/math_.c" -omath_M.o

math_D.o : ../gen/package/math_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/package/math_.c" -omath_D.o

math_L.o : ../gen/package/math_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/package/math_.c" -omath_L.o


konohac_M.o : ../gen/package/konohac_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/package/konohac_.c" -okonohac_M.o

konohac_D.o : ../gen/package/konohac_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/package/konohac_.c" -okonohac_D.o

konohac_L.o : ../gen/package/konohac_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/package/konohac_.c" -okonohac_L.o


konoha_M.o : ../gen/package/konoha_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/package/konoha_.c" -okonoha_M.o

konoha_D.o : ../gen/package/konoha_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/package/konoha_.c" -okonoha_D.o

konoha_L.o : ../gen/package/konoha_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/package/konoha_.c" -okonoha_L.o


naruto_M.o : ../gen/package/naruto_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/package/naruto_.c" -onaruto_M.o

naruto_D.o : ../gen/package/naruto_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/package/naruto_.c" -onaruto_D.o

naruto_L.o : ../gen/package/naruto_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/package/naruto_.c" -onaruto_L.o


konoha_tuple_M.o : ../gen/konoha_tuple_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konoha_tuple_.c" -okonoha_tuple_M.o

konoha_tuple_D.o : ../gen/konoha_tuple_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konoha_tuple_.c" -okonoha_tuple_D.o

konoha_tuple_L.o : ../gen/konoha_tuple_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konoha_tuple_.c" -okonoha_tuple_L.o


konohac_asm_M.o : ../gen/konohac_asm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konohac_asm_.c" -okonohac_asm_M.o

konohac_asm_D.o : ../gen/konohac_asm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konohac_asm_.c" -okonohac_asm_D.o

konohac_asm_L.o : ../gen/konohac_asm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konohac_asm_.c" -okonohac_asm_L.o


driver_mysql_M.o : ../gen/driver/driver_mysql_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/driver/driver_mysql_.c" -odriver_mysql_M.o

driver_mysql_D.o : ../gen/driver/driver_mysql_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/driver/driver_mysql_.c" -odriver_mysql_D.o

driver_mysql_L.o : ../gen/driver/driver_mysql_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/driver/driver_mysql_.c" -odriver_mysql_L.o


konoha_vm_M.o : ../gen/konoha_vm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konoha_vm_.c" -okonoha_vm_M.o

konoha_vm_D.o : ../gen/konoha_vm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konoha_vm_.c" -okonoha_vm_D.o

konoha_vm_L.o : ../gen/konoha_vm_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konoha_vm_.c" -okonoha_vm_L.o


konoha_load_M.o : ../gen/konoha_load_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konoha_load_.c" -okonoha_load_M.o

konoha_load_D.o : ../gen/konoha_load_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konoha_load_.c" -okonoha_load_D.o

konoha_load_L.o : ../gen/konoha_load_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konoha_load_.c" -okonoha_load_L.o


konohac_parser_M.o : ../gen/konohac_parser_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konohac_parser_.c" -okonohac_parser_M.o

konohac_parser_D.o : ../gen/konohac_parser_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konohac_parser_.c" -okonohac_parser_D.o

konohac_parser_L.o : ../gen/konohac_parser_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konohac_parser_.c" -okonohac_parser_L.o


konoha_spec_M.o : ../gen/konoha_spec_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../gen/konoha_spec_.c" -okonoha_spec_M.o

konoha_spec_D.o : ../gen/konoha_spec_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../gen/konoha_spec_.c" -okonoha_spec_D.o

konoha_spec_L.o : ../gen/konoha_spec_.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../gen/konoha_spec_.c" -okonoha_spec_L.o


mt19937arM.o : ../ext/mt19937ar.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../ext/mt19937ar.c" -omt19937arM.o

mt19937arD.o : ../ext/mt19937ar.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../ext/mt19937ar.c" -omt19937arD.o

mt19937arL.o : ../ext/mt19937ar.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../ext/mt19937ar.c" -omt19937arL.o


objs_narutoL = \
	knh_Counter_api1L.o\
	knh_AmazonL.o\
	knh_CounterL.o
LDLIBS_narutoL = 

knh_Counter_api1M.o : ../api/naruto/knh_Counter_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../api/naruto/knh_Counter_api1.c" -oknh_Counter_api1M.o

knh_Counter_api1D.o : ../api/naruto/knh_Counter_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../api/naruto/knh_Counter_api1.c" -oknh_Counter_api1D.o

knh_Counter_api1L.o : ../api/naruto/knh_Counter_api1.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../api/naruto/knh_Counter_api1.c" -oknh_Counter_api1L.o


knh_AmazonM.o : ../class/naruto/knh_Amazon.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/naruto/knh_Amazon.c" -oknh_AmazonM.o

knh_AmazonD.o : ../class/naruto/knh_Amazon.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/naruto/knh_Amazon.c" -oknh_AmazonD.o

knh_AmazonL.o : ../class/naruto/knh_Amazon.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/naruto/knh_Amazon.c" -oknh_AmazonL.o


knh_CounterM.o : ../class/naruto/knh_Counter.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/naruto/knh_Counter.c" -oknh_CounterM.o

knh_CounterD.o : ../class/naruto/knh_Counter.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/naruto/knh_Counter.c" -oknh_CounterD.o

knh_CounterL.o : ../class/naruto/knh_Counter.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/naruto/knh_Counter.c" -oknh_CounterL.o


objs_konohacL = \
	knh_Cmpl_arithmeticL.o\
	knh_Stmt_valueL.o\
	knh_Cmpl_classL.o\
	knh_StmtL.o\
	knh_Token_parserL.o\
	knh_Stmt_exprL.o\
	knh_VirtualMachineCodeL.o\
	knh_Stmt_usingL.o\
	stmtvisit_declvL.o\
	knh_Stmt_foreachL.o\
	knh_String_parserL.o\
	knh_CmplL.o\
	stmtvisit_asmL.o\
	knh_Stmt_methodL.o\
	knh_Cmpl_labelL.o\
	knh_Cmpl_variableL.o\
	stmtvisit_declmL.o\
	knh_Cmpl_methodL.o\
	stmtvisit_declcL.o\
	knh_TokenL.o\
	knh_Cmpl_runL.o\
	knh_Token_genericsL.o\
	knh_Cmpl_annotationL.o\
	knh_Cmpl_sevalL.o\
	knh_Stmt_metaL.o\
	knh_Stmt_trycatchL.o\
	knh_Cmpl_eprintL.o\
	knh_Cmpl_asmL.o\
	knh_Cmpl_asmvL.o
LDLIBS_konohacL = 

knh_Cmpl_arithmeticM.o : ../class/konohac/knh_Cmpl_arithmetic.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_arithmetic.c" -oknh_Cmpl_arithmeticM.o

knh_Cmpl_arithmeticD.o : ../class/konohac/knh_Cmpl_arithmetic.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_arithmetic.c" -oknh_Cmpl_arithmeticD.o

knh_Cmpl_arithmeticL.o : ../class/konohac/knh_Cmpl_arithmetic.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_arithmetic.c" -oknh_Cmpl_arithmeticL.o


knh_Stmt_valueM.o : ../class/konohac/knh_Stmt_value.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_value.c" -oknh_Stmt_valueM.o

knh_Stmt_valueD.o : ../class/konohac/knh_Stmt_value.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_value.c" -oknh_Stmt_valueD.o

knh_Stmt_valueL.o : ../class/konohac/knh_Stmt_value.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_value.c" -oknh_Stmt_valueL.o


knh_Cmpl_classM.o : ../class/konohac/knh_Cmpl_class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_class.c" -oknh_Cmpl_classM.o

knh_Cmpl_classD.o : ../class/konohac/knh_Cmpl_class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_class.c" -oknh_Cmpl_classD.o

knh_Cmpl_classL.o : ../class/konohac/knh_Cmpl_class.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_class.c" -oknh_Cmpl_classL.o


knh_StmtM.o : ../class/konohac/knh_Stmt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt.c" -oknh_StmtM.o

knh_StmtD.o : ../class/konohac/knh_Stmt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt.c" -oknh_StmtD.o

knh_StmtL.o : ../class/konohac/knh_Stmt.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt.c" -oknh_StmtL.o


knh_Token_parserM.o : ../class/konohac/knh_Token_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Token_parser.c" -oknh_Token_parserM.o

knh_Token_parserD.o : ../class/konohac/knh_Token_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Token_parser.c" -oknh_Token_parserD.o

knh_Token_parserL.o : ../class/konohac/knh_Token_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Token_parser.c" -oknh_Token_parserL.o


knh_Stmt_exprM.o : ../class/konohac/knh_Stmt_expr.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_expr.c" -oknh_Stmt_exprM.o

knh_Stmt_exprD.o : ../class/konohac/knh_Stmt_expr.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_expr.c" -oknh_Stmt_exprD.o

knh_Stmt_exprL.o : ../class/konohac/knh_Stmt_expr.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_expr.c" -oknh_Stmt_exprL.o


knh_VirtualMachineCodeM.o : ../class/konohac/knh_VirtualMachineCode.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_VirtualMachineCode.c" -oknh_VirtualMachineCodeM.o

knh_VirtualMachineCodeD.o : ../class/konohac/knh_VirtualMachineCode.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_VirtualMachineCode.c" -oknh_VirtualMachineCodeD.o

knh_VirtualMachineCodeL.o : ../class/konohac/knh_VirtualMachineCode.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_VirtualMachineCode.c" -oknh_VirtualMachineCodeL.o


knh_Stmt_usingM.o : ../class/konohac/knh_Stmt_using.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_using.c" -oknh_Stmt_usingM.o

knh_Stmt_usingD.o : ../class/konohac/knh_Stmt_using.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_using.c" -oknh_Stmt_usingD.o

knh_Stmt_usingL.o : ../class/konohac/knh_Stmt_using.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_using.c" -oknh_Stmt_usingL.o


stmtvisit_declvM.o : ../class/konohac/stmtvisit_declv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/stmtvisit_declv.c" -ostmtvisit_declvM.o

stmtvisit_declvD.o : ../class/konohac/stmtvisit_declv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/stmtvisit_declv.c" -ostmtvisit_declvD.o

stmtvisit_declvL.o : ../class/konohac/stmtvisit_declv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/stmtvisit_declv.c" -ostmtvisit_declvL.o


knh_Stmt_foreachM.o : ../class/konohac/knh_Stmt_foreach.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_foreach.c" -oknh_Stmt_foreachM.o

knh_Stmt_foreachD.o : ../class/konohac/knh_Stmt_foreach.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_foreach.c" -oknh_Stmt_foreachD.o

knh_Stmt_foreachL.o : ../class/konohac/knh_Stmt_foreach.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_foreach.c" -oknh_Stmt_foreachL.o


knh_String_parserM.o : ../class/konohac/knh_String_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_String_parser.c" -oknh_String_parserM.o

knh_String_parserD.o : ../class/konohac/knh_String_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_String_parser.c" -oknh_String_parserD.o

knh_String_parserL.o : ../class/konohac/knh_String_parser.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_String_parser.c" -oknh_String_parserL.o


knh_CmplM.o : ../class/konohac/knh_Cmpl.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl.c" -oknh_CmplM.o

knh_CmplD.o : ../class/konohac/knh_Cmpl.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl.c" -oknh_CmplD.o

knh_CmplL.o : ../class/konohac/knh_Cmpl.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl.c" -oknh_CmplL.o


stmtvisit_asmM.o : ../class/konohac/stmtvisit_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/stmtvisit_asm.c" -ostmtvisit_asmM.o

stmtvisit_asmD.o : ../class/konohac/stmtvisit_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/stmtvisit_asm.c" -ostmtvisit_asmD.o

stmtvisit_asmL.o : ../class/konohac/stmtvisit_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/stmtvisit_asm.c" -ostmtvisit_asmL.o


knh_Stmt_methodM.o : ../class/konohac/knh_Stmt_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_method.c" -oknh_Stmt_methodM.o

knh_Stmt_methodD.o : ../class/konohac/knh_Stmt_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_method.c" -oknh_Stmt_methodD.o

knh_Stmt_methodL.o : ../class/konohac/knh_Stmt_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_method.c" -oknh_Stmt_methodL.o


knh_Cmpl_labelM.o : ../class/konohac/knh_Cmpl_label.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_label.c" -oknh_Cmpl_labelM.o

knh_Cmpl_labelD.o : ../class/konohac/knh_Cmpl_label.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_label.c" -oknh_Cmpl_labelD.o

knh_Cmpl_labelL.o : ../class/konohac/knh_Cmpl_label.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_label.c" -oknh_Cmpl_labelL.o


knh_Cmpl_variableM.o : ../class/konohac/knh_Cmpl_variable.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_variable.c" -oknh_Cmpl_variableM.o

knh_Cmpl_variableD.o : ../class/konohac/knh_Cmpl_variable.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_variable.c" -oknh_Cmpl_variableD.o

knh_Cmpl_variableL.o : ../class/konohac/knh_Cmpl_variable.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_variable.c" -oknh_Cmpl_variableL.o


stmtvisit_declmM.o : ../class/konohac/stmtvisit_declm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/stmtvisit_declm.c" -ostmtvisit_declmM.o

stmtvisit_declmD.o : ../class/konohac/stmtvisit_declm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/stmtvisit_declm.c" -ostmtvisit_declmD.o

stmtvisit_declmL.o : ../class/konohac/stmtvisit_declm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/stmtvisit_declm.c" -ostmtvisit_declmL.o


knh_Cmpl_methodM.o : ../class/konohac/knh_Cmpl_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_method.c" -oknh_Cmpl_methodM.o

knh_Cmpl_methodD.o : ../class/konohac/knh_Cmpl_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_method.c" -oknh_Cmpl_methodD.o

knh_Cmpl_methodL.o : ../class/konohac/knh_Cmpl_method.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_method.c" -oknh_Cmpl_methodL.o


stmtvisit_declcM.o : ../class/konohac/stmtvisit_declc.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/stmtvisit_declc.c" -ostmtvisit_declcM.o

stmtvisit_declcD.o : ../class/konohac/stmtvisit_declc.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/stmtvisit_declc.c" -ostmtvisit_declcD.o

stmtvisit_declcL.o : ../class/konohac/stmtvisit_declc.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/stmtvisit_declc.c" -ostmtvisit_declcL.o


knh_TokenM.o : ../class/konohac/knh_Token.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Token.c" -oknh_TokenM.o

knh_TokenD.o : ../class/konohac/knh_Token.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Token.c" -oknh_TokenD.o

knh_TokenL.o : ../class/konohac/knh_Token.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Token.c" -oknh_TokenL.o


knh_Cmpl_runM.o : ../class/konohac/knh_Cmpl_run.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_run.c" -oknh_Cmpl_runM.o

knh_Cmpl_runD.o : ../class/konohac/knh_Cmpl_run.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_run.c" -oknh_Cmpl_runD.o

knh_Cmpl_runL.o : ../class/konohac/knh_Cmpl_run.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_run.c" -oknh_Cmpl_runL.o


knh_Token_genericsM.o : ../class/konohac/knh_Token_generics.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Token_generics.c" -oknh_Token_genericsM.o

knh_Token_genericsD.o : ../class/konohac/knh_Token_generics.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Token_generics.c" -oknh_Token_genericsD.o

knh_Token_genericsL.o : ../class/konohac/knh_Token_generics.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Token_generics.c" -oknh_Token_genericsL.o


knh_Cmpl_annotationM.o : ../class/konohac/knh_Cmpl_annotation.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_annotation.c" -oknh_Cmpl_annotationM.o

knh_Cmpl_annotationD.o : ../class/konohac/knh_Cmpl_annotation.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_annotation.c" -oknh_Cmpl_annotationD.o

knh_Cmpl_annotationL.o : ../class/konohac/knh_Cmpl_annotation.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_annotation.c" -oknh_Cmpl_annotationL.o


knh_Cmpl_sevalM.o : ../class/konohac/knh_Cmpl_seval.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_seval.c" -oknh_Cmpl_sevalM.o

knh_Cmpl_sevalD.o : ../class/konohac/knh_Cmpl_seval.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_seval.c" -oknh_Cmpl_sevalD.o

knh_Cmpl_sevalL.o : ../class/konohac/knh_Cmpl_seval.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_seval.c" -oknh_Cmpl_sevalL.o


knh_Stmt_metaM.o : ../class/konohac/knh_Stmt_meta.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_meta.c" -oknh_Stmt_metaM.o

knh_Stmt_metaD.o : ../class/konohac/knh_Stmt_meta.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_meta.c" -oknh_Stmt_metaD.o

knh_Stmt_metaL.o : ../class/konohac/knh_Stmt_meta.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_meta.c" -oknh_Stmt_metaL.o


knh_Stmt_trycatchM.o : ../class/konohac/knh_Stmt_trycatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Stmt_trycatch.c" -oknh_Stmt_trycatchM.o

knh_Stmt_trycatchD.o : ../class/konohac/knh_Stmt_trycatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Stmt_trycatch.c" -oknh_Stmt_trycatchD.o

knh_Stmt_trycatchL.o : ../class/konohac/knh_Stmt_trycatch.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Stmt_trycatch.c" -oknh_Stmt_trycatchL.o


knh_Cmpl_eprintM.o : ../class/konohac/knh_Cmpl_eprint.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_eprint.c" -oknh_Cmpl_eprintM.o

knh_Cmpl_eprintD.o : ../class/konohac/knh_Cmpl_eprint.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_eprint.c" -oknh_Cmpl_eprintD.o

knh_Cmpl_eprintL.o : ../class/konohac/knh_Cmpl_eprint.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_eprint.c" -oknh_Cmpl_eprintL.o


knh_Cmpl_asmM.o : ../class/konohac/knh_Cmpl_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_asm.c" -oknh_Cmpl_asmM.o

knh_Cmpl_asmD.o : ../class/konohac/knh_Cmpl_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_asm.c" -oknh_Cmpl_asmD.o

knh_Cmpl_asmL.o : ../class/konohac/knh_Cmpl_asm.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_asm.c" -oknh_Cmpl_asmL.o


knh_Cmpl_asmvM.o : ../class/konohac/knh_Cmpl_asmv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../class/konohac/knh_Cmpl_asmv.c" -oknh_Cmpl_asmvM.o

knh_Cmpl_asmvD.o : ../class/konohac/knh_Cmpl_asmv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../class/konohac/knh_Cmpl_asmv.c" -oknh_Cmpl_asmvD.o

knh_Cmpl_asmvL.o : ../class/konohac/knh_Cmpl_asmv.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../class/konohac/knh_Cmpl_asmv.c" -oknh_Cmpl_asmvL.o


objs_mathL = \
	math_MathL.o
LDLIBS_mathL = \
	-lm

math_MathM.o : ../package/math/math_Math.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../package/math/math_Math.c" -omath_MathM.o

math_MathD.o : ../package/math/math_Math.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../package/math/math_Math.c" -omath_MathD.o

math_MathL.o : ../package/math/math_Math.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../package/math/math_Math.c" -omath_MathL.o


pkg_math.dylib : $(objs_mathL)
	$(CC) -dynamiclib -o pkg_math.dylib -L"./lib" -L"./libexec" $(objs_mathL) $(LDLIBS_mathL) -lkonoha
	mkdir -p package/math
	mv pkg_math.dylib package/math

pkg_math.so : $(objs_mathL)
	$(CC) -shared -Wl,-soname,drv_math.so -o pkg_math.so -L"./lib" -L"./libexec" $(objs_mathL) $(LDLIBS_mathL) -lkonoha
	mkdir -p package/math
	mv pkg_math.so package/math

pkg_math.dll : $(objs_mathL)
	$(CC) -shared -Wl -o pkg_math.dll -L"./lib" -L"./libexec" $(objs_mathL) $(LDLIBS_mathL) -lkonoha
	mkdir -p package/math
	mv pkg_math.dll package/math



objs_mysqlL = \
	knh_Connection__mysqlL.o
LDLIBS_mysqlL = 

knh_Connection__mysqlM.o : ../driver/mysql/knh_Connection__mysql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../driver/mysql/knh_Connection__mysql.c" -oknh_Connection__mysqlM.o

knh_Connection__mysqlD.o : ../driver/mysql/knh_Connection__mysql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../driver/mysql/knh_Connection__mysql.c" -oknh_Connection__mysqlD.o

knh_Connection__mysqlL.o : ../driver/mysql/knh_Connection__mysql.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_LIB) -DKONOHA_PACKAGE -I"../include" -fno-common -fPIC  -c "../driver/mysql/knh_Connection__mysql.c" -oknh_Connection__mysqlL.o


drv_mysql.dylib : $(objs_mysqlL)
	$(CC) -dynamiclib -o drv_mysql.dylib -L"./lib" -L"./libexec" $(objs_mysqlL) $(LDLIBS_mysqlL) -lkonoha
	mkdir -p driver
	mv drv_mysql.dylib driver/

drv_mysql.so : $(objs_mysqlL)
	$(CC) -shared -Wl,-soname,drv_mysql.so -o drv_mysql.so -L"./lib" -L"./libexec" $(objs_mysqlL) $(LDLIBS_mysqlL) -lkonoha
	mkdir -p driver
	mv drv_mysql.so driver/

drv_mysql.dll : $(objs_mysqlL)
	$(CC) -shared -Wl -o drv_mysql.dll -L"./lib" -L"./libexec" $(objs_mysqlL) $(LDLIBS_mysqlL) -lkonoha
	mkdir -p driver
	mv drv_mysql.dll driver/



konohaM.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -DKONOHA_MONOLITHIC -I"../include" -c "../konoha.c" -okonohaM.o

konohaD.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_DEBUG) -DKONOHA_MONOLITHIC -DKONOHA_SAFEMODE -I"../include" -c "../konoha.c" -okonohaD.o

konohaL.o: ../konoha.c ../include/konoha/gen/manifesto.h
	$(CC) $(CFLAGS_MONO) -I"../include" -c "../konoha.c" -okonohaL.o

.PHONY: $(program)
$(program): konohaM.o $(objs_M)
	$(CC) -o $(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program)
	mkdir -p bin
	mv $(program) bin

.PHONY: $(program).exe
$(program).exe: konohaM.o $(objs_M)
	$(CC) -o $(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	strip $(program).exe
	mkdir -p bin
	mv $(program).exe bin

.PHONY: safe_$(program)
safe_$(program): konohaD.o $(objs_D)
	$(CC) -o safe_$(program) $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program) bin

.PHONY: safe_$(program).exe
safe_$(program).exe: konohaD.o $(objs_D)
	$(CC) -o safe_$(program).exe $^ -L"./lib" $(LDLIBS_M) $(LDLIBS)
	mkdir -p bin
	mv safe_$(program).exe bin

.PHONY: lib$(program).dylib
lib$(program).dylib: konohaL.o $(objs_L)
	$(CC) -dynamiclib -o libkonoha.dylib $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dylib libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).so
lib$(program).so: konohaL.o $(objs_L)
	$(CC) -shared -Wl,-soname,libkonoha.so -o libkonoha.so $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.so libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program).dll
lib$(program).dll: konohaL.o $(objs_L)
	$(CC) -shared -Wl,--output-def,libkonoha.def,--out-implib,libkonohadll.a -o libkonoha.dll $^ -L"./lib" $(LDLIBS_L) $(LDLIBS)
	mkdir -p libexec
	mv libkonoha.dll libexec
	$(CC) -o $(program) konohaL.o -L"./libexec" -lkonoha
	mv $(program) libexec

.PHONY: lib$(program)
lib$(program): 
	echo "choose one: dylib, so, cll"

.PHONY: dylib
dylib: lib$(program).dylib $(packages_dylib)

.PHONY: so
so: lib$(program).so $(packages_so)

.PHONY: dll
dll: lib$(program).dll $(packages_dll)

.PHONY: clean
clean:
	$(RM) -rf bin libexec package driver $(objs_M) $(objs_L) $(objs_D) *.o 

