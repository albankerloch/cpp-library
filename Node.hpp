#ifndef DEF_NODE_HPP
# define DEF_NODE_HPP

# include <iostream>

namespace ft 
{
	template <class Data_T>
    class Doubly_Linked_Node 
    {
        public :

            Doubly_Linked_Node  *m_previous;
            Doubly_Linked_Node  *m_next;
            Data_T              data;

          
            Doubly_Linked_Node()
            :
                m_previous(u_nullptr),
                m_next(u_nullptr)
            {}

     
            Doubly_Linked_Node(const Data_T& val)
            :
                m_previous(u_nullptr),
                m_next(u_nullptr),
                data(val)
            {}

       
            Doubly_Linked_Node(const Data_T& val,
                Doubly_Linked_Node *previous, Doubly_Linked_Node *next)
            :
                m_previous(previous),
                m_next(next),
                data(val)
            {}
    };

	
    template<typename T >
    class Node
    {
		public:

			T					data;
			Node				*m_previous;
			Node				*m_next;

			Node(): data(0), m_previous(0), m_next(0) {}
			
			Node(T const & elem): m_previous(0), data(elem), m_next(0) {}

			Node(T const & elem, Node *m_previousious, Node *m_next):  data(elem), m_previous(m_previousious), m_next(m_next) {}

			/*Node(Node const & Node_to_Copy)
			{
				*this = src;
			}

			Node &operator=(Node const & Node_to_Copy)
			{
				this->data = Node_to_Copy.data;
				this->m_next = Node_to_Copy.m_next;
				this->m_previous = Node_to_Copy.m_previous;

				return (*this);
			};*/
			
			virtual ~Node() {}
	};
}

#endif