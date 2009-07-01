#!/usr/local/bin/konoha
/*
   System.walk(String path);
   emulate python's os.walk;
*/
 
using posix.*;
import "array.k"
 
String[] System.walk(String path){
    String[] p = [];
    if(System.hasDir(path)){
        l = System.listDir(path);
        //foreach(String t in System.listDir(path))
        for(i=0;i<|l|;i++){
            String t = l[i];
            String newpath = path + "/" + t;
            if(System.hasDir(newpath)){
                p.addAll(System.walk(newpath));
            } else {
                p.add(newpath);
            }
        }
    }
    return p;
}

// example. read all dirs recurcivly without ".svn" file
/*
void main(String[] args){
    String[] list = System.walk(args[1]);
    String[] ret = [];
    //foreach(String line in list)
    for(i=0;i<|list|;i++){
        line = list[i];
        if(line.indexOf(".svn") < 0){
            ret.add(line + " \\");
        }
    }
    //foreach(String l in ret){
    //    OUT << l << EOL;
    //}
    for(i=0;i<|ret|;i++){
        OUT << ret[i] << EOL;
    }
}
*/
