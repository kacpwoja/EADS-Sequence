/************************
*	Kacper Wojakowski	*
*	kwojakow	293064	*
************************/

#ifndef SEQUENCE
#define SEQUENCE

#include <iostream>
#include <new>

template <typename Key, typename Info>
class Sequence
{
private:
        template <typename NKey, typename NInfo>
        struct Node
        {
            NKey key;
            NInfo info;
            Node<NKey, NInfo> *next;

            Node(): key(), info(), next( nullptr ) {};
            Node( const NKey &k, const NInfo &i): key( k ), info( i ), next( nullptr ) {};
        };

        Node<Key, Info> *head;

		/***************************************************
		*Private methods used to support the public methods*
		***************************************************/
        void printNode( const Node<Key, Info> *node, std::ostream &os ) const;
		//Prints a single node into an output stream
        void printBack( const Node<Key, Info> *curr, std::ostream &os ) const;
		//Prints the list into an output stream in reverse order

public:
	/*****************************************************************************
	*   Default Constructor, Copy Constructor, Assignment Operator, Destructor   *
	*****************************************************************************/
	Sequence(): head( nullptr ) {};
	Sequence( const Sequence<Key, Info> &seq ): head( nullptr ) { *this = seq; };
	Sequence<Key, Info>& operator=( const Sequence<Key, Info> &rhs );
    ~Sequence();

	/*****************************************************************************
	*		 Adding, removing and getting elements from the front and back	     *
	*****************************************************************************/

	//Adds an element to the front
	//Parameters:	Key and Info of the new element
	//Returns:		void
    void pushFront( const Key &key, const Info &info );

	//Adds an element to the back
	//Parameters:	Key and Info of the new element
	//Returns:		void
    void pushBack( const Key &key, const Info &info );

	//Deletes the first element
	//Parameters:	none
	//Returns:		Info of the deleted element
    Info popFront();

	//Deletes the last element
	//Parameters:	none
	//Returns:		Info of the deleted element
    Info popBack();

	//Returns the first element
	//Parameters:	none
	//Returns:		Info of the first element
	Info front() const;

	//Returns the last element
	//Parameters:	none
	//Returns:		Info of the last element
	Info back() const;

	/*****************************************************************************
	*			 Adding, removing, getting and searching elements by Key	     *
	*****************************************************************************/

	//Inserts a new element after a specified location
	//Parameters:	Location Key after which to insert the element, the Key and Info of the new element,
	//				and the number of the exact occurence of location Key (defaults to 1)
	//Returns:		True if successful, false otherwise
    bool insertAfter( const Key &location, const Key &newKey, const Info &newInfo, int occurence = 1 );

	//Removes a specified element
	//Parameters:	Key and the exact occurence of the element to delete
	//Returns:		True if successful, false otherwise
    bool removeByKey( const Key &location, int occurence = 1 );

	//Retrieves Info of a specific element
	//Parameters:	Key and exact occurence (defaults to 1) of the element to retrieve
	//Returns:		Info of the specified element
    Info getInfo( const Key &key, int occurence = 1 );

	//Searches for a given key
	//Parameters:	Key to search for
	//Returns:		True if the Key exists, false otherwise
	bool search( const Key &key ) const;

	/*****************************************************************************
	*				  Functions to operate the list by indexes???			 	 *
	*				(might be useful for shuffle without iterators)				 *
	*****************************************************************************/

	//Retrieves the element specified by an index
	//Parameters:	Index to be retrieved from, variables of type Key and Info to store the result in
	//Returns:		True if index is within the size of the sequence, false otherwise.
    bool getNode( int index, Key &key, Info &info ) const;

	//Removes the element specified by an index
	//Parameters:	Index to be removed
	//Returns:		True if successful, false otherwise
	bool removeByIndex( int index );

	/*****************************************************************************
	*							Other general methods						  	 *
	*****************************************************************************/

	//Clears the sequence
	//Parameters:	none
	//Returns:		void
    void clear();

	//Returns the number of elements in the sequence
	//Parameters:	none
	//Returns:		Number of elements stored in the sequence
    int length() const;

	//Checks if the sequence is empty
	//Parameters:	none
	//Returns:		True if empty, false otherwise
    bool isEmpty() const;

	/*****************************************************************************
	*							Merging two sequences						  	 *
	*****************************************************************************/

	//Merges two sequences together
	//Parameters:	Sequence to merge at the end
	//Returns:		New sequence achieved by merging
    Sequence<Key, Info> merge( const Sequence<Key, Info> &seq ) const;

	//Merging defined as the + operator
	Sequence<Key, Info> operator+( const Sequence<Key, Info> &rhs ) const { return this->merge( rhs ); };
	Sequence<Key, Info>& operator+=( const Sequence<Key, Info> &rhs ) { *this = *this + rhs; return *this; };

	/*****************************************************************************
	*								Logical operators						  	 *
	*****************************************************************************/

	//Comparing two sequences
	//Parameters:	The sequence to compare to
	//Returns:		True if identical, false otherwise
    bool operator==( const Sequence<Key, Info> &rhs ) const;

	//Comparing two sequences
	//Parameters:	The sequence to compare to
	//Returns:		True if not identical, false otherwise
	bool operator!=( const Sequence<Key, Info> &rhs ) const { return !( *this == rhs ); };

	/*****************************************************************************
	*								Display methods							  	 *
	*****************************************************************************/

	//Prints the list into an output stream
	//Parameters:	Output stream
	//Returns:		void
    void print( std::ostream &os = std::cout ) const;

	//Prints the list backwards into an output stream
	//Parameters:	Output stream
	//Returns:		void
	void printBackwards( std::ostream &os = std::cout ) const;
};

template<typename Key, typename Info>
inline void Sequence<Key, Info>::printNode( const Node<Key, Info> *node, std::ostream &os ) const
{
	os << "Key: " << node->key << " Info: " << node->info << std::endl;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printBack( const Node<Key, Info> *curr, std::ostream &os ) const
{
	if( curr == nullptr )
		return;

	printBack( curr->next, os );
	printNode( curr, os );
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=( const Sequence<Key, Info>& rhs )
{
	if( this == &rhs )
		return *this;

	clear();

	auto current = rhs.head;
	while( current != nullptr )
	{
		this->pushBack( current->key, current->info );
		current = current->next;
	}

	return *this;
}

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
	clear();
}

template<typename Key, typename Info>
void Sequence<Key, Info>::pushFront( const Key &key, const Info &info )
{
	auto newNode = new Node<Key, Info>( key, info );
	newNode->next = head;
	head = newNode;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::pushBack( const Key &key, const Info &info )
{
	//If the list is empty, add the element at the front
	if( head == nullptr )
	{
		pushFront( key, info );
		return;
	}
	//Otherwise, find the last element
	auto current = head;
	while( current->next != nullptr )
	{
		current = current->next;
	}
	//Then add a new one at the back
	auto newNode = new Node<Key, Info>( key, info );
	newNode->next = nullptr;
	current->next = newNode;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::popFront()
{
	//If the sequence is empty, return a default Info
	if( head == nullptr )
		return Info();
	//Take the Info out of the first element
	auto out = head->info;
	//Delete the element
	auto temp = head;
	head = head->next;
	delete temp;
	//Return the Info
	return out;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::popBack()
{
	//If the sequence is empty, return a default Info
	if( head == nullptr )
		return Info();
	//If there is only one element, remove it from the front
	auto current = head;
	if( current->next == nullptr )
		return popFront();
	//Otherwise, find the last element
	while( current->next->next != nullptr )
	{
		current = current->next;
	}
	//Take the value of Info and remove the element
	auto out = current->next->info;
	delete current->next;
	current->next = nullptr;
	//Return the obtained Info
	return out;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::front() const
{
	//If the sequence is empty, return a default Info
	if( head == nullptr )
		return Info();

	return head->info;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::back() const
{
	//If the sequence is empty, return a default Info
	if( head == nullptr )
		return Info();

	//Finding the last element
	auto current = head;
	while( current->next != nullptr )
	{
		current = current->next;
	}
	
	return current->info;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::insertAfter( const Key &location, const Key &newKey, const Info &newInfo, int occurence )
{
	//The occurence can't be lower than 1, incorrect data entered
	if( occurence < 1 )
		return false;

	auto current = head;
	int occ = 0;
	//Searching for the specified element and adding a new one
	while( current != nullptr )
	{
		if( current->key == location && ++occ == occurence )
		{
			auto newNode = new Node<Key, Info>( newKey, newInfo );
			newNode->next = current->next;
			current->next = newNode;
			return true;
		}
		current = current->next;
	}

	return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeByKey( const Key &location, int occurence )
{
	//The occurence can't be lower than 1, incorrect data entered
	if( occurence < 1 )
		return false;
	//Can't find an element in an empty sequence
	if( head == nullptr )
		return false;

	int occ = 0;
	//If the first element is the correct one, delete it
	if( head->key == location && ++occ == occurence )
	{
		popFront();
		return true;
	}

	auto current = head->next;
	auto previous = head;
	//Otherwise, find the correct element
	while( current != nullptr )
	{
		if( current->key && ++occ == occurence )
		{
			previous->next = current->next;
			delete current;
			return true;
		}
		//Traversing
		previous = current;
		current = current->next;
	}

	return false;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::getInfo( const Key &key, int occurence )
{
	//Occurence can't be lower than 1, incorrect data
	if( occurence < 1 || head == nullptr )
		return Info();

	auto current = head;
	int occ = 0;
	//Finding the element
	while( current != nullptr )
	{
		if( current->key == key && ++occ == occurence )
			return current->info;

		current = current->next;
	}
	//If it can't be found, return default Info()
	return Info();
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::search( const Key &key ) const
{
	//Finding the element
	auto current = head;
	while( current != nullptr )
	{
		if( current->key == key )
			return true;

		current = current->next;
	}

	return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::getNode( int index, Key &key, Info &info ) const
{
	//Index can't be lower than 0, incorrect data
	if( index < 0 )
		return false;

	auto current = head;
	int i = 0;

	while( current != nullptr )
	{
		if( i == index )
		{
			key = current->key;
			info = current->info;
			return true;
		}

		current = current->next;
		i++;
	}

	return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeByIndex( int index )
{
	//Index can't be lower than 0, incorrect data
	if( index < 0 )
		return false;
	//Can't delete from an empty list
	if( head == nullptr )
		return false;
	//If index = 0 delete the first element
	if( index == 0 )
	{
		popFront();
		return true;
	}
	//Otherwise, find the correct index
	int i = 1;
	auto current = head->next;
	auto previous = head;

	while( current != nullptr )
	{
		if( i == index )
		{
			previous->next = current->next;
			delete current;
			return true;
		}

		previous = current;
		current = current->next;
		i++;
	}

	return false;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::clear()
{
	while( head != nullptr )
	{
		auto temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename Key, typename Info>
int Sequence<Key, Info>::length() const
{
	int out = 0;

	auto current = head;
	//Counting elements
	while( current != nullptr )
	{
		out++;
		current = current->next;
	}

	return out;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty() const
{
	if( head == nullptr )
		return true;

	return false;
}

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::merge( const Sequence<Key, Info> &seq ) const
{
	//Creating copies of sequences to merge
	auto lhs( *this );

	auto current = seq.head;
	while( current != nullptr )
	{
		lhs.pushBack( current->key, current->info );
		current = current->next;
	}
	return lhs;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator==( const Sequence<Key, Info> &rhs ) const
{
	if( head == nullptr && rhs.head == nullptr )
		return true;

	if( length() != rhs.length() )
		return false;

	auto left = head;
	auto right = head;
	while( left != nullptr && right != nullptr )
	{
		if( left->key != right->key || left->info != right->info )
			return false;

		left = left->next;
		right = right->next;
	}

	return true;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::print( std::ostream &os ) const
{
	os << "Contents of the sequence: " << std::endl;
	auto current = head;
	while( current != nullptr )
	{
		printNode( current, os );
		current = current->next;
	}
	os << "End of the sequence." << std::endl;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printBackwards( std::ostream &os ) const
{
	os << "Contents of the sequence backwards:" << std::endl;
	printBack( head, os );
	os << "End of the sequence." << std::endl;
}

#endif