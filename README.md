For a binary search tree(BST), most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the height of the BST.
The cost of these operations may become O(n) for a skewed Binary tree. If we make sure that height of the tree remains O(Logn) after every insertion and deletion,
then we can guarantee an upper bound of O(Logn) for all these operations. In AVL tree, it is garanteed that the heights of the two child subtrees of any node differ by at most one.
However, this may cause more rotations during insertion and deletion. So if an application involves many frequent insertions and deletions, the cost is too high.
While a Red Black tree loosen this garantee only make sure that the height of a Red Black tree is always O(Logn) where n is the number of nodes in the tree to make a trade-off
between the cost of rotation and tree balance which is believed to improve the overall performance.

The red_black_tree structure in this directory is written with C++ class template.
It is free to initialize a variable with red_black_tree<T> var,
where T could be any standard type supporting "<" operator.
