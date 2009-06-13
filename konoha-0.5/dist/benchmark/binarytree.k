/* The Great Computer Language Shootout
   http://shootout.alioth.debian.org/

   contributed by Kimio Kuramitsu
*/

MINDEPTH = 4;

class TreeNode {
	TreeNode? left
	TreeNode? right;
	int item;

	TreeNode(TreeNode? left, TreeNode? right, int item) {
		_left = left;
		_right = right;
		_item = item;
	}
	
	@Static TreeNode bottomUpTree(int item, int depth){
		if (depth>0){
			return new TreeNode(
				bottomUpTree(2*item-1, depth-1), 
				bottomUpTree(2*item, depth-1), 
				item
			);
		}
		else {
			return new TreeNode(null, null, item);
		}
	}

	int itemCheck(){
		// if necessary deallocate here
		if (_left==null) return _item;
		return _item + _left.itemCheck() - _right.itemCheck();
	}
}


void main(String[] args) {
	int n = 20;
	print |args|;
	//if (|args| > 1) n = (int)args[0];

	int maxDepth = (MINDEPTH + 2 > n) ? MINDEPTH + 2 : n;
	int stretchDepth = maxDepth + 1;
	int check = (TreeNode.bottomUpTree(0,stretchDepth)).itemCheck();
	System.out.println("stretch tree of depth "+stretchDepth+"\t check: " + check);

	TreeNode longLivedTree = TreeNode.bottomUpTree(0,maxDepth);

	for (depth=MINDEPTH; depth<=maxDepth; depth+=2){
		int iterations = 1 << (maxDepth - depth + MINDEPTH);
		check = 0;

		for (i=1; i<=iterations; i++){
			check += (TreeNode.bottomUpTree(i,depth)).itemCheck();
			check += (TreeNode.bottomUpTree(-i,depth)).itemCheck();
		}
		System.out.println((iterations*2) + "\t trees of depth " + depth + "\t check: " + check);
	}
	System.out.println("long lived tree of depth " + maxDepth + "\t check: "+ longLivedTree.itemCheck());
}
