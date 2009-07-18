using openssl.*;
void main(String[] args)
{
    OUT << Crypt.sha1(args[0]) << EOL;
}
