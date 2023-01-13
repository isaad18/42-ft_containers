#ifndef MAP_HPP
#define MAP_HPP

#include"ft.hpp"
#include"pair.hpp"
#include "map_iterator.hpp"
#include "map_reverse_iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
#include <cstddef>

namespace ft{
	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<Key,T> > >
	class map{
		struct Node;
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<key_type, mapped_type> 								value_type;
			typedef std::less<key_type> 											key_compare;
			typedef Alloc 															allocator_type;
			typedef typename allocator_type::template rebind<Node>::other    		allocator_type2;
			typedef ft::m_iterator<Node, value_type> 								iterator;
			typedef ft::m_iterator<const Node, const value_type> 					const_iterator;
			typedef ft::map_reverse_iterator<Node, value_type> 						reverse_iterator;
			typedef ft::map_reverse_iterator<const Node, const value_type> 			const_reverse_iterator;
		private:
			struct Node {
				int index;
				Node* last;
				value_type all;
				Node* parent;
				Node* left;
				Node* right;
				int height;
			};

			allocator_type _alloc;

			allocator_type2 _alloca;

			Node *node;

			mutable Node *searched;

			mutable Node *parent;

			key_compare _comp;

			size_t _size;

			int Height(Node* node) const{
				if (node == nullptr)
					return 0;
				return node->height;
			}

			int Balance(Node* node) const{
				if (node == nullptr) {
				return 0;
				}
				return Height(node->left) - Height(node->right);
			}

			Node* minimum(Node *tmp2){
				if (tmp2 == nullptr)
					return nullptr;
				Node *tmp = tmp2;
				while (tmp->left != nullptr){
					tmp = tmp->left;
				}
				return tmp;
			}

			Node* minimum(Node *tmp2) const{
				if (tmp2 == nullptr)
					return nullptr;
				Node *tmp = tmp2;
				while (tmp->left != nullptr){
					tmp = tmp->left;
				}
				return tmp;
			}

			Node* maximum(Node *tmp2){
				if (tmp2 == nullptr)
					return nullptr;
				Node *tmp = tmp2;
				while (tmp->right != nullptr){
					tmp = tmp->right;
				}
				return tmp;
			}

			Node* maximum(Node *tmp2) const{
				if (tmp2 == nullptr)
					return nullptr;
				Node *tmp = tmp2;
				while (tmp->right != nullptr){
					tmp = tmp->right;
				}
				return tmp;
			}

			Node *rotateRight(Node* toRotate){
				Node *tmp_root = toRotate->left;
				Node *tmp_left = tmp_root->right;
				tmp_root->right = toRotate;
				toRotate->left = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				tmp_root->parent = toRotate->parent;
				toRotate->parent = tmp_root;
				if(toRotate->left) toRotate->left->parent = toRotate;
				return tmp_root;
			}

			Node *rotateLeft(Node* toRotate){
				Node *tmp_root = toRotate->right;
				Node *tmp_left = tmp_root->left;
				tmp_root->left = toRotate;
				toRotate->right = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				tmp_root->parent = toRotate->parent;
				toRotate->parent = tmp_root;
				if(toRotate->right) toRotate->right->parent = toRotate;
				return tmp_root;
			}

			Node *insertAVL(Node *toAdd, key_type key, T value){
				if (toAdd == nullptr){
					Node *l = _alloca.allocate(1);
					l->all = ft::make_pair(key, value);
					l->left = NULL;
					l->right = NULL;
					l->last = nullptr;
					l->index = 0;
					l->parent = toAdd;
					l->height = 1;
					// _size++;
					return l;
				}
				if (_comp(key, toAdd->all.first)){
					toAdd->left = insertAVL(toAdd->left, key, value); // insert smaller
					toAdd->left->parent = toAdd;
				}
				else if (_comp(toAdd->all.first, key)){
					toAdd->right = insertAVL(toAdd->right, key, value); // insert larger
					toAdd->right->parent = toAdd;
				}
				else{
					if (toAdd->all.second >= value)
						toAdd->all.second = (value);
				} // if he is adding value on the same key
				toAdd->height = std::max(Height(toAdd->right), Height(toAdd->left)) + 1;
				// rotation part to add
				int balance = Balance(toAdd);
				if (balance > 1 && _comp(key, toAdd->left->all.first)) // if the left side is bigger than the right side and the key that has been added is smaller than the left key so the left key can be root just rotate right
					return rotateRight(toAdd);
				if (balance < -1 && _comp(toAdd->right->all.first, key)) // if the right side is bigger than the left side and the key that has been added is smaller than the right key so the right key can be root just rotate left
					return rotateLeft(toAdd);
				if (balance > 1 && _comp(toAdd->left->all.first, key)){ // if the left side is bigger than the right side and the key that has been added is bigger than the left key so the left key can't be directly a root just rotate left for the left branch then right to the root
					toAdd->left = rotateLeft(toAdd->left);
					return rotateRight(toAdd);
				}
				if (balance < -1 && _comp(key, toAdd->right->all.first)){ // if the left side is bigger than the right side and the key that has been added is bigger than the right key so the right key can't be directly a root just rotate right for the right branch then left to the root
					toAdd->right = rotateRight(toAdd->right);
					return rotateLeft(toAdd);
				}
				return toAdd;
			}

			void search_N(Node *root, key_type key) const{
				if (root == nullptr)
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
				if (node == nullptr) {
					return nullptr;
				}
				if (node->right == nullptr) {
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
				if (crnt->right != nullptr) {
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
				if (crnt->left != nullptr) {
					crnt->left->parent = crnt;
				}
				return left;
			}

			Node* Max(Node* crnt) {
	if (crnt == nullptr) {
		return nullptr;
	}
	while (crnt->right != nullptr) {
		crnt = crnt->right;
	}
	return crnt;
}

			Node* Remove(Node* crnt, key_type key) {
	if (crnt == nullptr) {
		return nullptr;
	}
	else if(_size == 1){
		_alloca.deallocate(node, 1);
		// node = nullptr;
		return nullptr;
	}
	if (key < crnt->all.first) {
		crnt->left = Remove(crnt->left, key);
		if (crnt->left != nullptr)
			crnt->left->parent = crnt;
	}
	else if (key > crnt->all.first) {
		crnt->right = Remove(crnt->right, key);
		if (crnt->right != nullptr)
			crnt->right->parent = crnt;
	}
	else {
		if (crnt->left == nullptr && crnt->right == nullptr) {
			_alloca.deallocate(crnt, 1);
			if (_size == 1)
				node = nullptr;
			return nullptr;
		}
		else if (crnt->left == nullptr) {
			Node* temp = crnt->right;
			_alloca.deallocate(crnt, 1);
			return temp;
		}
		else if (crnt->right == nullptr) {
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
	if (crnt == nullptr) {
		return;
	}
	if (crnt->left != nullptr) {
		crnt->left->parent = crnt;
		updateParentPointer(crnt->left);
	}
	if (crnt->right != nullptr) {
		crnt->right->parent = crnt;
		updateParentPointer(crnt->right);
	}
}




		public:

			class value_compare
			: public std::binary_function<value_type, value_type, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
				key_compare comp;

				value_compare(key_compare c): comp(c) {}

				public:
				bool operator()(const value_type& x, const value_type& y) const
				{ return comp(x.first, y.first); }
			};

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), node(nullptr), searched(nullptr), parent(nullptr), _comp(comp), _size(0){}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _alloc(alloc), node(nullptr), searched(nullptr), parent(nullptr), _comp(comp), _size(0){
				// insert(first, last);
				while (first != last){
					this->insert(first->first, first->second);
					first++;
				}
			}

			map (const map& x){
				this->_size = 0;
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				node = nullptr;
				searched = nullptr;
				parent = nullptr;
				iterator it = x.begin();
				iterator it2 = x.end();
				this->insert(it, it2);
			}

			map& operator= (const map& x)
			{
				if(this != &x)
				{
					clear();
					insert(x.begin(), x.end());
				}
				return (*this);
			}

			~map(){ if (_size >0) deleteAll(); }

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
				std::cout << "NODE: " << root->all.first << "            ";
				// if (node->last->index == 2) std::cout << "wohooooo" << std::endl; 
				// if (node->last->index == 1) std::cout << "wohooooo" << std::endl; 
			  print2DUtil(root->left, space);
			}

			void check_add(key_type key){
				mapped_type it = search(key)->all;
			}

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
				if (search(val.first) != nullptr)
					ok = true;
				insert(val.first, val.second);
				return ft::make_pair(iterator(search(val.first)), ok);
			}
			private:
			value_type &insert(key_type key, T value){
				// size_t tmp = _size;
				// bool ok = false;
				// (void)ok;
				// if (search(key) == nullptr){
				// 	ok = true;
				// }
				if (node != nullptr){
					Node *tmp1 = node;
					while (tmp1->right != nullptr)
						tmp1 = tmp1->right;
					tmp1->last->index = 0;
					tmp1->index = 0;
					_alloca.deallocate(tmp1->last, 1);
					tmp1->last = nullptr;
				}
				// bool ok = false;
				// if (search(key) == nullptr){
				// 	ok = true;
				// }
				if (search(key) == nullptr)
					_size++;
				// std::cout << "__" << _size << std::endl;
				node = insertAVL(node, key, value);
				// if (ok){
				if (node != nullptr){
					Node *tmp = node;
					while (tmp->right != NULL)
						tmp = tmp->right;
					tmp->last = _alloca.allocate(1);
					tmp->last->parent = tmp;
					tmp->last->index = 1;
					tmp->index = 2;
				}
				// }
				// if (tmp == 0 && _size == 1){
				// 	sorted = _alloc.allocate(1);
				// 	sorted[0] = node->all;
				// }
				// else if (tmp < _size){
				// 	value_type* newArray = _alloc.allocate(_size);
				// 	if (tmp > 0) {
				// 		for (size_t i = 0; i < tmp; i++)
				// 			newArray[i] = sorted[i];
				// 	}
				// 	newArray[tmp].first = key;
				// 	newArray[tmp].second = value;
				// 	if (tmp > 0) {
				// 		_alloc.deallocate(sorted, tmp);
				// 	}
				// 	sorted = newArray;
				// 	for (size_t i = 0; i < _size - 1; i++){
				// 		if (_comp(key, sorted[i].first)){
				// 			for (size_t j = _size; j > i; j--){
				// 				sorted[j] = sorted[j - 1];
				// 			}
				// 			sorted[i] = search(key)->all;
				// 			break ;
				// 		}
				// 	}
				// }
				// else{
				// 	for (size_t i = 0; i < _size; i++){
				// 		if (sorted[i].first == key){
				// 			sorted[i].second = value;
				// 			break ;
				// 		}
				// 	}
				// }
				return search(key)->all;
			}
			public:

			size_t size() const{
				return _size;
			}

			bool empty() const{
				if (_size == 0)
					return true;
				return false;
			}

			size_t max_size() const{ return static_cast<std::size_t>(-1) / sizeof(T); }

			T& operator[]( const Key& key ) {
				Node *it = NULL;
				if (node != nullptr){
					if ((it = search(key)) == nullptr){
						insert(key, T());
						it = search(key);
					}
				}
				else{
					insert(key, T());
					it = search(key);
				}
				return it->all.second;
			}

			T& at( const Key& key )
			{
				ft::pair<key_type, T> it = search(key)->all;
				return(it->second);
			}

			const T& at( const Key& key ) const
			{
				ft::pair<key_type, T> it = search(key)->all;
				return(it->second);
			}

			Node *search(key_type key) const{
				searched = nullptr;
				search_N(node, key);
				if (searched == nullptr)
					return nullptr;
				return searched;
			}

			// Node *search1(key_type key)const{
			// 	// searched = NULL;
			// 	// parent = NULL;
			// 	search_N(node, key);
			// 	return searched;
			// }

			// Node *search(key_type key) const{
			// 	searched = nullptr;
			// 	parent = nullptr;
			// 	search_N(node, key);
			// 	return searched;
			// }

			void deleteit(key_type key){
				if (node != nullptr){
					Node *tmp1 = node;
					while (tmp1->right != nullptr)
						tmp1 = tmp1->right;
					tmp1->last->index = 0;
					tmp1->index = 0;
					_alloca.deallocate(tmp1->last, 1);
					tmp1->last = nullptr;
				}
				node = Remove(node, key);
				if (node != nullptr){
				Node *tmp = node;
					while (tmp->right != NULL)
						tmp = tmp->right;
					tmp->last = _alloca.allocate(1);
					tmp->last->parent = tmp;
					tmp->last->index = 1;
					tmp->index = 2;
				}
			}

			void deleteAll(){
				Node *l = node;
				if (l == nullptr)
					return ;
				while (l->right != nullptr){
					l = l->right;
				}
				_alloca.deallocate(l->last, 1);
				delete_node(node);
				_alloca.deallocate(node, 1);
				node = nullptr;
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
				// _size--;
			}

			size_t erase (const key_type& k){
				if (search(k) != nullptr){
					deleteit(k);
					if (_size > 0)
						--_size;
					return 1;
				}
				// std::cout << maximum(node)->all.first << std::endl;
				// std::cout << minimum(node)->all.first << std::endl;
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

			size_t count(const key_type& k) const {
				if (search(k) != nullptr)
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
				iterator  it = begin();
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
				return make_pair(it, it2);
			}

			pair<iterator,iterator> equal_range (const key_type& k){
				iterator it = lower_bound(k);
				iterator it2 = upper_bound(k);
				return make_pair(it, it2);
			}

			iterator begin(){
				if (minimum(node) == nullptr)
					return (iterator());
				return (iterator(&(*minimum(node))));
			}

			const_iterator begin() const{
				if (minimum(node) == nullptr)
					return (const_iterator());
				return (const_iterator(&(*minimum(node))));
			}

			iterator end(){
				if (maximum(node) == nullptr)
					return (iterator());
				return (iterator(&(*maximum(node)->last)));
			}

			const_iterator end() const{
				if (maximum(node) == nullptr)
					return (const_iterator());
				return (const_iterator(&(*maximum(node)->last)));
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
  bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }

  template <class Key, class T, class Compare, class Alloc>
  bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
	return !(lhs == rhs);
  }

  template <class Key, class T, class Compare, class Alloc>
  bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
  }

  template <class Key, class T, class Compare, class Alloc>
  bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
	return !(rhs < lhs);
  }

  template <class Key, class T, class Compare, class Alloc>
  bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
	return (rhs < lhs);
  }

  template <class Key, class T, class Compare, class Alloc>
  bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
	return !(lhs < rhs);
  }

  template <class Key, class T, class Compare, class Alloc>
  void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y) {
	x.swap(y);
  }
}

#endif