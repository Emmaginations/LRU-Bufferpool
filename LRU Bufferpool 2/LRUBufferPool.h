#include "BufferPoolADT.h"
#include "BufferBlock.h"
#include "constants.h"
#include <fstream>

using namespace std;

class LRUBufferPool : public BufferPoolADT {
private:
	BufferBlock* blocks[POOL_SIZE];
	string flName;
public:
	//Constructor gets the filename of the file to be buffered,
   //opens the file, and instantiates poolSize buffer blocks by
   //reading the file and filling the blocks in order.  When the constructor
   //is done the buffer pool blocks should be full with the beginning
   //contents of the input file.
	LRUBufferPool() {}
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096)
	{
		fstream input;
		input.open(filename.c_str(), fstream::in | fstream::binary);
		//blocks = new BufferBlock[poolSize];
		for (int i = 0; i < poolSize; i++)
		{
			//char* data = new char[blockSize]; // get char array
			char* data = getCharArray(blockSize); // get char a
			input.seekg(i * blockSize); // use global variable
			input.read(data, blockSize);
			// blocks[i]->setBlock(data);
			blocks[i] = new BufferBlock(data);
			blocks[i]->setID(i);
		}

		flName = filename;
	}
	~LRUBufferPool() {}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {
		//rearrange pool: check what buffer block, if it is in pool, where

		int blockNum = (pos / BLOCKSIZE); // which block (ID)

		int blockPos = (pos % BLOCKSIZE); // where in block

		

		bool found = false;
		int foundIndex;

		int b = 0;

		while ((found == false) && (b < POOL_SIZE)) {
			if (blockNum == blocks[b]->getID()) {
				found = true;
				foundIndex = b; // where in buffer pool
			}
			b++;
		}

		if (found == true) {
			//move found to front, slide rest down
			// first put data of found block in space
			blocks[foundIndex]->getData(blockPos, sz, space);
			// now shuffle blocks
			// potentially check if block is at index 0, or do elsewhere

			BufferBlock* temp;

			temp = blocks[foundIndex];

			for (int i = foundIndex; i >= 0; i--)
			{
				blocks[i] = blocks[i - 1]; // should i make concessions for last block? not sure. also can i assign like this oops
			}

			blocks[0] = temp;
		}
		else
		{
			// overwrite data
			// read data, reopen file, go into at blockNum * 4096

			for (int i = POOL_SIZE - 1; i > 0; i--)
			{
					blocks[i] = blocks[i - 1];
			}

			fstream input;
			input.open(flName.c_str(), fstream::in | fstream::binary);

			char* data = getCharArray(BLOCKSIZE); // new char array function thing
			input.seekg(blockNum * BLOCKSIZE);
			input.read(data, BLOCKSIZE);
			//blocks[0]->setBlock(data);
			blocks[0] = new BufferBlock;
			blocks[0]->setBlock(data);
			blocks[0]->setID(blockNum);

			blocks[0]->getData(blockPos, sz, space);
		}
	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
		for (int i = 0; i < POOL_SIZE; i++)
		{
			cout << blocks[i]->getID() << endl;
		}
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() {
		return blocks[POOL_SIZE - 1]->getID();
	}
};