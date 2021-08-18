#include <iostream>
#include <limits>


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

int buf[1024 * 1024] = {};
int buf2[1024 * 1024] = {};


int main(int argc, char const *argv[])
{
    int tmp[] = {4,4,4,5,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1};

    auto size = rle_encode<int>(buf, tmp, std::size(tmp));

    PrintArr<int>(buf, size);

    size = rle_decode<int>(buf2, buf, size);

    printf("\n%d\n", size);
    return 0;
}

