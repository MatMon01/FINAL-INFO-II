#include <iostream>

#define TRUE 1
#define FALSE 0

class Stack{
    public:
        Stack(int);
        void push(int);
        int pull();
    private:
        int *numStack;
        int *stackPtr;
        int maxElements;
};

Stack::Stack(int total_elements)
{
    numStack=new int[total_elements];
    stackPtr=numStack;
    maxElements=total_elements;
}

void Stack::push(int new_number)
{
    if(stackPtr==numStack+maxElements){
        std::cout<<"ERROR: Stack is full\n";
        return;
    }
    *stackPtr=new_number;
    stackPtr++;
}

int Stack::pull()
{
    if(stackPtr==numStack){
        std::cout<<"ERROR: Stack is empty\n";
        return 0;
    }
    stackPtr--;
    return *stackPtr;
}

//-----------------------------------------------------------------------------------------------------
class CircularQueue{
    public:
        CircularQueue(int);
        void push(int);
        int pull(void);
    private:
        int *numQueue;
        int *inputPtr;
        int *outputPtr;
        int fullFlag, emptyFlag;
        int maxElements;
};

CircularQueue::CircularQueue(int total_elements)
{
    numQueue=new int[total_elements];
    inputPtr=outputPtr=numQueue;
    maxElements=total_elements;
    emptyFlag=TRUE;
}

void CircularQueue::push(int new_number)
{
    if(fullFlag){
        std::cout<<"ERROR: Queue full\n";
        return;
    }

    *inputPtr=new_number;
    inputPtr++;

    if(inputPtr==numQueue+maxElements){
        inputPtr=numQueue;
    }

    emptyFlag=FALSE; //If the Q was empty before it no longer is since we pushed an element

    if(inputPtr==outputPtr){
        fullFlag=TRUE; //If after increasing inputPtr it is equal to outputPtr then the Q is full
    }
}

int CircularQueue::pull()
{
    int number;

    if(emptyFlag){
        std::cout<<"ERROR: Queue empty\n";
        return 0;
    }

    number=*inputPtr;
    inputPtr++;

    if(inputPtr==numQueue+maxElements){
        inputPtr=numQueue;
    }

    fullFlag=FALSE; //If the Q was full before it no longer will be since we are about to pull an element

    if(inputPtr==outputPtr){
        emptyFlag=TRUE; //If after increasing outputPtr it is equal to inputPtr then the Q is empty
    }

    return number;
}

//-----------------------------------------------------------------------------------------------------
class TreeBranch{
    public:
        TreeBranch(int);
        TreeBranch *leftBranch;
        TreeBranch *rightBranch;
        int number;
};

TreeBranch::TreeBranch(int new_number)
{
    number=new_number;
}

class Tree{
    public:
        Tree();
        void viewTree();
        void addBranch(int);
    private:
        TreeBranch *root;
        void findPlace(TreeBranch *, TreeBranch *, TreeBranch *);
        void showBranches(TreeBranch *);
};

Tree::Tree()
{
    root=NULL;
}

void Tree::addBranch(int new_number)
{
    TreeBranch *new_branch=new TreeBranch(new_number);

    new_branch->leftBranch=NULL;
    new_branch->rightBranch=NULL;

    if(!root){
        root=new_branch;
        return;
    }

    findPlace(root, root, new_branch);
}

void Tree::findPlace(TreeBranch * parent_branch, TreeBranch * child_branch, TreeBranch * new_branch)
{
    if(!child_branch){
        if(parent_branch->number > new_branch->number)
            parent_branch->leftBranch=new_branch;
        else{
            parent_branch->rightBranch=new_branch;
        }
        return;
    }

    if(child_branch->number > new_branch->number){
        findPlace(child_branch, child_branch->leftBranch, new_branch);
    }
    else{
        findPlace(child_branch, child_branch->rightBranch, new_branch);
    }
}

void Tree::viewTree()
{
    if(root){
        showBranches(root);
    }
    std::cout<<"\n";
}

void Tree::showBranches(TreeBranch * branch)
{
    if(branch->leftBranch){
        showBranches(branch->leftBranch);
    }
    std::cout<<"\t"<<branch->number;
    if(branch->rightBranch){
        showBranches(branch->rightBranch);
    }
}


int main()
{
    int counter, number;
    Stack stack_obj(10);
    CircularQueue Q_obj(10);
    Tree tree_obj;

    std::cout<<stack_obj.pull()<<"\n";
    std::cout<<Q_obj.pull()<<"\n\n";

    for(counter=0;counter<10;counter++){
        number=rand()%10+1;
        std::cout<<number<<", ";
        stack_obj.push(number);
        Q_obj.push(number);
        tree_obj.addBranch(number);
    }
    std::cout<<"\n\n";
    stack_obj.push(11);
    Q_obj.push(11);

    std::cout<<"Stack:\n";
    for(counter=0;counter<10;counter++){
        std::cout<<stack_obj.pull()<<"\t";
    }
    std::cout<<"\n\n";

    std::cout<<"Q:\n";
    for(counter=0;counter<10;counter++){
        std::cout<<Q_obj.pull()<<"\t";
    }
    std::cout<<"\n\n";

    std::cout<<"Tree:\n";
    tree_obj.viewTree();

    return 0;
}
