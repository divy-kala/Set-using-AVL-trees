#include <iostream>
#include <bits/stdc++.h>
using namespace std;


class node
{
public:
    node(long key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 0;
        parent=NULL;
        size = 1;
    }

    node(long key, node * par)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = par;
        height = 0;
        size = 1;
        //set left or right child of parent yourself
    }

    long Getkey()
    {
        return key;
    }
    void Setkey(long val)
    {
        key = val;
    }
    long Getsize()
    {
        return size;
    }
    void Updatesize() {
         if(Getleft() == nullptr && Getright() == nullptr)
            size = 1;
        else if(Getleft() == nullptr)
            size = Getright()->Getsize() + 1;
        else if(Getright() == nullptr)
            size = Getleft()->Getsize() + 1;
        else
        {
            long x = Getright()->Getsize();
            long y = Getleft()->Getsize();
            Setsize(x+y+1);
        }

    }
    void Setsize(long val)
    {
        size = val;
    }
    node * Getleft()
    {
        return left;
    }
    void Setleft(node * val)
    {
        left = val;     //does not affect parents
    }
    node * Getright()
    {
        return right;
    }
    void Setright(node * val)
    {
        right = val;    //does not affect parents
    }
    long Getht()
    {
        return height;
    }
    void Setht(long val)
    {
        height = val;
    }
    node * Getpar ()
    {
        return parent;
    }
    void Setpar(node * par, node *cur) //new parent for this, and make it the same direction child as cur
    {
        if(par == nullptr)
        {
            this->parent = nullptr;

        }
        else if( par->Getright() == cur)
        {
            par->Setrchild(this);
        }
        else if (par->Getleft () == cur)
        {
            par->Setlchild(this);
        }
        else
        {
            cerr << "In Setpar, cur is not the child of parent";
        }

    }

    void Setpar (node * par) {
        this -> parent = par;


    }
    void Setlchild (node * ch)
    {

        left = ch;
        if(ch == nullptr)
            return;
        ch->parent = this;


    }
    void Setrchild (node * ch)
    {

        right = ch;
        if(ch == nullptr)
            return;
        ch->parent = this;

    }

    void updateht ()
    {
        if(Getleft() == nullptr && Getright() == nullptr)
            height = 0;
        else if(Getleft() == nullptr)
            height = Getright()->Getht() + 1;
        else if(Getright() == nullptr)
            height = Getleft()->Getht() + 1;
        else
        {
            int x = Getright()->Getht();
            int y = Getleft()->Getht();
            height = max (x, y) + 1;
        }

    }


protected:

private:
    long key;
    long size;
    node * left;
    node * right;
    node * parent;
    int height;

};


class avl_tree
{
public:
    avl_tree()
    {
        this->root = nullptr;
    }


    avl_tree(node * root)
    {
        this->root = root;
    }

    node * Getroot()
    {
        return root;
    }
    void Setroot(node * val)
    {
        root = val;
    }


    bool contains (long key)
    {
        return contains_helper(key, Getroot());

    }

    bool contains_helper (long key, node * cur)
    {
        if(cur == NULL)
        {
            return false;
        }
        else if(cur->Getkey() == key)
        {
            return true;
        }
        else if (cur->Getkey() > key)
        {
            contains_helper (key, cur->Getleft() );
        }
        else if (cur->Getkey() < key)
        {
            contains_helper (key, cur->Getright() );
        }
    }

    void print_inorder ()
    {

        print_inorder_helper(Getroot());

    }
    void print_inorder_helper (node * cur) {
        if(cur == nullptr)
            return;
        print_inorder_helper (cur->Getleft());
       // cout << cur->Getkey() << "(" << cur->Getsize() <<")  ";
        cout << cur->Getkey() << "(" << cur->Getht() << ")  ";
        print_inorder_helper(cur->Getright());
    }

    void insert (long key)
    {
        insert_helper (key, root);


    }

    void insert_helper (long key, node * cur )
    {
        if(cur == NULL)
        {
            root = new node (key);
            cur = root;

        }
        else if(cur->Getkey() == key)
        {
            return;
        }
        else if (cur->Getkey() > key)
        {
            //left
            if(cur->Getleft() == NULL)
            {
                node * child = new node (key, cur);
                cur->Setlchild(child);

            }
            else
                insert_helper (key, cur->Getleft() );

            int x;
            if( cur->Getright() == nullptr)
                x = cur->Getleft()->Getht() + 1;
            else
                x = cur->Getleft()->Getht() - cur->Getright()->Getht() ;

            //TODO:Handle this for when duplicates are allowed make sure duplicate insertions are done on left, then for LL case it beocmes >=
            if(x > 1)
            {
                if(cur->Getleft()->Getkey() > key)
                {
                    //RL
                    LL(cur);
                }
                else if (cur->Getleft()->Getkey() < key)
                {
                    LR(cur);
                }
            }


        }
        else if (cur->Getkey() < key)
        {
            //go right
            if(cur->Getright() == NULL)
            {
                //insert if right does not exist
                node * child = new node (key, cur);
                cur->Setrchild(child);

            }
            else
                insert_helper (key, cur->Getright() );
            int x;
            if( cur->Getleft() == nullptr)
                x = cur->Getright()->Getht() + 1;
            else
                x = cur->Getright()->Getht() - cur->Getleft()->Getht()  ;
            //TODO:Handle this for when duplicates are allowed
            if(x > 1)
            {
                if(cur->Getright()->Getkey() > key)
                {
                    //RL
                    RL(cur);
                }
                else if (cur->Getright()->Getkey() < key)
                {
                    RR(cur);
                }
            }


        }

        cur->Updatesize();
        cur->updateht();

    }
    long curclosest;
    long closest (long key)
    {
        curclosest= Getroot()->Getkey();
        return closest_helper(key, Getroot());

    }
    long closest_helper (long key, node * cur)
    {


        if(cur->Getkey() == key)
        {
            curclosest = key;
            return curclosest;
        }
        else if (cur->Getkey() > key)
        {

            long k= cur->Getkey();

            if( abs(k-key) <= abs(curclosest-key) )
            {
                if(abs(k-key) ==  abs(curclosest-key))
                    curclosest = k < curclosest? k : curclosest;
                else
                {
                    curclosest = k;
                }
            }

            if(cur->Getleft() != nullptr)
            {
                return closest_helper (key, cur->Getleft() );

            }
            else
            {
                return curclosest;
            }
        }
        else if (cur->Getkey() < key)
        {
            long k= cur->Getkey();
            if( abs(k-key) <= abs(curclosest-key) )
            {
                if(abs(k-key) ==  abs(curclosest-key))
                    curclosest = k < curclosest? k : curclosest;
                else
                {
                    curclosest = k;
                }

            }
            if(cur->Getright() != nullptr)
                return closest_helper (key, cur->Getright() );
            else
                return curclosest;
        }

    }
    long count_in_range;
    long count_range (long x, long y) {
        count_in_range=0;
        count_rang_helper(x,y,Getroot());
        return count_in_range;
    }
    void count_rang_helper (long x, long y, node * cur) {
        if(cur == nullptr)
            return;
        if(cur->Getkey() >= x && cur->Getkey()<=y) {
            count_in_range++;
            count_rang_helper(x,y,cur->Getleft());
            count_rang_helper(x,y,cur->Getright());

        }
         else if(cur->Getkey() < x ) {
            count_rang_helper(x,y,cur->Getright());
        }
         else if(cur->Getkey() > y ) {
            count_rang_helper(x,y,cur->Getleft());
        }

    }
    long select_largest (long KthLargest) {

        //select selects kth smallest, use it to select kth largest
        long n = root->Getsize();
        long k = n - KthLargest +1;
        return select_helper(k, Getroot());
    }

    long select (long KthSmallest) {

        return select_helper(KthSmallest, Getroot());
    }

    long select_helper (long k, node * cur) {
        long sizel1;
        if(cur->Getleft() != nullptr)
            sizel1 = cur->Getleft()->Getsize() + 1;
        else
            sizel1 = 1;
        if( sizel1 == k) {
            return cur->Getkey();

        }
        if( k < sizel1 ) {
            if(cur->Getleft() != nullptr)
                return select_helper(  k, cur->Getleft());
            else {
                exit(-1);
            }

        }
        if (k > sizel1) {
           if(cur->Getright() != nullptr)
                return select_helper( k-sizel1,  cur->Getright());
            else {
                exit(-1);
            }
        }
        return -1;

    }

    node * successor( node * ptr) {

        return successor_helper (ptr->Getright());

    }
    node *  successor_helper (node * ptr) {
        if(ptr->Getleft() == nullptr)
            return ptr;
        return successor_helper(ptr->Getleft());
    }

    int LorR (node * cur) {

        if(cur->Getpar() == nullptr) {
            return 0;                      //it is the root node
        }
        if (cur->Getpar()->Getleft() == cur) {
            return -1;                     //left
        }
        if (cur->Getpar()->Getright() == cur) {
            return 1;                       //right
        }
        return 1000;                        //error

    }

    void avl_delete (long key) {
        avl_delete_helper(key, Getroot());

    }


    void avl_delete_helper (long key, node * cur)
    {
        if(cur == NULL)
        {
            //not found case
            return;
        }
        else if (cur->Getkey() > key)
        {
            //search left
            avl_delete_helper (key, cur->Getleft() );
        }
        else if (cur->Getkey() < key)
        {
            //search right
            avl_delete_helper (key, cur->Getright() );
        }
        else if(cur->Getkey() == key)
        {
            //delete case

            int dir = LorR( cur);
            node * par;

            if(cur->Getleft() == nullptr && cur->Getright() == nullptr) {
                //delete leaf
                if(dir == -1) {
                    par = cur->Getpar();
                    par->Setleft(nullptr) ;
                    delete cur;
                }
                else if (dir == 1) {
                    par = cur->Getpar();
                    par->Setright(nullptr) ;
                    delete cur;
                }
                else if (dir == 0) {
                    Setroot(nullptr);
                    delete cur;
                }
            }
            else if (cur->Getleft() == nullptr && cur->Getright() != nullptr) {

                //delete "leaf" with 1 right child only

                if(dir == 1 || dir == -1) {
                    par = cur->Getpar();
                    node * gchild = cur->Getright();
                 //   par->Setright(gchild) ;
                    gchild->Setpar(par, cur);

                    delete cur;
                }
                else if (dir == 0) {

                    root = cur->Getright();

                    root->Setpar(nullptr);
                    delete cur;
                }
            }
            else if (cur->Getleft() != nullptr && cur->Getright() == nullptr) {

                //delete "leaf" with 1 left child only
                if(dir == 1 || dir == -1) {
                    par = cur->Getpar();
                    node * gchild = cur->Getleft();
                    gchild->Setpar(par, cur);
                    delete cur;
                }
                else if (dir == 0) {
                    root = cur->Getleft();
                    root->Setpar(nullptr);

                    delete cur;
                }

            }
            else {
                //delete internal node with 2 children
                node * succ = successor(cur);
                long succkey = succ->Getkey();
                avl_delete_helper(succ->Getkey(), cur);
                cur->Setkey(succkey);

            }

            return;
        }


            cur->updateht();
            cur->Updatesize();


            //Fix AVL tree
            int x;
            node * l = cur->Getleft();
            node * r = cur->Getright();
            if(l != nullptr && r != nullptr) {
                x = abs(l->Getht() - r->Getht() );

            }
            else if (l != nullptr || r != nullptr) {
                node * tmp = (l == nullptr ) ? r : l;
                x = tmp->Getht() + 1;

            }
            else {
                x = 0;
            }
            int lht,rht;
            lht = (l == nullptr)? -1 : l->Getht();
            rht = (r == nullptr)? -1 : r->Getht();
            if(x>=2) {
                //imbalance
                node * z = cur;

                if (lht > rht ) {
                    //left heavy cases
                    node * y = l;
                    node * x;

                    // y has both children
                    if( y->Getleft() != nullptr && y->Getright() != nullptr) {

                        if( y->Getleft()->Getht() >= y->Getright()->Getht() ) {
                            x = y->Getleft();
                            LL(z);
                        }
                        else {
                            x = y->Getright();
                            LR(z);

                        }
                    }
                    //y has only 1 child
                    else if ( y->Getleft() != nullptr || y->Getright() != nullptr ) {
                        node * x = y->Getleft() == nullptr ? y->Getright() : y->Getleft();
                        if(x == y->Getleft()) {
                            LL(z);
                        }
                        else
                            LR(z);
                    }



                else if( lht < rht) {
                    //right heavy
                    node * y = r;
                    node * x;


                    if( y->Getleft() != nullptr && y->Getright() != nullptr) {
                        if( y->Getleft()->Getht() <= y->Getright()->Getht() ) {
                            x = y->Getright();
                            RR(z);
                        }
                        else {
                            x = y->Getleft();
                            RL(z);

                        }
                    }
                    else if ( y->Getleft() != nullptr || y->Getright() != nullptr ) {
                        node * x = y->Getleft() == nullptr ? y->Getright() : y->Getleft();
                        if(x == y->Getleft()) {
                            RL(z);
                        }
                        else
                            RR(z);
                    }

                }

            }



//         cur->updateht();
//            cur->Updatesize();


        }
        cur->updateht();
        cur->Updatesize();
        return;

    }



protected:

private:
node * root;

void R( node * cur)
{
    node *p, *q, *ctemp;
    p=cur;
    q=p->Getleft();
    ctemp = q->Getright();

    q->Setpar(p->Getpar(), p);
    if(q->Getpar() == nullptr)
    {
        root =q;
    }
    q->Setrchild(p);
    p->Setlchild(ctemp);
    p->updateht();
    q->updateht();
    p->Updatesize();
    q->Updatesize();

}

void L( node * cur)
{
    node *p, *q, *ctemp;
    p=cur;
    q=p->Getright();
    ctemp = q->Getleft();

    q->Setpar(p->Getpar(), p); //TODO check precedence
    if(q->Getpar() == nullptr)
    {
        root =q;
    }
    q->Setlchild(p);
    p->Setrchild(ctemp);
    p->updateht();
    q->updateht();
    p->Updatesize();
    q->Updatesize();

}
void LL (node * p)
{
    R(p);
}
void RR (node * p)
{
    L(p);

}
void LR (node * p)
{
    L(p->Getleft());
    R(p);
}
void RL (node * p)
{
    R(p->Getright());
    L(p);
}

};

class sets
{
    public:
    avl_tree avl;

    void insert( long key ) {
        avl.insert(key);

    }
    void remove (long key) {
        avl.avl_delete(key);
    }
    bool contains( long key) {
        return avl.contains(key);
    }
    long closest (long key) {
        return avl.closest(key);
    }
    long find_kth_largest(long k) {
        return avl.select_largest(k);
    }
    long range (long a, long b) {
        return avl.count_range(a,b);
    }
};

int main()
{
//    avl_tree avl;


    //avl.print_inorder(avl.Getroot());

//    long n ;
//    cin >> n;
//    vector<long> input;
//    for (long i = 0 ; i < n; i++) {
//        long x;
//        cin >> x;
//        input.push_back(x);
//    }
//    for (long i = 0 ; i < n; i++) {
//        long x = input[i];
//        avl.insert(x);
//
//        cout << endl;
//    }
//    avl.print_inorder();
//    getchar();
//    getchar();
//     cout << "\n\n\n*********************deletion***********************\n\n\n" ;
//
//    for (long i = n-1 ; i >=0; i--) {
//        long x = input[i];
//        avl.avl_delete(x);
//
//        cout << endl;
//    }
//    avl.print_inorder();
    sets s;
    long n ;
    cin >> n;
    vector<long> input;
    for (long i = 0 ; i < n; i++) {
        long x;
        cin >> x;
        input.push_back(x);
    }

    for (long i = 0 ; i < n; i++) {
        long x = input[i];
        s.insert(x);

    }
    s.avl.print_inorder();
    cout << "height of the tree is " << s.avl.Getroot()->Getht();
    cout << endl << s.contains(99999) << " " << s.contains(-5);
    cout << endl << s.closest(150000) << " " << s.find_kth_largest(1) << " " << s.range(0,5);
    getchar();
    getchar();
     cout << "\n\n\n*********************deletion***********************\n\n\n" ;

    for (long i = n-1 ; i >=10; i--) {
        long x = input[i];
        s.remove(x);

    }
    s.avl.print_inorder();
//  cout << "height of the tree is " << s.avl.Getroot()->Getht();
    return 0;
}
