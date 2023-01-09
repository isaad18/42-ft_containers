#ifndef MAP_HPP
#define MAP_HPP

#include"ft.hpp"
#include"pair.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
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
			typedef ft::pair<key_type, mapped_type> value_type;
			typedef std::less<key_type> key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::template rebind<Node>::other    allocator_type2;
			typedef ft::iterator<value_type> iterator;
			typedef ft::iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<value_type> reverse_iterator;
			typedef ft::reverse_iterator<const value_type> const_reverse_iterator;
		private:
			struct Node {
				value_type all;
				Node* left;
				Node* right;
				int height;
			};

			allocator_type _alloc;

			value_type *sorted;

			allocator_type2 _alloca;

			Node *node;

			Node *searched;

			Node *parent;

			key_compare _comp;

			size_t _size;

			int Height(Node* node) {
				if (node == nullptr)
					return 0;
				return node->height;
			}

			int Balance(Node* node) {
				if (node == nullptr) {
				return 0;
				}
				return Height(node->left) - Height(node->right);
			}

			Node *rotateRight(Node* toRotate){
				Node *tmp_root = toRotate->left;
				Node *tmp_left = tmp_root->right;
				tmp_root->right = toRotate;
				toRotate->left = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				return tmp_root;
			}

			Node *rotateLeft(Node* toRotate){
				Node *tmp_root = toRotate->right;
				Node *tmp_left = tmp_root->left;
				tmp_root->left = toRotate;
				toRotate->right = tmp_left;
				toRotate->height = 1 + std::max(Height(toRotate->right), Height(toRotate->left));
				tmp_root->height = 1 + std::max(Height(tmp_root->right), Height(tmp_root->left));
				return tmp_root;
			}

			Node *insertAVL(Node *toAdd, key_type key, T value){
				if (toAdd == nullptr){
					Node *l = _alloca.allocate(1);
					l->all = ft::make_pair(key, value);
					l->left = nullptr;
					l->right = nullptr;
					l->height = 1;
					_size++;
					return l;
				}
				if (_comp(key, toAdd->all.first)){
					toAdd->left = insertAVL(toAdd->left, key, value); // insert smaller
				}
				else if (_comp(toAdd->all.first, key)){
					toAdd->right = insertAVL(toAdd->right, key, value); // insert larger
				}
				else
					toAdd->all.setSecond(value); // if he is adding value on the same key
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

			void search_N(Node *root, key_type key){
				if (root->all.first == key){
					searched = root;
					return ;
				}
				if (_comp(key, root->all.first)){
					if (root->left){
						if (root->left->all.first == key)
							parent = root;
						search_N(root->left, key);
					}
				}
				else{
					if (root->right){
						if (root->right->all.first == key)
							parent = root;
						search_N(root->right, key);
					}
				}
			}

			Node* Min(Node* node) {
				if (node == nullptr) {
					return nullptr;
				}
				if (node->left == nullptr) {
					return node;
				}
				return Min(node->left);
			}

			Node* Remove(Node* crnt, key_type key) {
				if (crnt == nullptr) {
					return nullptr;
				}
				if (key < crnt->all.first) {
					crnt->left = Remove(crnt->left, key);
				}
				else if (key > crnt->all.first) {
					crnt->right = Remove(crnt->right, key);
				}
				else {
					if (crnt->left == nullptr && crnt->right == nullptr) {
						_alloca.deallocate(crnt, 1);
						return nullptr;
					}
					if (crnt->left != nullptr && crnt->right == nullptr) {
						Node* temp = crnt->left;
						_alloca.deallocate(node, 1);
						return temp;
					}
					if (node->left == nullptr && node->right != nullptr) {
						Node* temp = node->right;
						_alloca.deallocate(node, 1);
						return temp;
					}
					Node* successor = Min(crnt->right);
					crnt->all = successor->all;
					crnt->right = Remove(crnt->right, successor->all.first);
				}
				crnt->height = std::max(Height(crnt->right), Height(crnt->left)) + 1;
				int balance = Balance(crnt);
				if (balance > 1 && Balance(node->left) == -1){
					crnt->left = rotateLeft(crnt->left);
					return rotateRight(crnt);
				}
				if (balance < -1 && Balance(node->right) == 1){
					crnt->right = rotateRight(crnt->right);
					return rotateLeft(crnt);
				}
				if (balance > 1 && Balance(node->left) == 1)
					return rotateRight(crnt);
				if (balance < -1 && Balance(node->right) == -1)
					return rotateLeft(crnt);
				return crnt;
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
				insert(first, last);
			}

			map (const map& x){
				iterator it = x.begin();
				iterator it2 = x.end();
				this->insert(it, it2);
				return *this;
			}

			~map(){ deleteAll(); }

			void print2D() {
			  std::cout << "Tree:" << std::endl;
			  print2DUtil(node, 0);
			}

			 void print2DUtil(Node *root, int space) {
			  if (root == NULL) return;
			  space += 10;
			  print2DUtil(root->right, space);
			  std::cout << std::endl;
			  for (int i = 10; i < space; i++) std::cout << " ";
			  std::cout << root->all.second << "(" << Balance(root) << ")" << std::endl;
				for (int i = 10; i < space; i++) std::cout << " ";
			  print2DUtil(root->left, space);
			}

			void check_add(key_type key){
				mapped_type it = search(key)->all;
				bool ok = false;
				for (size_t i = 0; i < _size; i++){
					if (sorted[i].first == it->first){
						sorted[i].second = it->second;
						ok = true;
					}
				}
				if (ok)
					return ;
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
				if (search(val.first))
					ok = true;
				insert(val.first, val.second);
				return ft::make_pair<iterator,bool>(iterator(search(val.second), ok));
			}

			value_type &insert(key_type key, T value){
				size_t tmp = _size;
				bool ok = false;
				(void)ok;
				if (search(key) == nullptr){
					ok = true;
				}
				node = insertAVL(node, key, value);
				if (tmp == 0 && _size == 1){
					sorted = _alloc.allocate(1);
					sorted[0] = node->all;
				}
				else if (tmp < _size){
					value_type* newArray = _alloc.allocate(_size);
					if (tmp > 0) {
						for (size_t i = 0; i < tmp; i++)
							newArray[i] = sorted[i];
					}
					newArray[tmp].first = key;
					newArray[tmp].second = value;
					if (tmp > 0) {
						_alloc.deallocate(sorted, tmp);
					}
					sorted = newArray;
					for (size_t i = 0; i < _size - 1; i++){
						if (_comp(key, sorted[i].first)){
							for (size_t j = _size; j > i; j--){
								sorted[j] = sorted[j - 1];
							}
							sorted[i] = search(key)->all;
							break ;
						}
					}
				}
				else{
					for (size_t i = 0; i < _size; i++){
						if (sorted[i].first == key){
							sorted[i].second = value;
							break ;
						}
					}
				}
				return search(key)->all;
			}

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

			Node *search(key_type key){
				searched = nullptr;
				parent = nullptr;
				search_N(node, key);
				return searched;
			}

			void deleteit(key_type key){
				node = Remove(node, key);
			}

			void deleteAll(){
				delete_node(node);
				_alloca.deallocate(node, 1);
			}

			void delete_node(Node *nodes){
				if (nodes->right){
					delete_node(nodes->right);
					_alloca.deallocate(nodes->right, 1);
				}
				if (nodes->left){
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

			iterator upper_bound (const key_type& k){
				iterator it = begin();
				iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
			}

			const_iterator upper_bound (const key_type& k) const{
				const_iterator it = begin();
				const_iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
			}

			iterator lower_bound (const key_type& k){
				iterator it = begin();
				iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
			}

			const_iterator lower_bound (const key_type& k) const{
				const_iterator it = begin();
				const_iterator it2 = end();
				for (;it != it2; it++){
					if (_comp(k, it->first)){
						return it;
					}
				}
			}

			iterator begin(){
				return (iterator(&(*sorted)));
			}

			const_iterator begin() const{
				return (const_iterator(&(*sorted)));
			}

			iterator end(){
				return (iterator(&(sorted[this->_size])));
			}

			const_iterator end() const{
				return (const_iterator(&(sorted[this->_size])));
			}

			reverse_iterator rbegin(void) {
				return (reverse_iterator(iterator(&(sorted[this->_size]))));
			}

			const_reverse_iterator rbegin(void) const {
				return (const_reverse_iterator(const_iterator(&(sorted[this->_size]))));
			}

			reverse_iterator rend(void) {
				return (reverse_iterator(iterator(&(*sorted))));
			}

			const_reverse_iterator rend(void) const {
				return (const_reverse_iterator(const_iterator(&(*sorted))));
			}
	};
}

#endif