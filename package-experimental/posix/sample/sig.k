using posix.*;
void func1(int sig)
{
    OUT << %("segv %d{0}\n",sig);
}
void func2(int sig)
{
    OUT << %("bus %d{0}\n",sig);
}


void func3(int sig)
{
    OUT << %("kill %d{0}\n",sig);
}

Closure c1 = delegate(func1);
Closure c2 = delegate(func2);
Closure c3 = delegate(func3);

System.setSigSegv(c1);
System.setSigBus(c2);
System.setSigKill(c3);
System.setSigInt(c1);

