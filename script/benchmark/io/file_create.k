max = 50_000;
file = "./tmpfile_for_bm_io_file_create";

for (i=0; i < max; i++) {
    f = new OutputStream(file,"w");
    f.close();
}
os.unlink(file);
