using posix.*;
void func1(int sig)
{
    OUT << "segv\n";
    System.exit(1);
}

void func2(int sig)
{
    OUT << "killed\n";
}


int main(String[] argv)
{
    Closure c1 = delegate(func1);
    Closure c2 = delegate(func2);
    
    System.setSigSegv(c1);
    System.setSigBus(c1);
    System.setSigKill(c1);
    while(true){
        System.sleep(1);
    }
    return 0;
}
