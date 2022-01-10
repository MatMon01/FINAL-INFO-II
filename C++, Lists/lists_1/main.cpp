#include <iostream>

///NOTE (7/1/2022): Simple program with a list implementation and some useful methods.



class Node {
    public: //It is unnecessary to make the contents of each node private since it won't be possible to access them without using the list
        Node *next_node;
        static int counter;
        int id;
        int content;
        Node(int);
        ~Node();
        int get_content();
};

int Node :: counter = 0;

Node :: Node(int buffer)
{
    content=buffer;
    id=counter;
    counter++;
}

Node :: ~Node()
{
    std::cout<<"Deleting: "<<id<<" content: "<<content<<"\n";
    getchar();
}

int Node :: get_content()
{
    return content;
}

class List {
    private:
        Node * start;
        void add_node(Node *);
        Node * search_node(int);
        void delete_node(Node *);
        Node * minimum();
        Node * maximum();
        void recursive_scan(Node *);
        void unlink(Node *);
    public:
        List();
        ~List();
        void new_node(int);
        void find_node(int);
        void remove_node(int);
        void order_nodes();
        void show_minimum();
        void show_maximum();
        void insert_node(int);
        void show_list();
        void show_backwards();
};

List :: List()
{
    start=NULL;
}

List :: ~List()
{
    Node * scan_ptr=start, *del_ptr;

    std::cout<<"\nDeleting list\n";

    while(scan_ptr)
    {
        del_ptr=scan_ptr;
        scan_ptr=scan_ptr->next_node;
        delete del_ptr;
    }
}

void List :: new_node(int node_content)
{
    Node * new_node_ptr;

    new_node_ptr = new Node(node_content);

    add_node(new_node_ptr);
}

void List :: add_node(Node * new_node_ptr) //the new node is linked at the beginning of the list
{
    new_node_ptr->next_node = start;
    start = new_node_ptr;
}

void List :: find_node(int node_content)
{
    if(search_node(node_content))
        std::cout<<"Node found\n";
    else
        std::cout<<"Node not found\n";
}

Node * List :: search_node(int node_content)
{
    Node * scan_ptr = start;

    while(scan_ptr)
    {
        if(scan_ptr->content==node_content)
            return scan_ptr;
        scan_ptr = scan_ptr->next_node;
    }

    return NULL;
}

void List :: remove_node(int node_content)
{
    Node * del_ptr;

    del_ptr = search_node(node_content);
    if(del_ptr)
        delete_node(del_ptr);
}

void List :: delete_node(Node * del_ptr)
{
    Node * scan_ptr=start;

    if(start==del_ptr)
    {
        start=del_ptr->next_node;
        delete del_ptr;
        return;
    }

    while(scan_ptr->next_node!=del_ptr && scan_ptr)
    {
        scan_ptr=scan_ptr->next_node;
    }
    if(scan_ptr)
    {
        scan_ptr->next_node=del_ptr->next_node; //del_ptr->next_node == (scan_ptr->next_node)->next_node
        delete del_ptr;
    }
}

void List :: show_minimum()
{
    if(start)
        std::cout<<"The lowest number is "<<(minimum()->content)<<"\n";
}

Node * List :: minimum()
{
    Node * scan_ptr=start, * min_ptr=start;

    while(scan_ptr)
    {
        if(min_ptr->content>scan_ptr->content)
            min_ptr=scan_ptr;
        scan_ptr=scan_ptr->next_node;
    }
    return min_ptr;
}

void List :: show_maximum()
{
    if(start)
        std::cout<<"The highest number is "<<(maximum()->content)<<"\n";
}

Node * List :: maximum()
{
    Node * scan_ptr=start, * max_ptr=start;

    while(scan_ptr)
    {
        if(max_ptr->content<scan_ptr->content)
            max_ptr=scan_ptr;
        scan_ptr=scan_ptr->next_node;
    }
    return max_ptr;
}

void List :: order_nodes() //The nodes are sorted from smallest to greatest value
{
    Node * node_ptr, * aux_start_ptr=NULL;

    while(start)
    {
        node_ptr=maximum();
        unlink(node_ptr);
        std::cout<<node_ptr<<" "<<node_ptr->content<<" \n";
        node_ptr->next_node=aux_start_ptr;
        aux_start_ptr=node_ptr;
    }
    start=aux_start_ptr;
}

void List :: unlink(Node * node_ptr) //In this implementation we assume that node_ptr is in the list. If this wasn't the case we would have to check if scan_ptr becomes NULL
{
    Node * scan_ptr=start;

    if(start==node_ptr)
    {
        start=node_ptr->next_node;
        return;
    }

    while(scan_ptr->next_node != node_ptr)
    {
        scan_ptr=scan_ptr->next_node;
    }

    scan_ptr->next_node=node_ptr->next_node;
}

void List :: insert_node(int node_content)
{
    Node * prev_ptr=NULL, * scan_ptr=start, * node_ptr;
    node_ptr = new Node(node_content);

    if(!start)
    {
        node_ptr->next_node=NULL;
        start=node_ptr;
        return;
    }


    while(scan_ptr)
    {
        if(scan_ptr->content < node_ptr->content)
        {
            prev_ptr=scan_ptr;
            scan_ptr=scan_ptr->next_node;
        }
        else
        {
            if(prev_ptr)
            {
                prev_ptr->next_node=node_ptr;
                node_ptr->next_node=scan_ptr;
                return;
            }
            else
            {
                node_ptr->next_node=start;
                start=node_ptr;
                return;
            }
        }
    }
    node_ptr->next_node=NULL;
    prev_ptr->next_node=node_ptr;

}

void List :: show_list()
{
    Node * scan_ptr=start;

    while(scan_ptr)
    {
        std::cout<<scan_ptr->id<<" content: "<<scan_ptr->content<<"\n";
        scan_ptr=scan_ptr->next_node;
    }
}

void List :: show_backwards()
{
    if(!start)
    {
        std::cout<<"Empty list\n";
        return;
    }
    recursive_scan(start->next_node);
    std::cout<<start->id<<" content "<<start->content<<"\n";
}

void List :: recursive_scan(Node * scan_ptr) //This is one of many possible implementations of this function, using recursion
{
    if(scan_ptr)
    {
        recursive_scan(scan_ptr->next_node);
        std::cout<<scan_ptr->id<<" content "<<scan_ptr->content<<"\n";
    }
}

int main()
{
    List number_list;
    int counter, num_buf;

    for(counter=0;counter<10;counter++)
    {
        number_list.new_node(rand()%100 + 1);
    }

    number_list.show_list();

    std::cout<<"Type a number to find out whether it is the list or not: ";
    std::cin>>num_buf;
    number_list.find_node(num_buf);
    number_list.show_backwards();
    number_list.show_maximum();
    number_list.show_minimum();
    number_list.order_nodes(); // It explodes here
    number_list.show_list();
    std::cout<<"Type a number to insert it in the list: ";
    std::cin>>num_buf;
    number_list.insert_node(num_buf);
    number_list.show_list();
    std::cout<<"Type a number to remove it from the list: ";
    std::cin>>num_buf;
    number_list.remove_node(num_buf);
    number_list.show_list();

    return 0;
}
