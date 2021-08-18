from PIL import Image
from base64 import b64decode
from io import BytesIO

from typing import Iterable, Iterator


def img2pixel_arr(img: Image) -> Iterator[int]:
    for r, g, b, a in img.getdata():
        rgba = r | g << 8 | b << 16 | a << 24
        yield rgba



numbermap = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAABGCAYAAAAEo14nAAAArElEQVQ4T7WSWw6AMAgEJfEi3v9QXsSkBpNt2ELf0T9XbIcBuZ6UjuIRDe9TRHMU/Ba62xFYtIyiWISk1RTa83LlZjhuqXkRjlFe6gh/kWQKwxlV1dHgqkhlVx9SaT8OQyFzgwsXbLMjB18dHNbGSQaWfsibZrFICETHYfN2OtNuxgJS+bu+Z3grOu6oOc2xXbJVtN5WtEMiyX3z421aHBC0hSxaGkfqSp7fpRfJTix0xURWsAAAAABJRU5ErkJggg=="


data = numbermap[22:]

img = Image.open(BytesIO(
                    b64decode(data)))

pixels = list(img2pixel_arr(img))



data = (
    "static const uint32_t data[] = {" + 
    ", ".join(["0x%08x" % i for i in pixels]) +
    "};"
)

print(data)


