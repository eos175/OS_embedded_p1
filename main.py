
"""
// formato 
(
    "name",
    "base64"
),
"""

imgs = [
    (
        "game_over",
        "data:image/png;base64,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"
    ),
    (
        "title", 
        "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIAAAABACAYAAADS1n9/AAAE6UlEQVR4Xu1b23EkMQi0k3AYTudivHQchpPw1XyoisM8BWikHfznXQkB3WokZL+/9c+jM/D+6Og7+LcmwMNJ0ARoAjw8A5uH//H55+f76++vjcp97g2nFcCbsRvGY7CzwL9CaQLcAKhnyQtsbjylDB7bTQBvthaPH+BfQEMiwN+jJGgFWAyqdTlp52MbERJMEyCzDlmTsss4uDOrfBr51UpAFIcQAWZqE3Q46nxV8jW7M35750ACSLcAr10c2zQBoCEPqJ6xGhDR72d38kzSZ+aM+KizQET2Yd7SCaCBgoPJCkRbl/t+BphVc2Zj8sxbToDLOVzf7iRBFpgWNZlZywPmzNgSAmiBUmUAH3aspJidB+XVulZkDiT+DFBVc8oIIF1VOAIMIDznBGmsRkQJFIlYFrsUYNhXOAbf9a/vvMScIUkZASCYOBiPAmjSqgGl3VS4+R67XGMG2+DyoJ34Z4C1ztmKADOPHtJu5NTB+zlOpkRgHIN03sHAa2S3guoZV0KAIa1Y4qgaihM0xlDlQJNVC1BY9iUF4CS4igA4b8eWAAkICgApUK3ealKtqQpnH9qFNvAulXa4Bii3xsoDY4oCeCTn9LFaXY/EJ5E5Ylea2wSoyuwhdpsAhwBV5WYToCqzh9htAhwCVJWbTYCqzB5itwlwCFBVbjYBkjOr9S2Slwub244Ad7RDw1kEBpoAwWw2AYIJdE7fSgG8nTCqLXvFX91Dtz5AObG4Zfh2BLA+Ao1sab34FVn1EneFT9Y1jiGA9Ggz3uOpp9iRCO6ZlkuU55GJe162gnDnuO0IAJMhvcJBBdBApsijPepIoGJ7O6jQLIm2IwBXAizPtrj+4z+4gEniQMSl5frdMpYj7iwwq+a9BAEsf5KllQAKZEmNqg+aTQDwf/HS1RBLNVUOqPkc4K8CrJVAWymA1WlNyldcBWd83XHO8QTYMakn+dQEOAmtAl+bAAVJjZpc+Z7QBIiiVTD/NgJQzZGnHah2eIyyEsA6TuLofwpguS5Jxqj2aVWfHNrNvrplJNabJ+pmo3Ur8ZyZZlSIABiEKIE8aloJUqXt0Vkcysq1qanmltSRlFrXbgXAE6THFvgdtSsrFSCy8yUF0eKIrDsIIL16whY2hcX4jALdW8JUBYCLwS6bBCznRObOotSHejyCOw37r70ecgnOIIAFWC1f2L+SEkCxDcoYTCpVx7TPPLIv2eIIQe0mKK/UIVeT5SgBqNqNyYt9tPrpzadLASwPKpiFlSVA2tEQeK6EYTnmyI4Jn0kAL2DZG+pXH4CTHW5XUMyMBFU1lzuwYv+9NbTKX8lupo/dCLoDwY3WLCdAJls3ytvLuFJOAFxnmxDruCNddYcXIgGk+7DnIIRP4p6569K170ocDtRNAZ5ptGvkNVYlAD5BS85Ip2p4Ysen6lMOkpkU4W5H1OfStRT7xPUGuE1nJsAAidrNVMOEuq5w46oaLpmAZdvy5oLaQFwjS7uuw1hUAsDBlBpwn3H3VaoxQ8mWRb6yQVlpj9vpkoRLG407W2lnLvMhEDdWoNxrzR7PDrccXFYCVbWW1FehNp2kABTI1jyaCWBJhBQUfvzwkMay9mljrABZ4oqoZTkBLAFQYyJBza556rxIrrYkgFa3TgWqyu8tCNCgVcFbazdVAWpdbesVGWgCVGT1IJv/AJrBcJuriK7tAAAAAElFTkSuQmCC"
    ),
    (
        "numbermap", 
        "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAABGCAYAAAAEo14nAAAArElEQVQ4T7WSWw6AMAgEJfEi3v9QXsSkBpNt2ELf0T9XbIcBuZ6UjuIRDe9TRHMU/Ba62xFYtIyiWISk1RTa83LlZjhuqXkRjlFe6gh/kWQKwxlV1dHgqkhlVx9SaT8OQyFzgwsXbLMjB18dHNbGSQaWfsibZrFICETHYfN2OtNuxgJS+bu+Z3grOu6oOc2xXbJVtN5WtEMiyX3z421aHBC0hSxaGkfqSp7fpRfJTix0xURWsAAAAABJRU5ErkJggg=="
    ),
]


## --------------------------------------------------

from PIL import Image
from base64 import b64decode
from io import BytesIO

from typing import Iterable, Iterator


def rle_encode(src: Iterable[int]) -> Iterator[int]:
    size = len(src)
    
    i = 0
    while i < size:
        c = 1
        while i + 1 < size and src[i] == src[i + 1]:
            c += 1
            i += 1
    
        yield c
        yield src[i]
        i += 1


def rle_decode(s: Iterable[int]) -> Iterator[int]:
    i = 0
    while i < len(s):
        for _ in range(s[i]):
            yield s[i+1]
        i += 2


def img2pixel_arr(img: Image) -> Iterator[int]:
    for r, g, b, a in img.getdata():
        rgba = r | g << 8 | b << 16 | a << 24
        yield rgba





template = """// generado por python...
#include <stdint.h>
#include <rlc.h>


#define STD_SIZE(arr)   sizeof(arr) / sizeof(arr[0])


{names}



{names_rlc}



static inline void files_init() 
{{
{file_init}
}}

// generado por python...
"""


names = []
names_rlc = []
file_init = []


for name, data in imgs:
    data = data[22:]

    img = Image.open(BytesIO(
                        b64decode(data)))

    pixels = list(img2pixel_arr(img))

    size = len(pixels)

    names.append(f"static uint32_t {name}_data[{size}];")
    names_rlc.append((
        
        f"static const uint32_t {name}_rlc[] = {{" + 
        ",".join([str(i) for i in rle_encode(pixels)]) +
        "};"
    ))
    file_init.append(
        f"\tRLE_Decode({name}_data, {name}_rlc, STD_SIZE({name}_rlc));"
    )


with open("files.h", "w") as f:
    f.write(
        template.format(
            names="\n\n".join(names),
            names_rlc="\n\n".join(names_rlc),
            file_init="\n".join(file_init),
        )
    )

