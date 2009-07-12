// The Computer Language Benchmarks Game
// http://shootout.alioth.debian.org/
//
// contributed by masahiro ide

int[] range(int start,int end){
    int size = end - start + 1;
    int[] array = new Int[](size);
    for(i=start;i<=end;i++){
        array.add(i);
    }
    print start,end,size,array;
    return array;
}

int fannkuch(int n){
    int[] perm  = new Int[n];
    int[] perm1 = range(0,n-1);
    int[] count = new Int[n];
    int[] maxPerm = new Int[n];
    int m = n - 1;
    int r = n;
    int check = 0;
    int maxFlipsCount = 0;
    while(true){
        if(check < 30){
            for(i=0;i<n;i++){ OUT << perm1[i]+1; }
            OUT << EOL;
            check++;
        }
        while(r != 1){
            count[r-1] = r;
            r--;
        }

        if(perm1[0] != 0 && perm1[m] != m){
            for(i = 0; i<n; i++) perm[i] = perm1[i];
            flipsCount = 0;
            k = perm[0];
            while(k != 0){
                k2 = (k+1) >> 1;
                for(i=0;i<k2;i++){
                    perm.swap(i,k-i);
                }
                flipsCount++;
                k = perm[0];
            }
            if(flipsCount > maxFlipsCount){
                maxFlipsCount = flipsCount;
                for(i=0;i<n;i++){
                    maxPerm[i] = perm1[i];
                }
            }
        }

        while(true){
            if(r == n) return maxFlipsCount;
            perm0 = perm1[0];
            i = 0;
            while(i<r){
                int j = i + 1;
                perm1[i] = perm1[j];
                i = j;
            }
            perm1[r] = perm0;

            count[r] = count[r] - 1;
            if(count[r] > 0) break;
            r++;
        }
    }
}

void main(String[] args){
    int n = 7;
    if(|args| > 1){
        n = (int) args[1];
    }
    OUT << %("Pfannkuchen(%d{0}) = %d{1}",n,fannkuch(n)) << EOL;
}

