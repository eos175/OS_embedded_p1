#include <limits>
#include <stdint.h>


/*

TODO(eos175) archivo de demostracion, ignorar...

https://olegkutkov.me/2019/11/10/cpp-in-linux-kernel/

https://stackoverflow.com/questions/15981631/accessing-c-templates-from-c

*/


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

