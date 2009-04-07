

class DFlag {
  String cname;
  String fname;
}

@DFlag {
  cname: Object;
  pflag: Release;
  nflag: Debug;
  code: '(BASE)->h.flag';
  accessors: 'is:*:is:*';
}

/* @flag Object.Release!Debug OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Immutable OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Cyclic OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.MetaData OF (%s)->h.flag 'has:set:has:*' */
/* @flag Object.Synchronized OF (%s)->h.flag 'is:*:is:*' */
/* @flag Object.Modified OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.GCMarked OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Formatted OF (%s)->h.flag 'is:set:is:set' */
/* @flag Object.Local4 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local3 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local2 OF (%s)->h.flag 'is:set:*:*' */
/* @flag Object.Local1 OF (%s)->h.flag 'is:set:*:*' */

class DClassFlag extends Flag {
	boolean Cyclic;
}

class DClass {
  DClassFlag flag;
  String cname;
  String lname;
  String struct;
}

@DClass {
  flag:  +Cyclic;
  cname: Object;
  lname: konoha.Object;
}

