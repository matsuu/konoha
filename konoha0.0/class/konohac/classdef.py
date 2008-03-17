# Merlot class definition (python)

KNH_PACKAGE = {
  'author': 'Kimio Kuramitsu',
}

KNH_NAMESPACE = "knh"
KNH_PACKAGE_DEP = ''

#    'TKF  Block TailC Func PreOp Generated DeclName',
#    'TDF  Protected Init Param Const',
#    'STMTF  Assignment AtParam Closure FieldAccess',  #l

KNH_FLAGS = [
    ('Token', [
        ['TKF', 'TailC', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'TopDot', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        
        ['TKF', 'ExceptionType', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'NotNullType', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'IteratorType', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'ArrayType', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        
        ['TKF', 'NextParenthesis', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'NextBrace',       'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'NextBrancet',     'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],

        ['TKF', 'ToGet', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'ToSet', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'Generated', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],
        ['TKF', 'Perrored', 'knh_flag_tkf_t', '(%s)->flag', 'is:set:*:*'],

    ]),
    ('Stmt', [
	  ['STMTF', 'Adposition', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
      ['STMTF', 'PrintLine',    'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],

      ['STMTF', 'OpNext',    'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
      ['STMTF', 'OpPrev',    'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
      
#      ['STMTF', 'StaticChecked', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
#      ['STMTF', 'Silence', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
      ['STMTF', 'Visible', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
        
#        ['STMTF', 'Assignment', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
#        ['STMTF', 'AtParam', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
#        ['STMTF', 'Closure', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
#        ['STMTF', 'FieldAccess', 'knh_flag_stmtf_t', '(%s)->flag', 'is:set:*:*'],
    ]),
    ('Cmpl', [
        ['CPF', 'SyntaxError',  'knh_flag_cpf_t', '(%s)->flag', 'is:set:*:*'],
        ['CPF', 'TypeError',  'knh_flag_cpf_t', '(%s)->flag', 'is:set:*:*'],
        ['CPF', 'Cancelled', 'knh_flag_cpf_t', '(%s)->flag', 'is:set:*:*'],
        
    ]),
]

KNH_CLASSES = [
  ['Token',  'Object', None, '@Private', [
    ['knh_token_t',     'tt'],
    ['knh_flag_tkf_t',  'flag'],
    ['knh_filen_t',     'filen'],
    ['knh_line_t',      'line'],
    ['Object*',     'data'],
  ]],

  ['Stmt', 'Object', None, '@Private', [
   ['knh_flag_stmtf_t', 'flag'],
   ['knh_stmt_t', 'stt'],
   ['knh_ushort_t', 'size'],
   ['knh_ushort_t', 'capacity'],
   ['Term**', 'terms'],
   ['struct knh_Stmt*', 'meta'],
   ['struct knh_Stmt*', 'next'],
  ]],

  ['Cmpl', 'Object', None, '@Private', [
    ['knh_flag_cpf_t',  'flag'],
    ['knh_nsn_t',       'nsn'],

    ['knh_Prototype*',  'nsproto'],
    
    ['knh_filen_t',     'filen'],
    ['knh_class_t',     'this_cid'],
    
    ['knh_Method*',     'method'],
    
#    ['knh_type_t',      'rtype'],
#    ['knh_ushort_t',    'param_size'],
    
    ['knh_ushort_t',    'vars_size'],
    ['knh_ushort_t',    'vars_offset'],
    ['knh_cfield_t*',   'vars'],
    
    ['int',            'nastep'],
    ['int',            'llstep'],
    ['knh_Bytes*',     'elf'],
    ['knh_Bytes*',     'dwarf'],
    ['int',            'line'],

#    ['Token*',    'curop'],
    ['knh_DictIdx*',    'labelIdDictIdx'],
    ['knh_DictSet*',    'labelAddrDictSet'],
    ['knh_Array*',      'lstacks'],
#    ['String*',   'stmt_label'],
  ]],

  ['VirtualMachineCode',  'Object', None, None, [
    ['knh_vmc_t*',     'code'],
    ['size_t',   'size'],
    ['knh_filen_t',    'filen'],
    ['knh_nsn_t',      'nsn'],
    ['knh_dwarf_t*',  'dwarf'],
    ['size_t',   'dsize'],
  ]],

]


if __name__ == '__main__':
    for c in KNH_FLAGS:
        cname = c[0]
        for f in c[1]:
            if f[2].startswith("knh_flag"):
                print "/* @flag %s.%s %s %s '%s' */" % (cname, f[1], f[0],  f[3], f[4])
            else:
                print "/* @flag %s.%s %s:%s %s '%s' */" % (cname, f[1], f[0], f[2],  f[3], f[4])

