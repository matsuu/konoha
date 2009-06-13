/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/

   contributed by Kimio Kuramitsu
*/

MINDEPTH = 4;

class TreeNode {
	TreeNode? _left, _right;
	int _item;
	int flag;
	
	TreeNode(TreeNode? left, TreeNode? right, int item, flag) {
		_left = left;
		_right = right;
		_item = item;
		_flag = flag;
	}
	
	int itemCheck(){
		// if necessary deallocate here
		int n = _item;
		if (_flag == 1) {
		    n = _left.itemCheck() - _right.itemCheck();
			print %p(this), n;
		}
		return n;
	}
}

TreeNode bottomUpTree(int item, int depth){
	if (depth > 0){
		return new TreeNode(
			bottomUpTree((2*item)-1, depth-1), 
			bottomUpTree(2*item, depth-1), 
			item, 1
		);
	}
	else {
		print depth, item;
		return new TreeNode(null, null, item, 0);
	}
}

void main(String[] args) {
	int n = 2;
	//if (|args| > 1) n = (int)args[1];

	int maxDepth = (MINDEPTH + 2 > n) ? MINDEPTH + 2 : n;
	int stretchDepth = maxDepth + 1;
	int check = bottomUpTree(0,stretchDepth).itemCheck();
	System.out.println("stretch tree of depth "+stretchDepth+"\t check: " + check);
	
	/*return ;*/
	
	TreeNode longLivedTree = bottomUpTree(0,maxDepth);

	for (depth=MINDEPTH; depth<=maxDepth; depth+=2){
		int iterations = 1 << (maxDepth - depth + MINDEPTH);
		check = 0;

		for (i=1; i<=iterations; i++){
			check += bottomUpTree(i,depth).itemCheck();
			check += bottomUpTree(-i,depth).itemCheck();
		}
		print depth, check;
		System.out.println((iterations*2) + "\t trees of depth " + depth + "\t check: " + check);
	}
	System.out.println("long lived tree of depth " + maxDepth + "\t check: "+ longLivedTree.itemCheck());
}
