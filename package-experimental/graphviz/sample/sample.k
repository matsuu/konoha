using graphviz.*;

int main(String[] args){

    gvc = new GVC();
    gvc.gvParseArgs(args);
    g = new Agraph("g",GV.AG_DIGRAPH);
    a = new Agnode(g,"a");
    b = new Agnode(g,"b");
    c = new Agnode(g,"c");
    e1 = new Agedge(g,a,b);
    e2 = new Agedge(g,b,c);
    e3 = new Agedge(g,c,a);

    /*------------graph status-------------------*/

    GV.agSafeset(g,"label","sample","");
    GV.agSafeset(g,"labelloc","t","");
    GV.agSafeset(g,"fontname","ArialBd","");
    // GV.agSafeset(g,"fontsize","10","");
    GV.agSafeset(g,"fontcolor","Orange","");
    GV.agSafeset(g,"bgcolor","gray","");

    /*------------node a status----------------*/

    GV.agSafeset(a,"fillcolor","red","");
    GV.agSafeset(a,"shape","box","");
    GV.agSafeset(a,"style","filled","");
    GV.agSafeset(a,"fixedsize","true","");
    GV.agSafeset(a,"width","1.7","");
    GV.agSafeset(a,"height","0.8","");

    /*-----------node b status------------------*/

    GV.agSafeset(b,"style","filled","");
    GV.agSafeset(b,"fillcolor","blue","");
    GV.agSafeset(b,"peripheries","3","");


    /*------------node c status----------------*/

    GV.agSafeset(c,"style","filled","");
    GV.agSafeset(c,"fillcolor","green","");

    /*------------edge status-----------------*/

    GV.agSafeset(e1,"label","hi","");
    GV.agSafeset(e2,"label","hi","");
    GV.agSafeset(e3,"label","hi","");
    /*-----------------------------------------*/

    gvc.gvLayoutJobs(g);
    gvc.gvRenderJobs(g);
    gvc.gvFreeLayout(g);
    g.agclose();
    
    gvc.gvFreeContext();

    return 0;
}

