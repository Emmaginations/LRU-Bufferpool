#include "BufferBlockADT.h"
#include "constants.h"

using namespace std;

class BufferBlock : public BufferBlockADT {
private:
    int blockID;
    char* block;
public:

    BufferBlock() {}

    BufferBlock(char* data, int sz = 4096)
    {
        block = getCharArray(sz);
        for (int i = 0; i < sz; i++)
        {
            block[i] = data[i];
        }
    }

    //read the block from pos to pos + sz-1 (or to the end of the block)
    void getData(int pos, int sz, char* data) {
        // loop through file? for loop read data into block?
        // overall position modulus blocksize not zero!!!
        int j = 0;

        for (int i = pos; i < (pos + sz); i++)
        {
            data[j] = block[i];
            j++;
        }
    }

    //setID
    void setID(int id) {
        blockID = id;
    }

    //getID
    int getID() const {
        return blockID;
    }

    //getBlocksize
    int getBlockSize() const {
        return BLOCKSIZE; // replace with global variable
    }

    //return the block
    char* getBlock() const {
        return block;
    }

    //set the block
    void setBlock(char* blk) {
        block = getCharArray(BLOCKSIZE);  // replace with getCharArray function, include
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            block[i] = blk[i];
        }
    }
};
