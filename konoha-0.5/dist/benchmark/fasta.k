
class Frequency {
	int c;
	double p;
    Frequency(int c, double p) {
    	_c = c;
    	_p = p;
    }
}

IM = 139968;
IA = 3877;
IC = 29573;
LINE_LENGTH = 60;

last = 42;

// pseudo-random number generator
double random(double max) {
	last = (last * IA + IC) % IM;
	return max * last / IM;
}

// Weighted selection from alphabet
 alu =        "GGCCGGGCGCGGTGGCTCACGCCTGTAATCCCAGCACTTTGG"
            + "GAGGCCGAGGCGGGCGGATCACCTGAGGTCAGGAGTTCGAGA"
            + "CCAGCCTGGCCAACATGGTGAAACCCCGTCTCTACTAAAAAT"
            + "ACAAAAATTAGCCGGGCGTGGTGGCGCGCGCCTGTAATCCCA"
            + "GCTACTCGGGAGGCTGAGGCAGGAGAATCGCTTGAACCCGGG"
            + "AGGCGGAGGTTGCAGTGAGCCGAGATCGCGCCACTGCACTCC"
            + "AGCCTGGGCGACAGAGCGAGACTCCGTCTCAAAAA";

 alub = alu.getBytes();

 isb = [    new Frequency('a'.getChar(), 0.27),
            new Frequency('c'.getChar(), 0.12),
            new Frequency('g'.getChar(), 0.12),
            new Frequency('t'.getChar(), 0.27),

            new Frequency('B'.getChar(), 0.02),
            new Frequency('D'.getChar(), 0.02),
            new Frequency('H'.getChar(), 0.02),
            new Frequency('K'.getChar(), 0.02),
            new Frequency('M'.getChar(), 0.02),
            new Frequency('N'.getChar(), 0.02),
            new Frequency('R'.getChar(), 0.02),
            new Frequency('S'.getChar(), 0.02),
            new Frequency('V'.getChar(), 0.02),
            new Frequency('W'.getChar(), 0.02),
            new Frequency('Y'.getChar(), 0.02) ];

homoSapiens = [
            new Frequency('a'.getChar(), 0.3029549426680d),
            new Frequency('c'.getChar(), 0.1979883004921d),
            new Frequency('g'.getChar(), 0.1975473066391d),
            new Frequency('t'.getChar(), 0.3015094502008d)];

void makeCumulative(Frequency[] a) {
	double cp = 0.0;
	for (int i = 0; i < |a|; i++) {
		cp += a[i].p;
		a[i].p = cp;
    }
}

// naive
public int selectRandom(Frequency[] a) {
	int len = |a|;
	double r = random(1.0);
    for (int i = 0; i < len; i++)
    	if (r < a[i].p) return a[i].c;
    return a[len - 1].c;
}

BUFFER_SIZE = 1024;
int index = 0;

byte[] bbuffer = new byte[BUFFER_SIZE];
void makeRandomFasta(String id, String desc,Frequency[] a, int n, OutputStream writer) {
	index = 0;
    int m = 0;
    String descStr = ">" + id + " " + desc + '\n';
    writer.write(descStr.getBytes());
    while (n > 0) {
    	if (n < LINE_LENGTH) m = n;  else m = LINE_LENGTH;
    	if(BUFFER_SIZE - index < m){
    		writer.write(bbuffer, 0, index);
            index = 0;
        }
        for (int i = 0; i < m; i++) {
            bbuffer[index++] = selectRandom(a);
        }
        bbuffer[index++] = '\n';
        n -= LINE_LENGTH;
    }
    if(index != 0) writer.write(bbuffer, 0, index);
}

void makeRepeatFasta(String id, String desc, String alu, int n, OutputStream writer) {
        index = 0;
        int m = 0;
        int k = 0;
        int kn = |alub|;
        String descStr = ">" + id + " " + desc + '\n';
        writer.write(descStr.getBytes());
        while (n > 0) {
            if (n < LINE_LENGTH) m = n; else m = LINE_LENGTH;
            if(BUFFER_SIZE - index < m){
                writer.write(bbuffer, 0, index);
                index = 0;
            }
            for (int i = 0; i < m; i++) {
                if (k == kn) k = 0;
                bbuffer[index++] = alub[k];
                k++;
            }
            bbuffer[index++] = '\n';
            n -= LINE_LENGTH;
        }
        if(index != 0) writer.write(bbuffer, 0, index);
}

void main(String[] args) {
	makeCumulative(homoSapiens);
    makeCumulative(isb);
    int n = 2500000;
    if (|args| > 1) n = (int)args[1];
    OutputStream out = OUT;
    makeRepeatFasta("ONE", "Homo sapiens alu", alu, n * 2, out);
    makeRandomFasta("TWO", "IUB ambiguity codes", isb, n * 3, out);
    makeRandomFasta("THREE", "Homo sapiens frequency", homoSapiens, n * 5, out);
    out.flush();
}

