#ifndef MAP_HPP
#define MAP_HPP

#include"../utilities/ft.hpp"
#include"../utilities/pair.hpp"
#include "../utilities/map_iterator.hpp"
#include "../utilities/map_reverse_iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<Key,T> > >
	class map{
		struct Node;
		public:
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<key_type, mapped_type>										value_type;
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef value_type*															pointer;
			typedef const value_type*													const_pointer;
			typedef Compare																key_compare;
			typedef Alloc																allocator_type;
			typedef typename allocator_type::template rebind<Node>::other				allocator_type2;
			typedef ft::m_iterator<Node, value_type, Compare>							iterator;
			typedef ft::m_iterator<const Node, const value_type, Compare>				const_iterator;
			typedef ft::map_reverse_iterator<Node, value_type, Compare>					reverse_iterator;
			typedef ft::map_reverse_iterator<const Node, const value_type, Compare>		const_reverse_iterator;
		private:
			class value_compare: public std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
				key_compare comp;

				value_compare(key_compare c): comp(c){}

				public:
				bool operator()(const value_type& x, const value_type& y) const{
					return comp(x.first, y.first);
				}
			};

		private:
			allocator_type		_alloc;
			allocator_type2		_alloca;
			Node*				node;
			mutable Node*		searched;
			mutable Node*		parent;
			key_compare			_comp;
			size_t				_size;

			/*__________________AVL TREE__________________AVL TREE__________________AVL TREE_________________*/
			struct Node {
				int			index;
				Node*		last;
				value_type	all;
				Node*		parent;
				Node*		left;
				Node*		right;
				int			height;
			};

			// used to get the height inside the node and to protect from NULL nodes
			int Height(Node* node) const{
				if (node == NULL)
					return 0;
				return node->height;
			}

			// used to calculate the balance in the tree to check if balance is needed or not
			int Balance(Node* node) const{
				if (node == NULL) {
				return 0;
				}
				return Height(node->left) - Height(node->right);
			}

			// used to get the minimum element in the whole tree
			Node* minimum(Node *tmp2){
				if (tmp2 == NULL)
					return NULL;
				Node *tmp = tmp2;
				while (tmp->left && _comp(tmp->left->all.first, tmp->all.first)){
					tmp = tmp->left;
				}
				while (tmp->right && _comp(tmp->right->all.first, tmp->all.first)){
					tmp = tmp->right;
				}
				return tmp;
			}

			// used to get the minimum element in the whole tree (const)
			Node* minimum(Node *tmp2) const{
				if (tmp2 == NULL)
					return NULL;
				Node *tmp = tmp2;
				while (tmp->left && _comp(tmp->left->all.first, tmp->all.first)){
					tmp = tmp->left;
				}
				while (tmp->right && _comp(tmp->right->all.first, tmp->all.first)){
					tmp = tmp->right;
				}
				return tmp;
			}

			// used to get the maximum element in the whole tree
			Node* maximum(Node *tmp2){
				if (tmp2 == NULL)
					return NULL;
				Node *tmp = tmp2;
				while (tmp->left && _comp(tmp->all.first, tmp->left->all.first)){
					tmp = tmp->left;
				}
				while (tmp->right && _comp(tmp->all.first, tmp->right->all.first)){
					tmp = tmp->right;
				}
				return tmp;
			}

			// used to get the maximum element in the whole tree (const)
			Node* maximum(Node *tmp2) const{
				if (tmp2 == NULL)
					return NULL;
				Node *tmp = tmp2;
				while (tmp->left && _comp(tmp->all.first, tmp->left->all.first)){
					tmp = tmp->left;
				}
				while (tmp->right && _comp(tmp->all.first, tmp->right->all.first)){
					tmp = tmp->right;
				}
				return tmp;
			}

			// rotate the sent node to the right by making the sent node a child to its left child and making the right of the left child the left of the new root node
			Node *rotateRight(Node* toRotate){
				Node *tmp_root = toRotate->left;
				Node *tmp_left = tmp_root->right;
				toRotate->left = tmp_left;
				tmp_root->right = toRotate;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				tmp_root->parent = toRotate->parent;
				toRotate->parent = tmp_root;
				if(toRotate->left)
					toRotate->left->parent = toRotate;
				return tmp_root;
			}

			// rotate the sent node to the right by making the sent node a child to its right child and making the left of the right child the right of the new root node
			Node *rotateLeft(Node* toRotate){
				Node *tmp_root = toRotate->right;
				Node *tmp_left = tmp_root->left;
				toRotate->right = tmp_left;
				tmp_root->left = toRotate;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				tmp_root->parent = toRotate->parent;
				toRotate->parent = tmp_root;
				if(toRotate->right)
					toRotate->right->parent = toRotate;
				return tmp_root;
			}

			Node *insertAVL(Node *toAdd, key_type key, mapped_type value){
				if (toAdd == NULL){
					Node *l = _alloca.allocate(1);
					_alloca.construct(l, Node());
					l->all = ft::make_pair(key, value);
					l->left = NULL;
					l->right = NULL;
					l->last = NULL;
					l->index = 0;
					l->parent = toAdd;
					l->height = 1;
					return l;
				}
				if (_comp(key, toAdd->all.first)){
					toAdd->left = insertAVL(toAdd->left, key, value);
					toAdd->left->parent = toAdd;
				}
				else if (_comp(toAdd->all.first, key)){
					toAdd->right = insertAVL(toAdd->right, key, value);
					toAdd->right->parent = toAdd;
				}
				return ft_balance(toAdd);
			}

			void search_N(Node *root, key_type key) const{
				if (root == NULL)
					return ;
				if (root->all.first == key){
					searched = root;
					return ;
				}
				if (_comp(key, root->all.first)){
					if (root->left){
						search_N(root->left, key);
					}
				}
				else{
					if (root->right){
						search_N(root->right, key);
					}
				}
			}

			Node* Min(Node* node) {
				if (node == NULL) {
					return NULL;
				}
				if (node->right == NULL) {
					return node;
				}
				return Min(node->right);
			}

			Node* rotateLeftdelete(Node* crnt) {
				Node* right = crnt->right;
				crnt->right = right->left;
				right->left = crnt;
				right->parent = crnt->parent;
				crnt->parent = right;
				if (crnt->right != NULL) {
					crnt->right->parent = crnt;
				}
				return right;
			}

			Node* rotateRightdelete(Node* crnt) {
				Node* left = crnt->left;
				crnt->left = left->right;
				left->right = crnt;
				left->parent = crnt->parent;
				crnt->parent = left;
				if (crnt->left != NULL) {
					crnt->left->parent = crnt;
				}
				return left;
			}

			Node* Max(Node* crnt) {
				if (crnt == NULL) {
					return NULL;
				}
				while (crnt->right != NULL) {
					crnt = crnt->right;
				}
				return crnt;
			}

			Node* Remove(Node* crnt, key_type key) {
				if (crnt == NULL) {
					return NULL;
				}
				else if(_size == 1){
					_alloca.deallocate(node, 1);
					return NULL;
				}
				if (_comp(key, crnt->all.first)) {
					crnt->left = Remove(crnt->left, key);
					if (crnt->left != NULL)
						crnt->left->parent = crnt;
				}
				else if (_comp(crnt->all.first, key)) {
					crnt->right = Remove(crnt->right, key);
					if (crnt->right != NULL)
						crnt->right->parent = crnt;
				}
				else {
					if (crnt->left == NULL && crnt->right == NULL) {
						_alloca.deallocate(crnt, 1);
						if (_size == 1)
							node = NULL;
						return NULL;
					}
					else if (crnt->left == NULL) {
						Node* temp = crnt->right;
						_alloca.deallocate(crnt, 1);
						return temp;
					}
					else if (crnt->right == NULL) {
						Node* temp = crnt->left;
						_alloca.deallocate(crnt, 1);
						return temp;
					}
					else {
						Node* predecessor = Max(crnt->left);
						crnt->all = predecessor->all;
						crnt->left = Remove(crnt->left, predecessor->all.first);
						updateParentPointer(crnt);
					}
				}
				return ft_balance(crnt);
			}

			Node *ft_balance(Node *crnt){
				crnt->height = std::max(Height(crnt->right), Height(crnt->left)) + 1;
				int balance = Balance(crnt);
				if (balance > 1 && Balance(crnt->left) == -1){
					crnt->left = rotateLeft(crnt->left);
					return rotateRight(crnt);
				}
				if (balance < -1 && Balance(crnt->right) == 1){
					crnt->right = rotateRight(crnt->right);
					return rotateLeft(crnt);
				}
				if (balance > 1 && Balance(crnt->left) == 1)
					return rotateRight(crnt);
				if (balance < -1 && Balance(crnt->right) == -1)
					return rotateLeft(crnt);
				return crnt;
			}

			void updateParentPointer(Node* crnt) {
				if (crnt == NULL){
					return ;
				}
				if (crnt->left != NULL) {
					crnt->left->parent = crnt;
					updateParentPointer(crnt->left);
				}
				if (crnt->right != NULL) {
					crnt->right->parent = crnt;
					updateParentPointer(crnt->right);
				}
			}

			value_type &insert(key_type key, mapped_type value){
				Node *end;
				(void)end;
				if (_size == 0){
					end = _alloca.allocate(1);
				}
				if (node != NULL){
					Node *tmp1 = node;
					while (tmp1->right != NULL)
						tmp1 = tmp1->right;
					tmp1->last->index = 0;
					tmp1->index = 0;
					end = tmp1->last;
					tmp1->last = NULL;
				}
				if (search(key) == NULL)
					_size++;
				node = insertAVL(node, key, value);
				if (node != NULL){
					Node *tmp = node;
					while (tmp->right != NULL)
						tmp = tmp->right;
					tmp->last = end;
					tmp->last->parent = tmp;
					tmp->last->index = 1;
					tmp->index = 2;
				}
				return search(key)->all;
			}

			void deleteAll(){
				Node *l = node;
				if (l == NULL)
					return ;
				while (l->right != NULL){
					l = l->right;
				}
				_alloca.deallocate(l->last, 1);
				delete_node(node);
				_alloca.deallocate(node, 1);
				node = NULL;
			}

			void delete_node(Node *nodes){
				if (nodes->right == NULL){
					_alloca.deallocate(nodes->right, 1);
				}
				else if (nodes->right){
					delete_node(nodes->right);
					_alloca.deallocate(nodes->right, 1);
				}
				if (nodes->left == NULL){
					_alloca.deallocate(nodes->left, 1);
				}
				else if (nodes->left){
					delete_node(nodes->left);
					_alloca.deallocate(nodes->left, 1);
				}
			}

			Node *search(key_type key) const{
				searched = NULL;
				search_N(node, key);
				if (searched == NULL)
					return NULL;
				return searched;
			}

			void deleteit(key_type key){
				Node *end;
				(void)end;
				if (node != NULL){
					Node *tmp1 = node;
					while (tmp1->right != NULL)
						tmp1 = tmp1->right;
					tmp1->last->index = 0;
					tmp1->index = 0;
					end = tmp1->last;
					tmp1->last = NULL;
				}
				node = Remove(node, key);
				if (node != NULL){
				Node *tmp = node;
					while (tmp->right != NULL)
						tmp = tmp->right;
					tmp->last = end;
					tmp->last->parent = tmp;
					tmp->last->index = 1;
					tmp->index = 2;
				}
			}

			/*__________________AVL TREE__________________AVL TREE__________________AVL TREE_________________*/

		public:
			/*_____________________2D map printer_____________________*/
			void print2D() const{
				std::cout << "Tree:" << std::endl;
				print2DUtil(node, 0);
			}

			 void print2DUtil(Node *root, int space) const{
				if (root == NULL) return;
					space += 10;
				print2DUtil(root->right, space);
				std::cout << std::endl;
				for (int i = 10; i < space; i++) std::cout << " ";
				std::cout << root->all.first << "(" << Balance(root) << ")" << std::endl;
				for (int i = 10; i < space; i++) std::cout << " ";
					if (root->parent)
						std::cout << "Parent: " << root->parent->all.first << std::endl;
				// std::cout << "NODE: " << root->all.first << "            ";
				print2DUtil(root->left, space);
			}
			/*_____________________2D map printer_____________________*/

		public:

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), node(NULL), searched(NULL), parent(NULL), _comp(comp), _size(0){}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), node(NULL), searched(NULL), parent(NULL), _comp(comp), _size(0){
				while (first != last){
					this->insert(first->first, first->second);
					first++;
				}
			}

			map (const map& x){
				this->_size = 0;
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				node = NULL;
				searched = NULL;
				parent = NULL;
				const_iterator it = x.begin();
				const_iterator it2 = x.end();
				this->insert(it, it2);
			}

			map& operator=(const map& x)
			{
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}

			~map(){ if (_size > 0) deleteAll(); }


			template <class InputIterator>
			void insert (InputIterator first, typename enable_if<!ft::is_integral<InputIterator>::value,InputIterator>::type last){
				while (first != last){
					insert(first->first, first->second);
					first++;
				}
			}

			iterator insert (iterator position, const value_type& val){
				(void)position;
				return insert(val).first;
			}

			pair<iterator,bool> insert (const value_type& val){
				bool ok = false;
				(void)ok;
				if (search(val.first) == NULL)
					ok = true;
				insert(val.first, val.second);
				return ft::make_pair(iterator(search(val.first)), ok);
			}

			size_t size() const{
				return _size;
			}

			bool empty() const{
				if (_size == 0)
					return true;
				return false;
			}

			size_t max_size() const{
				return static_cast<std::size_t>(-1) / sizeof(T);
			}

			T& operator[]( const Key& key ) {
				iterator it;
				if (node != NULL){
					if (search(key) == NULL){
						insert(key, T());
					}
				}
				else{
					insert(key, T());
				}
				it = iterator(search(key));
				return it->second;
			}

			T at( const Key& key )
			{
				ft::pair<key_type, T> it = search(key)->all;
				return(it.second);
			}

			const T at( const Key& key ) const
			{
				ft::pair<key_type, T> it = search(key)->all;
				return(it.second);
			}

			key_compare key_comp() const{
				return (key_compare());
			}

			value_compare value_comp() const {
				return (value_compare(key_compare()));
			}

			void clear(){
				deleteAll();
				_size = 0;
			}

			void erase (iterator position){
				this->erase(position->first);
			}

			size_t erase (const key_type& k){
				if (search(k) != NULL){
					deleteit(k);
					if (_size > 0)
						--_size;
					return 1;
				}
				return 0;
			}

			void erase (iterator first1, iterator last1){
				std::allocator<key_type> tst;
				key_type *k = tst.allocate(ft::distance(first1, last1));
				size_t j = 0;
				for (;first1 != last1; first1++){
					k[j] = first1->first;
					j++;
				}
				for (size_t i = 0; i < j; i++){
					this->erase(k[i]);
				}
				tst.deallocate(k, ft::distance(first1, last1));

			}

			void swap(ft::map<key_type, mapped_type> &other){
				ft::swaps(_size, other._size);
				ft::swaps(node, other.node);
			}

			size_t count(const key_type& k) const {
				if (search(k) != NULL)
					return 1;
				return 0;
			}

			iterator find (const key_type& k){
				return iterator(search(k));
			}

			const_iterator find (const key_type& k) const{
				return const_iterator(search(k));
			}

			iterator upper_bound (const key_type& k){
				iterator it = begin();
				iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
				return it2;
			}

			const_iterator upper_bound (const key_type& k) const{
				const_iterator it = begin();
				const_iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
				return it2;
			}

			iterator lower_bound (const key_type& k){
				iterator  it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					it++;
				}
				return it;
			}

			const_iterator lower_bound (const key_type& k) const{
				const_iterator  it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					it++;
				}
				return it;
			}

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
				const_iterator it = lower_bound(k);
				const_iterator it2 = upper_bound(k);
				return ft::make_pair(it, it2);
			}

			pair<iterator,iterator> equal_range (const key_type& k){
				iterator it = lower_bound(k);
				iterator it2 = upper_bound(k);
				return ft::make_pair(it, it2);
			}

			iterator begin(){
				if (minimum(node) == NULL)
					return (iterator());
				return (iterator(&(*minimum(node))));
			}

			const_iterator begin() const{
				if (minimum(node) == NULL)
					return (const_iterator());
				return (const_iterator(&(*minimum(node))));
			}

			iterator end(){
				if (maximum(node) == NULL)
					return (iterator());
				return (iterator(&(*maximum(node)->last)));
			}

			const_iterator end() const{
				if (maximum(node) == NULL)
					return (const_iterator());
				return (const_iterator(&(*(maximum(node)->last))));
			}

			reverse_iterator rbegin(void) {
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin(void) const {
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend(void) {
				return (reverse_iterator(iterator(this->begin())));
			}

			const_reverse_iterator rend(void) const {
				return (const_reverse_iterator(const_iterator(this->begin())));
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y){
		x.swap(y);
	}
}

#endif
