max = 20_000;
file = "./tmpfile_for_bm_io_file_read";
str = "Hello world!  " * 1000;

f = new OutputStream(file,"w");
f.print(str);
f.close();

for (i=0; i < max; i++) {
    f.seek(0);
    f.read();
}
os.unlink(file);
