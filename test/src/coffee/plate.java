package coffee;
//Use trie tree rather than HashSet to store the assigned plates.
// space comsumptin: worst case 26^4 * 10^3 * sizeof(reference_to_treeNode) \
// but it's better than HashSet that if store continuous plate numbers, it saves much 
// more space than hash, because hash need a string for each plate numbers. But trie tree
// can reuse nodes.

// In time complexity, trie is much more effectient since depth of trie tree is fixed
//giveMeOne(): o(n)
//isTaken(): o(1)
//iGaveOut():  o(1)


public class plate{
	treeNode root = null;
	String curReleasedNum = "AAAA111";
	public plate(){
		root = new treeNode();
	}
	
	public boolean isTaken(String plate){
		return isTaken(plate.toCharArray(), 0, root );
	}

	public boolean  isTaken(char[] plate,  int position, treeNode node ){
		if(position == 7) return true;
		char c = plate[position];
		//----------------is an alphabetical character
		if(position < 4){                    
			if(node.children[c-'A'] == null) return false;
			return isTaken(plate, position+1, node.children[c-'A']);
		}
		//-----------------is a number	
		if(node.children[c-'0'] == null) return false;
		return isTaken(plate, position+1, node.children[c-'0']);
	}
	
	public void iGaveOut(String plate){
		iGaveOut(plate.toCharArray(), 0, root );
	}
	
	public void iGaveOut(char[] plate,  int position, treeNode node){
		
		char c = plate[position];
		//----------------is an alphabetical character
		if(position < 4){                    
			if(node.children[c-'A'] == null) node.children[c-'A'] = new treeNode();
			iGaveOut(plate, position+1, node.children[c-'A']);
		}
		//--------------till the end of the String
		else if(position == 6){
			node.children[c-'0'] = root;
			return;
		}
		//-----------------is a number	
		else if(node.children[c-'0'] == null){
			node.children[c-'0'] = new treeNode();
			iGaveOut(plate, position+1, node.children[c-'0']);
		}
	}
		
	public String giveMeOne(){
		String tmp = curReleasedNum;
		while(isTaken(tmp)){
			tmp = tmp.substring(0,4) + (Integer.parseInt(tmp.substring(4))+1);
		}
		curReleasedNum = tmp;
		return curReleasedNum;
	}


}


class treeNode{
	treeNode[] children = new treeNode[26];
}