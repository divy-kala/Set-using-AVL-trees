
class avl_tree
{
    public:
        avl_tree() {}

        node * Getroot() { return root; }
        void Setroot(node * val) { root = val; }

    protected:

    private:
        node * root;
};
