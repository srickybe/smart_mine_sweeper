#ifndef MTL_LOADER_H
#define MTL_LOADER_H


namespace ngn {
    class MaterialManager;

    
    class MTLLoader {
    public:
        MTLLoader();
        void loadMTL(char const *, MaterialManager &)const;
    };

    //////////////////////////////////////////////////////////////////////////
}

#endif // MTL_LOADER_H
