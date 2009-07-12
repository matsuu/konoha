int tak(int x,int y, int z)
{
    OUT << x + "/" + y + "/" + z << EOL;
    if (!(y < x)) {
        return z;
    }
    else return tak(tak(x-1, y, z),
                    tak(y-1, z, x),
                    tak(z-1, x, y));
}
OUT << tak(18, 9, 0) << EOL;
