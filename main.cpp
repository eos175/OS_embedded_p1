#include <iostream>
#include <limits>

#include <cmath>

#include "tmp.h"
#include "kernel/include/trig8.h"


namespace std {

template<class T, size_t N>
constexpr size_t size(T (&)[N]) { return N; }

}


template <class T>
int rle_encode(void *dst1, const void *src1, size_t size)
{
    auto dst = static_cast<T *>(dst1);
    auto src = static_cast<const T *>(src1);

    int k = 0;
    for (size_t i = 0; i < size; i++) {
        T c = 1;
        while (i + 1 < size &&
               src[i] == src[i + 1] &&
               c < std::numeric_limits<T>::max())
        {
            c++;
            i++;
        }

        dst[k++] = c;
        dst[k++] = src[i];
    }
    return k;
}


template <class T>
int rle_decode(void *dst1, const void *src1, size_t size)
{
    auto dst = static_cast<T *>(dst1);
    auto src = static_cast<const T *>(src1);

    int k = 0;
    for (size_t i = 0; i < size; i += 2) {
        size_t count = src[i];
        for (size_t j = 0; j < count; j++) {
            dst[k] = src[i + 1];
            k++;
        }
    }
    return k;
}


template <class T>
void PrintArr(const void *arr1, size_t len)
{
    auto arr = (const T *)arr1;
    printf("%ld|[ ", len);

    for (size_t i = 0; i < len; i++)
    {
        printf("%d,", arr[i]);
    }

    printf("]\n");
}


int64_t abs(int64_t a)
{
    if (a < 0)
        return -a;
    return a;
}

static bool check_margin(int *arr, int size, int value, int eps)
{
    for (int i = 0; i < size; i++)
    {
        int tmp = arr[i];
        if ((abs(tmp - value) - 1 ) < eps)
        {
            return true;
        }
        
    }
    return false;  
}


int buf[1024 * 1024] = {};
int buf2[1024 * 1024] = {};


int main(int argc, char const *argv[])
{
    int tmp[] = {4,4,4,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1};

    auto size = rle_encode<int>(buf, tmp, std::size(tmp));

    PrintArr<int>(buf, size);

    //size = rle_decode<int>(buf2, buf, size);
    size = 45;

    printf("\n%d || %d | %.9f | %.9f | %.9f\n", size, sin16(size), cos(size), fast_cos(size), cos2<double>(size));

    for (size_t i = 0; i < 255; i+=1)
    {
        printf("sin8(%ld)=%d\n", i, sin8(i));
    }
    
    
    

    return 0;
}

