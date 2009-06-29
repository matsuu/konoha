
void readfile (String s)
{
  OUT << s << EOL;
}

int main(String[] argv)
{
  foreach(String s in argv) {
    readfile(s);
  }
}