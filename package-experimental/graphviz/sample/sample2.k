using graphviz.*;
//using posix.*;

int main(String[] args){
    gvc = new GVC();
    gvc.gvParseArgs(["konoha","-Tps","-odcase.ps"]);
    graph = new Agraph("graph",GV.AG_DIGRAPH);
    str = ["G:Service A can run against Fault B","G:Diagnosis","G:Monitor","G:Analyzer","G:Prescription","E:Konoha P-Script"];
    Agnode[] a = [];
    foreach(s in str ){
	a.add(new Agnode(graph,s));
    }
    e1 = new Agedge(graph,a[1],a[2]);
    e2 = new Agedge(graph,a[1],a[3]);
    e3 = new Agedge(graph,a[0],a[1]);
    e4 = new Agedge(graph,a[4],a[5]);
    e5 = new Agedge(graph,a[0],a[4]);
    
    /*------------graph status-------------------*/
    
    GV.agSafeset(graph,"label","D-Case Diagnpsis & Prescription","");
    GV.agSafeset(graph,"labelloc","t","");
    
    /*------------node a[0] status----------------*/
    
    GV.agSafeset(a[0],"fillcolor","yellow","");
    GV.agSafeset(a[0],"shape","box","");
    GV.agSafeset(a[0],"style","filled","");
    GV.agSafeset(a[0],"fixedsize","true","");
    GV.agSafeset(a[0],"width","2.0","");
    GV.agSafeset(a[0],"height","0.8","");
    
    /*-----------edge e1 stattus-----------------*/
    
    GV.agSafeset(e1,"dir","back","");
    GV.agSafeset(e1,"label","strategy","");
    
    /*-----------Copy Attribute-------------------*/
    
    GV.copyAttr(a[0],a[1]);
    GV.copyAttr(a[1],a[2]);
    GV.copyAttr(a[2],a[3]);
    GV.copyAttr(a[3],a[4]);
    GV.copyAttr(e1,e2);
    GV.copyAttr(e2,e3);
    GV.copyAttr(e3,e4);
    GV.copyAttr(e4,e5);

    /*-----------a[0] Status---------------------*/
    
    GV.agSafeset(a[0],"fixedsize","true","");
    GV.agSafeset(a[0],"width","4.0","");
    GV.agSafeset(a[0],"height","0.8","");
    
    
    /*-----------node a[5] status-----------------*/
    
    GV.agSafeset(a[5],"fillcolor","green","");
    GV.agSafeset(a[5],"shape","box","");
    GV.agSafeset(a[5],"style","filled","");
    GV.agSafeset(a[5],"fixedsize","true","");
    GV.agSafeset(a[5],"width","3.0","");
    GV.agSafeset(a[5],"height","0.8","");
    
    GV.agSafeset(a[0],"label","G:\\nService A can run against Fault B","");
    GV.agSafeset(a[1],"label","G:\\nDiagnosis","");
    GV.agSafeset(a[2],"label","G:\\nMonitor","");
    GV.agSafeset(a[3],"label","G:\\nAnalyzer","");
    GV.agSafeset(a[4],"label","G:\\nPrescription","");
    GV.agSafeset(a[5],"label","E:\\nKonoha P-Script","");
    
    gvc.gvLayoutJobs(graph);
    gvc.gvRenderJobs(graph);
    gvc.gvFreeLayout(graph);
    graph.agclose();
    
    gvc.gvFreeContext();

    return 0;
}


