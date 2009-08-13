void utest(String name, boolean test)
{
    if(test) {
        OUT << "[" << name << "]: PASS" << EOL;
    }
    else {
        OUT << "[" << name << "]: ** FAILED **" << EOL;
        os.exit(1);
    }
}
