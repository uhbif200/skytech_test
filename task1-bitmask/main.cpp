#include <bitset>
#include <cassert>
#include <chrono>
#include <iostream>

typedef std::bitset<32> mask;

//Наивное решение 
bool checkValid(const mask& bitset)
{
    bool maskEnded = false;
    for(int i = 31; i >= 0; i--)
    {
        maskEnded |= !bitset[i];
        if(maskEnded && bitset[i])
            return false;
    }
    return true;
}

//Решение побыстрее
bool checkValidFast(const mask& bitset)
{
    size_t count = bitset.count();
    if(count == 0)
        return true;

    //Создадим "правильную маску" из того же количества "1" для сравнения с оригиналом 
    mask tmp((1 << 32 - count) - 1);
    tmp.flip();
    return !(bitset ^ tmp).count();
}

int main()
{

    {
        auto start = std::chrono::system_clock::now();
        for(int i = 0; i < 1000000; i++)
        {
            assert(checkValid(0b11110000000000000000000000000000) == true); 
            assert(checkValid(0b11111000000000000000000000000000) == true); 
            assert(checkValid(0b11111111111100000000000000000000) == true); 
            assert(checkValid(0b10000000000000000000000000000000) == true); 
            assert(checkValid(0b00000000000000000000000000000000) == true); 

            assert(checkValid(0b10110000000000000000000000001000) == false); 
            assert(checkValid(0b01111100000000000000001000000001) == false); 
            assert(checkValid(0b10000000000000000000000000000001) == false); 
        }
        auto end = std::chrono::system_clock::now();
        std::cout <<"check valid speed test: passed " <<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<"ms" <<std::endl;
    }

    {
        auto start = std::chrono::system_clock::now();
        for(int i = 0; i < 1000000; i++)
        {
            assert(checkValidFast(0b11110000000000000000000000000000) == true); 
            assert(checkValidFast(0b11111000000000000000000000000000) == true); 
            assert(checkValidFast(0b11111111111100000000000000000000) == true); 
            assert(checkValidFast(0b10000000000000000000000000000000) == true); 
            assert(checkValidFast(0b00000000000000000000000000000000) == true); 

            assert(checkValidFast(0b10110000000000000000000000001000) == false); 
            assert(checkValidFast(0b01111100000000000000001000000001) == false); 
            assert(checkValidFast(0b10000000000000000000000000000001) == false);
        }
        auto end = std::chrono::system_clock::now();
        std::cout <<"checkValidFast speed test: passed " <<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<"ms" <<std::endl;
    }
    return 0;
}