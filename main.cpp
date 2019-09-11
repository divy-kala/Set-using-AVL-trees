#include <iostream>

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
    }
    node(long key, node * par)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = par;
        height = 0;
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
        contains_helper(key, Getroot());

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

    void print_inorder (node * cur)
    {

        if(cur == nullptr)
            return;
        print_inorder (cur->Getleft());
        cout << cur->Getkey() << "(" << cur->Getht() <<")  ";
        print_inorder(cur->Getright());

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
            //TODO:Handle this for when duplicates are allowed
            if(x > 1)
            {
                if(cur->Getleft()->Getkey() > key)
                {
                    //RL
                    LL(cur);
                }
                else if (cur->Getright()->Getkey() < key)
                {
                    LR(cur);
                }
            }

        }
        else if (cur->Getkey() < key)
        {
            if(cur->Getright() == NULL)
            {
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
        int asd= cur->Getkey();
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

};

int main()
{
    avl_tree avl;
//    avl.insert(5);
//    avl.insert(1);
//    avl.insert(7);
//    avl.insert(51);
//    avl.insert(12);
//    avl.insert(73);
//    avl.insert(56);
//    avl.insert(14);
//    avl.insert(71);
//    avl.insert(58);
//    avl.insert(133);
    avl.insert(12);
    avl.insert(14);
    avl.insert(3);
    avl.insert(7);
    avl.insert(50);
    avl.insert(21);
    avl.insert(5);
//    cout << avl.closest(5) << endl;
//    cout << avl.closest(22) << endl;
//    cout << avl.closest(13) << endl;
//    cout << avl.count_range(3,50);

    //avl.print_inorder(avl.Getroot());



    return 0;
}
