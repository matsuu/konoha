String test(){
OUT << "test" << EOL
return "test";
}

String hello(){
OUT << "hello" << EOL
return hello;
}

String func2(String a, String b){
    ret = a + " " + b;
    return ret;
}

String func3(String a, String b){
    int i = (int)a;
    int j = (int)b;
    ret = i + j;
    return (String)ret;
}

int fib(int i){
    int ret;
    if(i > 2){
        ret = fib(i-1) + fib(i-2);
    }
    else{
	ret = 1;
    }
    return ret;
}

String func4(String a){
    int i = (int)a;
    ret = fib(i);
    return (String)ret;
}

String write(String case1){
    OUT << case1 << EOL;
    file = new OutputStream("/home/kato/log/log.txt","w");
    file.println("case: " + case1);
    file.close();
    return "writen";
}

//String write(String case1, String part){
//    OUT << case1 << @ << part << EOL;
//    file = new OutputStream("/home/kato/log/log.txt","w");
//    file.println("case: " + case1);
//    file.println("part: " + part);
//    file.close();
//    return "writen";
//}
