# Merlot class definition (python)

KNH_PACKAGE = {
  'author': 'Kimio Kuramitsu',
}

KNH_NAMESPACE = "knh"
KNH_PACKAGE_DEP = ''

KNH_FLAGS = [
    ('Nue', [
        ['NUE', 'GCHook', '1',  'knh_Object_head(%s)->flag', 'is:set:*:*'],
        ['NUE', 'ObjectText', '2',  'knh_Object_head(%s)->flag', 'is:set:*:*'],
    ]),
    
    ('String', [
        ['STRING', 'STEXT', '1',  'knh_Object_head(%s)->flag', 'is:set:*:*'],
    ]),
    ('Bytes', [
        ['BYTES', 'StackBuffer', '1',  'knh_Object_head(%s)->flag', 'is:set:*:*'],
    ]),
    ('Object', [
        ['OF', 'Release!Debug',     'knh_flag_of_t',  'knh_Object_head(%s)->flag', 'is:*:is:*'],
        ['OF', 'Immutable', 'knh_flag_of_t',  'knh_Object_head(%s)->flag', 'is:*:is:*'],
        ['OF', 'MetaData',  'knh_flag_of_t',  'knh_Object_head(%s)->flag', 'has:set:has:*'],
        ['OF', 'Synchronized', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:*:is:*'],
        ['OF', 'Modified',  'knh_flag_of_t',  'knh_Object_head(%s)->flag', 'is:set:is:set'],
#        ['OF', 'NullObject', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:*:is:*'],
        ['OF', 'Local4', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:set:*:*'],
        ['OF', 'Local3', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:set:*:*'],
        ['OF', 'Local2', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:set:*:*'],
        ['OF', 'Local1', 'knh_flag_of_t', 'knh_Object_head(%s)->flag', 'is:set:*:*'],
    ]),
    
    ('Class', [
        ['CF', 'Release!Debug', 'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
        ['CF', 'Immutable', 'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
        ['CF', 'MetaExtensible', 'knh_flag_cf_t',  'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
#        ['CF', 'Syncronized', 'knh_flag_cf_t', 'knh_tclass_cflag(knh_Class_cid(%s)', 'is:*:is:*'],
        ['CF', 'Private!Public',  'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
        ['CF', 'Final',  'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
        ['CF', 'Strict', 'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:*:*'],
        ['CF', 'System',  'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
        ['CF', 'NullObject', 'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:*:*'],
        ['CF', 'NA',  'knh_flag_cf_t', 'knh_tclass_table(knh_Class_cid(%s))->cflag', 'is:*:is:*'],
    ]),
    
    ('ClassStruct', [
        ['CFF', 'Hidden',    'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'AutoName',  'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'SafeValue', 'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'Protected', 'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'Getter',    'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'Setter',    'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
        ['CFF', 'Key',       'knh_flag_cff_t', '((ClassStruct)%s)->fields[n].flag', 'is:set:*:*'],
    ]),
    
    ('Method', [
        ['MF', 'Public!Private', 'knh_flag_mf_t', '((Method*)%s)->flag', 'is:set:is:*'],
        ['MF', 'Virtual!Final',  'knh_flag_mf_t', '((Method*)%s)->flag', 'is:set:is:*'],
        ['MF', 'Static', 'knh_flag_mf_t', '((Method*)%s)->flag', 'is:*:is:*'],
        ['MF', 'Class', 'knh_flag_mf_t', '((Method*)%s)->flag', 'is:*:is:*'],
        ['MF', 'VarArgs',  'knh_flag_mf_t', '((Method*)%s)->mf->flag', 'is:set:is:*'],
        ['MF', 'Aspect',  'knh_flag_mf_t', '((Method*)%s)->mf->flag', 'is:set:is:*'],
        ['MF', 'ObjectCode',  'knh_flag_mf_t', '((Method*)%s)->flag', 'is:set:*:*'],
        ['MF', 'Generated',  'knh_flag_mf_t', '((Method*)%s)->mf->flag', 'is:set:*:*'],
    ]),
#    'MAPF DB HighPriority Synonym LossLess Total Static Temporal Interface Derived',
    ('MapMap', [
        ['MMF', 'Interface', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'VerySignificant', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', '*:*:*:*'],
        ['MMF', 'Significant', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'Synonym', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'LossLess', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'Total!Partial', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'Static!Temporal', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'Local', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
        ['MMF', 'Derived', 'knh_flag_mmf_t', '((MapMap*)%s)->flag', 'is:set:is:*'],
    ]),
    
    # 'EF   Fatal Logging Static Generated',
    ('Exception', [
        ['EF', 'Fatal', 'knh_flag_ef_t', '((Exception*)%s)->flag', 'is:*:is:*'],
        ['EF', 'Logging', 'knh_flag_ef_t', '((Exception*)%s)->flag', 'is:*:is:*'],
        ['EF', 'Generated', 'knh_flag_ef_t', '((Exception*)%s)->flag', 'is:*:is:*'],
        ['EF', 'Caught', 'knh_flag_ef_t', '((Exception*)%s)->flag', 'is:set:*:*'],
    ]),

    ('ExceptionHandler', [
        ['EHF', 'Catching', '1', 'knh_Object_head(%s)->flag', 'is:set:*:*'],
    ]),

    ('IntUnit', [
        ['UF', 'Unsigned', 'knh_flag_uf_t', '((IntUnit*)%s)->spec.flag', 'is:*:is:*'],
    ]),
    
]

KNH_CLASSES = [
  ['Object', 'Object', None, None, 0],
  ['Tuple1', 'Object', None, None, 1],
  ['Tuple2', 'Object', None, None, 2],
  ['Tuple3', 'Object', None, None, 3],
  ['Tuple4', 'Object', None, None, 4],
  ['Tuple5', 'Object', None, None, 5],
  ['Tuple6', 'Object', None, None, 6],
  ['Tuple7', 'Object', None, None, 7],
  ['Tuple8', 'Object', None, None, 8],
  ['Tuple9', 'Object', None, None, 9],
  ['Tuple10', 'Object', None, None, 10],
  ['Tuple11', 'Object', None, None, 11],
  ['Tuple12', 'Object', None, None, 12],
  ['Tuple13', 'Object', None, None, 13],
  ['Tuple14', 'Object', None, None, 14],
  ['Tuple15', 'Object', None, None, 15],

  ['Prototype', 'Object', None, '@Struct', 'knh_Prototype'],

  ['Nue', 'Object', None, '@Struct', 'knh_Nue'],

  ['Bool', 'Object', None, '@Struct', 'knh_Bool'],
   
  ['Int', 'Object', None, '@Struct', 'knh_Int'],

  ['Int64', 'Object', None, '@Struct', 'knh_Int64'],

  ['Float', 'Object', None, '@Struct', 'knh_Float'],

# string.h
  ['String', 'Object', None, '@Struct', 'knh_String'],
  ['Regex', 'Object', None, '@Struct', 'knh_Regex'],
   
  ['Bytes', 'Object', None, '@Struct', 'knh_Bytes'],
  ['BytesConv', 'Object', None, '@Struct', 'knh_BytesConv'],


# collection.h
  ['Array', 'Object', None, '@Struct', 'knh_Array'],
  ['HashMap', 'Object', None, '@Struct', 'knh_HashMap'],
  ['HashSet', 'Object', None, '@Struct', 'knh_HashSet'],
  ['DictMap', 'Object', None, '@Struct', 'knh_DictMap'],
  ['DictSet', 'Object', None, '@Struct', 'knh_DictSet'],
  ['Iterator', 'Object', None, '@Struct', 'knh_Iterator'],
  ['DictIdx', 'Object', None, '@Struct', 'knh_DictIdx'],
   
  #class.h
  ['Class', 'Object', None, '@Struct', 'knh_Class'],
  ['ClassStruct',  'Object', None, '@Struct', 'knh_ClassStruct'],
  ['MethodField',  'Object', None, '@Struct', 'knh_MethodField'],
  
  ['Method',  'Object', None, '@Struct', 'knh_Method'],
  ['MapMap',  'Object', None, '@Struct', 'knh_MapMap'],
  ['ClassRel',  'Object', None, '@Struct', 'knh_ClassRel'],
  ['Closure',  'Object', None, '@tuple @Struct', 'knh_Closure'],

  ['IntUnit',  'Object', None, '@Struct', 'knh_IntUnit'],
  ['FloatUnit',  'Object', None, '@Struct', 'knh_FloatUnit'],
  ['Vocabulary',  'Object', None, '@Struct', 'knh_Vocabulary'],
  ['AffineConv',  'Object', None, '@Struct', 'knh_AffineConv'],

  ['InputStream',  'Object', None, '@Struct', 'knh_InputStream'],
  ['OutputStream',  'Object', None, '@Struct', 'knh_OutputStream'],
  ['Socket',  'Object', None, '@Struct', 'knh_Socket'],
  ['Connection', 'Object', None, '@Struct', 'knh_Connection'],
  ['ResultSet', 'Object', None, '@Struct', 'knh_ResultSet'],
  
#  ['Writer',  'Object', None, '@Struct', 'knh_Writer'],
#  ['MovableText',  'Object', None, '@Struct', 'knh_MovableText'],
   
  ['Exception',  'Object', None, '@Struct', 'knh_Exception'],
  ['ExceptionHandler',  'Object', None, '@Struct', 'knh_ExceptionHandler'],
  ['Mutex',  'Object', None, '@Struct', 'knh_Mutex'],

  ['System',  'Object', None, '@Struct @tuple', 'knh_System'],
  ['NameSpace', 'Object', None, '@Struct @tuple', 'knh_NameSpace'],
  ['Runtime',  'Object', None, '@Struct', 'knh_Runtime'],
  ['Context',  'Object', None, '@Struct', 'knh_Context'],

]

#['NUE', 'ObjectText', '2',  'knh_Object_head(%s)->flag', 'is:set:*:*'],

if __name__ == '__main__':
    for c in KNH_FLAGS:
        cname = c[0]
        for f in c[1]:
            if f[2].startswith("knh_flag"):
                print "/* @flag %s.%s %s %s '%s' */" % (cname, f[1], f[0],  f[3], f[4])
            else:
                print "/* @flag %s.%s %s:%s %s '%s' */" % (cname, f[1], f[0], f[2],  f[3], f[4])

